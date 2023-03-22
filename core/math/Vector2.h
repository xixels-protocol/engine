#pragma once

#include "Math.hpp"

namespace Xixels
{

class Matrix2;
class Matrix3;

class Vector2
{
public:
	const static Vector2 cOrigin;
	const static Vector2 cIdentity;
	const static Vector2 cXAxis;
	const static Vector2 cYAxis;
	const static Vector2 cMaxVector;
	const static Vector2 cMinVector;

	inline static _float Dot( const Vector2& v1, const Vector2& v2 )
		{ return v1.x * v2.x + v1.y * v2.y; }

	inline static _float Cross( const Vector2& v1, const Vector2& v2 )
		{ return v1.x * v2.y - v1.y * v2.x; }

	inline static Vector2 Project( const Vector2& v1, const Vector2& v2 )
		{ Vector2 n = v2; n.Normalize( ); return n * Dot( v1, n ); }

	inline static Vector2 Plumb( const Vector2& v1, const Vector2& v2 )
		{ return v1 - Project( v1, v2 ); }

	inline static Vector2 Lerp( const Vector2& v1, const Vector2& v2, _float f )
		{ return v1 + ( v2 - v1 ) * Math::Clamp( f, 0.0f, 1.0f ); }

	inline static Vector2 Min( const Vector2& v1, const Vector2& v2 )
		{ return Vector2( Math::Min( v1.x, v2.x ), Math::Min( v1.y, v2.y ) ); }

	inline static Vector2 Max( const Vector2& v1, const Vector2& v2 )
		{ return Vector2( Math::Max( v1.x, v2.x ), Math::Max( v1.y, v2.y ) ); }

public:
	_float	x;
	_float	y;

public:
	inline Vector2( )
		{ }
	inline Vector2( _float xx, _float yy )
		: x( xx ), y( yy ) { }

	inline Vector2 operator + ( ) const
		{ return Vector2( x, y ); }
	inline Vector2 operator - ( ) const
		{ return Vector2( -x, -y ); }

	inline Vector2& operator += ( const Vector2& v )
		{ x += v.x; y += v.y; return *this; }
	inline Vector2& operator -= ( const Vector2& v )
		{ x -= v.x; y -= v.y; return *this; }

	inline Vector2 operator + ( const Vector2& v ) const
		{ return Vector2( x + v.x, y + v.y ); }
	inline Vector2 operator - ( const Vector2& v ) const
		{ return Vector2( x - v.x, y - v.y ); }

	inline Vector2& operator *= ( _float s )
		{ x *= s; y *= s; return *this; }
	inline Vector2& operator /= ( _float s )
		{ x /= s; y /= s; return *this; }

	inline Vector2 operator * ( _float s ) const
		{ return Vector2( x * s, y * s ); }
	inline Vector2 operator / ( _float s ) const
		{ return Vector2( x / s, y / s ); }

	inline Vector2& operator *= ( const Vector2& v )
		{ x *= v.x; y *= v.y; return *this; }
	inline Vector2& operator /= ( const Vector2& v )
		{ x /= v.x; y /= v.y; return *this; }

	inline Vector2 operator * ( const Vector2& v ) const
		{ return Vector2( x * v.x, y * v.y ); }
	inline Vector2 operator / ( const Vector2& v ) const
		{ return Vector2( x / v.x, y / v.y ); }

	inline Vector2 operator * ( const Matrix2& mat ) const
		{ Vector2 ret( *this ); return ret *= mat; }
	inline Vector2 operator * ( const Matrix3& mat ) const
		{ Vector2 ret( *this ); return ret *= mat; }

	inline _bool operator == ( const Vector2& v ) const
		{ return x == v.x && y == v.y; }
	inline _bool operator != ( const Vector2& v ) const
		{ return x != v.x || y != v.y; }

	inline _bool Equal( const Vector2& v, _float margin = Math::cEpsilon ) const
		{ return Math::Abs( x - v.x ) <= margin && Math::Abs( y - v.y ) <= margin; }

	inline Vector2& Absolute( )
		{ x = Math::Abs( x ); y = Math::Abs( y ); return *this; }
	inline Vector2& Normalize( )
		{ _float m = Magnitude( ); if ( m > 0.0f ) { x /= m; y /= m; } return *this; }

	inline _float Magnitude( ) const
		{ return Math::Sqrt( x * x + y * y ); }
	inline _float MagnitudeSquared( ) const
		{ return x * x + y * y; }

	Vector2& operator *= ( const Matrix2& mat );
	Vector2& operator *= ( const Matrix3& mat );
};

};