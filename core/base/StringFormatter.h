#pragma once

#include "String.hpp"
#include "Array.h"

namespace Xixels
{

class StringFormatter
{
public:
	#ifdef _TYPECHECKER_ENABLE

	static String		FormatStringHelper( const _char* format, ... );
	static StringPtr	FormatBufferHelper( _char* buffer, _dword length, const _char* format, ... );

	inline static _void Checker( ) { }

	template < typename T, typename ...Args >
	inline static _void Checker( T head, Args... rest )
	{
		static_assert( TypeChecker< T >::Value, "Unsupport Type!" );
		Checker( rest... );
	}

	// Multiversion of FormatString with different number of param.
	template < typename ...Args >
	inline static String FormatString( const _char* format, Args... args )
	{
		Checker( args... );
		return FormatStringHelper( format, args... );
	}

	// Multiversion of FormatBuffer with different number of param.
	template < typename ...Args >
	inline static StringPtr FormatBuffer( _char* buffer, _dword length, const _char* format, Args... args )
	{
		Checker( args... );
		return FormatBufferHelper( buffer, length, format, args... );
	}

	#else

	static String		FormatString( const _char* format, ... );
	static StringPtr	FormatBuffer( _char* buffer, _dword length, const _char* format, ... );

	#endif

	static String		FormatStringV( const _char* format, const _void* arguments );
	static StringPtr	FormatBufferV( _char* buffer, _dword length, const _char* format, const _void* arguments );

	static String		FormatBytes( _qword bytes );
	static String		FormatNumber( _dword number );
	static String		FormatTime( _dword millisecond );

	static _void		SplitString( StringPtr source, Array< String >& output, StringPtr division = L"\r\n", StringPtr trim = L" \t" );

};

};