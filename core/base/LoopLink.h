#pragma once

namespace Xixels
{

template< typename Type, typename Key = Type > class LoopLink
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

		inline bool operator == ( const Iterator& it ) const
			{ return mNode == it.mNode; }
		inline bool operator != ( const Iterator& it ) const
			{ return mNode != it.mNode; }

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
	_dword	mLength;

public:
	inline LoopLink( )
		: mHead( _null ), mLength( 0 ) { }

	// Insert a node into the link at head.
	inline _void InsertHead( Node* node )
		{ InsertBefore( node, Iterator( mHead ) ); mHead = node; }

	// Insert a node into the link at tail.
	inline _void InsertTail( Node* node )
		{ InsertBefore( node, Iterator( mHead ) ); }

	inline const Type& Head( ) const
		{ assert( mHead != _null ); return mHead->mElement; }
	inline Type& Head( )
		{ assert( mHead != _null ); return mHead->mElement; }

	inline Node* GetHeadNode( ) const
		{ return mHead; }
	inline Node* GetPrevNode( Node* node ) const
		{ return node != _null ? node->mPrev : _null; }
	inline Node* GetNextNode( Node* node ) const
		{ return node != _null ? node->mNext : _null; }

	inline Iterator GetHeadIterator( ) const
		{ return Iterator( mHead ); }
	inline Iterator GetIterator( Node* node ) const
		{ return Iterator( node ); }

	inline _dword Length( ) const
		{ return mLength; }

	// Search an element by the key in the link.
	Iterator IndexOf( const Key& key ) const
	{
		Node* node = mHead;
		for ( _dword i = 0; i < mLength; i ++ )
		{
			if ( (const Key&) node->mElement == key )
				return Iterator( node );

			node = node->mNext;
		}

		return Iterator( _null );
	}

	// Insert a node into the link before the position specified by an iterator.
	_void InsertBefore( Node* node, const Iterator& it )
	{
		assert( node != _null );

		if ( it )
		{
			Node* curr = it.GetNode( );
			node->mPrev = it.GetPrev( );
			node->mNext = curr;

			// Relink the previous one and next one both to this node.
			node->mNext->mPrev = node;
			if ( node->mPrev != _null )
				node->mPrev->mNext = node;
		}
		else
		{
			node->mNext = node->mPrev = node;
			mHead = node;
		}

		mLength ++;
	}

	// Insert a node into the link after the position specified by an iterator.
	_void InsertAfter( Node* node, const Iterator& it )
	{
		assert( node != _null );

		if ( it )
		{
			Node* curr = it.GetNode( );
			node->mNext = it.GetNext( );
			node->mPrev = curr;

			// Relink the previous one and next one both to this node.
			node->mPrev->mNext = node;
			if ( node->mNext != _null )
				node->mNext->mPrev = node;
		}
		else
		{
			node->mNext = node->mPrev = node;
			mHead = node;
		}

		mLength ++;
	}

	_void MoveHead( const Iterator& it )
	{
		assert( it );

		mHead = it.GetNode( );
	}

	// Remove a node from the link.
	_void RemoveNode( Node* node )
	{
		assert( node != _null );

		if ( mLength == 1 )
		{
			mHead = _null;
			mLength = 0;
			return;
		}

		// Relink the previous one to next one of this node.
		if ( node->mPrev != _null )
			node->mPrev->mNext = node->mNext;
		if ( node->mNext != _null )
			node->mNext->mPrev = node->mPrev;

		// Adjust head pointer.
		if ( node == mHead )
			mHead = node->mNext;

		// Remove the link from the node.
		node->mPrev = _null;
		node->mNext = _null;

		// Decrease the element number.
		mLength --;
	}
};

};