#pragma once

#include "StringPtr.h"

namespace Xixels
{

class Oword;
class Qword;

class String : public StringPtr
{
private:
	_dword	mLength;
	_dword	mSize;

public:
	inline String( )
		: mLength( 0 ), mSize( 0 ) { }
	inline String( _char ch )
		: mLength( 0 ), mSize( 0 ) { Copy( ch ); }
	inline String( const _char* str, _dword length = -1 )
		: mLength( 0 ), mSize( 0 ) { Copy( str, length ); }
	inline String( StringPtr str, _dword length = -1 )
		: mLength( 0 ), mSize( 0 ) { Copy( str, length ); }
	inline String( const String& str )
		: mLength( 0 ), mSize( 0 ) { Copy( str, str.mLength ); }
	inline ~String( )
		{ FreeBuffer( ); }

	String( const Oword& oword );
	String( const Qword& qw );

private:
	_void AllocBuffer( _dword length );
	_void FreeBuffer( );

public:
	inline _char& operator [] ( _long index )
		{ return mString[ index ]; }
	inline _char& operator [] ( _dword index )
		{ return mString[ index ]; }

	inline _dword Length( ) const
		{ return mLength; }
	inline _dword SizeOfBytes( ) const
		{ return ( mLength + 1 ) * sizeof( _char ); }

	inline const _char* operator * ( ) const
		{ return mLength ? this->mString : L""; }
	inline String& operator = ( _char ch )
		{ Copy( ch ); return *this; }
	inline String& operator = ( const _char* str )
		{ Copy( str ); return *this; }
	inline String& operator = ( StringPtr str )
		{ Copy( str ); return *this; }
	inline String& operator = ( const String& str )
		{ Copy( str, str.mLength ); return *this; }

	inline String& operator += ( _char ch )
		{ Insert( mLength, ch ); return *this; }
	inline String& operator += ( const _char* str )
		{ Insert( mLength, str ); return *this; }
	inline String& operator += ( StringPtr str )
		{ Insert( mLength, str ); return *this; }
	inline String& operator += ( const String& str )
		{ Insert( mLength, str, str.mLength ); return *this; }

	inline String& TrimBoth( _char ch )
		{ TrimLeft( ch ); TrimRight( ch ); return *this; }
	inline String& TrimBoth( StringPtr chset )
		{ TrimLeft( chset ); TrimRight( chset ); return *this; }

	inline String SubString( _dword start, _dword length ) const
		{ return start >= mLength ? L"" : String( mString + start, start + length > mLength ? -1 : length ); }

	inline String SubStringLeft( _char d ) const
		{ _dword index = IndexOf( d ); return index == -1 ? *this : String( mString, index ); }
	inline String SubStringLeft( StringPtr d ) const
		{ _dword index = IndexOf( d ); return index == -1 ? *this : String( mString, index ); }

	inline String SubStringRight( _char d ) const
		{ _dword index = LastIndexOf( d ); return index == -1 ? *this : String( mString + index + 1, mLength - index - 1 ); }
	inline String SubStringRight( StringPtr d ) const
		{ _dword index = LastIndexOf( d ); return index == -1 ? *this : String( mString + index + 1, mLength - index - 1 ); }

	String&	Empty( );
	String&	ToLower( );
	String&	ToUpper( );

	String&	Copy( _char ch );
	String&	Copy( StringPtr str, _dword length = -1 );

	String&	Insert( _dword index, _char ch );
	String&	Insert( _dword index, StringPtr str, _dword length = -1 );

	String&	Remove( _dword index, _dword length = -1 );

	String&	Replace( _char oldch, _char newch, _bool sensitive = _true );
	String&	Replace( StringPtr oldstr, StringPtr newstr, _bool sensitive = _true );

	String&	TrimLeft( _char ch, _bool sensitive = _true );
	String&	TrimRight( _char ch, _bool sensitive = _true );

	String&	TrimLeft( StringPtr chset, _bool sensitive = _true );
	String&	TrimRight( StringPtr chset, _bool sensitive = _true );
};

class StringBuffer
{
private:
	static StringBuffer* sUsingBuffer;

	enum { _MAX_BUFFER_LENGTH = 1024 };
	enum { _MAX_BUFFER_COUNT = 64 };

	_char*	mBuffers[ _MAX_BUFFER_COUNT ];
	_dword	mBufferIndex;
	_dword	mBufferOffset;

public:
	StringBuffer( );
	~StringBuffer( );

	static StringBuffer* GetUsingBuffer( );

	static _char* BufferAlloc( _dword length );

	_void EnableBuffer( );
	_void DisableBuffer( );
	_void ResetBuffer( );
};

class StringBufferUser
{
private:
	StringBuffer&	mBuffer;

public:
	inline StringBufferUser( StringBuffer& buffer, _bool reset = _false ) : mBuffer( buffer )
		{ if ( reset ) mBuffer.ResetBuffer( ); mBuffer.EnableBuffer( ); }
	inline ~StringBufferUser( )
		{ mBuffer.DisableBuffer( ); }
};

inline String operator + ( const String& str, _char ch )
	{ String ret = str; return ret += ch; }
inline String operator + ( const String& str1, const _char* str2 )
	{ String ret = str1; return ret += str2; }
inline String operator + ( const String& str1, StringPtr str2 )
	{ String ret = str1; return ret += (const _char*) str2; }
inline String operator + ( const String& str1, const String& str2 )
	{ String ret = str1; return ret += str2; }

inline String operator + ( _char ch, const String& str )
	{ String ret = ch; return ret += str; }
inline String operator + ( const _char* str1, const String& str2 )
	{ String ret = str1; return ret += str2; }
inline String operator + ( StringPtr str1, const String& str2 )
	{ String ret = str1; return ret += str2; }

};