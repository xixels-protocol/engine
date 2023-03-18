#pragma once

#include "../base/Typedef.h"
#include <math.h>

namespace Xixels
{

class Math
{
public:
	// 0.0f
	const static _float cZero;
	// 1.0f
	const static _float cOne;
	// The ratio of a circle's circumference to its diameter.
	const static _float cPi;
	// Double of the ratio of a circle's circumference to its diameter.
	const static _float c2Pi;
	const static _float cPiOver2;
	const static _float cPiOver4;
	// The base of the natural system of logarithms (e).
	const static _float cE;
	// The epsilon value for float value comparison.
	const static _float cEpsilon;
	// The maximum float value.
	const static _float	cMaxFloat;
	// The minimum float value.
	const static _float	cMinFloat;
	// The minimum low precision float value.
	const static _float	cMinLowpFloat;
	// The maximum low precision float value.
	const static _float	cMaxLowpFloat;
	// The minimum medium precision float value.
	const static _float	cMinMediumFloat;
	// The maximum medium precision float value.
	const static _float	cMaxMediumFloat;

	// The maximum tiny value.
	const static _tiny	cMaxTiny	= 127;
	// The minimum tiny value.
	const static _tiny	cMinTiny	= -128;
	// The maximum byte value.
	const static _byte	cMaxByte	= 0xFF;
	// The minimum tiny value.
	const static _byte	cMinByte	= 0x00;
	// The maximum short value.
	const static _short	cMaxShort	= 32767;
	// The minimum short value.
	const static _short	cMinShort	= -32768;
	// The maximum word value.
	const static _word	cMaxWord	= 0xFFFF;
	// The minimum word value.
	const static _word	cMinWord	= 0x0000;
	// The maximum long value.
	const static _long	cMaxLong	= 2147483647;
	// The minimum long value.
	const static _long	cMinLong	= -2147483647-1;
	// The maximum word value.
	const static _dword	cMaxDword	= 0xFFFFFFFF;
	// The minimum word value.
	const static _dword	cMinDword	= 0x00000000;

public:
	// Calculates the absolute value.
	template < typename Type >
	inline static Type Abs( Type value )
		{ return value >= 0 ? value : -value; }

	// Compares two arguments and returns the larger one.
	template < typename Type >
	inline static Type Max( Type value1, Type value2 )
		{ return value1 >= value2 ? value1 : value2; }

	// Compares two arguments and returns the smaller one.
	template < typename Type >
	inline static Type Min( Type value1, Type value2 )
		{ return value1 < value2 ? value1 : value2; }

	// Swap two arguments.
	template < typename Type >
	inline static _void Swap( Type& value1, Type& value2 )
		{ Type temp = value1; value1 = value2; value2 = temp; }

	// Clamp value into the range specified by min and max.
	template < typename Type >
	inline static Type Clamp( Type value, Type min, Type max )
		{ if ( value < min ) value = min; if ( value > max ) value = max; return value; }

	// Calculates linear interpolation of two values.
	template < typename Type >
	inline static Type Lerp( Type value1, Type value2, _float factor )
		{ return value1 + ( value2 - value1 ) * Clamp( factor, 0.0f, 1.0f ); }

	// Converts radian to degree.
	inline static _float Radian2Degree( _float radian )
		{ return radian / cPi * 180.0f; }
	// Converts degree to radian.
	inline static _float Degree2Radian( _float degree )
		{ return degree / 180.0f * cPi; }

	// Wrap an angle in range -pi...pi by adding the correct multiple of 2 pi.
	inline static _float WrapPi( _float radian )
		{ radian += cPi; radian -= Floor( radian / c2Pi ) * c2Pi; radian += cPi; return radian; }

	// Test if two lines parallel.
	template < typename Type >
	inline static _bool Parallel( Type x1, Type y1, Type x2, Type y2, Type x3, Type y3, Type x4, Type y4 )
	{
		return (_float) Abs( ( x1 - x2 ) * ( y3 - y4 ) - ( x3 - x4 ) * ( y1 - y2 ) ) < cEpsilon;
	}

	// Get the projection if a point to a line.
	template < typename Type >
	inline static Type PointOnLine( Type x1, Type y1, Type x2, Type y2, Type x0, Type y0, Type& x, Type& y )
	{
		_double px = x2 - x1;
		_double py = y2 - y1;
		_double m  = px * px + py * py;
		_double u  = ( ( x0 - x1 ) * px + ( y0 - y1 ) * py ) / m;

		if ( u > 1.0 )
			u = 1.0;
		if ( u < 0.0 )
			u = 0.0;

		_double xx = x1 + u * px;
		_double yy = y1 + u * py;

		_double dx = xx - x0;
		_double dy = yy - y0;

		x = (Type) xx;
		y = (Type) yy;

		// No need to set sqrt value for now.
		return (Type) ( dx * dx + dy * dy );
	}

	// Test if a point on left side or right side of a line.
	template < typename Type >
	inline static _long PointVSLine( Type x1, Type y1, Type x2, Type y2, Type x0, Type y0 )
	{
		x1 -= x0; y1 -= y0; x2 -= x0; y2 -= y0;

		_double ret = x1 * y2 - y1 * x2;

		if ( ret > Math::cEpsilon )
			return 1;
		if ( ret < -Math::cEpsilon )
			return -1;

		return 0;
	}

	// Test if two lines intersect.
	template < typename Type >
	inline static _bool LineVSLine( Type x1, Type y1, Type x2, Type y2, Type x3, Type y3, Type x4, Type y4, Type* x0 = _null, Type* y0 = _null )
	{
		if ( Parallel( x1, y1, x2, y2, x3, y3, x4, y4 ) )
			return _false;

		if ( PointVSLine( x1, y1, x2, y2, x3, y3 ) * PointVSLine( x1, y1, x2, y2, x4, y4 ) > 0 )
			return _false;

		if ( PointVSLine( x3, y3, x4, y4, x1, y1 ) * PointVSLine( x3, y3, x4, y4, x2, y2 ) > 0 )
			return _false;

		if ( x0 != _null && y0 != _null )
		{
			_double p1 = ( x1 - x3 ) * ( y3 - y4 ) - ( y1 - y3 ) * ( x3 - x4 );
			_double p2 = ( x1 - x2 ) * ( y3 - y4 ) - ( y1 - y2 ) * ( x3 - x4 );
			_double p  = p1 / p2;

			*x0 = (Type) ( x1 + ( x2 - x1 ) * p );
			*y0 = (Type) ( y1 + ( y2 - y1 ) * p );
		}

		return _true;
	}

	// Test if a point and a line intersect. The function also returns true if the point is one of the ends of the line segment.
	template < typename Type >
	inline static _bool Intersect( Type x1, Type y1, Type x2, Type y2, Type x0, Type y0 )
	{
		return Math::PointVSLine( x1, y1, x2, y2, x0, y0 ) == 0 && ( x0 - x1 ) * ( x0 - x2 ) <= 0 && ( y0 - y1 ) * ( y0 - y2 ) <= 0;
	}

	// Test if two lines intersect. The function also returns true if two lines are overlapped or some parts of them are overlapped.
	template < typename Type >
	inline static _bool Intersect( Type x1, Type y1, Type x2, Type y2, Type x3, Type y3, Type x4, Type y4 )
	{
		return Math::Max( x1, x2 ) >= Math::Min( x3, x4 ) &&
			Math::Max( x3, x4 ) >= Math::Min( x1, x2 ) &&
			Math::Max( y1, y2 ) >= Math::Min( y3, y4 ) &&
			Math::Max( y3, y4 ) >= Math::Min( y1, y2 ) &&
			Math::PointVSLine( x1, y1, x2, y2, x3, y3 ) * Math::PointVSLine( x1, y1, x2, y2, x4, y4 ) <= 0 &&
			Math::PointVSLine( x3, y3, x4, y4, x1, y1 ) * Math::PointVSLine( x3, y3, x4, y4, x2, y2 ) <= 0;
	}

	// Calculates the ceiling of a value.
	static _float	Ceil( _float value );
	static _double	CeilD( _double value );
	// Calculates the floor of a value.
	static _float	Floor( _float value );
	static _double	FloorD( _double value );
	// Calculates the round of a value.
	static _float	Round( _float value );
	static _double	RoundD( _double value );
	// Calculates the floating-point remainder.
	static _float	Fmod( _float valuex, _float valuey );
	static _double	FmodD( _double valuex, _double valuey );

	// Calculates the square root.
	static _float	Sqrt( _float value );
	static _double	SqrtD( _double value );
	// Calculates the exponential.
	static _float	Exp( _float value );
	static _double	ExpD( _double value );
	// Calculates logarithms.
	static _float	Log( _float value );
	static _double	LogD( _double value );
	// Calculates base raised to the power of exponent.
	static _float	Pow( _float base, _float exponent );
	static _double	PowD( _double base, _double exponent );
	// Decompose a floating-point number into integral and fractional parts.
	static _void	Modf( _double number, _long& ipart, _double& fpart );
	// Check if an interger is power of two.
	static _bool	IsPowerOfTwo( _dword number );
	// Get next power of two.
	static _dword	NextPowerOfTwo( _dword number );
	// Align value to be a multiple of alignment. alignment must be power of two.
	static _dword	Align( _dword value, _dword alignment );

	// Calculate the sine.
	static _float	Sin( _float radian );
	static _double	SinD( _double radian );
	// Calculate the cosine.
	static _float	Cos( _float radian );
	static _double	CosD( _double radian );
	// Calculate the tangent.
	static _float	Tan( _float radian );
	static _double	TanD( _double radian );
	// Calculate the cotangent.
	static _float	Cot( _float radian );
	static _double	CotD( _double radian );
	// Calculates the arcsine.
	static _float	Asin( _float value );
	static _double	AsinD( _double radian );
	// Calculates the arccosine.
	static _float	Acos( _float value );
	static _double	AcosD( _double value );
	// Calculates the arctangent.
	static _float	Atan( _float value );
	static _double	AtanD( _double value );
	// Calculates the arctangent.
	static _float	Atan( _float valuey, _float valuex );
	static _double	AtanD( _double valuey, _double valuex );
	// Equality judgement.
	static _bool	Equal( _float valuex, _float valuey, _float margin = cEpsilon );
	static _bool	EqualD( _double valuex, _double valuey, _double margin = cEpsilon );
};

};