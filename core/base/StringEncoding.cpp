#include <assert.h>
#include <stdlib.h>
#include "../math/Math.h"
#include "String.h"
#include "StringEncoding.h"

using namespace Xixels;

_charw* StringEncoding::AsciiToUCS2( _charw* buffer, _dword size, const _chara* str, _dword number, _dword* chcopy )
{
	assert( str != _null );

	_dword length = (_dword) ::mbstowcs( _null, str, 0 );
	length = Math::Min( length, number );

	if ( buffer == _null )
	{
		// Create the buffer and fill it.
		buffer = new _charw[ length + 1 ];
	}
	else
	{
		length = Math::Min( length, size - 1 );
	}

	::mbstowcs( buffer, str, length );

	buffer[ length ] = 0;

	if ( chcopy != _null )
	{
		if ( length > 0 && buffer[ length - 1 ] == 0 )
			length --;

		*chcopy = length;
	}

	return buffer;
}

_chara* StringEncoding::UCS2ToAscii( _chara* buffer, _dword size, const _charw* str, _dword number, _dword* chcopy )
{
	assert( str != _null );

	_dword length = (_dword) ::wcstombs( _null, str, 0 );

	if ( buffer == _null )
	{
		// Create the buffer and fill it.
		buffer = new _chara[ length + 1 ];
	}
	else
	{
		length = Math::Min( length, size - 1 );
	}

	::wcstombs( buffer, str, length );


	buffer[ length ] = 0;

	if ( chcopy != _null )
	{
		if ( length > 0 && buffer[ length - 1 ] == 0 )
			length --;

		*chcopy = length;
	}

	return buffer;
}

_charw* StringEncoding::UTF8ToUCS2( _charw* buffer, _dword size, const _chara* str, _dword number, _dword* chcopy, _bool* morespace )
{
	assert( str != _null );

	if ( buffer == _null )
		size = -1;

	if ( morespace != _null )
		*morespace = _false;

	const _chara* c = str;
	const _chara* endc = str + Math::Min( (_dword)( ::strlen( str ) ), number );
	_dword wn = 0;
	for ( ; c < endc; wn ++ )
	{
		if ( (*c & 0x80) == 0 )
		{
			c ++;
		}
		else if ( (*c & 0xE0) == 0xC0 )
		{
			c += 2;
		}
		else if ( (*c & 0xF0) == 0xE0 )
		{
			c += 3;
		}
		else
		{
			c ++;
		}
	}

	wn = c == endc ? wn : wn - 1;
	_dword sn = size > 0 ? size - 1 : 0;
	if ( wn > sn )
	{
		if ( morespace != _null )
			*morespace = _true;

		wn = sn;
	}

	if ( buffer == _null )
		buffer = new _charw[wn + 1];

	if ( chcopy != _null )
		*chcopy = wn;

	_charw* w = buffer;
	for ( const _chara* c = str; wn > 0; wn -- )
	{
		if ( (*c & 0x80) == 0 )
		{
			*w ++ = *c;
			c ++;
		}
		else if ( (*c & 0xE0) == 0xC0 )
		{
			*w ++ = (c[0] & 0x1F) << 6 | (c[1] & 0x3F);
			c += 2;
		}
		else if ( (*c & 0xF0) == 0xE0 )
		{
			*w ++ = (c[0] & 0x0F) << 12 | (c[1] & 0x3F) << 6 | (c[2] & 0x3F);
			c += 3;
		}
		else
		{
			*w ++ = *c;
			c ++;
		}
	}

	if ( size > 0 )
		*w = 0;

	return buffer;
}

_chara* StringEncoding::UCS2ToUTF8( _chara* buffer, _dword size, const _charw* str, _dword number, _dword* chcopy, _bool* morespace )
{
	assert( str != _null )
	if ( buffer == _null )
		size = -1;

	if ( morespace != _null )
		*morespace = _false;

	_dword ci = 0, wi = 0;
	for ( const _charw* w = str; *w != 0 && wi < number; w ++, wi ++ )
	{
		_dword wt = ( *w & (_charw) 0xFFFFFF80 ) == 0 ? 1 : ( *w & (_charw) 0xFFFFF800 ) == 0 ? 2 : 3;
		if ( ci + wt >= size )
		{
			if ( morespace != _null )
				*morespace = _true;

			break;
		}

		ci += wt;
	}

	if ( buffer == _null )
		buffer = new _chara[ci + 1];

	const _charw* w = str;
	_chara* c = buffer;
	for ( _dword i = 0; i < wi; i ++, w ++ )
	{
		if ( ( *w & (_charw) 0xFFFFFF80 ) == 0 )
		{
			*c++ = (_chara)*w;
		}
		else if ( ( *w & (_charw) 0xFFFFF800 ) == 0 )
		{
			*c++ = (_chara)( ( *w >> 6 & 0x1F ) | 0xC0 );
			*c++ = (_chara)( ( *w & 0x3F ) | 0x80 );
		}
		else
		{
			*c++ = (_chara)( ( *w >> 12 & 0x0F ) | 0xE0 );
			*c++ = (_chara)( ( *w >> 6 & 0x3F ) | 0x80 );
			*c++ = (_chara)( ( *w & 0x3F ) | 0x80 );
		}
	}

	if ( size > 0 )
		buffer[ci] = 0;

	if ( chcopy != _null )
		*chcopy = ci;

	return buffer;
}

_char* StringEncoding::UCS2ToWCHAR( _char* buffer, _dword size, const _word* str, _dword number )
{
	if ( number == (_dword) -1 )
	{
		number = 0;
		while ( *( str ++ ) != 0 )
			number ++;
	}

	if ( buffer == _null || size == 0 )
		buffer = new _char[number + 1];
	else if ( size <= number )
		number = size - 1;

	for ( _dword i = 0; i < number; i ++ )
		buffer[i] = str[i];

	buffer[number] = 0;

	return buffer;
}