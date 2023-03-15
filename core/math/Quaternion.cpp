#include "Vector3.h"
#include "Quaternion.h"

using namespace Xixels;

const Quaternion Quaternion::cIdentity( 0.0f, 0.0f, 0.0f, 1.0f );

Quaternion Quaternion::Slerp( const Quaternion& q1, const Quaternion& q2, _float f )
{
	f = Math::Clamp( f, 0.0f, 1.0f );

	_float dot = Dot( q1, q2 );

	_bool flip = dot < 0.0f;

	if ( dot < 0.0f )
		dot = -dot;

	_float d = 0.0f;

	if ( 1.0f - dot < Math::cEpsilon )
	{
		d = 1.0f - f;
	}
	else
	{
		_float theta	 = Math::Acos( dot );
		_float recipsqrt = 1.0f / Math::Sin( theta );

		d = Math::Sin( ( 1.0f - f ) * theta ) * recipsqrt;
		f = Math::Sin( f * theta ) * recipsqrt;
	}

	if ( flip )
		f = -f;

	return Quaternion(
		q1.x * d + q2.x * f,
		q1.y * d + q2.y * f,
		q1.z * d + q2.z * f,
		q1.w * d + q2.w * f );
}

_void Quaternion::PrecomputeSlerpParams( const Quaternion& q1, const Quaternion& q2, _float& dot, _float& theta, _float& recipsqrt )
{
	dot = Dot( q1, q2 );

	theta	  = Math::Acos( dot < 0.0f ? -dot : dot );
	recipsqrt = 1.0f / Math::Sin( theta );
}

Quaternion Quaternion::Slerp( const Quaternion& q1, const Quaternion& q2, _float dot, _float theta, _float recipsqrt, _float f )
{
	// Dont need clamp f to speed up.
	_bool flip = dot < 0.0f;

	if ( dot < 0.0f )
		dot = -dot;

	_float d = 0.0f;

	if ( 1.0f - dot < Math::cEpsilon )
	{
		d = 1.0f - f;
	}
	else
	{
		d = Math::Sin( ( 1.0f - f ) * theta ) * recipsqrt;
		f = Math::Sin( f * theta ) * recipsqrt;
	}

	if ( flip )
		f = -f;

	return Quaternion(
		q1.x * d + q2.x * f,
		q1.y * d + q2.y * f,
		q1.z * d + q2.z * f,
		q1.w * d + q2.w * f );
}

Quaternion& Quaternion::operator *= ( const Quaternion& q )
{
	// User Definition of Quaternion Cross. p * q means rotate p first and then rotate q.
	_float qx1 = x, qy1 = y, qz1 = z, qw1 = w;

	x = qw1 * q.x + qx1 * q.w - qy1 * q.z + qz1 * q.y;
	y = qw1 * q.y + qx1 * q.z + qy1 * q.w - qz1 * q.x;
	z = qw1 * q.z - qx1 * q.y + qy1 * q.x + qz1 * q.w;
	w = qw1 * q.w - qx1 * q.x - qy1 * q.y - qz1 * q.z;

	return *this;
}

Quaternion& Quaternion::Cross( const Quaternion& q )
{
	// Standard Definition of Quaternion Cross. p.Cross( q ) means rotate q first and then rotate p.
	_float qx1 = x, qy1 = y, qz1 = z, qw1 = w;

	x = qw1 * q.x + qx1 * q.w + qy1 * q.z - qz1 * q.y;
	y = qw1 * q.y - qx1 * q.z + qy1 * q.w + qz1 * q.x;
	z = qw1 * q.z + qx1 * q.y - qy1 * q.x + qz1 * q.w;
	w = qw1 * q.w - qx1 * q.x - qy1 * q.y - qz1 * q.z;

	return *this;
}

Quaternion& Quaternion::Rotation( const Vector3& a, _float r )
{
	Vector3 n = a;
	n.Normalize( );

	_float sinvalue = Math::Sin( r * 0.5f );

	x = sinvalue * n.x;
	y = sinvalue * n.y;
	z = sinvalue * n.z;
	w = Math::Cos( r * 0.5f );

	return *this;
}

Quaternion& Quaternion::Rotation( const Vector3& v1, const Vector3& v2 )
{
	Vector3 vv1 = v1;
	vv1.Normalize( );

	Vector3 vv2 = v2;
	vv2.Normalize( );

	_float dotvalue = Vector3::Dot( vv1, vv2 );
	if ( dotvalue >= 1.0f - Math::cEpsilon )
		return ( *this = Quaternion::cIdentity );

	if ( dotvalue <= Math::cEpsilon - 1.0f )
	{
		if ( Math::Abs( vv1.z ) < Math::cEpsilon && Math::Abs( vv2.z ) < Math::cEpsilon )
		{
			return Rotation( Vector3::cZAxis, Math::Acos( dotvalue ) );
		}
		else if ( Math::Abs( vv1.y ) < Math::cEpsilon && Math::Abs( vv2.y ) < Math::cEpsilon )
		{
			return Rotation( Vector3::cYAxis, Math::Acos( dotvalue ) );
		}
		else if ( Math::Abs( vv1.x ) < Math::cEpsilon && Math::Abs( vv2.x ) < Math::cEpsilon )
		{
			return Rotation( Vector3::cXAxis, Math::Acos( dotvalue ) );
		}
		else if ( Math::Abs( vv1.x ) > Math::cEpsilon )
		{
			Vector3 n0( vv1.x, 0.0f, 0.0f );
			Vector3 n1 = Vector3::Cross( n0, Vector3( 0.0f, 1.0f, 1.0f ) );
			return Rotation( n1, Math::cPi );
		}
		else if ( Math::Abs( vv1.y ) > Math::cEpsilon )
		{
			Vector3 n0( 0.0f, vv1.y, 0.0f );
			Vector3 n1 = Vector3::Cross( n0, Vector3( 1.0f, 0.0f, 1.0f ) );
			return Rotation( n1, Math::cPi );
		}
		else if ( Math::Abs( vv1.z ) > Math::cEpsilon )
		{
			Vector3 n0( 0.0f, 0.0f, vv1.z );
			Vector3 n1 = Vector3::Cross( n0, Vector3( 1.0f, 1.0f, 0.0f ) );
			return Rotation( n1, Math::cPi );
		}
		else
		{
			// Should not happen.
			return ( *this = Quaternion::cIdentity );
		}
	}

	_float m = Math::Sqrt( ( 1.0f + dotvalue ) * 2.0f );
	if ( m < Math::cEpsilon )
		return ( *this = Quaternion::cIdentity );

	Vector3 a = Vector3::Cross( vv1, vv2 );

	x = a.x / m;
	y = a.y / m;
	z = a.z / m;
	w = m * 0.5f;

	return *this;
}

_void Quaternion::Decompose( Vector3& a, _float& r ) const
{
	_float m = x * x + y * y + z * z;

	if ( m > Math::cEpsilon )
	{
		m = Math::Sqrt( m );

		a.x = x / m;
		a.y = y / m;
		a.z = z / m;
		r = 2.0f * Math::Acos( w );
	}
	else
	{
		a.x = 0.0f;
		a.y = 0.0f;
		a.z = 1.0f;
		r = 0.0f;
	}

	a.Normalize( );
}