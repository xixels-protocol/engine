#include <memory.h>
#include <assert.h>
#include <wchar.h>
#include "String.hpp"
#include "StringFormatter.h"
#include "../math/Math.hpp"
#include "Memory.hpp"
#include "Trace.h"
#include <stdlib.h>

using namespace Xixels;

const _char* _Mem_Profile_Type_Name[] =
{
	L"All",
	L"Array",
	L"String",
	L"Unknown",
};

// RefBufferHeader: [0] is reference buffer tag and [1] if reference count.
_dword Memory::sRefBufferHeader[ 2 ] = { 0x4642544E, 1 };

_dword Memory::sNewCount[ _TYPE_MAX ] = { 0 };
_dword Memory::sDelCount[ _TYPE_MAX ] = { 0 };
_dword Memory::sAllocSize[ _TYPE_MAX ] = { 0 };

_void Memory::MemSet( _void* desbuffer, _byte value, _dword length )
{
	::memset( desbuffer, value, length );
}

_bool Memory::MemNot( const _void* buffer, _byte value, _dword length )
{
	for ( _dword i = 0; i < length; i ++ )
	{
		if ( ( (_byte*) buffer )[i] != value )
			return _true;
	}

	return _false;
}

_bool Memory::MemCmp( const _void* buffer1, const _void* buffer2, _dword length )
{
	return ::memcmp( buffer1, buffer2, length ) == 0;
}

_void Memory::MemCpy( _void* desbuffer, const _void* srcbuffer, _dword length )
{
	::memcpy( desbuffer, srcbuffer, length );
}

_void Memory::MemMove( _void* desbuffer, const _void* srcbuffer, _dword length )
{
	::memmove( desbuffer, srcbuffer, length );
}

_void Memory::MemDump( const _void* buffer, _dword length, const _char* prefix )
{
	_char tempbuf1[1024], tempbuf2[1024];

	for ( _dword i = 0; i < length / 32 + 1; i ++ )
	{
		if ( i * 32 >= length )
			return;

		tempbuf2[0] = 0;

		for ( _dword j = 0; j < 32; j ++ )
		{
			_dword k = i * 32 + j;

			if ( k < length )
			{
				_byte data = ( (_byte*) buffer )[k];

				StringFormatter::FormatBuffer( tempbuf1, 1024, L"%.2X ", data );
				StringPtr::Append( tempbuf2, tempbuf1 );
			}
			else
			{
				StringPtr::Append( tempbuf2, L"   " );
			}

			if ( j == 15 )
				StringPtr::Append( tempbuf2, L"- " );
		}

		StringPtr::Append( tempbuf2, L"--- " );

		for ( _dword k = 0; k < Math::Min( (_dword) 16, length - i * 32 ); k ++ )
		{
			_char c = *( (_chara*) buffer + i * 32 + k );
			StringPtr::Append( tempbuf2, &c, 1 );
		}

		XX_LOG( L"%ls%ls", prefix, tempbuf2 )
	}
}

_void* Memory::HeapAlloc( _dword length )
{
	if ( length == 0 || length >= (_dword) Math::cMaxLong )
		return _null;

	_void* pointer = ::malloc( length );

	if ( pointer == _null )
		XX_LOG( L"Out of memory" )

	assert( pointer != _null );

	IncreaseAllocSize( _TYPE_ALL, length );

	// return ( (_dword*) pointer ) + 1;
	return pointer;
}

_void Memory::HeapFree( _void* pointer )
{
	if ( pointer == _null )
		return;

	::free( pointer );
}

_void* Memory::CreateRefBuffer( _dword length )
{
	if ( length == 0 || length >= (_dword) Math::cMaxLong )
		return _null;

	_byte* realbuffer = new _byte[ length + 8 ];

	( (_dword*) realbuffer )[0] = sRefBufferHeader[0];
	( (_dword*) realbuffer )[1] = sRefBufferHeader[1];

	return realbuffer + 8;
}

_void* Memory::CreateRefBuffer( const _void* buffer, _dword length )
{
	if ( length == 0 || length >= (_dword) Math::cMaxLong )
		return _null;

	_byte* realbuffer = new _byte[ length + 8 ];

	( (_dword*) realbuffer )[0] = sRefBufferHeader[0];
	( (_dword*) realbuffer )[1] = sRefBufferHeader[1];

	if ( buffer != _null )
		MemCpy( realbuffer + 8, buffer, length );

	return realbuffer + 8;
}

_void* Memory::ReserveRefBuffer( _void* buffer )
{
	if ( buffer == _null )
		return _null;

	_byte* realbuffer = (_byte*) buffer - 8;

	assert( ( (_dword*) realbuffer )[0] == sRefBufferHeader[0] );
	assert( ( (_dword*) realbuffer )[1] >= 1 );

	( (_dword*) realbuffer )[1] ++;

	return buffer;
}

_bool Memory::ReleaseRefBuffer( _void* buffer )
{
	if ( buffer == _null )
		return _true;

	_byte* realbuffer = (_byte*) buffer - 8;

	assert( ( (_dword*) realbuffer )[0] == sRefBufferHeader[0] );
	assert( ( (_dword*) realbuffer )[1] >= 1 );

	( (_dword*) realbuffer )[1] --;

	if ( ( (_dword*) realbuffer )[1] != 0 )
		return _false;

	delete[] realbuffer;
	return _true;
}

_void Memory::IncreaseAllocSize( _dword type, _dword size )
{
	if ( type >= _TYPE_MAX )
		return;

	sNewCount[ type ] ++;
	sAllocSize[ type ] += size;
}

_void Memory::DecreaseAllocSize( _dword type, _dword size )
{
	if ( type >= _TYPE_MAX )
		return;

	sDelCount[ type ] ++;
	sAllocSize[ type ] -= size;
}

_void Memory::ReportUsage( )
{
	for ( _dword i = 0; i < _TYPE_MAX; i ++ )
	{
		if ( i == _TYPE_ALL )
			continue;

		_dword activenew = Memory::sNewCount[i] - Memory::sDelCount[i];
		XX_LOG( L"%ls heap memory : %ls", _Mem_Profile_Type_Name[i], (const _char*) StringFormatter::FormatBytes( sAllocSize[i] ) )
		XX_LOG( L"Active new count (%ls): %d = %d - %d", _Mem_Profile_Type_Name[i], activenew, Memory::sNewCount[i], Memory::sDelCount[i] )
	}
}

_dword Memory::GetMemoryUsage( )
{
	return sAllocSize[ _TYPE_ALL ];
}

MemoryBuffer::~MemoryBuffer( )
{
	if ( mBuffer != _null )
		delete[] mBuffer;
}

_void MemoryBuffer::CreateBuffer( _dword length )
{
	if ( length == 0 )
		return;

	assert( mBuffer == _null );

	mBuffer  = new _byte[ length ];
	mPointer = mBuffer;
	mLength  = length;
}

_void* MemoryBuffer::BufferAlloc( _dword length )
{
	if ( mBuffer == _null || (_ptr) mPointer - (_ptr) mBuffer + length > mLength )
		return new _byte[ length ];

	_void* ptr = mPointer;

	mPointer += length;
	mRefCount ++;

	return ptr;
}

_void MemoryBuffer::BufferFree( _void* pointer )
{
	if ( mBuffer == _null || (_ptr) pointer < (_ptr) mBuffer || (_ptr) pointer - (_ptr) mBuffer > mLength )
		delete[] (_byte*) pointer;

	if ( -- mRefCount == 0 )
	{
		delete[] mBuffer;
		mBuffer  = _null;
		mPointer = _null;
		mLength  = 0;
	}
}