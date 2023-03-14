#pragma once

namespace Xixels
{

class Matrix3;
class Matrix4;
class Quaternion;

class Vector3
{
public:
	const static Vector3 cIdentity;
	const static Vector3 cOrigin;
	const static Vector3 cXAxis;
	const static Vector3 cYAxis;
	const static Vector3 cZAxis;
	const static Vector3 cZero;
	const static Vector3 cOne;
	const static Vector3 cMaxVector;
	const static Vector3 cMinVector;

	inline static float Dot( const Vector3& v1, const Vector3& v2 )
		{ return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; }

	inline static Vector3 Cross( const Vector3& v1, const Vector3& v2 )
		{ return Vector3( v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x ); }

	inline static Vector3 Project( const Vector3& v1, const Vector3& v2 )
		{ Vector3 n = v2; n.Normalize( ); return n * Dot( v1, n ); }

	inline static Vector3 Plumb( const Vector3& v1, const Vector3& v2 )
		{ return v1 - Project( v1, v2 ); }

	inline static Vector3 Lerp( const Vector3& v1, const Vector3& v2, float f )
		{ return v1 + ( v2 - v1 ) * Math::Clamp( f, 0.0f, 1.0f ); }

	inline static Vector3 Min( const Vector3& v1, const Vector3& v2 )
		{ return Vector3( Math::Min( v1.x, v2.x ), Math::Min( v1.y, v2.y ), Math::Min( v1.z, v2.z ) ); }

	inline static Vector3 Max( const Vector3& v1, const Vector3& v2 )
		{ return Vector3( Math::Max( v1.x, v2.x ), Math::Max( v1.y, v2.y ), Math::Max( v1.z, v2.z ) ); }

	static Vector3 Slerp( const Vector3& v1, const Vector3& v2, float f );
	static Vector3 Slerp( const Vector3& v1, const Vector3& v2, const Vector3& v3, float f );

public:
	float	x;
	float	y;
	float	z;

public:
	inline Vector3( )
		{ }
	inline Vector3( float xx, float yy, float zz )
		: x( xx ), y( yy ), z( zz ) { }

	inline Vector3 operator + ( ) const
		{ return Vector3( x, y, z ); }
	inline Vector3 operator - ( ) const
		{ return Vector3( -x, -y, -z ); }

	inline Vector3& operator += ( const Vector3& v )
		{ x += v.x; y += v.y; z += v.z; return *this; }
	inline Vector3& operator -= ( const Vector3& v )
		{ x -= v.x; y -= v.y; z -= v.z; return *this; }

	inline Vector3 operator + ( const Vector3& v ) const
		{ return Vector3( x + v.x, y + v.y, z + v.z ); }
	inline Vector3 operator - ( const Vector3& v ) const
		{ return Vector3( x - v.x, y - v.y, z - v.z ); }

	inline Vector3& operator *= ( float s )
		{ x *= s; y *= s; z *= s; return *this; }
	inline Vector3& operator /= ( float s )
		{ x /= s; y /= s; z /= s; return *this; }

	inline Vector3 operator * ( float s ) const
		{ return Vector3( x * s, y * s, z * s ); }
	inline Vector3 operator / ( float s ) const
		{ return Vector3( x / s, y / s, z / s ); }

	inline Vector3& operator *= ( const Vector3& v )
		{ x *= v.x; y *= v.y; z *= v.z; return *this; }
	inline Vector3& operator /= ( const Vector3& v )
		{ x /= v.x; y /= v.y; z /= v.z; return *this; }

	inline Vector3 operator * ( const Vector3& v ) const
		{ return Vector3( x * v.x, y * v.y, z * v.z ); }
	inline Vector3 operator / ( const Vector3& v ) const
		{ return Vector3( x / v.x, y / v.y, z / v.z ); }

	inline Vector3 operator * ( const Matrix3& mat ) const
		{ Vector3 ret( *this ); return ret *= mat; }
	inline Vector3 operator * ( const Matrix3x4& mat ) const
		{ Vector3 ret( *this ); return ret *= mat; }
	inline Vector3 operator * ( const Matrix4& mat ) const
		{ Vector3 ret( *this ); return ret *= mat; }
	inline Vector3 operator * ( const Quaternion& q ) const
		{ Vector3 ret( *this ); return ret *= q; }

	inline _bool operator == ( const Vector3& v ) const
		{ return x == v.x && y == v.y && z == v.z; }
	inline _bool operator != ( const Vector3& v ) const
		{ return x != v.x || y != v.y || z != v.z; }

	inline _bool Equal( const Vector3& v, float margin = Math::cEpsilon ) const
		{ return Math::Abs( x - v.x ) <= margin && Math::Abs( y - v.y ) <= margin && Math::Abs( z - v.z ) <= margin; }

	inline Vector3& Absolute( )
		{ x = Math::Abs( x ); y = Math::Abs( y ); z = Math::Abs( z ); return *this; }
	inline Vector3& Normalize( )
	{ 
		float m = Magnitude( );
		if ( m > 0.0f )
			{ x /= m; y /= m; z /= m; }
		
		return *this;
	}

	inline float Magnitude( ) const
		{ return Math::Sqrt( x * x + y * y + z * z ); }
	inline float MagnitudeSquared( ) const
		{ return x * x + y * y + z * z; }

	Vector3& operator *= ( const Matrix3& mat );
	Vector3& operator *= ( const Matrix4& mat );
	Vector3& operator *= ( const Quaternion& q );
};

};