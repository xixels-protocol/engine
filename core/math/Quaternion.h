#pragma once

#include "Math.h"

namespace Xixels
{

class Quaternion
{
public:
	const static Quaternion cIdentity;

	inline static _float Dot( const Quaternion& q1, const Quaternion& q2 )
		{ return q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w; }

	static _void		PrecomputeSlerpParams( const Quaternion& q1, const Quaternion& q2, _float& dot, _float& theta, _float& recipsqrt );
	static Quaternion	Slerp( const Quaternion& q1, const Quaternion& q2, _float f );
	static Quaternion	Slerp( const Quaternion& q1, const Quaternion& q2, _float dot, _float theta, _float recipsqrt, _float f );

public:
	_float	x;
	_float	y;
	_float	z;
	_float	w;

public:
	inline Quaternion( )
		{ }
	inline Quaternion( _float xx, _float yy, _float zz, _float ww )
		: x( xx ), y( yy ), z( zz ), w( ww ) { }

	inline Quaternion operator + ( ) const
		{ return Quaternion( x, y, z, w ); }
	inline Quaternion operator - ( ) const
		{ return Quaternion( -x, -y, -z, w ); }

	inline Quaternion& operator += ( const Quaternion& q )
		{ x += q.x; y += q.y; z += q.z; w += q.w; return *this; }
	inline Quaternion& operator -= ( const Quaternion& q )
		{ x -= q.x; y -= q.y; z -= q.z; w -= q.w; return *this; }

	inline Quaternion operator + ( const Quaternion& q ) const
		{ return Quaternion( x + q.x, y + q.y, z + q.z, w + q.w ); }
	inline Quaternion operator - ( const Quaternion& q ) const
		{ return Quaternion( x - q.x, y - q.y, z - q.z, w - q.w ); }

	inline Quaternion& operator /= ( const Quaternion& q )
		{ Quaternion t = *this; *this = -q; return *this *= t; }

	inline Quaternion operator * ( const Quaternion& q ) const
		{ Quaternion ret( *this ); return ret *= q; }
	inline Quaternion operator / ( const Quaternion& q ) const
		{ Quaternion ret( *this ); return ret /= q; }

	inline _bool operator == ( const Quaternion& q ) const
		{ return x == q.x && y == q.y && z == q.z && w == q.w; }
	inline _bool operator != ( const Quaternion& q ) const
		{ return x != q.x || y != q.y || z != q.z || w != q.w; }

	inline _bool Equal( const Quaternion& q, _float margin = Math::cEpsilon ) const
		{ return Math::Abs( x - q.x ) <= margin && Math::Abs( y - q.y ) <= margin && Math::Abs( z - q.z ) <= margin && Math::Abs( w - q.w ) <= margin; }

	inline Quaternion& Identity( )
		{ x = 0.0f; y = 0.0f; z = 0.0f; w = 1.0f; return *this; }
	inline Quaternion& Normalize( )
		{ _float m = Magnitude( ); if ( m > 0.0f ) { x /= m; y /= m; z /= m; w /= m; } return *this; }

	inline _float Magnitude( ) const
		{ return Math::Sqrt( x * x + y * y + z * z + w * w ); }
	inline _float MagnitudeSquared( ) const
		{ return x * x + y * y + z * z + w * w; }

	inline Quaternion& RotationX( _float r )
		{ x = Math::Sin( r * 0.5f ); y = 0.0f; z = 0.0f; w = Math::Cos( r * 0.5f ); return *this; }
	inline Quaternion& RotationY( _float r )
		{ x = 0.0f; y = Math::Sin( r * 0.5f ); z = 0.0f; w = Math::Cos( r * 0.5f ); return *this; }
	inline Quaternion& RotationZ( _float r )
		{ x = 0.0f; y = 0.0f; z = Math::Sin( r * 0.5f ); w = Math::Cos( r * 0.5f ); return *this; }

	Quaternion& operator *= ( const Quaternion& q );
	Quaternion& Cross( const Quaternion& q );

	Quaternion&	Rotation( const Vector3& a, _float r );
	Quaternion& Rotation( const Vector3& v1, const Vector3& v2 );

	_void		Decompose( Vector3& axis, _float& r ) const;
};

};