#include "Matrix3.h"
#include "Matrix4.h"
#include "Quaternion.h"
#include "Vector3.h"

using namespace Xixels;

const Vector3 Vector3::cIdentity( 1.0f, 1.0f, 1.0f );

const Vector3 Vector3::cOrigin( 0.0f, 0.0f, 0.0f );
const Vector3 Vector3::cXAxis( 1.0f, 0.0f, 0.0f );
const Vector3 Vector3::cYAxis( 0.0f, 1.0f, 0.0f );
const Vector3 Vector3::cZAxis( 0.0f, 0.0f, 1.0f );

const Vector3 Vector3::cZero( 0.0f, 0.0f, 0.0f );
const Vector3 Vector3::cOne( 1.0f, 1.0f, 1.0f );
const Vector3 Vector3::cMaxVector( Math::cMaxFloat, Math::cMaxFloat, Math::cMaxFloat );
const Vector3 Vector3::cMinVector( Math::cMinFloat, Math::cMinFloat, Math::cMinFloat );

Vector3 Vector3::Slerp( const Vector3& v1, const Vector3& v2, _float f )
{
	Vector3 v3 = Vector3::Lerp( v1, v2, f );
	_float k = Math::Sqrt( v1.MagnitudeSquared( ) / v3.MagnitudeSquared( ) );
	return v3 * k;
}

Vector3 Vector3::Slerp( const Vector3& v1, const Vector3& v2, const Vector3& v3, _float f )
{
	Vector3 vv1 = v1 - v3;
	Vector3 vv2 = v2 - v3;
	return Vector3::Slerp( vv1, vv2, f ) + v3;
}

Vector3& Vector3::operator *= ( const Matrix3& mat )
{
	_float xx = x, yy = y, zz = z;

	x = xx * mat.m[0][0] + yy * mat.m[1][0] + zz * mat.m[2][0];
	y = xx * mat.m[0][1] + yy * mat.m[1][1] + zz * mat.m[2][1];
	z = xx * mat.m[0][2] + yy * mat.m[1][2] + zz * mat.m[2][2];

	return *this;
}

Vector3& Vector3::operator *= ( const Matrix4& mat )
{
	_float xx = x, yy = y, zz = z;

	_float w = xx * mat.m[0][3] + yy * mat.m[1][3] + zz * mat.m[2][3] + mat.m[3][3];

	x = xx * mat.m[0][0] + yy * mat.m[1][0] + zz * mat.m[2][0] + mat.m[3][0];
	y = xx * mat.m[0][1] + yy * mat.m[1][1] + zz * mat.m[2][1] + mat.m[3][1];
	z = xx * mat.m[0][2] + yy * mat.m[1][2] + zz * mat.m[2][2] + mat.m[3][2];

	if ( w != 0.0f )
	{
		_float winv = 1.0f / w;
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

Vector3& Vector3::Cartesian2Spherical( )
{
	_float xx = Math::Sqrt( x * x + y * y + z * z );
	_float yy = xx == 0.0f ? 0.0f : Math::Acos( z / xx );
	_float zz = ( x == 0.0f && y == 0.0f ) ? 0.0f : Math::Asin( y / Math::Sqrt( x * x + y * y ) );

	if ( x < 0.0f )
		zz = Math::cPi - zz;

	if ( zz < 0.0f )
		zz += Math::c2Pi;

	x = xx;
	y = yy;
	z = zz;

	return *this;
}

Vector3& Vector3::Spherical2Cartesian( )
{
	_float xx = x * Math::Sin( y ) * Math::Cos( z );
	_float yy = x * Math::Sin( y ) * Math::Sin( z );
	_float zz = x * Math::Cos( y );

	x = xx;
	y = yy;
	z = zz;

	return *this;
}

Vector3& Vector3::Cartesian2Cylindrical( )
{
	_float xx = Math::Atan( y / x );
	_float yy = Math::Sqrt( x * x + y * y );

	if ( x < 0.0f )
		xx += Math::cPi;

	x = xx;
	y = yy;

	return *this;
}

Vector3& Vector3::Cylindrical2Cartesian( )
{
	_float xx = y * Math::Cos( x );
	_float yy = y * Math::Sin( x );

	x = xx;
	y = yy;

	return *this;
}