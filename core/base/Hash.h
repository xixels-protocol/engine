#pragma once

namespace Xixels
{

template< typename Type, typename Key = Type > class Hash : public Link< Type, Key >
{
public:
	typedef typename Link< Type, Key >::Node		Node;
	typedef typename Link< Type, Key >::Iterator	Iterator;

private:
	class HashNode : public Node
	{
	public:
		HashNode*	mBucketPrev;
		HashNode*	mBucketNext;
		_dword		mHashCode;

	public:
		inline HashNode( )
			: mBucketPrev( _null ), mBucketNext( _null ), mHashCode( -1 ) { }
	};

	_dword		mDivisor;
	HashNode**	mNodes;

public:
	inline Hash( _dword divisor )
		: mDivisor( divisor ), mNodes( _null ) { assert( divisor > 0 ); }

	Hash( const Hash< Type, Key >& hash )
	{
		mDivisor = hash.mDivisor;
		mNodes	 = _null;

		for ( Node* node = hash.mHead; node != _null; node = node->mNext )
			Insert( node->mElement );
	}

	Hash< Type, Key >& operator = ( const Hash< Type, Key >& hash )
	{
		Clear( );

		mDivisor = hash.mDivisor;

		for ( Node* node = hash.mHead; node != _null; node = node->mNext )
			Insert( node->mElement );

		return *this;
	}

	inline ~Hash( )
		{ Clear( ); }

	inline const Type& operator [] ( const Key& key ) const
		{ Iterator it = IndexOf( key ); assert( it ); return *it; }
	inline Type& operator [] ( const Key& key )
		{ Iterator it = IndexOf( key ); assert( it ); return *it; }

	// Get an iterator by the key of an element.
	Iterator IndexOf( const Key& key ) const
	{
		if ( mNodes == _null )
			return Iterator( _null );

		// Calculate hash code from key.
		_dword hashcode = (_dword) (_ptr) key;
		_dword bucketid = hashcode % mDivisor;

		if ( mNodes[ bucketid ] == _null )
			return Iterator( _null );

		HashNode* node = mNodes[ bucketid ];

		// Find the node by hash code, nodes are sort ascending.
		while ( node != _null && node->mHashCode < hashcode )
			node = node->mBucketNext;

		// Can not find node.
		if ( node == _null || node->mHashCode != hashcode )
			return Iterator( _null );

		// There may be many elements has same key, so find the exact one.
		while ( node != _null && (const Key&) node->mElement != key && node->mHashCode == hashcode )
			node = node->mBucketNext;

		// Can not find the exact one.
		if ( node == _null || (const Key&) node->mElement != key )
			return Iterator( _null );

		return Iterator( node );
	}

	// Insert an 'empty' element into the hash table by hash code, and let user set value later.
	Iterator InsertByKey( const Key& key )
	{
		if ( mNodes == _null )
		{
			mNodes = new HashNode*[ mDivisor ];
			for ( _dword i = 0; i < mDivisor; i ++ )
				mNodes[i] = _null;
		}

		// Calculate hash code from key.
		_dword hashcode = (_dword) (_ptr) key;
		_dword bucketid = hashcode % mDivisor;

		HashNode* node = new HashNode;
		node->mHashCode	= hashcode;

		// If the hash bucket has no node, put the new node as head of the hash bucket.
		if ( mNodes[ bucketid ] == _null )
		{
			mNodes[ bucketid ] = node;
		}
		// Put the new node into the hash bucket sort ascending
		else
		{
			HashNode* temp1 = _null;
			HashNode* temp2 = mNodes[ bucketid ];

			// Skip the less node compare to the new one.
			while ( temp2 != _null && temp2->mHashCode <= hashcode )
				{ temp1 = temp2; temp2 = temp2->mBucketNext; }

			// Relink the hash bucket.
			node->mBucketPrev = temp1;
			node->mBucketNext = temp2;

			if ( temp2 != _null )
				temp2->mBucketPrev = node;

			if ( temp1 != _null )
				temp1->mBucketNext = node;
			else
				mNodes[ bucketid ] = node;
		}

		Link< Type, Key >::InsertTail( node );

		return Iterator( node );
	}

	// Insert an element into the hash table by hash code that calculated from element key.
	Iterator Insert( const Type& element )
	{
		Iterator it = InsertByKey( (const Key&) element );
		*it = element;

		return it;
	}

	// Remove the first element match the key from the hash.
	_bool Remove( const Key& key )
	{
		if ( mNodes == _null )
			return _false;

		// Calculate hash code from key.
		_dword hashcode = (_dword) (_ptr) key;
		_dword bucketid = hashcode % mDivisor;

		if ( mNodes[ bucketid ] == _null )
			return _false;

		HashNode* temp1 = _null;
		HashNode* temp2 = mNodes[ bucketid ];

		// Find the node by hash code, nodes are sort ascending.
		while ( temp2 != _null && temp2->mHashCode < hashcode )
			{ temp1 = temp2; temp2 = temp2->mBucketNext; }

		// Can not find node.
		if ( temp2 == _null || temp2->mHashCode != hashcode )
			return _false;

		// There may be many elements has same key, so find the exact one.
		while ( temp2 != _null && (const Key&) temp2->mElement != key && temp2->mHashCode == hashcode )
			{ temp1 = temp2; temp2 = temp2->mBucketNext; }

		// Can not find the exact one.
		if ( temp2 == _null || (const Key&) temp2->mElement != key )
			return _false;

		if ( temp2->mBucketNext != _null )
			temp2->mBucketNext->mBucketPrev = temp2->mBucketPrev;

		// Relink the hash bucket.
		if ( temp1 != _null )
			temp1->mBucketNext = temp2->mBucketNext;
		else
			mNodes[ bucketid ] = temp2->mBucketNext;

		// Remove from hash link.
		Link< Type, Key >::RemoveNode( temp2 );

		delete temp2;

		return _true;
	}

	// Remove all elements match the key from the hash.
	_void RemoveAll( const Key& key )
	{
		while ( Remove( key ) );
	}

	// Remove an element from the hash table, the element is specified by an iterator.
	_bool RemoveAt( const Iterator& it )
	{
		if ( !it )
			return _false;

		if ( mNodes == _null )
			return _false;

		// Calculate hash code from key.
		_dword hashcode = (_dword) (_ptr) (const Key&) ( *it );
		_dword bucketid = hashcode % mDivisor;

		if ( mNodes[ bucketid ] == _null )
			return _false;

		HashNode* node = (HashNode*) it.GetNode( );

		if ( node->mBucketNext != _null )
			node->mBucketNext->mBucketPrev = node->mBucketPrev;

		if ( node->mBucketPrev != _null )
			node->mBucketPrev->mBucketNext = node->mBucketNext;
		else
			mNodes[ bucketid ] = node->mBucketNext;

		// Remove from hash link.
		Link< Type, Key >::RemoveNode( node );
		delete node;

		return _true;
	}

	// Clear hash table and release memory used by nodes.
	_void Clear( )
	{
		if ( mNodes == _null )
			return;

		for ( _dword i = 0; i < mDivisor; i ++ )
		{
			while ( mNodes[i] != _null )
			{
				HashNode* node = mNodes[i]; mNodes[i] = node->mBucketNext;
				delete node;
			}
		}

		delete[] mNodes;
		mNodes = _null;

		Link< Type, Key >::ClearNode( );
	}
};

};