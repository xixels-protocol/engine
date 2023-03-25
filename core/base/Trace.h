#pragma once

#include "Array.h"
#include "DataType.h"

namespace Xixels
{

class Trace
{
public:
	// Trace a string to target function prototype.
	typedef _void (*OnTraceString)( const _char* string, _void* param, _bool autoendline );
	// Trace an error to target function prototype.
	typedef _void (*OnTraceError)( const _char* error, _void* param, _bool autoendline );
	// Finalize trace.
	typedef _void (*OnTraceFinalize)( );

private:
	static _bool			sAutoEndLine;
	static _bool			sAutoTimestamp;
	static _bool			sTraceEnabled;

	static _void*			sTraceStringParam;
	static _void*			sTraceErrorParam;

	static OnTraceString	sTraceStringFunc;
	static OnTraceError		sTraceErrorFunc;
	static OnTraceFinalize	sTraceFinalizeFunc;

public:
	inline static _void EnableAutoEndLine( _bool enable )
		{ sAutoEndLine = enable; }
	inline static _void EnableAutoTimestamp( _bool enable )
		{ sAutoTimestamp = enable; }
	inline static _void EnableTrace( _bool enable )
		{ sTraceEnabled = enable; }
	inline static _bool IsTraceEnabled( )
		{ return sTraceEnabled; }

	inline static _void SetTraceStringParam( _void* param )
		{ sTraceStringParam = param; }
	inline static _void* GetTraceStringParam( )
		{ return sTraceStringParam; }

	inline static _void SetTraceErrorParam( _void* param )
		{ sTraceErrorParam = param; }
	inline static _void* GetTraceErrorParam( )
		{ return sTraceErrorParam; }

	inline static _void SetTraceStringCallback( OnTraceString functpr )
		{ sTraceStringFunc = functpr; }
	inline static OnTraceString GetTraceStringCallback( )
		{ return sTraceStringFunc; }

	inline static _void SetTraceErrorCallback( OnTraceError functpr )
		{ sTraceErrorFunc = functpr; }
	inline static OnTraceError GetTraceErrorCallback( )
		{ return sTraceErrorFunc; }

	inline static _void SetTraceFinalizeCallback( OnTraceFinalize functpr )
		{ sTraceFinalizeFunc = functpr; }
	inline static OnTraceFinalize GetTraceFinalizeCallback( )
		{ return sTraceFinalizeFunc; }

	#ifdef _TYPECHECKER_ENABLE

	static _void	TraceStringHelper( const _char* format, ... );
	static _void	TraceErrorHelper( const _char* format, ... );

	inline static _void Checker( ) { }

	template < typename T, typename ...Args >
	inline static _void Checker( T head, Args... rest )
	{
		static_assert( TypeChecker< T >::Value, "Unsupport Type!" );
		Checker( rest... );
	}

	// Trace string with param(s).
	template < typename ...Args >
	inline static _void TraceString( const _char* format, Args... args )
	{
		Checker( args... );
		return TraceStringHelper( format, args... );
	}

	template < typename ...Args >
	inline static _void TraceError( const _char* format, Args... args )
	{
		Checker( args... );
		return TraceErrorHelper( format, args... );
	}

	#else

	static _void	TraceString( const _char* format, ... );
	static _void	TraceError( const _char* format, ... );

	#endif

	// Get if default trace target ( IDE output ) present.
	static _bool	IsDefaultTargetPresent( );
	// Set to default trace target.
	static _void	SetDefaultTarget( );
	// Get if same trace target.
	static _bool	IsSameTarget( );

	// Trace string time.
	static _void	TraceStringTime( );

	// Trace error time.
	static _void	TraceErrorTime( );
};

#ifdef _TRACE_ENABLE
	#define XX_LOG( x, ... ) \
		{ \
			Trace::TraceString( x, ##__VA_ARGS__ ); \
		}
	#define XX_TRACETIME( ) \
		{ \
			Trace::TraceStringTime( ); \
		}
	#define XX_TRACELINE( ) \
		{ \
			Trace::TraceString( L"" ); \
		}

	#define XX_ERROR( x, ... ) \
		{ \
			Trace::TraceError( x, ##__VA_ARGS__ ); \
		}
	#define XX_ERRORTIME( ) \
		{ \
			Trace::TraceErrorTime( ); \
		}
	#define XX_ERRORLINE( ) \
		{ \
			Trace::TraceError( L"" ); \
		}

	#define XX_LOG2( x, ... ) \
		{ \
			Trace::TraceString( x, ##__VA_ARGS__ ); \
			if ( !Trace::IsSameTarget( ) ) \
				Trace::TraceError( x, ##__VA_ARGS__ ); \
		}
	#define XX_TRACEBOTHTIME( ) \
		{ \
			Trace::TraceStringTime( ); \
			Trace::TraceErrorTime( ); \
		}
	#define XX_TRACEBOTHLINE( ) \
		{ \
			Trace::TraceString( L"" ); \
			Trace::TraceError( L"" ); \
		}
	
#else

	#define XX_LOG( x, ... ) \
		{ \
		}
	#define XX_TRACETIME( ) \
		{ \
		}
	#define XX_TRACELINE( ) \
		{ \
		}

	#define XX_ERROR( x ) \
		{ \
		}
	#define XX_ERRORTIME( ) \
		{ \
		}
	#define XX_ERRORLINE( ) \
		{ \
		}
	
	#define XX_LOG2( x, ... ) \
		{ \
		}
	#define XX_TRACEBOTHTIME( ) \
		{ \
		}
	#define XX_TRACEBOTHLINE( ) \
		{ \
		}

#endif

};