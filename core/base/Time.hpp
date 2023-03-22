#pragma once

#include "String.hpp"

namespace Xixels
{

class Time
{
public:
	enum _DAY_OF_WEEK
	{
		_SUNDAY		= 0,
		_MONDAY		= 1,
		_TUESDAY	= 2,
		_WEDNESDAY	= 3,
		_THURSDAY	= 4,
		_FRIDAY		= 5,
		_SATURDAY	= 6,
	};

	static Time		GetCurrentLocalTime( );
	static Time		GetCurrentSystemTime( );
	static Time		GetSystemTime( _qword utc );
	static Time		GetLocalTime( _qword local );
	static _dword	GetCurrentTickcount( );
	static _dword	GetElapsedSecondSinceUTC( );

public:
	_short	year;
	_short	month;
	_short	dayofweek;
	_short	day;
	_short	hour;
	_short	minute;
	_short	second;
	_short	millisecond;

public:
	inline Time( )
		: year( 0 ), month( 0 ), dayofweek( 0 ), day( 0 ), hour( 0 ), minute( 0 ), second( 0 ), millisecond( 0 ) { }

	Time( StringPtr str );
	Time( _large ms, _bool utc = _true );

	inline _bool operator == ( const Time& time ) const
	{
		return	year == time.year && month == time.month && day == time.day && hour == time.hour &&
				minute == time.minute && second == time.second && millisecond == time.millisecond;
	}

	inline _bool operator != ( const Time& time ) const
	{
		return	year != time.year || month != time.month || day != time.day || hour != time.hour ||
				minute != time.minute || second != time.second || millisecond != time.millisecond;
	}

	_bool operator >  ( const Time& time ) const;
	_bool operator <  ( const Time& time ) const;
	_bool operator >= ( const Time& time ) const;
	_bool operator <= ( const Time& time ) const;

	String	ToString( ) const;
	_large	ToLarge( _bool utc = _true ) const;
};

};