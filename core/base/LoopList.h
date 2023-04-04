#pragma once

namespace Xixels
{

	//----------------------------------------------------------------------------
	// LoopList
	//----------------------------------------------------------------------------

	template< typename Type, typename Key = Type > class LoopList : public LoopLink< Type, Key >
	{
	public:
		// For g++ compiler.
		typedef typename LoopLink< Type, Key >::Node		Node;
		typedef typename LoopLink< Type, Key >::Iterator	Iterator;

	public:
		inline LoopList( )
			{ }

		LoopList( const LoopList< Type, Key >& llist )
		{
			Node* node = llist.mHead;
			for ( _long i = 0; i < llist.Length( ); i ++ )
			{
				InsertTail( node->mElement );
				node = node->mNext;
			}
		}

		LoopList< Type, Key >& operator = ( const LoopList< Type, Key >& llist )
		{
			if ( this == &llist )
				return *this;

			Clear( );
			Node* node = llist.mHead;
			for ( _long i = 0; i < llist.Length( ); i ++ )
			{
				InsertTail( node->mElement );
				node = node->mNext;
			}
		}

		inline ~LoopList( )
			{ Clear( ); }

		// Insert an element into the list at head.
		inline _void InsertHead( const Type& element )
			{ LoopLink< Type, Key >::InsertHead( new Node( element ) ); }

		// Insert an element into the list at tail.
		inline _void InsertTail( const Type& element )
			{ LoopLink< Type, Key >::InsertTail( new Node( element ) ); }

		// Insert an element into the list before the position specified by an iterator.
		inline _void InsertBefore( const Type& element, const Iterator& it )
			{ LoopLink< Type, Key >::InsertBefore( new Node( element ), it ); }

		// Insert an element into the list after the position specified by an iterator.
		inline _void InsertAfter( const Type& element, const Iterator& it )
			{ LoopLink< Type, Key >::InsertAfter( new Node( element ), it ); }

		// Remove an element from the list, the element is specified by an iterator.
		_bool RemoveAt( const Iterator& it )
		{
			if ( !it )
				return _false;

			LoopLink< Type, Key >::RemoveNode( it.GetNode( ) );
			delete it.GetNode( );

			return _true;
		}

		// Remove the first element match the key from the list.
		_bool Remove( const Key& key )
		{
			return RemoveAt( LoopLink< Type, Key >::IndexOf( key ) );
		}

		// Remove all elements match the key from the list.
		_void RemoveAll( const Key& key )
		{
			Node* next = _null;
			Node* node = LoopLink< Type, Key >::mHead;
			_dword len = LoopLink< Type, Key >::mLength;
			for ( _dword i = 0; i < len; i ++ )
			{
				if ( (const Key&) node->mElement == key )
				{
					next = node->mNext;
					LoopLink< Type, Key >::RemoveNode( node );
					delete node;
					node = next;
				}
				else
				{
					node = node->mNext;
				}
			}
		}

		// Clear list and release memory used by nodes.
		_void Clear( )
		{
			Node* next = _null;
			Node* node = LoopLink< Type, Key >::mHead;
			_dword len = LoopLink< Type, Key >::mLength;
			for ( _dword i = 0; i < len; i ++ )
			{
				next = node->mNext;
				LoopLink< Type, Key >::RemoveNode( node );
				delete node;
				node = next;
			}
		}
	};

};