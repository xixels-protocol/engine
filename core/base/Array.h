#pragma once

#include "Typedef.h"
#include <assert.h>

namespace Xixels
{

template< typename Type, typename Key = Type > class Array
{
protected:
	_long	mSize;
	_long	mLength;
	Type*	mElements;

public:
	class Iterator
	{
	private:
		Array< Type, Key >*	mArray;
		_long				mIndex;

	public:
		inline Iterator( Array< Type, Key >* ary, _long index )
			: mArray( ary ), mIndex( index ) { }

		inline operator _bool ( ) const
			{ return mArray->IsIndexValid( mIndex ); }

		inline const Type& operator * ( ) const
			{ return (*mArray)[ mIndex ]; }
		inline Type& operator * ( )
			{ return (*mArray)[ mIndex ]; }

		inline Iterator operator ++ ( )
			{ mIndex ++; return *this; }
		inline Iterator operator -- ( )
			{ mIndex --; return *this; }
		inline Iterator operator ++ ( _long )
			{ Iterator it = *this; mIndex ++; return it; }
		inline Iterator operator -- ( _long )
			{ Iterator it = *this; mIndex --; return it; }

		inline _long Index( ) const
			{ return mIndex; }
	};

	inline Array( )
		: mSize( 0 ), mLength( 0 ), mElements( _null ) { }

	Array( const Array< Type, Key >& ary )
	{
		mSize		= ary.mSize;
		mLength		= ary.mLength;
		mElements	= _null;

		if ( mSize > 0 )
		{
			mElements = new Type[ mSize ];

			// Copy elements into new memory, execute opertor = of Type class.
			for ( _long i = 0; i < mLength; i ++ )
				mElements[i] = ary.mElements[i];
		}
	}

	Array( const Array< Type, Key >&& ary )
	{
		mSize		= ary.mSize;
		mLength		= ary.mLength;
		mElements	= ary.mElements;
		ary.mSize	= 0;
		ary.mLength	= 0;
		ary.mElements	= _null;
	}

	Array< Type, Key >& operator = ( const Array< Type, Key >& ary )
	{
		if ( mSize < ary.mLength )
			Grow( ary.mLength - mSize );

		mLength = ary.mLength;

		// Copy elements into new memory, execute opertor = of Type class.
		for ( _long i = 0; i < mLength; i ++ )
			mElements[i] = ary.mElements[i];

		return *this;
	}

	inline ~Array( )
	{
		delete[] mElements;
	}

	inline operator Type* ( )
		{ return mElements; }
	inline operator const Type* ( ) const
		{ return mElements; }

	inline _bool IsIndexValid( _long index ) const
		{ return index < mLength && index >= 0; }

	inline const Type& operator [] ( _long index ) const
		{ assert( IsIndexValid( index ) ); return mElements[ index ]; }
	inline Type& operator [] ( _long index )
		{ assert( IsIndexValid( index ) ); return mElements[ index ]; }

	inline const Type& Head( ) const
		{ assert( mLength > 0 ); return mElements[0]; }
	inline Type& Head( )
		{ assert( mLength > 0 ); return mElements[0]; }

	inline const Type& Tail( ) const
		{ assert( mLength > 0 ); return mElements[ mLength - 1 ]; }
	inline Type& Tail( )
		{ assert( mLength > 0 ); return mElements[ mLength - 1 ]; }

	inline Iterator GetHeadIterator( ) const
		{ return Iterator( (Array< Type, Key >*) this, 0 ); }
	inline Iterator GetTailIterator( ) const
		{ return Iterator( (Array< Type, Key >*) this, mLength - 1 ); }
	inline Iterator GetIterator( _long index ) const
		{ return Iterator( (Array< Type, Key >*) this, index ); }

	inline _long Size( ) const
		{ return mSize; }
	inline _long Length( ) const
		{ return mLength; }
	inline _long SizeOfBytes( ) const
		{ return mLength * sizeof( Type ); }

	// Copy elements from buffer into array.
	_void CopyFrom( const Type* buffer, _long length )
	{
		if ( length == 0 )
			return;

		_long newlength = mLength + length;
		if ( newlength > mSize ) 
			Grow( newlength - mSize );

		for ( _long i = 0; i < length; i ++ )
			mElements[ mLength + i ] = buffer[i];

		mLength = newlength;
	}

	// Copy elements from array into buffer.
	_void CopyTo( Type* buffer, _long length )
	{
		length = Math::Min( length, mLength );

		for ( _long i = 0; i < length; i ++ )
			buffer[i] = mElements[i];
	}

	// Search an element by the key in the array.
	_long IndexOf( const Key& key ) const
	{
		for ( _long i = 0; i < mLength; i ++ )
		{
			if ( (const Key&) mElements[i] == key )
				return i;
		}

		return -1;
	}

	// Add an element to the end of the array.
	_long Add( const Type& element )
	{
		// Grow the array when necessary.
		if ( mLength == mSize )
			Grow( mSize == 0 ? 16 : mSize );

		mElements[ mLength ++ ] = element;

		return mLength - 1;
	}

	// Insert an element into the array, the position is specified by an index.
	_void Insert( const Type& element, _long index )
	{
		if ( index == mLength )
		{
			Add( element );
			return;
		}

		if ( !IsIndexValid( index ) )
			return;

		// Grow the array when necessary.
		if ( mLength == mSize )
			Grow( mSize == 0 ? 16 : mSize );

		// Move elements after the index backward, make a place for the new element.
		for ( _long i = 0; i < mLength - index; i++ )
			mElements[ mLength - i ] = mElements[ mLength - i - 1 ];

		// Assign the element.
		mElements[ index ] = element;

		mLength ++;
	}

	// Remove the first element match the key from the array.
	_bool Remove( const Key& key )
	{
		_long index = IndexOf( key );
		if ( index == -1 )
			return _false;

		RemoveAt( index );
		return _true;
	}

	// Remove all elements match the key from the array.
	_void RemoveAll( const Key& key )
	{
		_long index = IndexOf( key );
		while ( index != -1 )
		{
			RemoveAt( index );
			index = IndexOf( key );
		}
	}

	// Remove an element from the array, the element is specified by an index.
	_bool RemoveAt( _long index )
	{
		if ( !IsIndexValid( index ) )
			return _false;

		// Move elements after the index forward, replace the deleted one.
		for ( _long i = index; i < mLength - 1; i ++ )
			mElements[i] = mElements[ i + 1 ];

		mLength --;
		return _true;
	}

	// Remove elements from the array, the elements are specified by two indexes.
	_bool RemoveFromTo( _long from, _long to )
	{
		if ( !IsIndexValid( from ) || !IsIndexValid( to ) )
			return _false;

		if ( from >= to )
			return _false;

		_long dis = to - from;
		for ( _long i = to; i < mLength; i ++ )
			mElements[ i - dis ] = mElements[i];

		mLength -= dis;
		return _true;
	}

	// Allocated Size > mLength.
	_void ReSize( _long size )
	{
		if ( size < mLength || size == mSize )
			return;

		mSize = size;
		Type* newelements = new Type[ mSize ];

		// Copy elements into new memory, execute operator = of Type class.
		for ( _long i = 0; i < mLength; i ++ )
			newelements[ i ] = mElements[ i ];

		delete[ ] mElements;
		mElements = newelements;
	}

	// Sort array in ascending.
	inline _void SortAscending( )
		{ QuickSort< Type, Key >::SortAscending( mElements, mLength ); }

	// Sort array in descending.
	inline _void SortDescending( )
		{ QuickSort< Type, Key >::SortDescending( mElements, mLength ); }

	// Grow size of the array by grow.
	_void Grow( _long grow )
	{
		if ( grow == 0 )
			return;

		mSize += grow;

		Type* newelements = new Type[ mSize ];

		// Copy elements into new memory, execute operator = of Type class.
		for ( _long i = 0; i < mLength; i ++ )
			newelements[i] = mElements[i];

		delete[] mElements;
		mElements = newelements;
	}

	// Reduce size of array.
	inline _void Reduce( _long length )
		{ mLength -= Math::Clamp( length, (_long) 0, mLength ); }

	// Clear array.
	_void Clear( _bool freemem = _false )
	{
		mLength = 0;

		if ( freemem )
		{
			mSize = 0;

			delete[] mElements;
			mElements = _null;
		}
	}

	_void Empty( _long size = 0 )
	{
		Clear( _true );

		if ( size > 0 )
			Grow( size );
	}

	_long AddZeroed( _long size = 1 )
	{
		if ( size > 0 )
			Grow( size );

		return mLength;
	}

	_long GetAllocatedSize( ) const
	{
		return mSize * sizeof( Type );
	}
};

};