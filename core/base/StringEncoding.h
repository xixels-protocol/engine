#pragma once

#include "Typedef.h"

namespace Xixels
{

class StringEncoding
{
public:
	enum _ENCODING
	{
		_ASCII	= 0,
		_UCS2	= 1,
		_UTF8	= 2,
	};

public:
	inline static _charw* AsciiToUCS2( _charw* buffer, _dword size, const _chara* str, _dword* chcopy = _null )
		{ return AsciiToUCS2( buffer, size, str, -1, chcopy ); }
	inline static _chara* UCS2ToAscii( _chara* buffer, _dword size, const _charw* str, _dword* chcopy = _null )
		{ return UCS2ToAscii( buffer, size, str, -1, chcopy ); }
	inline static _charw* UTF8ToUCS2( _charw* buffer, _dword size, const _chara* str, _dword* chcopy = _null, _bool* morespace = _null )
		{ return UTF8ToUCS2( buffer, size, str, -1, chcopy, morespace ); }
	inline static _chara* UCS2ToUTF8( _chara* buffer, _dword size, const _charw* str, _dword* chcopy = _null, _bool* morespace = _null )
		{ return UCS2ToUTF8( buffer, size, str, -1, chcopy, morespace ); }

	static _charw*	AsciiToUCS2( _charw* buffer, _dword size, const _chara* str, _dword number, _dword* chcopy = _null );
	static _chara*	UCS2ToAscii( _chara* buffer, _dword size, const _charw* str, _dword number, _dword* chcopy = _null );
	static _charw*	UTF8ToUCS2( _charw* buffer, _dword size, const _chara* str, _dword number, _dword* chcopy = _null, _bool* morespace = _null );
	static _chara*	UCS2ToUTF8( _chara* buffer, _dword size, const _charw* str, _dword number, _dword* chcopy = _null, _bool* morespace = _null );
	static _char*	UCS2ToWCHAR( _char* buffer, _dword size, const _word* str, _dword number );
};

};