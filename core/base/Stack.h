#pragma once

namespace Xixels
{

template< typename Type, typename Key = Type > class Stack
{
private:
	_dword	mSize;
	_dword	mLength;
	Type*	mElements;

public:
	class Iterator
	{
	private:
		Stack< Type, Key >*	mStack;
		_dword				mIndex;

	public:
		inline Iterator( Stack< Type, Key >* stack, _dword index )
			: mStack( stack ), mIndex( index ) { }

		inline operator _bool ( ) const
			{ return mStack->IsIndexValid( mIndex ); }

		inline const Type& operator * ( ) const
			{ return (*mStack)[ mIndex ]; }
		inline Type& operator * ( )
			{ return (*mStack)[ mIndex ]; }

		inline Iterator operator ++ ( )
			{ mIndex ++; return *this; }
		inline Iterator operator -- ( )
			{ mIndex --; return *this; }
		inline Iterator operator ++ ( _long )
			{ Iterator it = *this; mIndex ++; return it; }
		inline Iterator operator -- ( _long )
			{ Iterator it = *this; mIndex --; return it; }

		inline _dword Index( ) const
			{ return mIndex; }
	};

	inline Stack( )
		: mSize( 0 ), mLength( 0 ), mElements( _null ) { }

	Stack( const Stack< Type, Key >& stack )
	{
		mSize		= stack.mSize;
		mLength		= stack.mLength;
		mElements	= _null;

		if ( mSize > 0 )
		{
			mElements = new Type[ mSize ];

			// Copy elements into new memory, execute opertor = of Type class.
			for ( _dword i = 0; i < mLength; i ++ )
				mElements[i] = stack.mElements[i];
		}
	}

	Stack< Type, Key >& operator = ( const Stack< Type, Key >& stack )
	{
		if ( mSize < stack.mLength )
			Grow( stack.mLength - mSize );

		mLength = stack.mLength;

		// Copy elements into new memory, execute opertor = of Type class.
		for ( _dword i = 0; i < mLength; i ++ )
			mElements[i] = stack.mElements[i];

		return *this;
	}

	inline ~Stack( )
		{ delete[] mElements; }

	inline _bool IsIndexValid( _dword index ) const
		{ return index < mLength; }

	inline const Type& operator [] ( _long index ) const
		{ assert( IsIndexValid( index ) ); return mElements[ index ]; }
	inline Type& operator [] ( _long index )
		{ assert( IsIndexValid( index ) ); return mElements[ index ]; }

	inline const Type& Bottom( ) const
		{ assert( mLength > 0 ); return mElements[0]; }
	inline Type& Bottom( )
		{ assert( mLength > 0 ); return mElements[0]; }

	inline const Type& Top( ) const
		{ assert( mLength > 0 ); return mElements[ mLength - 1 ]; }
	inline Type& Top( )
		{ assert( mLength > 0 ); return mElements[ mLength - 1 ]; }

	inline Iterator GetHeadIterator( ) const
		{ return Iterator( (Stack< Type, Key >*) this, 0 ); }
	inline Iterator GetTailIterator( ) const
		{ return Iterator( (Stack< Type, Key >*) this, mLength - 1 ); }
	inline Iterator GetIterator( _dword index ) const
		{ return Iterator( (Stack< Type, Key >*) this, index ); }

	inline _dword Size( ) const
		{ return mSize; }
	inline _dword Length( ) const
		{ return mLength; }

	// Search an element by the key in the stack.
	_dword IndexOf( const Key& key ) const
	{
		for ( _dword i = 0; i < mLength; i ++ )
		{
			if ( (const Key&) mElements[i] == key )
				return i;
		}

		return -1;
	}

	_dword IndexFromEnd( const Key& key ) const
	{
		for ( _long i = mLength - 1; i > 0; i -- )
		{
			if ( (const Key&) mElements[i] == key )
				return i;
		}

		return -1;
	}

	// Push an element into stack.
	_void Push( const Type& element )
	{
		// Grow the stack when necessary.
		if ( mLength == mSize )
			Grow( mSize );

		mElements[ mLength ++ ] = element;
	}

	// Pop an element from stack top.
	_void Pop( )
	{
		if ( mLength > 0 )
			mLength --;
	}

	// Remove the first element match the key from the stack.
	_bool Remove( const Key& key )
	{
		_dword index = IndexOf( key );
		if ( index == -1 )
			return _false;

		RemoveAt( index );
		return _true;
	}

	// Remove all elements match the key from the stack.
	_void RemoveAll( const Key& key )
	{
		_dword index = IndexOf( key );
		while ( index != -1 )
		{
			RemoveAt( index );
			index = IndexOf( key );
		}
	}

	// Remove an element from the stack, the element is specified by an index.
	_bool RemoveAt( _dword index )
	{
		if ( !IsIndexValid( index ) )
			return _false;

		// Move elements after the index forward, replace the deleted one.
		for ( _dword i = index; i < mLength - 1; i ++ )
			mElements[i] = mElements[ i + 1 ];

		mLength --;
		return _true;
	}

	// Grow size of the stack by grow.
	_void Grow( _dword grow )
	{
		if ( grow == 0 )
			grow = 16;

		mSize += grow;

		Type* newelements = new Type[ mSize ];

		// Copy elements into new memory, execute opertor = of Type class.
		for ( _dword i = 0; i < mLength; i ++ )
			newelements[i] = mElements[i];

		delete[] mElements;
		mElements = newelements;
	}

	// Reduce size of stack.
	inline _void Reduce( _dword length )
		{ mLength -= Math::Clamp( length, (_dword) 0, mLength ); }

	// Clear stack.
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
};

};