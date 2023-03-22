#pragma once

#include "Typedef.h"

namespace Xixels
{

class Memory
{
public:
	enum _PROFILE_TYPE
	{
		_TYPE_ALL		= 0,
		_TYPE_ARRAY		= 1,
		_TYPE_STRING	= 2,
		_TYPE_MAX		= 3,
	};

	static _dword	sRefBufferHeader[ 2 ];

private:
	static _dword	sNewCount[ _TYPE_MAX ];
	static _dword	sDelCount[ _TYPE_MAX ];
	static _dword	sAllocSize[ _TYPE_MAX ];

public:
	static _void	MemSet( _void* buffer, _byte value, _dword length );
	static _bool	MemNot( const _void* buffer, _byte value, _dword length );
	static _bool	MemCmp( const _void* buffer1, const _void* buffer2, _dword length );
	static _void	MemCpy( _void* buffer1, const _void* buffer2, _dword length );
	static _void	MemMove( _void* buffer1, const _void* buffer2, _dword length );

	static _void	MemDump( const _void* buffer, _dword length, const _char* prefix = L"" );

	static _void*	HeapAlloc( _dword length );
	static _void	HeapFree( _void* pointer );

	static _void*	CreateRefBuffer( _dword length );
	static _void*	CreateRefBuffer( const _void* buffer, _dword length );
	static _void*	ReserveRefBuffer( _void* buffer );
	static _bool	ReleaseRefBuffer( _void* buffer );

	static _void	IncreaseAllocSize( _dword type, _dword size );
	static _void	DecreaseAllocSize( _dword type, _dword size );
	static _void	ReportUsage( );
	static _dword	GetMemoryUsage( );
};

class MemoryBuffer
{
private:
	_byte*	mBuffer;
	_byte*	mPointer;
	_dword	mLength;
	_dword	mRefCount;

public:
	inline MemoryBuffer( )
		: mBuffer( _null ), mPointer( _null ), mLength( 0 ), mRefCount( 0 ) { }

	~MemoryBuffer( );

	inline _dword RemainBytes( ) const
		{ return mLength - _dword( mPointer - mBuffer ); }

	_void	CreateBuffer( _dword length );
	_void*	BufferAlloc( _dword length );
	_void	BufferFree( _void* pointer );
};

};