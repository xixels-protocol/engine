#include "Matrix2.h"

using namespace Xixels;

const Matrix2 Matrix2::cZero( 0.0f, 0.0f, 0.0f, 0.0f );
const Matrix2 Matrix2::cIdentity( 1.0f, 0.0f, 0.0f, 1.0f );

Matrix2& Matrix2::operator += ( const Matrix2& mat )
{
	m[0][0] += mat.m[0][0]; m[0][1] += mat.m[0][1];
	m[1][0] += mat.m[1][0]; m[1][1] += mat.m[1][1];

	return *this;
}

Matrix2& Matrix2::operator *= ( _float s )
{
	m[0][0] *= s; m[0][1] *= s;
	m[1][0] *= s; m[1][1] *= s;

	return *this;
}

Matrix2& Matrix2::operator *= ( const Matrix2& mat )
{
	_float m00 = m[0][0], m01 = m[0][1], m10 = m[1][0], m11 = m[1][1];

	m[0][0] = m00 * mat.m[0][0] + m01 * mat.m[1][0];
	m[0][1] = m00 * mat.m[0][1] + m01 * mat.m[1][1];
	m[1][0] = m10 * mat.m[0][0] + m11 * mat.m[1][0];
	m[1][1] = m10 * mat.m[0][1] + m11 * mat.m[1][1];

	return *this;
}

_bool Matrix2::operator == ( const Matrix2& mat ) const
{
	return	m[0][0] == mat.m[0][0] && m[0][1] == mat.m[0][1] &&
			m[1][0] == mat.m[1][0] && m[1][1] == mat.m[1][1];
}

_float Matrix2::Determinant( ) const
{
	return m[0][0] * m[1][1] - m[0][1] * m[1][0];
}

Matrix2& Matrix2::Identity( )
{
	m[0][0]	= 1.0f; m[0][1] = 0.0f;
	m[1][0] = 0.0f; m[1][1] = 1.0f;

	return *this;
}

Matrix2& Matrix2::Transpose( )
{
	_float m01 = m[0][1], m10 = m[1][0];

	m[0][1] = m10;
	m[1][0] = m01;

	return *this;
}

Matrix2& Matrix2::Inverse( )
{
	_float d = Determinant( );

	if ( d != 0.0f )
	{
		Adjoint( );

		d = 1.0f / d;

		m[0][0] *= d; m[0][1] *= d;
		m[1][0] *= d; m[1][1] *= d;
	}

	return *this;
}

Matrix2& Matrix2::Adjoint( )
{
	_float m00 = m[0][0], m01 = m[0][1], m10 = m[1][0], m11 = m[1][1];

	m[0][0] =   m11; m[0][1] = - m01;
	m[1][0] = - m10; m[1][1] =   m00;

	return *this;
}

Matrix2& Matrix2::Scaling( _float x, _float y )
{
	m[0][0]	=    x; m[0][1] = 0.0f;
	m[1][0] = 0.0f; m[1][1] =    y;

	return *this;
}

Matrix2& Matrix2::Rotation( _float r )
{
	_float sinvalue = Math::Sin( r ), cosvalue = Math::Cos( r );

	m[0][0]	=   cosvalue; m[0][1] = sinvalue;
	m[1][0] = - sinvalue; m[1][1] = cosvalue;

	return *this;
}

Matrix2& Matrix2::Scaling( const Vector2& v, _float f )
{
	Vector2 n( v );
	n.Normalize( );

	_float k  = f - 1.0f;
	_float xx = n.x * n.x;
	_float yy = n.y * n.y;
	_float xy = n.x * n.y;

	m[0][0]	= 1.0f + k * xx; m[0][1] =        k * xy;
	m[1][0]	=        k * xy; m[1][1] = 1.0f + k * yy;

	return *this;
}