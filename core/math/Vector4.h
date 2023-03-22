#pragma once

#include "Math.hpp"

namespace Xixels
{

class Matrix4;

class Vector4
{
public:
	// The origin vector.
	const static Vector4 cOrigin;
	// The identity vector.
	const static Vector4 cIdentity;
	// The x-axis vector.
	const static Vector4 cXAxis;
	// The y-axis vector.
	const static Vector4 cYAxis;
	// The z-axis vector.
	const static Vector4 cZAxis;
	// The w-axis vector.
	const static Vector4 cWAxis;
	// The maximal vector.
	const static Vector4 cMaxVector;
	// The minimal vector.
	const static Vector4 cMinVector;

	inline static _float Dot( const Vector4& v1, const Vector4& v2 )
		{ return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w; };

	inline static Vector4 Project( const Vector4& v1, const Vector4& v2 )
		{ Vector4 n = v2; n.Normalize( ); return n * Dot( v1, n ); }

	inline static Vector4 Plumb( const Vector4& v1, const Vector4& v2 )
		{ return v1 - Project( v1, v2 ); }

	inline static Vector4 Lerp( const Vector4& v1, const Vector4& v2, _float f )
		{ return v1 + ( v2 - v1 ) * Math::Clamp( f, 0.0f, 1.0f ); }

	inline static Vector4 Min( const Vector4& v1, const Vector4& v2 )
		{ return Vector4( Math::Min( v1.x, v2.x ), Math::Min( v1.y, v2.y ), Math::Min( v1.z, v2.z ), Math::Min( v1.w, v2.w ) ); }

	inline static Vector4 Max( const Vector4& v1, const Vector4& v2 )
		{ return Vector4( Math::Max( v1.x, v2.x ), Math::Max( v1.y, v2.y ), Math::Max( v1.z, v2.z ), Math::Max( v1.w, v2.w ) ); }

public:
	_float	x;
	_float	y;
	_float	z;
	_float	w;

public:
	inline Vector4( )
		{ }
	inline Vector4( _float xx, _float yy, _float zz, _float ww )
		: x( xx ), y( yy ), z( zz ), w( ww ) { }
	inline Vector4( const Vector3& v, _float ww )
		: x( v.x ), y( v.y ), z( v.z ), w( ww ) { }

	inline Vector4& operator = ( const Vector3 &v )
		{ x = v.x; y = v.y; z = v.z, w = 0.0f; return *this; }
	inline Vector4& operator = ( const Vector4 &v )
		{ x = v.x; y = v.y; z = v.z, w = v.w; return *this; }

	inline operator Vector3 ( ) const
		{ return Vector3( x, y, z ); }

	inline Vector4 operator + ( ) const
		{ return Vector4( x, y, z, w ); }
	inline Vector4 operator - ( ) const
		{ return Vector4( -x, -y, -z, -w ); }

	inline Vector4& operator += ( const Vector4& v )
		{ x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
	inline Vector4& operator -= ( const Vector4& v )
		{ x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }

	inline Vector4 operator + ( const Vector4& v ) const
		{ return Vector4( x + v.x, y + v.y, z + v.z, w + v.w ); }
	inline Vector4 operator - ( const Vector4& v ) const
		{ return Vector4( x - v.x, y - v.y, z - v.z, w - v.w ); }

	inline Vector4& operator *= ( _float s )
		{ x *= s; y *= s; z *= s; w *= s; return *this; }
	inline Vector4& operator /= ( _float s )
		{ x /= s; y /= s; z /= s; w /= s; return *this; }

	inline Vector4 operator * ( _float s ) const
		{ return Vector4( x * s, y * s, z * s, w * s ); }
	inline Vector4 operator / ( _float s ) const
		{ return Vector4( x / s, y / s, z / s, w / s ); }

	inline Vector4& operator *= ( const Vector4& v )
		{ x *= v.x; y *= v.y; z *= v.z; w *= v.w; return *this; }
	inline Vector4& operator /= ( const Vector4& v )
		{ x /= v.x; y /= v.y; z /= v.z; w /= v.w; return *this; }

	inline Vector4 operator * ( const Vector4& v ) const
		{ return Vector4( x * v.x, y * v.y, z * v.z, w * v.w ); }
	inline Vector4 operator / ( const Vector4& v ) const
		{ return Vector4( x / v.x, y / v.y, z / v.z, w / v.w ); }

	inline Vector4 operator * ( const Matrix4& mat ) const
		{ Vector4 ret( *this ); return ret *= mat; }

	inline _bool operator == ( const Vector4& v ) const
		{ return x == v.x && y == v.y && z == v.z && w == v.w; }
	inline _bool operator != ( const Vector4& v ) const
		{ return x != v.x || y != v.y || z != v.z || w != v.w; }

	inline Vector4 operator ^ ( const Vector4& v ) const
		{ return Vector4( y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x, 0.0f ); }

	inline _float& operator[](_long ComponentIndex)
		{ return (&x)[ ComponentIndex ]; }

	inline _float operator[](_long ComponentIndex) const
		{ return (&x)[ ComponentIndex ]; }

	inline _float& Component(_long Index)
		{ return (&x)[Index]; }

	inline const _float& Component(_long Index) const
		{ return (&x)[Index]; }

	inline _float GetComponent( _dword index ) const
		{ if ( index == 0 ) return x; if ( index == 1 ) return y; if ( index == 2 ) return z; return w; }

	inline _bool Equal( const Vector4& v, _float margin = Math::cEpsilon ) const
		{ return Math::Abs( x - v.x ) <= margin && Math::Abs( y - v.y ) <= margin && Math::Abs( z - v.z ) <= margin && Math::Abs( w - v.w ) <= margin; }

	inline Vector4& Absolute( )
		{ x = Math::Abs( x ); y = Math::Abs( y ); z = Math::Abs( z ); w = Math::Abs( w ); return *this; }
	inline Vector4& Normalize( )
		{ _float m = Magnitude( ); if ( m > 0.0f ) { x /= m; y /= m; z /= m; w /= m; } return *this; }

	inline _float Magnitude( ) const
		{ return Math::Sqrt( x * x + y * y + z * z + w * w ); }
	inline _float MagnitudeSquared( ) const
		{ return x * x + y * y + z * z + w * w; }

	Vector4& operator *= ( const Matrix4& mat );
};

};