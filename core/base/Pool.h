#pragma once

namespace Xixels
{

template< typename Type, typename Key = Type > class Pool : public Link< Type, Key >
{
public:
	typedef typename Link< Type, Key >::Node		Node;
	typedef typename Link< Type, Key >::Iterator	Iterator;

private:
	// The node in the pool stores an element, and linked as a chain.
	class PoolNode : public Node
	{
	public:
		_dword	mIndex;

	public:
		inline PoolNode( )
			: mIndex( -1 ) { }
	};

	_dword		mSize;
	_dword		mNext;
	PoolNode*	mNodes;

public:
	inline Pool( _dword size )
		: mSize( size ), mNext( 0 ), mNodes( _null ) { assert( size > 0 ); }

	Pool( const Pool< Type, Key >& pool )
	{
		mSize	= pool.mSize;
		mNext	= pool.mNext;
		mNodes	= _null;

		for ( Node* node = pool.mHead; node != _null; node = node->mNext )
			Insert( node->mElement, ( (PoolNode*) node )->mIndex );
	}

	Pool< Type, Key >& operator = ( const Pool< Type, Key >& pool )
	{
		Clear( );

		for ( Node* node = pool.mHead; node != _null; node = node->mNext )
			Insert( node->mElement, ( (PoolNode*) node )->mIndex );

		return *this;
	}

	inline ~Pool( )
		{ delete[] mNodes; }

	inline _bool IsIndexValid( _dword index ) const
		{ return index < mSize && mNodes != _null && mNodes[ index ].mIndex != -1; }

	inline const Type& operator [] ( _long index ) const
		{ assert( IsIndexValid( index ) ); return mNodes[ index ].mElement; }
	inline Type& operator [] ( _long index )
		{ assert( IsIndexValid( index ) ); return mNodes[ index ].mElement; }

	inline _dword Size( ) const
		{ return mSize; }

	// Get an iterator by pool index.
	Iterator IndexOf( _dword index ) const
	{
		if ( index >= mSize || mNodes == _null )
			return Iterator( _null );

		if ( mNodes[ index ].mIndex == -1 )
			return Iterator( _null );

		return Iterator( mNodes + index );
	}

	// Find an available index for the pool.
	_dword NextIndex( ) const
	{
		if ( Link< Type, Key >::mLength == mSize )
			return -1;

		_dword index = mNext;

		// Find a empty node to place the new element.
		while ( mNodes[ index ].mIndex != -1 )
			index = ( index + 1 ) % mSize;

		return index;
	}

	// Create a node to store element in the pool.
	_dword Create( const Type& element )
	{
		if ( Link< Type, Key >::mLength == mSize )
			return -1;

		if ( mNodes == _null )
			mNodes = new PoolNode[ mSize ];

		// Find a empty node to place the new element.
		while ( mNodes[ mNext ].mIndex != -1 )
			mNext = ( mNext + 1 ) % mSize;

		Insert( element, mNext );

		_dword index = mNext;

		// Update next index.
		mNext = ( mNext + 1 ) % mSize;

		return index;
	}

	// Insert an element into the pool at specified index.
	_void Insert( const Type& element, _dword index )
	{
		if ( mNodes == _null )
			mNodes = new PoolNode[ mSize ];

		assert( mNodes[ index ].mIndex == -1 );

		mNodes[ index ].mElement	= element;
		mNodes[ index ].mIndex		= index;

		Link< Type, Key >::InsertTail( &( mNodes[ index ] ) );
	}

	// Remove the first element match the key from the pool.
	inline _bool Remove( const Key& key )
		{ return RemoveAt( IndexOf( key ) ); }

	// Remove all elements match the key from the pool.
	_void RemoveAll( const Key& key )
	{
		Iterator it = IndexOf( key );
		while ( it )
		{
			RemoveAt( it );
			it = IndexOf( key );
		}
	}

	// Remove an element from the pool, the element is specified by an index.
	_bool RemoveAt( _dword index )
	{
		if ( !IsIndexValid( index ) )
			return _false;

		mNodes[ index ].mIndex = -1;
		Link< Type, Key >::RemoveNode( &( mNodes[ index ] ) );
		return _true;
	}

	// Remove an element from the pool, the element is specified by an iterator.
	_bool RemoveAt( const Iterator& it )
	{
		if ( !it )
			return _false;

		RemoveAt( ( (PoolNode*) it.GetNode( ) )->mIndex );
		return _true;
	}

	// Resize the pool by create new memory, and clear all the old element.
	_void Resize( _dword newsize )
	{
		delete[] mNodes;

		mSize	= newsize;
		mNext	= 0;
		mNodes	= _null;

		Link< Type, Key >::ClearNode( );
	}

	// Clear pool and release memory used by nodes.
	_void Clear( )
	{
		mNext = 0;

		delete[] mNodes;
		mNodes = _null;

		Link< Type, Key >::ClearNode( );
	}
};

};