#include "Matrix3x4.h"

const Matrix3x4 Matrix3x4::cZero( 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f );
const Matrix3x4 Matrix3x4::cIdentity( 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f );

Matrix3x4& Matrix3x4::operator += ( const Matrix3x4& mat )
{
	m[0][0] += mat.m[0][0]; m[0][1] += mat.m[0][1]; m[0][2] += mat.m[0][2]; m[0][3] += mat.m[0][3];
	m[1][0] += mat.m[1][0]; m[1][1] += mat.m[1][1]; m[1][2] += mat.m[1][2]; m[1][3] += mat.m[1][3];
	m[2][0] += mat.m[2][0]; m[2][1] += mat.m[2][1]; m[2][2] += mat.m[2][2]; m[2][3] += mat.m[2][3];

	return *this;
}

Matrix3x4& Matrix3x4::operator *= ( _float s )
{
	m[0][0] *= s; m[0][1] *= s; m[0][2] *= s; m[0][3] *= s;
	m[1][0] *= s; m[1][1] *= s; m[1][2] *= s; m[1][3] *= s;
	m[2][0] *= s; m[2][1] *= s; m[2][2] *= s; m[2][3] *= s;

	return *this;
}

_bool Matrix3x4::operator == ( const Matrix3x4& mat ) const
{
	return	m[0][0] == mat.m[0][0] && m[0][1] == mat.m[0][1] && m[0][2] == mat.m[0][2] && m[0][3] == mat.m[0][3] &&
			m[1][0] == mat.m[1][0] && m[1][1] == mat.m[1][1] && m[1][2] == mat.m[1][2] && m[1][3] == mat.m[1][3] &&
			m[2][0] == mat.m[2][0] && m[2][1] == mat.m[2][1] && m[2][2] == mat.m[2][2] && m[2][3] == mat.m[2][3];
}

Matrix3x4& Matrix3x4::Translation( _float x, _float y, _float z )
{
	m[0][0] = 1.0f; m[1][0] = 0.0f; m[2][0] = 0.0f;
	m[0][1] = 0.0f; m[1][1] = 1.0f; m[2][1] = 0.0f;
	m[0][2] = 0.0f; m[1][2] = 0.0f; m[2][2] = 1.0f;
	m[0][3] =    x; m[1][3] =    y; m[2][3] =    z;

	return *this;
}

Matrix3x4& Matrix3x4::RotationX( _float r )
{
	_float sinvalue = Math::Sin( r ), cosvalue = Math::Cos( r );

	m[0][0]	= 1.0f; m[1][0] =       0.0f; m[2][0] =     0.0f;
	m[0][1] = 0.0f; m[1][1] =   cosvalue; m[2][1] = sinvalue;
	m[0][2] = 0.0f; m[1][2] = - sinvalue; m[2][2] = cosvalue;

	return *this;
}

Matrix3x4& Matrix3x4::RotationY( _float r )
{
	_float sinvalue = Math::Sin( r ), cosvalue = Math::Cos( r );

	m[0][0]	= cosvalue; m[1][0] = 0.0f; m[2][0] = - sinvalue;
	m[0][1] =     0.0f; m[1][1] = 1.0f; m[2][1] =       0.0f;
	m[0][2] = sinvalue; m[1][2] = 0.0f; m[2][2] =   cosvalue;

	return *this;
}

Matrix3x4& Matrix3x4::RotationZ( _float r )
{
	_float sinvalue = Math::Sin( r ), cosvalue = Math::Cos( r );

	m[0][0]	=   cosvalue; m[1][0] = sinvalue; m[2][0] = 0.0f;
	m[0][1] = - sinvalue; m[1][1] = cosvalue; m[2][1] = 0.0f;
	m[0][2] =       0.0f; m[1][2] =     0.0f; m[2][2] = 1.0f;

	return *this;
}
