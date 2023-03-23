#pragma once

namespace Xixels
{

template< typename Type, typename Key = Type > class Link
{
public:
	class Node
	{
	public:
		Type	mElement;
		Node*	mPrev;
		Node*	mNext;

		inline Node( )
			: mPrev( _null ), mNext( _null ) { }
		inline Node( const Type& element )
			: mElement( element ), mPrev( _null ), mNext( _null ) { }

		inline operator const Type& ( ) const
			{ return mElement; }
		inline operator Type& ( )
			{ return mElement; }
	};

	class Iterator
	{
	private:
		Node*	mNode;
		Node*	mPrev;
		Node*	mNext;

	public:
		inline Iterator( )
			: mNode( _null ), mPrev( _null ), mNext( _null ) { }
		inline Iterator( Node* node ) : mNode( node ), mPrev( _null ), mNext( _null )
			{ if ( mNode != _null ) { mPrev = mNode->mPrev; mNext = mNode->mNext; } }

		inline operator _bool ( ) const
			{ return mNode != _null; }

		inline const Type& operator * ( ) const
			{ return mNode->mElement; }
		inline Type& operator * ( )
			{ return mNode->mElement; }

		inline Iterator operator ++ ( )
			{ mPrev = mNode; mNode = mNext; mNext = mNode != _null ? mNode->mNext : _null; return *this; }
		inline Iterator operator -- ( )
			{ mNext = mNode; mNode = mPrev; mPrev = mNode != _null ? mNode->mPrev : _null; return *this; }
		inline Iterator operator ++ ( _long )
			{ Iterator it = *this; mPrev = mNode; mNode = mNext; mNext = mNode != _null ? mNode->mNext : _null; return it; }
		inline Iterator operator -- ( _long )
			{ Iterator it = *this; mNext = mNode; mNode = mPrev; mPrev = mNode != _null ? mNode->mPrev : _null; return it; }

		inline Node* GetNode( ) const
			{ return mNode; }
		inline Node* GetPrev( ) const
			{ return mPrev; }
		inline Node* GetNext( ) const
			{ return mNext; }
		inline Type* GetElement( ) const
			{ return mNode == _null ? _null : &( mNode->mElement ); }
	};

protected:
	Node*	mHead;
	Node*	mTail;
	_dword	mLength;

private:
	// TODO.
	// Link( const Link< Type, Key >& );
	// Link< Type, Key >& operator = ( const Link< Type, Key >& );

public:
	inline Link( )
		: mHead( _null ), mTail( _null ), mLength( 0 ) { }

	// Insert a node into the link at head.
	inline _void InsertHead( Node* node )
		{ InsertBefore( node, Iterator( mHead ) ); }

	// Insert a node into the link at tail.
	inline _void InsertTail( Node* node )
		{ InsertAfter( node, Iterator( mTail ) ); }

	inline const Type& Head( ) const
		{ assert( mHead != _null ); return mHead->mElement; }
	inline Type& Head( )
		{ assert( mHead != _null ); return mHead->mElement; }

	inline const Type& Tail( ) const
		{ assert( mTail != _null ); return mTail->mElement; }
	inline Type& Tail( )
		{ assert( mTail != _null ); return mTail->mElement; }

	inline Node* GetHeadNode( ) const
		{ return mHead; }
	inline Node* GetTailNode( ) const
		{ return mTail; }
	inline Node* GetPrevNode( Node* node ) const
		{ return node != _null ? node->mPrev : _null; }
	inline Node* GetNextNode( Node* node ) const
		{ return node != _null ? node->mNext : _null; }

	inline Iterator GetHeadIterator( ) const
		{ return Iterator( mHead ); }
	inline Iterator GetTailIterator( ) const
		{ return Iterator( mTail ); }
	inline Iterator GetIterator( Node* node ) const
		{ return Iterator( node ); }

	inline _dword Length( ) const
		{ return mLength; }

	// Search an element by the key in the link.
	Iterator IndexOf( const Key& key ) const
	{
		for ( Node* node = mHead; node != _null; node = node->mNext )
		{
			if ( (const Key&) node->mElement == key )
				return Iterator( node );
		}

		return Iterator( _null );
	}

	// Insert a node into the link before the position specified by an iterator.
	_void InsertBefore( Node* node, const Iterator& it )
	{
		assert( node != _null );

		if ( it )
		{
			node->mPrev = it.GetPrev( );
			node->mNext = it.GetNode( );

			// Relink the previous one and next one both to this node.
			if ( node->mPrev != _null )
				node->mPrev->mNext = node;
			if ( node->mNext != _null )
				node->mNext->mPrev = node;

			// Adjuset head and tail pointer.
			if ( node->mPrev == _null )
				mHead = node;
			if ( node->mNext == _null )
				mTail = node;
		}
		else
		{
			mHead = mTail = node;
		}

		mLength ++;
	}

	// Insert a node into the link after the position specified by an iterator.
	_void InsertAfter( Node* node, const Iterator& it )
	{
		assert( node != _null );

		if ( it )
		{
			node->mPrev = it.GetNode( );
			node->mNext = it.GetNext( );

			// Relink the previous one and next one both to this node.
			if ( node->mPrev != _null )
				node->mPrev->mNext = node;
			if ( node->mNext != _null )
				node->mNext->mPrev = node;

			// Adjuset head and tail pointer.
			if ( node->mPrev == _null )
				mHead = node;
			if ( node->mNext == _null )
				mTail = node;
		}
		else
		{
			mHead = mTail = node;
		}

		mLength ++;
	}

	// Remove a node from the link.
	_void RemoveNode( Node* node )
	{
		assert( node != _null );

		// Relink the previous one to next one of this node.
		if ( node->mPrev != _null )
			node->mPrev->mNext = node->mNext;
		if ( node->mNext != _null )
			node->mNext->mPrev = node->mPrev;

		// Adjuset head and tail pointer.
		if ( mHead == node )
			mHead = node->mNext;
		if ( mTail == node )
			mTail = node->mPrev;

		// Remove the link from the node.
		node->mPrev = _null;
		node->mNext = _null;

		// Decrease the element number.
		mLength --;
	}

	// Clear the link, just clean the head and tail pointer, derived classes must release memory used by nodes.
	inline _void ClearNode( )
		{ mHead = mTail = _null; mLength = 0; }
};

};