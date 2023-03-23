#pragma once

namespace Xixels
{

template< typename Type, typename Key = Type > class List : public Link< Type, Key >
{
public:
	typedef typename Link< Type, Key >::Node		Node;
	typedef typename Link< Type, Key >::Iterator	Iterator;

public:
	inline List( )
		{ }

	List( const List< Type, Key >& list )
	{
		for ( Node* node = list.mHead; node != _null; node = node->mNext )
			InsertTail( node->mElement );
	}

	List< Type, Key >& operator = ( const List< Type, Key >& list )
	{
		Clear( );

		for ( Node* node = list.mHead; node != _null; node = node->mNext )
			InsertTail( node->mElement );

		return *this;
	}

	inline ~List( )
		{ Clear( ); }

	// Insert an element into the list at head.
	inline _void InsertHead( const Type& element )
		{ Link< Type, Key >::InsertHead( new Node( element ) ); }

	// Insert an element into the list at tail.
	inline _void InsertTail( const Type& element )
		{ Link< Type, Key >::InsertTail( new Node( element ) ); }

	// Insert an element into the list before the position specified by an iterator.
	inline _void InsertBefore( const Type& element, const Iterator& it )
		{ Link< Type, Key >::InsertBefore( new Node( element ), it ); }

	// Insert an element into the list after the position specified by an iterator.
	inline _void InsertAfter( const Type& element, const Iterator& it )
		{ Link< Type, Key >::InsertAfter( new Node( element ), it ); }

	// Remove the first element match the key from the list.
	_bool Remove( const Key& key )
	{
		Iterator it = Link< Type >::IndexOf( key );
		if ( !it )
			return _false;

		RemoveAt( it );
		return _true;
	}

	// Remove all elements match the key from the list.
	_void RemoveAll( const Key& key )
	{
		Iterator it = IndexOf( key );
		while ( it )
		{
			RemoveAt( it );
			it = IndexOf( key );
		}
	}

	// Remove an element from the list, the element is specified by an iterator.
	_bool RemoveAt( const Iterator& it )
	{
		if ( !it )
			return _false;

		Link< Type, Key >::RemoveNode( it.GetNode( ) );
		delete it.GetNode( );

		return _true;
	}

	// Clear list and release memory used by nodes.
	_void Clear( )
	{
		while ( Link< Type, Key >::mHead != _null )
		{
			Node* node = Link< Type, Key >::mHead;
			Link< Type, Key >::mHead = node->mNext;
			delete node;
		}

		Link< Type, Key >::ClearNode( );
	}
};

};