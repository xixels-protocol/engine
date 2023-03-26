#include "Typedef.h"
#include <time.h>
#include "StringFormatter.h"
#include "Time.hpp"

using namespace Xixels;

Time Time::GetCurrentLocalTime( )
{
	Time time;

	// TODO.

	return time;
}

Time Time::GetCurrentSystemTime( )
{
	Time time;

	// TODO.

	return time;
}

Time Time::GetSystemTime( _qword utc )
{
	return Time( utc );
}

Time Time::GetLocalTime( _qword local )
{
	return Time( local, _false );
}

_dword Time::GetCurrentTickcount( )
{
	// TODO.
	return 0;
}

_dword Time::GetElapsedSecondSinceUTC( )
{
	time_t tt = 0;
	::time( &tt );
	return (_dword) tt;
}

Time::Time( StringPtr str )
	: year( 0 ), month( 0 ), dayofweek( 0 ), day( 0 ), hour( 0 ), minute( 0 ), second( 0 ), millisecond( 0 )
{
	// Year.
	year = Short( str );

	_long index = -1;

	// Month.
	if ( ( index = str.IndexOf( '-' ) ) == -1 )
		return;

	str = StringPtr( (const _char*) str + index + 1 );
	month = Short( str );

	// Day.
	if ( ( index = str.IndexOf( '-' ) ) == -1 )
		return;

	str = StringPtr( (const _char*) str + index + 1 );
	day = Short( str );

	// Hour.
	if ( ( index = str.IndexOf( ' ' ) ) == -1 )
		return;

	str = StringPtr( (const _char*) str + index + 1 );
	hour = Short( str );

	// Minute.
	if ( ( index = str.IndexOf( ':' ) ) == -1 )
		return;

	str = StringPtr( (const _char*) str + index + 1 );
	minute = Short( str );

	// Second.
	if ( ( index = str.IndexOf( ':' ) ) == -1 )
		return;

	str = StringPtr( (const _char*) str + index + 1 );
	second = Short( str );
}

Time::Time( _large ms, _bool utc )
	: year( 0 ), month( 0 ), dayofweek( 0 ), day( 0 ), hour( 0 ), minute( 0 ), second( 0 ), millisecond( 0 )
{
	_large ss = ms / 1000;

	tm* tt = utc ? gmtime( (const time_t *) &ss ) : localtime( (const time_t *) &ss );
	if ( tt != _null )
	{
		year			= 1900 + (_short) tt->tm_year;
		month			= (_short) tt->tm_mon + 1;
		dayofweek		= (_short) tt->tm_wday;
		day				= (_short) tt->tm_mday;
		hour			= (_short) tt->tm_hour;
		minute			= (_short) tt->tm_min;
		second			= (_short) tt->tm_sec;
		millisecond		= ms % 1000;
	}
}

_bool Time::operator > ( const Time& time ) const
{
	if ( year > time.year )
		return _true;
	if ( year < time.year )
		return _false;

	if ( month > time.month )
		return _true;
	if ( month < time.month )
		return _false;

	if ( day > time.day )
		return _true;
	if ( day < time.day )
		return _false;

	if ( hour > time.hour )
		return _true;
	if ( hour < time.hour )
		return _false;

	if ( minute > time.minute )
		return _true;
	if ( minute < time.minute )
		return _false;

	if ( second > time.second )
		return _true;
	if ( second < time.second )
		return _false;

	return millisecond > time.millisecond;
}

_bool Time::operator < ( const Time& time ) const
{
	if ( year < time.year )
		return _true;
	if ( year > time.year )
		return _false;

	if ( month < time.month )
		return _true;
	if ( month > time.month )
		return _false;

	if ( day < time.day )
		return _true;
	if ( day > time.day )
		return _false;

	if ( hour < time.hour )
		return _true;
	if ( hour > time.hour )
		return _false;

	if ( minute < time.minute )
		return _true;
	if ( minute > time.minute )
		return _false;

	if ( second < time.second )
		return _true;
	if ( second > time.second )
		return _false;

	return millisecond < time.millisecond;
}

_bool Time::operator >= ( const Time& time ) const
{
	if ( year > time.year )
		return _true;
	if ( year < time.year )
		return _false;

	if ( month >= time.month )
		return _true;
	if ( month < time.month )
		return _false;

	if ( day > time.day )
		return _true;
	if ( day < time.day )
		return _false;

	if ( hour > time.hour )
		return _true;
	if ( hour < time.hour )
		return _false;

	if ( minute > time.minute )
		return _true;
	if ( minute < time.minute )
		return _false;

	if ( second > time.second )
		return _true;
	if ( second < time.second )
		return _false;

	return millisecond >= time.millisecond;
}

_bool Time::operator <= ( const Time& time ) const
{
	if ( year < time.year )
		return _true;
	if ( year > time.year )
		return _false;

	if ( month < time.month )
		return _true;
	if ( month > time.month )
		return _false;

	if ( day < time.day )
		return _true;
	if ( day > time.day )
		return _false;

	if ( hour < time.hour )
		return _true;
	if ( hour > time.hour )
		return _false;

	if ( minute < time.minute )
		return _true;
	if ( minute > time.minute )
		return _false;

	if ( second < time.second )
		return _true;
	if ( second > time.second )
		return _false;

	return millisecond <= time.millisecond;
}

String Time::ToString( ) const
{
	// Format time to string as "YYYY-MM-DD HH:MM:SS(MMMM)".
	return StringFormatter::FormatString( L"%.4d-%.2d-%.2d-%.2d-%.2d-%.2d(%.4d)",
		year, month, day, hour, minute, second, millisecond );
}

_large Time::ToLarge( _bool utc ) const
{
	tm tt;
	tt.tm_year	= year - 1900;
	tt.tm_mon	= month - 1;
	tt.tm_wday	= dayofweek;
	tt.tm_mday	= day;
	tt.tm_hour	= hour;
	tt.tm_min	= minute;
	tt.tm_sec	= second;

	if ( utc )
		return (_large) ::_mkgmtime( &tt ) * 1000 + millisecond;
	else
		return (_large) ::mktime( &tt ) * 1000 + millisecond;
}