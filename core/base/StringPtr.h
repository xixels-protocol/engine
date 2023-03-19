#pragma once

#include <string.h>
#include "Typedef.h"

namespace Xixels
{

_char tolower2( _char a )	{ return ( a >= 'A' && a <= 'Z' ) ? a + 'a' - 'A' : a; }
_char toupper2( _char a )	{ return ( a >= 'a' && a <= 'z' ) ? a - 'a' + 'A' : a; }
_chara tolower2( _chara a )	{ return ( a >= 'A' && a <= 'Z' ) ? a + 'a' - 'A' : a; }
_chara toupper2( _chara a )	{ return ( a >= 'a' && a <= 'z' ) ? a - 'a' + 'A' : a; }

class StringPtr
{
public:
	static _dword	Length( const _char* str );
	static _char*	Copy( _char* buffer, const _char* str, _dword length = -1 );
	static _char*	Append( _char* buffer, const _char* str, _dword length = -1 );
	static _char*	ToLower( _char* buffer );
	static _char*	ToUpper( _char* buffer );
	static _char*	Find( _char* buffer, const _char* str );
	static _bool	IsPunct( _char ch );

	static _dword	Length( const _chara* str );
	static _chara*	Copy( _chara* buffer, const _chara* str, _dword length = -1 );
	static _chara*	Append( _chara* buffer, const _chara* str, _dword length = -1 );
	static _chara*	ToLower( _chara* buffer );
	static _chara*	ToUpper( _chara* buffer );
	static _long	Compare( const _chara* str1, const _chara* str2, _bool sensitive = _true );
	static _chara*	Find( _chara* buffer, const _chara* str );
	static _bool	IsPunct( _chara ch );

protected:
	_char*	mString;

public:
	inline StringPtr( )
		: mString( (_char*) L"" ) { }
	inline StringPtr( const _char* str )
		: mString( (_char*) ( str != _null ? str : L"" ) ) { }

	inline operator const _char* ( ) const
		{ return mString; }
	inline _char operator [] ( _long index ) const
		{ return mString[ index ]; }
	inline _char operator [] ( _dword index ) const
		{ return mString[ index ]; }

	inline operator _dword ( ) const
		{ return HashCode1( ); }

	inline StringPtr SubStringPtr( _dword index ) const
		{ return StringPtr( mString + index ); }

	_dword	Length( ) const;
	_dword	SizeOfBytes( ) const;
	_bool	IsBlank( ) const;

	_dword	HashCode1( ) const;
	_dword	HashCode2( ) const;
	_dword	HashCode3( ) const;

	_bool	StartOf( _char ch, _bool sensitive = _true ) const;
	_bool	StartOf( StringPtr str, _bool sensitive = _true ) const;
	_bool	EndOf( StringPtr str, _bool sensitive = _true ) const;

	_dword	IndexOf( _char ch, _bool sensitive = _true ) const;
	_dword	IndexOf( StringPtr str, _bool sensitive = _true ) const;

	_dword	LastIndexOf( _char ch, _bool sensitive = _true ) const;
	_dword	LastIndexOf( StringPtr str, _bool sensitive = _true ) const;

	_long	Compare( StringPtr str, _bool sensitive = _true ) const;
	_bool	SameAs( StringPtr str ) const;
};

inline _bool operator == ( StringPtr str1, StringPtr str2 )
	{ return str1.Compare( str2 ) == 0; }
inline _bool operator != ( StringPtr str1, StringPtr str2 )
	{ return str1.Compare( str2 ) != 0; }
inline _bool operator > ( StringPtr str1, StringPtr str2 )
	{ return str1.Compare( str2 ) > 0; }
inline _bool operator < ( StringPtr str1, StringPtr str2 )
	{ return str1.Compare( str2 ) < 0; }
inline _bool operator >= ( StringPtr str1, StringPtr str2 )
	{ return str1.Compare( str2 ) >= 0; }
inline _bool operator <= ( StringPtr str1, StringPtr str2 )
	{ return str1.Compare( str2 ) <= 0; }

inline _bool operator == ( StringPtr str1, const _char* str2 )
	{ return str1.Compare( str2 ) == 0; }
inline _bool operator != ( StringPtr str1, const _char* str2 )
	{ return str1.Compare( str2 ) != 0; }
inline _bool operator > ( StringPtr str1, const _char* str2 )
	{ return str1.Compare( str2 ) > 0; }
inline _bool operator < ( StringPtr str1, const _char* str2 )
	{ return str1.Compare( str2 ) < 0; }
inline _bool operator >= ( StringPtr str1, const _char* str2 )
	{ return str1.Compare( str2 ) >= 0; }
inline _bool operator <= ( StringPtr str1, const _char* str2 )
	{ return str1.Compare( str2 ) <= 0; }

inline _bool operator == ( const _char* str1, StringPtr str2 )
	{ return StringPtr( str1 ).Compare( str2 ) == 0; }
inline _bool operator != ( const _char* str1, StringPtr str2 )
	{ return StringPtr( str1 ).Compare( str2 ) != 0; }
inline _bool operator > ( const _char* str1, StringPtr str2 )
	{ return StringPtr( str1 ).Compare( str2 ) > 0; }
inline _bool operator < ( const _char* str1, StringPtr str2 )
	{ return StringPtr( str1 ).Compare( str2 ) < 0; }
inline _bool operator >= ( const _char* str1, StringPtr str2 )
	{ return StringPtr( str1 ).Compare( str2 ) >= 0; }
inline _bool operator <= ( const _char* str1, StringPtr str2 )
	{ return StringPtr( str1 ).Compare( str2 ) <= 0; }

};