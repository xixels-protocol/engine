#include "StringFormatter.h"
#include "Trace.h"

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>

using namespace Xixels;

#ifdef _TYPECHECKER_ENABLE
String StringFormatter::FormatStringHelper( const _char* format, ... )
#else
String StringFormatter::FormatString( const _char* format, ... )
#endif
{
	assert( format != _null );

	_char buffer[8192];

	va_list alist;
	va_start( alist, format );

	::vswprintf( buffer, 8192, format, alist );

	va_end( alist );

	buffer[8191] = 0;

	return String( buffer );
}

#ifdef _TYPECHECKER_ENABLE
StringPtr StringFormatter::FormatBufferHelper( _char* buffer, _dword length, const _char* format, ... )
#else
StringPtr StringFormatter::FormatBuffer( _char* buffer, _dword length, const _char* format, ... )
#endif
{
	assert( buffer != _null && length != 0 && format != _null );

	va_list alist;
	va_start( alist, format );

	::vswprintf( buffer, 8192, format, alist );

	va_end( alist );

	buffer[ length - 1 ] = 0;

	return StringPtr( buffer );
}

String StringFormatter::FormatStringV( const _char* format, const _void* arguments )
{
	assert( format != _null && arguments != _null );

	_char buffer[8192];

	va_list alist;
	Memory::MemCpy( &alist, arguments, sizeof( alist ) );
	::vswprintf( buffer, 8192, format, alist );

	buffer[8191] = 0;

	return String( buffer );
}

StringPtr StringFormatter::FormatBufferV( _char* buffer, _dword length, const _char* format, const _void* arguments )
{
	assert( buffer != _null && length != 0 && format != _null && arguments != _null );

	va_list alist;
	Memory::MemCpy( &alist, arguments, sizeof( alist ) );
	::vswprintf( buffer, length, format, alist );

	buffer[ length - 1 ] = 0;

	return StringPtr( buffer );
}

String StringFormatter::FormatBytes( _qword bytes )
{
	if ( bytes >= 1000 * 1024 * 1024 )
		return FormatString( L"%3.2f GB", (_float) bytes / 1024.0f / 1024.0f / 1024.0f );
	else if ( bytes >= 1000 * 1024 )
		return FormatString( L"%3.2f MB", (_float) bytes / 1024.0f / 1024.0f );
	else
		return FormatString( L"%3.2f KB", (_float) bytes / 1024.0f );
}

String StringFormatter::FormatNumber( _dword number )
{
	// Max value 4294967295 => 4,294,967,295

	_dword a = number / 1000000000;
	_dword b = ( number % 1000000000 ) / 1000000;
	_dword c = ( number % 1000000 ) / 1000;
	_dword d = number % 1000;

	if ( a > 0 )
		return FormatString( L"%d,%.3d,%.3d,%.3d", a, b, c, d );
	else if ( b > 0 )
		return FormatString( L"%d,%.3d,%.3d", b, c, d );
	else if ( c > 0 )
		return FormatString( L"%d,%.3d", c, d );
	else
		return FormatString( L"%d", d );
}

String StringFormatter::FormatTime( _dword millisecond )
{
	_dword hourunit = 60 * 60 * 1000, minuteunit = 60 * 1000, secondunit = 1000;

	_dword hours	= millisecond / hourunit;
	_dword minutes	= ( millisecond - hours * hourunit ) / minuteunit;
	_dword seconds	= ( millisecond - hours * hourunit - minutes* minuteunit ) / secondunit;

	return FormatString( L"%.3d:%.2d:%.2d", hours, minutes, seconds );
}

_void StringFormatter::SplitString( StringPtr source, Array< String >& output, StringPtr division, StringPtr trim )
{
	assert( division != L"" );

	_long length = source.Length( ), start = -1;

	for ( _long i = 0; i < length; i ++ )
	{
		if ( division.IndexOf( source[i] ) == -1 )
		{
			// Start of a string.
			if ( start == -1 )
				start = i;
		}
		else
		{
			// End of a string.
			if ( start != -1 )
			{
				// Build candidate string.
				String candidate( (const _char*) source + start, i - start );

				// Trim candidate string.
				candidate.TrimBoth( trim );

				// It is valid string, can be part of output.
				output.Add( candidate );

				start = -1;
			}
			else
			{
				output.Add( L"" );
			}
		}
	}

	// End of a string.
	if ( start != -1 )
	{
		// Build candidate string.
		String candidate( (const _char*) source + start );

		// Trim candidate string.
		candidate.TrimBoth( trim );

		// It is valid string, can be part of output.
		if ( candidate.Length( ) > 0 )
			output.Add( candidate );
	}
	else
	{
		output.Add( L"" );
	}
}