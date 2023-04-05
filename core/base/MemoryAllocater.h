#pragma once

#include "DataType.h"
#include "Array.h"
#include "Link.h"

namespace Xixels
{

class MemoryAllocater
{
private:
	enum _CHUNK_FLAG
	{
		_USED_CHUNK = 0x80706050,
		_FREE_CHUNK = 0xA0B0C0E0,
	};

	// The allocate chunk header, linked in a chain.
	struct ChunkHeader
	{
		// The page it belongs to.
		_void*		mPage;
		// Chunk flag.
		_dword		mFlag;
		// The size of the chunk, without the header.
		_dword		mSize;
	};

	// The allocate chunk end, used as chunk marker.
	struct ChunkEnd
	{
		// The chunk node pointer.
		_void*		mNode;
		// Chunk flag.
		_dword		mFlag;
	};

	typedef Link< ChunkHeader > ChunkLink;

	// The pre-allocated page from system heap, all pages linked in a chain.
	struct MemPage
	{
		// The size of the page, without the header.
		_dword		mSize;

		// The used space of the page, in number of bytes.
		_dword		mUsedSpace;
		// The free space of the page, in number of bytes.
		_dword		mFreeSpace;
		// The bound of the page.
		_byte*		mPageBound;

		// The free chunk link of the page.
		ChunkLink	mFreeChunkLink;
	};

	typedef Array< MemPage* > PageArray;

	// The size per page in number of bytes, not include page header.
	_dword		mPageSize;
	// The array of page.
	PageArray	mPages;

private:
	_void 	CreatePage( MemPage* page, _dword size );

	_void 	CreateChunk( MemPage* page, ChunkLink::Node* freenode, _dword size, _bool newnode );
	_void 	ReleaseChunk( MemPage* page, ChunkLink::Node* freenode, _dword size );

	_void*	CreateBuffer( MemPage* page, _dword size );

public:
	// Constructor, create an empty allocater with specified page size.
	MemoryAllocater( _dword pagesize = 1024 );
	// Destructor, delete all pre-allocated pages.
	~MemoryAllocater( );

	// Allocates memory block in the allocater.
	_void*	Allocate( _dword size );
	_void*	Allocate( const _void* pointer, _dword size );

	// Deallocates memory block in the allocater, decrease the reference count of the block, when it reachs zero, then will be released.
	_void	Free( const _void* pointer );

	// Clear all allocated memory block.
	_void	Clear( );

	_void	SetPageSize( _dword pagesize );

	// Get the space information of the allocater.
	_void	GetAllocationInfo( _dword& totalspace, _dword& usedspace, _dword& freespace ) const;
};

};