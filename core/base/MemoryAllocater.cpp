#include <assert.h>
#include "Memory.hpp"
#include "MemoryAllocater.h"

using namespace Xixels;

MemoryAllocater::MemoryAllocater( _dword pagesize )
{
	mPageSize = pagesize;
}

MemoryAllocater::~MemoryAllocater( )
{
	for ( _long i = 0; i < mPages.Length( ); i ++ )
		delete[] (_byte*) mPages[i];
}

_void MemoryAllocater::CreatePage( MemPage* page, _dword size )
{
	// Make sure page size is big enough.
	if ( size < sizeof( ChunkLink::Node ) + sizeof( ChunkEnd ) )
		size = sizeof( ChunkLink::Node ) + sizeof( ChunkEnd );

	page->mSize		 = size;
	page->mUsedSpace = 0;
	page->mFreeSpace = size;
	page->mPageBound = (_byte*) page + sizeof( MemPage ) + size;

	page->mFreeChunkLink.ClearNode( );

	ChunkLink::Node* freenode = (ChunkLink::Node*) ( (_byte*) page + sizeof( MemPage ) );

	// Create default free chunk.
	CreateChunk( page, freenode, size - sizeof( ChunkLink::Node ) - sizeof( ChunkEnd ), _true );
}

_void MemoryAllocater::CreateChunk( MemPage* page, ChunkLink::Node* freenode, _dword size, _bool newnode )
{
	// Set chunk header for this node.
	ChunkHeader* header = &freenode->mElement;
	header->mPage = page;
	header->mFlag = _FREE_CHUNK;
	header->mSize = size;

	// Set chunk end for this node.
	ChunkEnd* end = (ChunkEnd*)( (_byte*) freenode + sizeof( ChunkLink::Node ) + size );
	end->mNode = freenode;
	end->mFlag = _FREE_CHUNK;

	if ( newnode )
	{
		freenode->mNext = _null;
		freenode->mPrev = _null;

		// Adjust space.
		page->mUsedSpace += sizeof( ChunkLink::Node ) + sizeof( ChunkEnd );
		page->mFreeSpace -= sizeof( ChunkLink::Node ) + sizeof( ChunkEnd );

		// Put the free node into free chunk list.
		page->mFreeChunkLink.InsertTail( freenode );
	}
}

_void MemoryAllocater::ReleaseChunk( MemPage* page, ChunkLink::Node* freenode, _dword size )
{
	// Get next node.
	ChunkLink::Node* nextnode = (ChunkLink::Node*) ( (_byte*) freenode + sizeof( ChunkLink::Node ) + size + sizeof( ChunkEnd ) );

	// Try to combine with next page.
	_dword delta = size + sizeof( ChunkLink::Node ) + sizeof( ChunkEnd );
	if ( (_byte*) nextnode < (_byte*) page->mPageBound )
	{
		// Next chunk is free.
		if ( nextnode->mElement.mFlag == _FREE_CHUNK )
		{
			size += sizeof( ChunkLink::Node ) + sizeof( ChunkEnd ) + nextnode->mElement.mSize;
			delta += sizeof( ChunkLink::Node ) + sizeof( ChunkEnd );
			page->mFreeChunkLink.RemoveNode( nextnode );
		}
		// Next chunk is used.
		else
		{
			assert( nextnode->mElement.mFlag == _USED_CHUNK );
		}
	}
	else
	{
		assert( (_byte*) nextnode == (_byte*) page->mPageBound );
	}

	page->mUsedSpace -= delta;
	page->mFreeSpace += delta;

	_bool recycled = _false;

	// Try to combine with previous page.
	if ( (_byte*) freenode > (_byte*) page + sizeof( MemPage ) )
	{
		// Get previous chunk end.
		ChunkEnd* end = (ChunkEnd*)( (_byte*) freenode - sizeof( ChunkEnd ) );

		// Previous chunk is free.
		if ( end->mFlag == _FREE_CHUNK )
		{
			// Get previous node.
			ChunkLink::Node* prevnode = (ChunkLink::Node*) end->mNode;
			assert( prevnode->mElement.mFlag == _FREE_CHUNK );

			_dword newsize = prevnode->mElement.mSize + size + sizeof( ChunkLink::Node ) + sizeof( ChunkEnd );

			// Adjust the previous node.
			CreateChunk( page, prevnode, newsize, _false );

			recycled = _true;
		}
		// Previous chunk is used.
		else
		{
			assert( end->mFlag == _USED_CHUNK );
		}
	}
	else
	{
		assert( (_byte*) freenode == (_byte*) page + sizeof( MemPage ) );
	}

	// We must recycle this chunk.
	if ( recycled == _false )
		CreateChunk( page, freenode, size, _true );
}

_void* MemoryAllocater::CreateBuffer( MemPage* page, _dword size )
{
	// Try to find a node big enough.
	ChunkLink::Node* freenode = page->mFreeChunkLink.GetHeadNode( );

	while ( freenode != _null )
	{
		// We found a free node is big enough.
		if ( freenode->mElement.mSize >= size )
			break;

		freenode = freenode->mNext;
	}

	// There is no candidate node to create chunk.
	if ( freenode == _null )
		return _null;

	assert( freenode->mElement.mFlag == _FREE_CHUNK );

	_dword freenodesize = freenode->mElement.mSize;

	// Remove the node from free chunk link.
	page->mFreeChunkLink.RemoveNode( freenode );

	// This free node is big enough, we can split it into two node.
	if ( freenodesize > size + sizeof( ChunkLink::Node ) + sizeof( ChunkEnd ) + 24 )
	{
		// Adjust node size.
		freenode->mElement.mSize = size;
		page->mUsedSpace += size;
		page->mFreeSpace -= size;

		// Find the next node position.
		ChunkLink::Node* newnode = (ChunkLink::Node*)( (_byte*) freenode + sizeof( ChunkLink::Node ) + size + sizeof( ChunkEnd ) );

		CreateChunk( page, newnode, freenodesize - size - sizeof( ChunkEnd ) - sizeof( ChunkLink::Node ), _true );
	}
	else
	{
		page->mUsedSpace += freenode->mElement.mSize;
		page->mFreeSpace -= freenode->mElement.mSize;
	}

	// We use the free node as used node.
	freenode->mNext = _null;
	freenode->mPrev = _null;

	// Set chunk header for this node.
	ChunkHeader* header = &freenode->mElement;
	header->mFlag = _USED_CHUNK;

	// Set chunk end for this node.
	ChunkEnd* end = (ChunkEnd*)( (_byte*) freenode + sizeof( ChunkLink::Node ) + freenode->mElement.mSize );
	end->mNode = freenode;
	end->mFlag = _USED_CHUNK;

	return (_byte*) freenode + sizeof( ChunkLink::Node );
}

_void* MemoryAllocater::Allocate( _dword size )
{
	while ( mPageSize < size )
		mPageSize *= 2;

	for ( _long i = 0; i < mPages.Length( ); i ++ )
	{
		MemPage* page = mPages[ mPages.Length( ) - i - 1 ];

		// This page has enough space to allocate memory block, but maybe cant because of fragment.
		if ( page->mFreeSpace >= size )
		{
			_void* pointer = CreateBuffer( page, size );
			if ( pointer != _null )
				return pointer;
		}
	}

	// Create memory block to hold one page.
	_byte* buffer = new _byte[ mPageSize + sizeof( MemPage ) ];

	// Create new page to allocate memory block.
	MemPage* page = (MemPage*) buffer;
	CreatePage( page, mPageSize );

	mPages.Add( page );

	// Create chunk in the page.
	return CreateBuffer( page, size );
}

_void* MemoryAllocater::Allocate( const _void* pointer, _dword size )
{
	_void* buffer = Allocate( size );

	if ( buffer == _null )
		return _null;

	Memory::MemCpy( buffer, pointer, size );

	return buffer;
}

_void MemoryAllocater::Free( const _void* pointer )
{
	if ( pointer == _null )
		return;

	// Get the node pointer from memory pointer.
	ChunkLink::Node* node = (ChunkLink::Node*) ( (_byte*) pointer - sizeof( ChunkLink::Node ) );
	assert( node->mElement.mFlag == _USED_CHUNK );

	MemPage* page = (MemPage*) node->mElement.mPage;
	assert( page != _null );

	// Release the chunk in the page.
	ReleaseChunk( page, node, node->mElement.mSize );
}

_void MemoryAllocater::Clear( )
{
	for ( _long i = 0; i < mPages.Length( ); i ++ )
		CreatePage( mPages[i], mPages[i]->mSize );
}

_void MemoryAllocater::SetPageSize( _dword pagesize )
{
	mPageSize = pagesize;
}

_void MemoryAllocater::GetAllocationInfo( _dword& totalspace, _dword& usedspace, _dword& freespace ) const
{
	totalspace	= 0;
	usedspace	= 0;
	freespace	= 0;

	for ( _long i = 0; i < mPages.Length( ); i ++ )
	{
		totalspace	+= mPages[i]->mSize;
		usedspace	+= mPages[i]->mUsedSpace;
		freespace	+= mPages[i]->mFreeSpace;
	}
}