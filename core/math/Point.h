#pragma once

#include "Math.h"

namespace Xixels
{

class Point
{
public:
	const static Point cZeroPoint;
	const static Point cMaxPoint;
	const static Point cMinPoint;
	const static Point cInvalidPoint;

public:
	_long	x;
	_long	y;

public:
	inline Point( )
		{ }
	inline Point( _long xx, _long yy )
		: x( xx ), y( yy ) { }

	inline Point operator + ( ) const
		{ return Point( x, y ); }
	inline Point operator - ( ) const
		{ return Point( -x, -y ); }

	inline Point& operator += ( const Point& pt )
		{ x += pt.x; y += pt.y; return *this; }
	inline Point& operator -= ( const Point& pt )
		{ x -= pt.x; y -= pt.y; return *this; }

	inline Point operator + ( const Point& pt ) const
		{ return Point( x + pt.x, y + pt.y ); }
	inline Point operator - ( const Point& pt ) const
		{ return Point( x - pt.x, y - pt.y ); }

	inline Point& operator *= ( _long s )
		{ x *= s; y *= s; return *this; }
	inline Point& operator /= ( _long s )
		{ x /= s; y /= s; return *this; }

	inline Point operator * ( _long s ) const
		{ return Point( x * s, y * s ); }
	inline Point operator / ( _long s ) const
		{ return Point( x / s, y / s ); }

	inline _bool operator == ( const Point& pt ) const
		{ return x == pt.x && y == pt.y; }
	inline _bool operator != ( const Point& pt ) const
		{ return x != pt.x || y != pt.y; }
};

};