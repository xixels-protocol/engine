#include "StringPtr.h"
#include <wchar.h>
#include <string.h>
#include <ctype.h>

using namespace Xixels;

_dword StringPtr::Length( const _char* str )
{
	if ( str == _null )
		return 0;

	return (_dword) ::wcslen( str );
}

_char* StringPtr::Copy( _char* buffer, const _char* str, _dword length )
{
	if ( length == -1 )
	{
		::wcscpy( buffer, str );
	}
	else
	{
		::wcsncpy( buffer, str, length );

		buffer[ length ] = 0;
	}

	return buffer;
}

_char* StringPtr::Append( _char* buffer, const _char* str, _dword length )
{
	if ( length == -1 )
	{
		::wcscat( buffer, str );
	}
	else
	{
		_dword oldlen = Length( buffer );

		::wcsncat( buffer, str, length );

		buffer[ oldlen + length ] = 0;
	}

	return buffer;
}

_char* StringPtr::ToLower( _char* buffer )
{
	if ( buffer == _null )
		return (_char*) L"";

	for ( _dword i = 0; buffer[i] != 0; i ++ )
		buffer[i] = tolower2( buffer[i] );

	return buffer;
}

_char* StringPtr::ToUpper( _char* buffer )
{
	if ( buffer == _null )
		return (_char*) L"";

	for ( _dword i = 0; buffer[i] != 0; i ++ )
		buffer[i] = toupper2( buffer[i] );

	return buffer;
}

_char* Xixels::StringPtr::Find( _char* buffer, const _char* str )
{
	if ( buffer == _null )
		return _null;

	return ::wcsstr( buffer, str );
}

_bool StringPtr::IsPunct( _char ch )
{
	return ::iswpunct( ch ) != 0;
}

_dword StringPtr::Length( const _chara* str )
{
	if ( str == _null )
		return 0;

	return (_dword) ::strlen( str );
}

_chara* StringPtr::Copy( _chara* buffer, const _chara* str, _dword length )
{
	if ( length == -1 )
	{
		::strcpy( buffer, str );
	}
	else
	{
		::strncpy( buffer, str, length );
		buffer[ length ] = 0;
	}

	return buffer;
}

_chara* StringPtr::Append( _chara* buffer, const _chara* str, _dword length )
{
	if ( length == -1 )
	{
		::strcat( buffer, str );
	}
	else
	{
		_dword oldlen = Length( buffer );
		::strncat( buffer, str, length );
		buffer[ oldlen + length ] = 0;
	}

	return buffer;
}

_chara* StringPtr::ToLower( _chara* buffer )
{
	if ( buffer == _null )
		return (_chara*) "";

	for ( _dword i = 0; buffer[i] != 0; i ++ )
		buffer[i] = tolower2( buffer[i] );

	return buffer;
}

_chara* StringPtr::ToUpper( _chara* buffer )
{
	if ( buffer == _null )
		return (_chara*) "";

	for ( _dword i = 0; buffer[i] != 0; i ++ )
		buffer[i] = toupper2( buffer[i] );

	return buffer;
}

_long StringPtr::Compare( const _chara* str1, const _chara* str2, _bool sensitive )
{
	return sensitive ? ::strcmp( str1, str2 ) : ::stricmp( str1, str2 );
}

_chara* Xixels::StringPtr::Find( _chara* buffer, const _chara* str )
{
	if ( buffer == _null )
		return _null;

	return ::strstr( buffer, str );
}

_bool StringPtr::IsPunct( _chara ch )
{
	return ::ispunct( ch ) != 0;
}

_dword StringPtr::Length( ) const
{
	return (_dword) ::wcslen( mString );
}

_dword StringPtr::SizeOfBytes( ) const
{
	return (_dword) ( ::wcslen( mString ) + 1 ) * sizeof( _char );
}

_bool StringPtr::IsBlank( ) const
{
	for ( _dword i = 0; mString[i] != 0; i ++ )
	{
		if ( mString[i] != ' ' && mString[i] != '\t' && mString[i] != '\r' && mString[i] != '\n' )
			return _false;
	}

	return _true;
}

_dword StringPtr::HashCode1( ) const
{
	_char* key = mString;

	_dword seed1 = 0x7FED7FED, seed2 = 0xEEEEEEEE, ch = 0;

	while ( *key != 0 )
	{
		ch = *key ++;
		seed1 = ch ^ ( seed1 + seed2 );
		seed2 = ch + seed1 + seed2 + ( seed2 << 5 ) + 3;
	}

	return seed1;
}

_dword StringPtr::HashCode2( ) const
{
	_char* key = mString; _dword seed = 0;

	while ( *key != 0 )
	{
		seed = 31 * seed + *key;
		key ++;
	}

	return seed;
}

_dword StringPtr::HashCode3( ) const
{
	_dword hashcode[4] = { 0 };

	// Calculate hash code by add each ch together.
	for ( _dword i = 0; mString[i] != 0; i ++ )
		hashcode[ i % 4 ] += ( (_byte) mString[i] );

	return ( hashcode[0] ) | ( hashcode[1] << 8 ) | ( hashcode[2] << 16 ) | ( hashcode[3] << 24 );
}

_bool StringPtr::StartOf( _char ch, _bool sensitive ) const
{
	if ( ch == 0 )
		return _false;

	if ( sensitive )
	{
		return mString[0] == ch;
	}
	else
	{
		return tolower2( mString[0] ) == tolower2( ch );
	}
}

_bool StringPtr::StartOf( StringPtr str, _bool sensitive ) const
{
	if ( str == L"" )
		return _false;

	_dword i = 0;

	if ( sensitive )
	{
		for ( ; mString[i] != 0; i ++ )
		{
			if ( str[i] == 0 )
				return _true;

			if ( mString[i] != str[i] )
				return _false;
		}
	}
	else
	{
		for ( ; mString[i] != 0; i ++ )
		{
			if ( str[i] == 0 )
				return _true;

			if ( tolower2( mString[i] ) != tolower2( str[i] ) )
				return _false;
		}
	}

	return str[i] == 0;
}

_bool StringPtr::EndOf( StringPtr str, _bool sensitive ) const
{
	if ( str == L"" || mString[0] == 0 )
		return _false;

	_long i = Length( ) - 1;
	_long j = str.Length( ) - 1;

	if ( sensitive )
	{
		for ( ; i >= 0; i --, j -- )
		{
			if ( mString[i] != str[j] )
				return _false;

			if ( j == 0 )
				return _true;
		}
	}
	else
	{
		for ( ; i >= 0; i --, j -- )
		{
			if ( tolower2( mString[i] ) != tolower2( str[j] ) )
				return _false;

			if ( j == 0 )
				return _true;
		}
	}

	return _false;
}

_dword StringPtr::IndexOf( _char ch, _bool sensitive ) const
{
	if ( ch == 0 )
		return -1;

	if ( sensitive )
	{
		for ( _dword i = 0; mString[i] != 0; i ++ )
		{
			if ( mString[i] == ch )
				return i;
		}
	}
	else
	{
		ch = tolower2( ch );

		for ( _dword i = 0; mString[i] != 0; i ++ )
		{
			if ( tolower2( mString[i] ) == ch )
				return i;
		}
	}

	return -1;
}

_dword StringPtr::IndexOf( StringPtr str, _bool sensitive ) const
{
	if ( str == L"" )
		return -1;

	if ( sensitive )
	{
		for ( _dword i = 0; mString[i] != 0; i ++ )
		{
			if ( mString[i] != str[0] )
				continue;

			for ( _dword j = 1; 1; j ++ )
			{
				if ( str[j] == 0 )
					return i;

				if ( mString[i + j] == 0 )
					return -1;

				if ( mString[i + j] != str[j] )
					break;
			}
		}
	}
	else
	{
		for ( _dword i = 0; mString[i] != 0; i ++ )
		{
			if ( tolower2( mString[i] ) != tolower2( str[0] ) )
				continue;

			for ( _dword j = 1; 1; j ++ )
			{
				if ( str[j] == 0 )
					return i;

				if ( mString[i + j] == 0 )
					return -1;

				if ( tolower2( mString[i + j] ) != tolower2( str[j] ) )
					break;
			}
		}
	}

	return -1;
}

_dword StringPtr::LastIndexOf( _char ch, _bool sensitive ) const
{
	_dword len = Length( );

	if ( sensitive )
	{
		for ( _dword i = 0; i < len; i ++ )
		{
			if ( mString[ len - i - 1 ] == ch )
				return len - i - 1;
		}
	}
	else
	{
		ch = tolower2( ch );

		for ( _dword i = 0; i < len; i ++ )
		{
			if ( tolower2( mString[ len - i - 1 ] ) == ch )
				return len - i - 1;
		}
	}

	return -1;
}

_dword StringPtr::LastIndexOf( StringPtr str, _bool sensitive ) const
{
	_dword len1 = Length( ), len2 = str.Length( );

	if ( len1 < len2 )
		return -1;

	if ( sensitive )
	{
		for ( _dword i = 0; i <= len1 - len2; i ++ )
		{
			_bool match = _true;
			for ( _dword j = 0; j < len2; j ++ )
			{
				if ( mString[ len1 - len2 - i + j ] != str[j] )
					{ match = _false; break; }
			}

			if ( match )
				return len1 - len2 - i;
		}
	}
	else
	{
		for ( _dword i = 0; i <= len1 - len2; i ++ )
		{
			_bool match = _true;
			for ( _dword j = 0; j < len2; j ++ )
			{
				if ( tolower2( mString[ len1 - len2 - i + j ] ) != tolower2( str[j] ) )
					{ match = _false; break; }
			}

			if ( match )
				return len1 - len2 - i;
		}
	}

	return -1;
}

_long StringPtr::Compare( StringPtr str, _bool sensitive ) const
{
	return sensitive ? ::wcscmp( mString, str ) : ::wcsicmp( mString, str );
}

_bool StringPtr::SameAs( StringPtr str ) const
{
	return ::wcsicmp( mString, str ) == 0;
}