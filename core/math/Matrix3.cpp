#include "Matrix3.h"

using namespace Xixels;

const Matrix3 Matrix3::cZero( 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f );
const Matrix3 Matrix3::cIdentity( 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f );

const Matrix3 Matrix3::cProjectXY( 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f );
const Matrix3 Matrix3::cProjectYZ( 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f );
const Matrix3 Matrix3::cProjectZX( 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f );

const Matrix3 Matrix3::cRefectionXY( 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f );
const Matrix3 Matrix3::cRefectionYZ( -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f );
const Matrix3 Matrix3::cRefectionZX( 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f );

Matrix3& Matrix3::operator += ( const Matrix3& mat )
{
	m[0][0] += mat.m[0][0]; m[0][1] += mat.m[0][1]; m[0][2] += mat.m[0][2];
	m[1][0] += mat.m[1][0]; m[1][1] += mat.m[1][1]; m[1][2] += mat.m[1][2];
	m[2][0] += mat.m[2][0]; m[2][1] += mat.m[2][1]; m[2][2] += mat.m[2][2];

	return *this;
}

Matrix3& Matrix3::operator *= ( _float s )
{
	m[0][0] *= s; m[0][1] *= s; m[0][2] *= s;
	m[1][0] *= s; m[1][1] *= s; m[1][2] *= s;m[2][0] *= s; m[2][1] *= s; m[2][2] *= s;

	return *this;
}

Matrix3& Matrix3::operator *= ( const Matrix3& mat )
{
	Matrix3 temp = Matrix3::cZero;
	for ( _dword i = 0; i < 3; i ++ )
		for ( _dword j = 0; j < 3; j ++ )
			for ( _dword k = 0; k < 3; k ++ )
				temp.m[i][j] += m[i][k] * mat.m[k][j];

	*this = temp;

	return *this;
}

_bool Matrix3::operator == ( const Matrix3& mat ) const
{
	return	m[0][0] == mat.m[0][0] && m[0][1] == mat.m[0][1] && m[0][2] == mat.m[0][2] &&
			m[1][0] == mat.m[1][0] && m[1][1] == mat.m[1][1] && m[1][2] == mat.m[1][2] &&
			m[2][0] == mat.m[2][0] && m[2][1] == mat.m[2][1] && m[2][2] == mat.m[2][2];
}

_bool Matrix3::HasTranslation( ) const
{
	return m[2][0] != 0.0f || m[2][1] != 0.0f;
}

_bool Matrix3::HasRotation( ) const
{
	return m[0][1] != 0.0f || m[1][0] != 0.0f;
}

_float Matrix3::Determinant( ) const
{
	return m[0][0] * m[1][1] * m[2][2] + m[0][1] * m[1][2] * m[2][0] + m[0][2] * m[1][0] * m[2][1]
		 - m[0][0] * m[1][2] * m[2][1] - m[0][1] * m[1][0] * m[2][2] - m[0][2] * m[1][1] * m[2][0];
}

Matrix3& Matrix3::Identity( )
{
	m[0][0]	= 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f;
	m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f;
	m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f;

	return *this;
}

Matrix3& Matrix3::Transpose( )
{
	_float m01 = m[0][1], m02 = m[0][2], m10 = m[1][0], m12 = m[1][2], m20 = m[2][0], m21 = m[2][1];

	m[0][1] = m10; m[0][2] = m20;
	m[1][0] = m01; m[1][2] = m21;
	m[2][0] = m02; m[2][1] = m12;

	return *this;
} 

Matrix3& Matrix3::Inverse( )
{
	_float d = Determinant( );

	if ( d != 0.0f )
	{
		Adjoint( );

		d = 1.0f / d;

		m[0][0] *= d; m[0][1] *= d; m[0][2] *= d;
		m[1][0] *= d; m[1][1] *= d; m[1][2] *= d;
		m[2][0] *= d; m[2][1] *= d; m[2][2] *= d;
	}

	return *this;
}

Matrix3& Matrix3::Adjoint( )
{
	_float m00 = m[0][0], m01 = m[0][1], m02 = m[0][2], m10 = m[1][0], m11 = m[1][1],
		m12 = m[1][2], m20 = m[2][0], m21 = m[2][1], m22 = m[2][2];

	m[0][0] = m11 * m22 - m12 * m21; m[0][1] = m02 * m21 - m01 * m22; m[0][2] = m01 * m12 - m02 * m11;
	m[1][0] = m12 * m20 - m10 * m22; m[1][1] = m00 * m22 - m02 * m20; m[1][2] = m02 * m10 - m00 * m12;
	m[2][0] = m10 * m21 - m11 * m20; m[2][1] = m01 * m20 - m00 * m21; m[2][2] = m00 * m11 - m01 * m10;

	return *this;
}

Matrix3& Matrix3::Translation( _float x, _float y )
{
	m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f;
	m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f;
	m[2][0] =    x; m[2][1] =    y; m[2][2] = 1.0f;

	return *this;
}

Matrix3& Matrix3::Rotation( _float r )
{
	_float sinvalue = Math::Sin( r ), cosvalue = Math::Cos( r );

	m[0][0]	=   cosvalue; m[0][1] = sinvalue; m[0][2] = 0.0f;
	m[1][0] = - sinvalue; m[1][1] = cosvalue; m[1][2] = 0.0f;
	m[2][0] =       0.0f; m[2][1] =     0.0f; m[2][2] = 1.0f;

	return *this;
}

Matrix3& Matrix3::RotationX( _float r )
{
	_float sinvalue = Math::Sin( r ), cosvalue = Math::Cos( r );

	m[0][0]	= 1.0f; m[0][1] =       0.0f; m[0][2] =     0.0f;
	m[1][0] = 0.0f; m[1][1] =   cosvalue; m[1][2] = sinvalue;
	m[2][0] = 0.0f; m[2][1] = - sinvalue; m[2][2] = cosvalue;

	return *this;
}

Matrix3& Matrix3::RotationY( _float r )
{
	_float sinvalue = Math::Sin( r ), cosvalue = Math::Cos( r );

	m[0][0]	= cosvalue; m[0][1] = 0.0f; m[0][2] = - sinvalue;
	m[1][0] =     0.0f; m[1][1] = 1.0f; m[1][2] =       0.0f;
	m[2][0] = sinvalue; m[2][1] = 0.0f; m[2][2] =   cosvalue;

	return *this;
}

Matrix3& Matrix3::RotationZ( _float r )
{
	_float sinvalue = Math::Sin( r ), cosvalue = Math::Cos( r );

	m[0][0]	=   cosvalue; m[0][1] = sinvalue; m[0][2] = 0.0f;
	m[1][0] = - sinvalue; m[1][1] = cosvalue; m[1][2] = 0.0f;
	m[2][0] =       0.0f; m[2][1] =     0.0f; m[2][2] = 1.0f;

	return *this;
}

Matrix3& Matrix3::Rotation( const Vector3& a, _float r )
{
	_float sinvalue = Math::Sin( r ), cosvalue = Math::Cos( r ), cosreverse = 1.0f - cosvalue;

	Vector3 n( a );
	n.Normalize( );

	m[0][0] = cosreverse * n.x * n.x + cosvalue;
	m[0][1] = cosreverse * n.x * n.y + sinvalue * n.z;
	m[0][2] = cosreverse * n.x * n.z - sinvalue * n.y;

	m[1][0] = cosreverse * n.x * n.y - sinvalue * n.z;
	m[1][1] = cosreverse * n.y * n.y + cosvalue;
	m[1][2] = cosreverse * n.y * n.z + sinvalue * n.x;

	m[2][0] = cosreverse * n.x * n.z + sinvalue * n.y;
	m[2][1] = cosreverse * n.y * n.z - sinvalue * n.x;
	m[2][2] = cosreverse * n.z * n.z + cosvalue;

	return *this;
}

Matrix3& Matrix3::Rotation( const Quaternion& q )
{
	_float xx = q.x * q.x * 2.0f, yy = q.y * q.y * 2.0f, zz = q.z * q.z * 2.0f;
	_float xy = q.x * q.y * 2.0f, zw = q.z * q.w * 2.0f, xz = q.x * q.z * 2.0f;
	_float yw = q.y * q.w * 2.0f, yz = q.y * q.z * 2.0f, xw = q.x * q.w * 2.0f;

	m[0][0] = 1.0f - yy - zz; m[0][1] =        xy + zw; m[0][2] =        xz - yw;
	m[1][0] =        xy - zw; m[1][1] = 1.0f - xx - zz; m[1][2] =        yz + xw;
	m[2][0] =        xz + yw; m[2][1] =        yz - xw; m[2][2] = 1.0f - xx - yy;

	return *this;
}

Matrix3& Matrix3::Rotation( const Vector3& x, const Vector3& y, const Vector3& z )
{
	Vector3 nx = x; nx.Normalize( );
	Vector3 ny = y; ny.Normalize( );
	Vector3 nz = z; nz.Normalize( );

	m[0][0] = nx.x; m[0][1] = nx.y; m[0][2] = nx.z;
	m[1][0] = ny.x; m[1][1] = ny.y; m[1][2] = ny.z;
	m[2][0] = nz.x; m[2][1] = nz.y; m[2][2] = nz.z;

	return *this;
}

Matrix3& Matrix3::Scaling( _float x, _float y, _float z )
{
	m[0][0]	=    x; m[0][1] = 0.0f; m[0][2] = 0.0f;
	m[1][0] = 0.0f; m[1][1] =    y; m[1][2] = 0.0f;
	m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] =    z;

	return *this;
}

Matrix3& Matrix3::Scaling( const Vector3& v, _float f )
{
	Vector3 n( v );
	n.Normalize( );

	_float k  = f - 1.0f;
	_float xx = n.x * n.x;
	_float yy = n.y * n.y;
	_float zz = n.z * n.z;
	_float xy = n.x * n.y;
	_float yz = n.y * n.z;
	_float zx = n.z * n.x;

	m[0][0] = 1.0f + k * xx; m[0][1] =        k * xy; m[0][2] =        k * zx;
	m[1][0] =        k * xy; m[1][1] = 1.0f + k * yy; m[1][2] =        k * yz;
	m[2][0] =        k * zx; m[2][1] =        k * yz; m[2][2] = 1.0f + k * zz;

	return *this;
}

Matrix3& Matrix3::Compose( const Vector2& offset, const Vector3& scale, float angle )
{
	_float sin = Math::Sin( angle );
	_float cos = Math::Cos( angle );

	m[0][0] =  cos * scale.x; m[0][1] = sin * scale.y; m[0][2] =           0.0f;
	m[1][0] = -sin * scale.x; m[1][1] = cos * scale.y; m[1][2] =           0.0f;
	m[2][0] =       offset.x; m[2][1] =      offset.y; m[2][2] =        scale.z;

	return *this;
}

_void Matrix3::Decompose( Quaternion& q ) const
{
	// Determine which of w, x, y, or z has the largest absolute value.
	_float fourWSquaredMinus1 = m[0][0] + m[1][1] + m[2][2];
	_float fourXSquaredMinus1 = m[0][0] - m[1][1] - m[2][2];
	_float fourYSquaredMinus1 = m[1][1] - m[0][0] - m[2][2];
	_float fourZSquaredMinus1 = m[2][2] - m[0][0] - m[1][1];

	_long biggestIndex = 0;
	_float fourBiggestSquaredMinus1 = fourWSquaredMinus1;

	if ( fourXSquaredMinus1 > fourBiggestSquaredMinus1 )
	{
		fourBiggestSquaredMinus1 = fourXSquaredMinus1;
		biggestIndex = 1;
	}

	if ( fourYSquaredMinus1 > fourBiggestSquaredMinus1 )
	{
		fourBiggestSquaredMinus1 = fourYSquaredMinus1;
		biggestIndex = 2;
	}

	if ( fourZSquaredMinus1 > fourBiggestSquaredMinus1 )
	{
		fourBiggestSquaredMinus1 = fourZSquaredMinus1;
		biggestIndex = 3;
	}

	_float biggestVal = Math::Sqrt( fourBiggestSquaredMinus1 + 1.0f ) * 0.5f;
	_float mult = 0.25f / biggestVal;

	// Apply table to compute quaternion values.
	switch ( biggestIndex )
	{
		case 0:
			q.w = biggestVal;
			q.x = ( m[1][2] - m[2][1] ) * mult;
			q.y = ( m[2][0] - m[0][2] ) * mult;
			q.z = ( m[0][1] - m[1][0] ) * mult;
			break;

		case 1:
			q.x = biggestVal;
			q.w = ( m[1][2] - m[2][1] ) * mult;
			q.y = ( m[0][1] + m[1][0] ) * mult;
			q.z = ( m[2][0] + m[0][2] ) * mult;
			break;

		case 2:
			q.y = biggestVal;
			q.w = ( m[2][0] - m[0][2] ) * mult;
			q.x = ( m[0][1] + m[1][0] ) * mult;
			q.z = ( m[1][2] + m[2][1] ) * mult;
			break;

		case 3:
			q.z = biggestVal;
			q.w = ( m[0][1] - m[1][0] ) * mult;
			q.x = ( m[2][0] + m[0][2] ) * mult;
			q.y = ( m[1][2] + m[2][1] ) * mult;
			break;
	}
}