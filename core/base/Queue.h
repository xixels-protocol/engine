#pragma once

namespace Xixels
{

template< typename Type, typename Key = Type > class Queue
{
private:
	_dword	mSize;
	_dword	mLength;
	_dword	mFront;
	_dword	mRear;
	Type*	mElements;

public:
	class Iterator
	{
	private:
		Queue< Type, Key >*	mQueue;
		_dword				mIndex;

	public:
		inline Iterator( Queue< Type, Key >* queue, _dword index )
			: mQueue( queue ), mIndex( index ) { }

		inline operator _bool ( ) const
			{ return mQueue->IsIndexValid( mIndex ); }

		inline const Type& operator * ( ) const
			{ return (*mQueue)[ mIndex ]; }
		inline Type& operator * ( )
			{ return (*mQueue)[ mIndex ]; }

		inline Iterator operator ++ ( )
			{ mIndex = ( mIndex + 1 ) % ( mQueue->mSize + 1 ); return *this; }
		inline Iterator operator -- ( )
			{ mIndex = ( mQueue->mSize + mIndex ) % ( mQueue->mSize + 1 ); return *this; }
		inline Iterator operator ++ ( _long )
			{ Iterator it = *this; mIndex = ( mIndex + 1 ) % ( mQueue->mSize + 1 ); return it; }
		inline Iterator operator -- ( _long )
			{ Iterator it = *this; mIndex = ( mQueue->mSize + mIndex ) % ( mQueue->mSize + 1 ); return it; }

		inline _dword Index( ) const
			{ return mIndex; }
	};

public:
	inline Queue( )
		: mSize( 0 ), mLength( 0 ), mFront( 0 ), mRear( 0 ), mElements( _null ) { }

	Queue( const Queue< Type, Key >& queue )
	{
		mSize		= queue.mSize;
		mLength		= queue.mLength;
		mFront		= 0;
		mRear		= queue.mLength;
		mElements	= _null;

		if ( mSize > 0 )
		{
			mElements = new Type[ mSize + 1 ];

			for ( _dword i = 0; i < mLength; i ++ )
				mElements[i] = queue.mElements[ ( queue.mFront + i ) % ( mSize + 1 ) ];
		}
	}

	Queue< Type, Key >& operator = ( const Queue< Type, Key >& queue )
	{
		if ( mSize < queue.mLength )
			Grow( queue.mLength - mSize );

		mLength		= queue.mLength;
		mFront		= 0;
		mRear		= queue.mLength;

		if ( mSize > 0 )
		{
			mElements = new Type[ mSize + 1 ];

			for ( _dword i = 0; i < mLength; i ++ )
				mElements[i] = queue.mElements[ ( queue.mFront + i ) % ( mSize + 1 ) ];
		}

		return *this;
	}

	inline ~Queue( )
		{ delete[] mElements; }

	inline _bool IsIndexValid( _dword index ) const
	{
		if ( mFront <= mRear )
			return index >= mFront && index < mRear;
		else
			return ( index < mRear ) || ( index >= mFront && index <= mSize );
	}

	inline const Type& operator [] ( _long index ) const
		{ assert( IsIndexValid( index ) ); return mElements[ index ]; }
	inline Type& operator [] ( _long index )
		{ assert( IsIndexValid( index ) ); return mElements[ index ]; }

	inline const Type& Front( ) const
		{ assert( IsIndexValid( mFront ) ); return mElements[ mFront ]; }
	inline Type& Front( )
		{ assert( IsIndexValid( mFront ) ); return mElements[ mFront ]; }

	inline const Type& Rear( ) const
		{ _dword index = ( mRear + mSize ) % ( mSize + 1 ); assert( IsIndexValid( index ) ); return mElements[ index ]; }
	inline Type& Rear( )
		{ _dword index = ( mRear + mSize ) % ( mSize + 1 ); assert( IsIndexValid( index ) ); return mElements[ index ]; }

	inline Iterator GetHeadIterator( ) const
		{ return Iterator( (Queue< Type, Key >*) this, mFront ); }
	inline Iterator GetTailIterator( ) const
		{ return Iterator( (Queue< Type, Key >*) this, ( mRear + mSize ) % ( mSize + 1 ) ); }
	inline Iterator GetIterator( _dword index ) const
		{ return Iterator( (Queue< Type, Key >*) this, index ); }

	inline _dword Size( ) const
		{ return mSize; }
	inline _dword Length( ) const
		{ return mLength; }
	inline _dword SizeOfBytes( ) const
		{ return mLength * sizeof( Type ); }

	// Search an element by the key in the queue.
	_dword IndexOf( const Key& key ) const
	{
		for ( Iterator it = GetHeadIterator( ); it; it ++ )
		{
			if ( ( (const Key&) (const Type&) *it ) == key )
				return it.Index( );
		}

		return -1;
	}

	// Add an element at rear of the queue.
	_void Add( const Type& element )
	{
		// Grow the queue when necessary.
		if ( mLength == mSize )
			Grow( mSize );

		mElements[ mRear ] = element;

		mRear = ( mRear + 1 ) % ( mSize + 1 );
		mLength ++;
	}

	// Remove an element from front of the queue.
	_bool Remove( )
	{
		if ( mLength == 0 )
			return _false;

		mFront = ( mFront + 1 ) % ( mSize + 1 );
		mLength --;
		return _true;
	}

	// Remove the first element match the key from the queue.
	_bool Remove( const Key& key )
	{
		_dword index = IndexOf( key );
		if ( index == -1 )
			return _false;

		RemoveAt( index );
		return _true;
	}

	// Remove all elements match the key from the queue.
	_void RemoveAll( const Key& key )
	{
		_dword index = IndexOf( key );
		while ( index != -1 )
		{
			RemoveAt( index );
			index = IndexOf( key );
		}
	}

	// Remove an element from the queue, the element is specified by an index.
	_bool RemoveAt( _dword index )
	{
		if ( !IsIndexValid( index ) )
			return _false;

		Iterator it( this, index );

		_dword index1 = 0, index2 = 0;

		do
		{
			index1 = it.Index( );
			it ++;
			index2 = it.Index( );

			// Move element forward.
			mElements[ index1 ] = mElements[ index2 ];
		}
		while ( it );

		mRear = index1;
		mLength --;

		return _true;
	}

	// Grow size of the queue by grow.
	_void Grow( _dword grow )
	{
		if ( grow == 0 )
			grow = 16;

		_dword size = mSize;
		mSize += grow;

		Type* newelements = new Type[ mSize + 1 ];

		// Copy elements into new memory, execute opertor = of Type class.
		for ( _dword i = 0; i < mLength; i ++ )
			newelements[i] = mElements[ ( mFront + i ) % ( size + 1 ) ];

		delete[] mElements;
		mElements = newelements;
		mFront = 0;
		mRear  = mLength;
	}

	// Clear queue.
	_void Clear( _bool freemem = _false )
	{
		mLength = mFront = mRear = 0;

		if ( freemem )
		{
			mSize = 0;

			delete[] mElements;
			mElements = _null;
		}
	}
};

};