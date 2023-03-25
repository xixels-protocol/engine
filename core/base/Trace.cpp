#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "StringFormatter.h"
#include "StringEncoding.h"
#include "Trace.h"
#include "Time.hpp"

using namespace Xixels;

_bool Trace::sAutoEndLine = _true;
_bool Trace::sAutoTimestamp = _true;
_bool Trace::sTraceEnabled = _true;

_void* Trace::sTraceStringParam = _null;
_void* Trace::sTraceErrorParam = _null;

Trace::OnTraceString Trace::sTraceStringFunc = _null;
Trace::OnTraceError Trace::sTraceErrorFunc = _null;
Trace::OnTraceFinalize Trace::sTraceFinalizeFunc = _null;

#ifdef _TYPECHECKER_ENABLE
_void Trace::TraceStringHelper( const _char* format, ... )
#else
_void Trace::TraceString( const _char* format, ... )
#endif
{
	if ( !sTraceEnabled )
		return;

	_char buffer[8192];
	StringFormatter::FormatBufferV( buffer, 8192, format, (_chara*)( &format ) + sizeof( format ) );

	va_list alist;
	va_start( alist, format );

	::vswprintf( buffer, 8192, format, alist );

	va_end( alist );

	OnTraceString funcptr = sTraceStringFunc;
	_void* param = sTraceStringParam;

	if ( funcptr != _null )
	{
		if ( sAutoTimestamp )
		{
			_char buf[1024];
			Time t = Time::GetCurrentLocalTime( );
			(*funcptr)( StringFormatter::FormatBuffer( buf, 1024, L"%.4d/%.2d/%.2d-%.2d:%.2d:%.2d.%.3d ",
				t.year, t.month, t.day, t.hour, t.minute, t.second, t.millisecond ), param, _false );
		}

		(*funcptr)( buffer, param, sAutoEndLine );
	}

	_chara log[8192];
	StringEncoding::UCS2ToUTF8( log, 8192, buffer );
	if ( sAutoTimestamp )
	{
		Time t = Time::GetCurrentLocalTime( );
		::printf( "%.4d/%.2d/%.2d-%.2d:%.2d:%.2d.%.3d %s", t.year, t.month, t.day, t.hour, t.minute, t.second, t.millisecond, log );
	}
	else
	{
		::printf( "%s", log );
	}

	if ( sAutoEndLine )
		::printf( "\n" );
}

#ifdef _TYPECHECKER_ENABLE
_void Trace::TraceErrorHelper( const _char* format, ... )
#else
_void Trace::TraceError( const _char* format, ... )
#endif
{
	if ( !sTraceEnabled )
		return;

	_char buffer[8192];

	va_list alist;
	va_start( alist, format );

	::vswprintf( buffer, 8192, format, alist );

	va_end( alist );

	OnTraceString funcptr = sTraceErrorFunc;
	_void* param = sTraceErrorParam;

	_chara log[8192];
	StringEncoding::UCS2ToUTF8( log, 8192, buffer );
	if ( sAutoTimestamp )
	{
		Time t = Time::GetCurrentLocalTime( );
		::printf( "%.4d/%.2d/%.2d-%.2d:%.2d:%.2d.%.3d %s", t.year, t.month, t.day, t.hour, t.minute, t.second, t.millisecond, log );
	}
	else
	{
		::printf( "%s", log );
	}

	if ( sAutoEndLine )
		::printf( "\n" );

	if ( funcptr != _null )
	{
		if ( sAutoTimestamp )
		{
			Time t = Time::GetCurrentLocalTime( ); _char buffer[1024];
			(*funcptr)( StringFormatter::FormatBuffer( buffer, 1024, L"%.4d/%.2d/%.2d-%.2d:%.2d:%.2d.%.3d ",
				t.year, t.month, t.day, t.hour, t.minute, t.second, t.millisecond ), param, _false );
		}

		(*funcptr)( buffer, param, sAutoEndLine );
	}
}

_bool Trace::IsDefaultTargetPresent( )
{
	return _false;
}

_void Trace::SetDefaultTarget( )
{
	sTraceStringFunc = _null;
	sTraceStringParam = _null;
	sTraceErrorFunc = _null;
	sTraceErrorParam = _null;
	sTraceFinalizeFunc = _null;
}

_bool Trace::IsSameTarget( )
{
	return ( sTraceStringFunc == sTraceErrorFunc && sTraceStringParam == sTraceErrorParam );
}

_void Trace::TraceStringTime( )
{
	Time t = Time::GetCurrentLocalTime( );
	TraceString( L"[%ls]", (const _char*) t.ToString( ) );
}

_void Trace::TraceErrorTime( )
{
	Time t = Time::GetCurrentLocalTime( );
	TraceError( L"[%ls]", (const _char*) t.ToString( ) );
}