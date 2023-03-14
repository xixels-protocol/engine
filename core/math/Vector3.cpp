#include "Math.h"
#include "Matrix3.h"
#include "Matrix4.h"
#include "Quaternion.h"
#include "Vector3.h"

const Vector3 Vector3::cIdentity( 1.0f, 1.0f, 1.0f );
const Vector3 Vector3::cOrigin( 0.0f, 0.0f, 0.0f );
const Vector3 Vector3::cXAxis( 1.0f, 0.0f, 0.0f );
const Vector3 Vector3::cYAxis( 0.0f, 1.0f, 0.0f );
const Vector3 Vector3::cZAxis( 0.0f, 0.0f, 1.0f );
const Vector3 Vector3::cZero( 0.0f, 0.0f, 0.0f );
const Vector3 Vector3::cOne( 1.0f, 1.0f, 1.0f );
const Vector3 Vector3::cMaxVector( Math::cMaxFloat, Math::cMaxFloat, Math::cMaxFloat );
const Vector3 Vector3::cMinVector( Math::cMinFloat, Math::cMinFloat, Math::cMinFloat );

Vector3 Vector3::Slerp( const Vector3& v1, const Vector3& v2, float f )
{
	Vector3 v3 = Vector3::Lerp( v1, v2, f );
	float k = Math::Sqrt( v1.MagnitudeSquared( ) / v3.MagnitudeSquared( ) );
	return v3 * k;
}

Vector3 Vector3::Slerp( const Vector3& v1, const Vector3& v2, const Vector3& v3, float f )
{
	Vector3 vv1 = v1 - v3;
	Vector3 vv2 = v2 - v3;
	return Vector3::Slerp( vv1, vv2, f ) + v3;
}

Vector3& Vector3::operator *= ( const Matrix3& mat )
{
	float xx = x, yy = y, zz = z;

	x = xx * mat.m[0][0] + yy * mat.m[1][0] + zz * mat.m[2][0];
	y = xx * mat.m[0][1] + yy * mat.m[1][1] + zz * mat.m[2][1];
	z = xx * mat.m[0][2] + yy * mat.m[1][2] + zz * mat.m[2][2];

	return *this;
}

Vector3& Vector3::operator *= ( const Matrix4& mat )
{
	float xx = x, yy = y, zz = z;

	float w = xx * mat.m[0][3] + yy * mat.m[1][3] + zz * mat.m[2][3] + mat.m[3][3];

	x = xx * mat.m[0][0] + yy * mat.m[1][0] + zz * mat.m[2][0] + mat.m[3][0];
	y = xx * mat.m[0][1] + yy * mat.m[1][1] + zz * mat.m[2][1] + mat.m[3][1];
	z = xx * mat.m[0][2] + yy * mat.m[1][2] + zz * mat.m[2][2] + mat.m[3][2];

	if ( w != 0.0f )
	{
		float winv = 1.0f / w;
		x *= winv;
		y *= winv;
		z *= winv;
	}

	return *this;
}

Vector3& Vector3::operator *= ( const Quaternion& q )
{
	Vector3 qv( q.x, q.y, q.z );
	Vector3 uv = Vector3::Cross( qv, *this );
	Vector3 uuv = Vector3::Cross( qv, uv );

	uv *= 2.0f * q.w;
	uuv *= 2.0f;

	x += uv.x + uuv.x;
	y += uv.y + uuv.y;
	z += uv.z + uuv.z;

	return *this;
}