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

Matrix3x4& Matrix3x4::Compose( const Vector3& t, const Matrix3& r, const Vector3& s )
{
	m[0][0] = r.m[0][0]; m[1][0] = r.m[0][1]; m[2][0] = r.m[0][2];
	m[0][1] = r.m[1][0]; m[1][1] = r.m[1][1]; m[2][1] = r.m[1][2];
	m[0][2] = r.m[2][0]; m[1][2] = r.m[2][1]; m[2][2] = r.m[2][2];
	m[0][3] =       t.x; m[1][3] =       t.y; m[2][3] =       t.z;

	if ( s.x != 1.0f )
		{ m[0][0] *= s.x; m[1][0] *= s.x; m[2][0] *= s.x; }
	if ( s.y != 1.0f )
		{ m[0][1] *= s.y; m[1][1] *= s.y; m[2][1] *= s.y; }
	if ( s.z != 1.0f )
		{ m[0][2] *= s.z; m[1][2] *= s.z; m[2][2] *= s.z; }

	return *this;
}

_void Matrix3x4::Decompose( Vector3& t, Matrix3& r, Vector3& s ) const
{
	t.x = m[0][3];
	t.y = m[1][3];
	t.z = m[2][3];

	Vector3 cols[3] = { Vector3( m[0][0], m[1][0], m[2][0] ), Vector3( m[0][1], m[1][1], m[2][1] ), Vector3( m[0][2], m[1][2], m[2][2] ) };

	s.x = cols[0].Magnitude( );
	s.y = cols[1].Magnitude( );
	s.z = cols[2].Magnitude( );

	if ( s.x != 0.0f )
		{ cols[0].x /= s.x; cols[0].y /= s.x; cols[0].z /= s.x; }
	if ( s.y != 0.0f )
		{ cols[1].x /= s.y; cols[1].y /= s.y; cols[1].z /= s.y; }
	if ( s.z != 0.0f )
		{ cols[2].x /= s.z; cols[2].y /= s.z; cols[2].z /= s.z; }

	r.m[0][0] = cols[0].x; r.m[0][1] = cols[0].y; r.m[0][2] = cols[0].z;
	r.m[1][0] = cols[1].x; r.m[1][1] = cols[1].y; r.m[1][2] = cols[1].z;
	r.m[2][0] = cols[2].x; r.m[2][1] = cols[2].y; r.m[2][2] = cols[2].z;
}
