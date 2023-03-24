#include "String.hpp"
#include "Memory.hpp"
#include <wchar.h>

using namespace Xixels;

String::String( const Oword& oword ) : mLength( 0 ), mSize( 0 )
{
	String str = oword.ToString( );
	Copy( str, str.mLength );
}

String::String( const Qword& qword ) : mLength( 0 ), mSize( 0 )
{
	String str = qword.ToString( );
	Copy( str, str.mLength );
}

_void String::AllocBuffer( _dword length )
{
	// Create using buffer.
	mString = StringBuffer::BufferAlloc( length + 1 );
	mLength = length;

	// If failed, create in heap.
	if ( mString == _null )
	{
		mSize = length + 1;
		mString = (_char*) Memory::HeapAlloc( mSize * sizeof( _char ) );
	}
	else
	{
		mSize = 0;
	}
}

_void String::FreeBuffer( )
{
	if ( mSize > 0 )
		Memory::HeapFree( mString );
}

String&	String::Empty( )
{
	FreeBuffer( );

	mLength	= 0;
	mSize	= 0;
	mString = (_char*) L"";

	return *this;
}

String& String::ToLower( )
{
	for ( _dword i = 0; i < mLength; i ++ )
	{
		if ( (_word) mString[i] < 0x0080 )
			mString[i] = tolower2( mString[i] );
	}

	return *this;
}

String& String::ToUpper( )
{
	for ( _dword i = 0; i < mLength; i ++ )
	{
		if ( (_word) mString[i] < 0x0080 )
			mString[i] = toupper2( mString[i] );
	}

	return *this;
}

String& String::Copy( _char ch )
{
	mLength = ch != 0 ? 1 : 0;

	// Clear string buffer.
	if ( mLength == 0 )
	{
		FreeBuffer( );

		mString	= (_char*) L"";
		mSize	= 0;
	}
	else
	{
		// Create more memory if necessary.
		if ( mSize < mLength + 1 )
		{
			FreeBuffer( );

			AllocBuffer( mLength );
		}

		// Append character.
		mString[0] = ch;

		// Set null-terminated.
		mString[ mLength ] = 0;
	}

	return *this;
}

String& String::Copy( StringPtr str, _dword length )
{
	// Get string length.
	if ( length == -1 )
		length = str.Length( );

	// Clear string buffer.
	if ( length == 0 )
	{
		FreeBuffer( );

		mString	= (_char*) L"";
		mSize	= 0;
	}
	else
	{
		// Create more memory if necessary.
		if ( mSize < length + 1 )
		{
			FreeBuffer( );

			AllocBuffer( length );
		}

		// Copy string.
		Memory::MemCpy( mString, str, length * sizeof( _char ) );

		// Set null-terminated.
		mString[ length ] = 0;
	}

	mLength = (_dword) ::wcslen( mString );

	return *this;
}

String& String::Insert( _dword index, _char ch )
{
	if ( index > mLength )
		return *this;

	_dword oldlen = mLength;

	mLength ++;

	// Create more memory if necessary.
	if ( mSize < mLength + 1 )
	{
		_char* oldstr = mString;
		_dword oldsize = mSize;

		AllocBuffer( mLength );

		// Copy old string back to buffer.
		Memory::MemCpy( mString, oldstr, index * sizeof( _char ) );
		Memory::MemCpy( mString + index + 1, oldstr + index, ( oldlen - index ) * sizeof( _char ) );

		// Delete the old memory.
		if ( oldsize > 0 )
			Memory::HeapFree( oldstr );
	}
	else
	{
		for ( _dword i = index; i < oldlen; i ++ )
			mString[ mLength - i + index - 1 ] = mString[ oldlen - i + index - 1 ];
	}

	// Insert ch.
	mString[ index ] = ch;

	// Set null-terminated.
	mString[ mLength ] = 0;

	return *this;
}

String& String::Insert( _dword index, StringPtr str, _dword length )
{
	if ( index > mLength )
		return *this;

	_dword len1 = mLength, len2 = length == -1 ? str.Length( ) : length;

	mLength = len1 + len2;

	// Create more memory if necessary.
	if ( mSize < mLength + 1 )
	{
		_char* oldstr = mString;
		_dword oldsize = mSize;

		AllocBuffer( mLength );

		// Copy old string back to buffer.
		Memory::MemCpy( mString, oldstr, index * sizeof( _char ) );
		Memory::MemCpy( mString + index + len2, oldstr + index, ( len1 - index ) * sizeof( _char ) );

		// Delete the old memory.
		if ( oldsize > 0 )
			Memory::HeapFree( oldstr );
	}
	else
	{
		for ( _dword i = index; i < len1; i ++ )
			mString[ mLength - i + index - 1 ] = mString[ len1 - i + index - 1 ];
	}

	// Insert str.
	Memory::MemCpy( mString + index, (const _char*) str, len2 * sizeof( _char ) );

	// Set null-terminated.
	mString[ mLength ] = 0;

	return *this;
}

String& String::Remove( _dword index, _dword length )
{
	if ( index >= mLength )
		return *this;

	if ( length == -1 || length > mLength - index )
		length = mLength - index;

	if ( length == 0 )
		return *this;

	for ( _dword i = index + length; i <= mLength; i ++ )
		mString[ i - length ] = mString[i];

	mLength -= length;

	return *this;
}

String& String::Replace( _char oldch, _char newch, _bool sensitive )
{
	if ( sensitive )
	{
		for ( _dword i = 0; mString[i] != 0; i ++ )
		{
			if ( mString[i] == oldch )
				mString[i] = newch;
		}
	}
	else
	{
		oldch = tolower2( oldch );

		for ( _dword i = 0; mString[i] != 0; i ++ )
		{
			if ( tolower2( mString[i] ) == oldch )
				mString[i] = newch;
		}
	}

	return *this;
}

String& String::Replace( StringPtr oldstr, StringPtr newstr, _bool sensitive )
{
	_dword start = 0, len1 = oldstr.Length( ), len2 = newstr.Length( );

	while ( _true )
	{
		StringPtr str = mString + start;

		_dword index = str.IndexOf( oldstr, sensitive );

		// Cant find the substring.
		if ( index == -1 )
			break;

		// Remove the old substring, and insert the new one.
		Remove( index + start, len1 );
		Insert( index + start, newstr );

		start += ( index + len2 );
	}

	return *this;
}

String& String::TrimLeft( _char ch, _bool sensitive )
{
	_dword number = 0;

	if ( sensitive )
	{
		for ( number = 0; number < mLength; number ++ )
		{
			if ( mString[ number ] != ch )
				break;
		}
	}
	else
	{
		ch = tolower2( ch );

		for ( number = 0; number < mLength; number ++ )
		{
			if ( tolower2( mString[ number ] ) != ch )
				break;
		}
	}

	if ( number > 0 )
		Remove( 0, number );

	return *this;
}

String& String::TrimRight( _char ch, _bool sensitive )
{
	_dword number = 0;

	if ( sensitive )
	{
		for ( number = 0; number < mLength; number ++ )
		{
			if ( mString[ mLength - number - 1 ] != ch )
				break;
		}
	}
	else
	{
		ch = tolower2( ch );

		for ( number = 0; number < mLength; number ++ )
		{
			if ( tolower2( mString[ mLength - number - 1 ] ) != ch )
				break;
		}
	}

	if ( number > 0 )
		Remove( mLength - number, number );

	return *this;
}

String& String::TrimLeft( StringPtr chset, _bool sensitive )
{
	_dword number = 0, length = chset.Length( );

	if ( sensitive )
	{
		for ( number = 0; number < mLength; number ++ )
		{
			_dword i = 0;
			for ( i = 0; i < length; i ++ )
			{
				if ( mString[ number ] == chset[i] )
					break;
			}

			if ( i == length )
				break;
		}
	}
	else
	{
		for ( number = 0; number < mLength; number ++ )
		{
			_dword i = 0;
			for ( i = 0; i < length; i ++ )
			{
				if ( tolower2( mString[ number ] ) == tolower2( chset[i] ) )
					break;
			}

			if ( i == length )
				break;
		}
	}

	if ( number > 0 )
		Remove( 0, number );

	return *this;
}

String& String::TrimRight( StringPtr chset, _bool sensitive )
{
	_dword number = 0, length = chset.Length( );

	if ( sensitive )
	{
		for ( number = 0; number < mLength; number ++ )
		{
			_dword i = 0;
			for ( i = 0; i < length; i ++ )
			{
				if ( mString[ mLength - number - 1 ] == chset[i] )
					break;
			}

			if ( i == length )
				break;
		}
	}
	else
	{
		for ( number = 0; number < mLength; number ++ )
		{
			_dword i = 0;
			for ( i = 0; i < length; i ++ )
			{
				if ( tolower2( mString[ mLength - number - 1 ] ) == tolower2( chset[i] ) )
					break;
			}

			if ( i == length )
				break;
		}
	}

	if ( number > 0 )
		Remove( mLength - number, number );

	return *this;
}

StringBuffer* StringBuffer::sUsingBuffer = _null;

StringBuffer::StringBuffer( ) : mBufferIndex( 0 ), mBufferOffset( 0 )
{
	for ( _dword i = 0; i < _MAX_BUFFER_COUNT; i ++ )
		mBuffers[i] = _null;
}

StringBuffer::~StringBuffer( )
{
	for ( _dword i = 0; i < _MAX_BUFFER_COUNT; i ++ )
		Memory::HeapFree( mBuffers[i] );
}

StringBuffer* StringBuffer::GetUsingBuffer( )
{
	if ( sUsingBuffer != _null )
		return sUsingBuffer;
	else
		return _null;
}

_char* StringBuffer::BufferAlloc( _dword length )
{
	if ( sUsingBuffer == _null || length > _MAX_BUFFER_LENGTH )
		return _null;

	StringBuffer* This = sUsingBuffer;

	// All buffer is used.
	if ( This->mBufferIndex >= _MAX_BUFFER_COUNT )
		return _null;

	// Move to next buffer when needed.
	if ( This->mBufferOffset + length > _MAX_BUFFER_LENGTH )
	{
		This->mBufferOffset = 0;
		This->mBufferIndex ++;
		if ( This->mBufferIndex >= _MAX_BUFFER_COUNT )
			return _null;
	}

	_char*& buffer = This->mBuffers[ This->mBufferIndex ];

	// Create buffer when needed.
	if ( buffer == _null )
		buffer = (_char*) Memory::HeapAlloc( _MAX_BUFFER_LENGTH * sizeof( _char ) );

	_char* pointer = buffer + This->mBufferOffset;
	This->mBufferOffset += length;

	return pointer;
}

_void StringBuffer::EnableBuffer( )
{
	sUsingBuffer = this;
}

_void StringBuffer::DisableBuffer( )
{
	sUsingBuffer = _null;
}

_void StringBuffer::ResetBuffer( )
{
	mBufferIndex = 0;
	mBufferOffset = 0;
}