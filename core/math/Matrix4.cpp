#include "Matrix4.h"

using namespace Xixels;

const Matrix4 Matrix4::cZero( 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f );
const Matrix4 Matrix4::cIdentity( 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f );
const Matrix4 Matrix4::cClip2Image( 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -0.5f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f );

const Matrix4 Matrix4::cMirrorX( -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f );
const Matrix4 Matrix4::cMirrorY( 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f );
const Matrix4 Matrix4::cMirrorZ( 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f );

const Matrix4 Matrix4::cProjectXY( 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f );
const Matrix4 Matrix4::cProjectYZ( 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f );
const Matrix4 Matrix4::cProjectZX( 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f );

const Matrix4 Matrix4::cRefectionXY( 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f );
const Matrix4 Matrix4::cRefectionYZ( -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f );
const Matrix4 Matrix4::cRefectionZX( 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f );

Matrix4 Matrix4::CreateOrthoLH( _float width, _float height, _float znear, _float zfar )
{
	_float xs = 2.0f / width;
	_float ys = 2.0f / height;
	_float zf = 1.0f / ( zfar - znear );
	_float zn = - znear * zf;

	return Matrix4(
		  xs, 0.0f, 0.0f, 0.0f,
		0.0f,   ys, 0.0f, 0.0f,
		0.0f, 0.0f,   zf, 0.0f,
		0.0f, 0.0f,   zn, 1.0f );
}

Matrix4 Matrix4::CreateOrthoOffCenterLH( _float left, _float right, _float bottom, _float top, _float znear, _float zfar )
{
	_float xs1 = 2.0f / ( right - left );
	_float xs2 = ( left + right ) / ( left - right );
	_float ys1 = 2.0f / ( top - bottom );
	_float ys2 = ( bottom + top ) / ( bottom - top );
	_float zf  = 1.0f / ( zfar - znear );
	_float zn  = - znear * zf;

	return Matrix4(
		 xs1, 0.0f, 0.0f, 0.0f,
		0.0f,  ys1, 0.0f, 0.0f,
		0.0f, 0.0f,   zf, 0.0f,
		 xs2,  ys2,   zn, 1.0f );
}

Matrix4 Matrix4::CreateOrthoRH( _float width, _float height, _float znear, _float zfar )
{
	_float xs = 2.0f / width;
	_float ys = 2.0f / height;
	_float zf = 1.0f / ( znear - zfar );
	_float zn = znear * zf;

	return Matrix4(
		  xs, 0.0f, 0.0f, 0.0f,
		0.0f,   ys, 0.0f, 0.0f,
		0.0f, 0.0f,   zf, 0.0f,
		0.0f, 0.0f,   zn, 1.0f );
}

Matrix4 Matrix4::CreateOrthoOffCenterRH( _float left, _float right, _float bottom, _float top, _float znear, _float zfar )
{
	_float xs1 = 2.0f / ( right - left );
	_float xs2 = ( left + right ) / ( left - right );
	_float ys1 = 2.0f / ( top - bottom );
	_float ys2 = ( bottom + top ) / ( bottom - top );
	_float zf  = 1.0f / ( znear - zfar );
	_float zn  = znear * zf;

	return Matrix4(
		 xs1, 0.0f, 0.0f, 0.0f,
		0.0f,  ys1, 0.0f, 0.0f,
		0.0f, 0.0f,   zf, 0.0f,
		 xs2,  ys2,   zn, 1.0f );
}

Matrix4 Matrix4::CreatePerspectiveLH( _float width, _float height, _float znear, _float zfar )
{
	_float xs = 2.0f * znear / width;
	_float ys = 2.0f * znear / height;
	_float zf = zfar / ( zfar - znear );
	_float zn = - znear * zf;

	return Matrix4(
		  xs, 0.0f, 0.0f, 0.0f,
		0.0f,   ys, 0.0f, 0.0f,
		0.0f, 0.0f,   zf, 1.0f,
		0.0f, 0.0f,   zn, 0.0f );
}

Matrix4 Matrix4::CreatePerspectiveFovLH( _float fovy, _float aspect, _float znear, _float zfar )
{
	_float ys = Math::Cot( fovy / 2.0f );
	_float xs = ys / aspect;
	_float zf = zfar / ( zfar - znear );
	_float zn = - znear * zf;

	return Matrix4(
		  xs, 0.0f, 0.0f, 0.0f,
		0.0f,   ys, 0.0f, 0.0f,
		0.0f, 0.0f,   zf, 1.0f,
		0.0f, 0.0f,   zn, 0.0f );
}

Matrix4 Matrix4::CreatePerspectiveOffCenterLH( _float left, _float right, _float bottom, _float top, _float znear, _float zfar )
{
	_float xs1 = 2.0f * znear / ( right - left );
	_float xs2 = ( left + right ) / ( left - right );
	_float ys1 = 2.0f * znear / ( top - bottom );
	_float ys2 = ( bottom + top ) / ( bottom - top );
	_float zf  = zfar / ( zfar - znear );
	_float zn  = - znear * zf;

	return Matrix4(
		 xs1, 0.0f, 0.0f, 0.0f,
		0.0f,  ys1, 0.0f, 0.0f,
		 xs2,  ys2,   zf, 1.0f,
		0.0f, 0.0f,   zn, 0.0f );
}

Matrix4 Matrix4::CreatePerspectiveRH( _float width, _float height, _float znear, _float zfar )
{
	_float xs = 2.0f * znear / width;
	_float ys = 2.0f * znear / height;
	_float zf = zfar / ( znear - zfar );
	_float zn = znear * zf;

	return Matrix4(
		  xs, 0.0f, 0.0f,  0.0f,
		0.0f,   ys, 0.0f,  0.0f,
		0.0f, 0.0f,   zf, -1.0f,
		0.0f, 0.0f,   zn,  0.0f );
}

Matrix4 Matrix4::CreatePerspectiveFovRH( _float fovy, _float aspect, _float znear, _float zfar )
{
	_float ys = Math::Cot( fovy / 2.0f );
	_float xs = ys / aspect;
	_float zf = zfar / ( znear - zfar );
	_float zn = znear * zf;

	return Matrix4(
		  xs, 0.0f, 0.0f,  0.0f,
		0.0f,   ys, 0.0f,  0.0f,
		0.0f, 0.0f,   zf, -1.0f,
		0.0f, 0.0f,   zn,  0.0f );
}

Matrix4 Matrix4::CreatePerspectiveOffCenterRH( _float left, _float right, _float bottom, _float top, _float znear, _float zfar )
{
	_float xs1 = 2.0f * znear / ( right - left );
	_float xs2 = ( left + right ) / ( right - left );
	_float ys1 = 2.0f * znear / ( top - bottom );
	_float ys2 = ( bottom + top ) / ( top - bottom );
	_float zf  = zfar / ( znear - zfar );
	_float zn  = znear * zf;

	return Matrix4(
		 xs1, 0.0f, 0.0f,  0.0f,
		0.0f,  ys1, 0.0f,  0.0f,
		 xs2,  ys2,   zf, -1.0f,
		0.0f, 0.0f,   zn,  0.0f );
}

Matrix4 Matrix4::CreateTranslate( const Vector3& translate )
{
	return Matrix4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		translate.x, translate.y, translate.z, 1.0f );
}

Matrix4 Matrix4::CreateLookAtLH( const Vector3& eye, const Vector3& lookat, const Vector3& upaxis )
{
	Vector3 zaxis = ( lookat - eye ).Normalize( );
	Vector3 xaxis = Vector3::Cross( upaxis, zaxis ).Normalize( );
	Vector3 yaxis = Vector3::Cross( zaxis, xaxis );

	_float xeye = - Vector3::Dot( xaxis, eye );
	_float yeye = - Vector3::Dot( yaxis, eye );
	_float zeye = - Vector3::Dot( zaxis, eye );

	return Matrix4(
		xaxis.x, yaxis.x, zaxis.x, 0.0f,
		xaxis.y, yaxis.y, zaxis.y, 0.0f,
		xaxis.z, yaxis.z, zaxis.z, 0.0f,
		   xeye,    yeye,    zeye, 1.0f );
}

Matrix4 Matrix4::CreateLookAtRH( const Vector3& eye, const Vector3& lookat, const Vector3& upaxis )
{
	Vector3 zaxis = ( eye - lookat ).Normalize( );
	Vector3 xaxis = Vector3::Cross( upaxis, zaxis ).Normalize( );
	Vector3 yaxis = Vector3::Cross( zaxis, xaxis );

	_float xeye = - Vector3::Dot( xaxis, eye );
	_float yeye = - Vector3::Dot( yaxis, eye );
	_float zeye = - Vector3::Dot( zaxis, eye );

	return Matrix4(
		xaxis.x, yaxis.x, zaxis.x, 0.0f,
		xaxis.y, yaxis.y, zaxis.y, 0.0f,
		xaxis.z, yaxis.z, zaxis.z, 0.0f,
		   xeye,    yeye,    zeye, 1.0f );
}

Matrix4 Matrix4::CreatePlanarShadow( const Vector3& L, const Vector3& N, _float D )
{
	_float NoL = Vector3::Dot( N, L );
	return Matrix4(
		1 - N.x * L.x / NoL,   - N.y * L.x / NoL,   - N.z * L.x / NoL, - D * L.x / NoL,
		  - N.x * L.y / NoL, 1 - N.y * L.y / NoL,   - N.z * L.y / NoL, - D * L.y / NoL,
		  - N.x * L.z / NoL,    -N.y * L.z / NoL, 1 - N.z * L.z / NoL, - D * L.z / NoL,
		0,0,0,1
	).Transpose( );
}

Matrix4 Matrix4::Lerp( const Matrix4& mat1, const Matrix4& mat2, _float f )
{
	Vector3 t1, s1; Quaternion r1;
	mat1.Decompose( t1, r1, s1 );

	Vector3 t2, s2; Quaternion r2;
	mat2.Decompose( t2, r2, s2 );

	Vector3 t0 = Vector3::Lerp( t1, t2, f );
	Vector3 s0 = Vector3::Lerp( s1, s2, f );
	Quaternion r0 = Quaternion::Slerp( r1, r2, f );

	return Matrix4( ).Compose( t0, r0, s0 );
}

Matrix4& Matrix4::operator += ( const Matrix4& mat )
{
	m[0][0] += mat.m[0][0]; m[0][1] += mat.m[0][1]; m[0][2] += mat.m[0][2]; m[0][3] += mat.m[0][3];
	m[1][0] += mat.m[1][0]; m[1][1] += mat.m[1][1]; m[1][2] += mat.m[1][2]; m[1][3] += mat.m[1][3];
	m[2][0] += mat.m[2][0]; m[2][1] += mat.m[2][1]; m[2][2] += mat.m[2][2]; m[2][3] += mat.m[2][3];
	m[3][0] += mat.m[3][0]; m[3][1] += mat.m[3][1]; m[3][2] += mat.m[3][2]; m[3][3] += mat.m[3][3];

	return *this;
}

Matrix4& Matrix4::operator *= ( const Matrix4& mat )
{
	// TODO.

	return *this;
}

Matrix4& Matrix4::operator *= ( _float s )
{
	m[0][0] *= s; m[0][1] *= s; m[0][2] *= s; m[0][3] *= s;
	m[1][0] *= s; m[1][1] *= s; m[1][2] *= s; m[1][3] *= s;
	m[2][0] *= s; m[2][1] *= s; m[2][2] *= s; m[2][3] *= s;
	m[3][0] *= s; m[3][1] *= s; m[3][2] *= s; m[3][3] *= s;

	return *this;
}

_bool Matrix4::operator == ( const Matrix4& mat ) const
{
	return	m[0][0] == mat.m[0][0] && m[0][1] == mat.m[0][1] && m[0][2] == mat.m[0][2] && m[0][3] == mat.m[0][3] &&
			m[1][0] == mat.m[1][0] && m[1][1] == mat.m[1][1] && m[1][2] == mat.m[1][2] && m[1][3] == mat.m[1][3] &&
			m[2][0] == mat.m[2][0] && m[2][1] == mat.m[2][1] && m[2][2] == mat.m[2][2] && m[2][3] == mat.m[2][3] &&
			m[3][0] == mat.m[3][0] && m[3][1] == mat.m[3][1] && m[3][2] == mat.m[3][2] && m[3][3] == mat.m[3][3];
}

_bool Matrix4::HasTranslation( ) const
{
	return	m[3][0] != 0.0f || m[3][1] != 0.0f || m[3][2] != 0.0f;
}

_bool Matrix4::HasRotation( ) const
{
	return	m[0][1] != 0.0f ||
			( m[0][2] != 0.0f || m[1][0] != 0.0f ) ||
			( m[1][2] != 0.0f || m[2][0] != 0.0f ) ||
			m[2][1] != 0.0f;
}

_float Matrix4::Determinant( ) const
{
	return	m[0][0] * Matrix3( m[1][1], m[1][2], m[1][3], m[2][1], m[2][2], m[2][3], m[3][1], m[3][2], m[3][3] ).Determinant( )
		-	m[0][1] * Matrix3( m[1][0], m[1][2], m[1][3], m[2][0], m[2][2], m[2][3], m[3][0], m[3][2], m[3][3] ).Determinant( )
		+	m[0][2] * Matrix3( m[1][0], m[1][1], m[1][3], m[2][0], m[2][1], m[2][3], m[3][0], m[3][1], m[3][3] ).Determinant( )
		-	m[0][3] * Matrix3( m[1][0], m[1][1], m[1][2], m[2][0], m[2][1], m[2][2], m[3][0], m[3][1], m[3][2] ).Determinant( );
}

Matrix4& Matrix4::Identity( )
{
	m[0][0]	= 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
	m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
	m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
	m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;

	return *this;
}

Matrix4& Matrix4::Transpose( )
{
	_float m01 = m[0][1], m02 = m[0][2], m03 = m[0][3], m10 = m[1][0], m12 = m[1][2], m13 = m[1][3],
		m20 = m[2][0], m21 = m[2][1], m23 = m[2][3], m30 = m[3][0], m31 = m[3][1], m32 = m[3][2];

	m[0][1] = m10; m[0][2] = m20; m[0][3] = m30;
	m[1][0] = m01; m[1][2] = m21; m[1][3] = m31;
	m[2][0] = m02; m[2][1] = m12; m[2][3] = m32;
	m[3][0] = m03; m[3][1] = m13; m[3][2] = m23;

	return *this;
}

Matrix4 Matrix4::InverseProjection( ) const
{
	if ( m[1][0] == 0.0f &&
		 m[3][0] == 0.0f &&
		 m[0][1] == 0.0f &&
		 m[3][1] == 0.0f &&
		 m[0][2] == 0.0f &&
		 m[1][2] == 0.0f &&
		 m[0][3] == 0.0f &&
		 m[1][3] == 0.0f &&
		 m[2][3] == 1.0f &&
		 m[3][3] == 0.0f )
	{
		double a = m[0][0];
		double b = m[1][1];
		double c = m[2][2];
		double d = m[3][2];
		double s = m[2][0];
		double t = m[2][1];

		return Matrix4(
			_float(1.0 / a), 0.0f, 0.0f, 0.0f,
			0.0f, _float( 1.0 / b ), 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, _float( 1.0 / d ),
			_float( -s / a ), _float( -t / b ), 1.0f, _float( -c / d ) );
	}
	else
	{
		//return Inverse( );
		Vector3 X( m[0][0], m[0][1], m[0][2] );
		Vector3 Y( m[0][0], m[0][1], m[0][2] );
		Vector3 Z( m[0][0], m[0][1], m[0][2] );

		if ( X.IsNearlyZero( 1.e-8f ) && Y.IsNearlyZero( 1.e-8f ) && Z.IsNearlyZero( 1.e-8f ) )
		{
			return Matrix4::cIdentity;
		}
		else
		{
			const _float det = Determinant( );
			if ( det == 0.0f )
			{
				return Matrix4::cIdentity;
			}
			else
			{
				//typedef _float Float4x4[4][4];
				const Matrix4& M = *this;
				Matrix4 Result;
				float Det[4];
				Matrix4 Tmp;

				Tmp.m[0][0] = M.m[2][2] * M.m[3][3] - M.m[2][3] * M.m[3][2];
				Tmp.m[0][1] = M.m[1][2] * M.m[3][3] - M.m[1][3] * M.m[3][2];
				Tmp.m[0][2] = M.m[1][2] * M.m[2][3] - M.m[1][3] * M.m[2][2];

				Tmp.m[1][0] = M.m[2][2] * M.m[3][3] - M.m[2][3] * M.m[3][2];
				Tmp.m[1][1] = M.m[0][2] * M.m[3][3] - M.m[0][3] * M.m[3][2];
				Tmp.m[1][2] = M.m[0][2] * M.m[2][3] - M.m[0][3] * M.m[2][2];

				Tmp.m[2][0] = M.m[1][2] * M.m[3][3] - M.m[1][3] * M.m[3][2];
				Tmp.m[2][1] = M.m[0][2] * M.m[3][3] - M.m[0][3] * M.m[3][2];
				Tmp.m[2][2] = M.m[0][2] * M.m[1][3] - M.m[0][3] * M.m[1][2];

				Tmp.m[3][0] = M.m[1][2] * M.m[2][3] - M.m[1][3] * M.m[2][2];
				Tmp.m[3][1] = M.m[0][2] * M.m[2][3] - M.m[0][3] * M.m[2][2];
				Tmp.m[3][2] = M.m[0][2] * M.m[1][3] - M.m[0][3] * M.m[1][2];

				Det[0] = M.m[1][1] * Tmp.m[0][0] - M.m[2][1] * Tmp.m[0][1] + M.m[3][1] * Tmp.m[0][2];
				Det[1] = M.m[0][1] * Tmp.m[1][0] - M.m[2][1] * Tmp.m[1][1] + M.m[3][1] * Tmp.m[1][2];
				Det[2] = M.m[0][1] * Tmp.m[2][0] - M.m[1][1] * Tmp.m[2][1] + M.m[3][1] * Tmp.m[2][2];
				Det[3] = M.m[0][1] * Tmp.m[3][0] - M.m[1][1] * Tmp.m[3][1] + M.m[2][1] * Tmp.m[3][2];

				float Determinant = M.m[0][0] * Det[0] - M.m[1][0] * Det[1] + M.m[2][0] * Det[2] - M.m[3][0] * Det[3];
				const float RDet = 1.0f / Determinant;

				Result.m[0][0] = RDet * Det[0];
				Result.m[0][1] = -RDet * Det[1];
				Result.m[0][2] = RDet * Det[2];
				Result.m[0][3] = -RDet * Det[3];
				Result.m[1][0] = -RDet * ( M.m[1][0] * Tmp.m[0][0] - M.m[2][0] * Tmp.m[0][1] + M.m[3][0] * Tmp.m[0][2] );
				Result.m[1][1] = RDet * ( M.m[0][0] * Tmp.m[1][0] - M.m[2][0] * Tmp.m[1][1] + M.m[3][0] * Tmp.m[1][2] );
				Result.m[1][2] = -RDet * ( M.m[0][0] * Tmp.m[2][0] - M.m[1][0] * Tmp.m[2][1] + M.m[3][0] * Tmp.m[2][2] );
				Result.m[1][3] = RDet * ( M.m[0][0] * Tmp.m[3][0] - M.m[1][0] * Tmp.m[3][1] + M.m[2][0] * Tmp.m[3][2] );
				Result.m[2][0] = RDet * ( M.m[1][0] * ( M.m[2][1] * M.m[3][3] - M.m[2][3] * M.m[3][1] ) -
										M.m[2][0] * ( M.m[1][1] * M.m[3][3] - M.m[1][3] * M.m[3][1] ) +
										M.m[3][0] * ( M.m[1][1] * M.m[2][3] - M.m[1][3] * M.m[2][1] ) );
				Result.m[2][1] = -RDet * ( M.m[0][0] * ( M.m[2][1] * M.m[3][3] - M.m[2][3] * M.m[3][1] ) -
										 M.m[2][0] * ( M.m[0][1] * M.m[3][3] - M.m[0][3] * M.m[3][1] ) +
										 M.m[3][0] * ( M.m[0][1] * M.m[2][3] - M.m[0][3] * M.m[2][1] ) );
				Result.m[2][2] = RDet * ( M.m[0][0] * ( M.m[1][1] * M.m[3][3] - M.m[1][3] * M.m[3][1] ) -
										M.m[1][0] * ( M.m[0][1] * M.m[3][3] - M.m[0][3] * M.m[3][1] ) +
										M.m[3][0] * ( M.m[0][1] * M.m[1][3] - M.m[0][3] * M.m[1][1] ) );
				Result.m[2][3] = -RDet * ( M.m[0][0] * ( M.m[1][1] * M.m[2][3] - M.m[1][3] * M.m[2][1] ) -
										 M.m[1][0] * ( M.m[0][1] * M.m[2][3] - M.m[0][3] * M.m[2][1] ) +
										 M.m[2][0] * ( M.m[0][1] * M.m[1][3] - M.m[0][3] * M.m[1][1] ) );
				Result.m[3][0] = -RDet * ( M.m[1][0] * ( M.m[2][1] * M.m[3][2] - M.m[2][2] * M.m[3][1] ) -
										 M.m[2][0] * ( M.m[1][1] * M.m[3][2] - M.m[1][2] * M.m[3][1] ) +
										 M.m[3][0] * ( M.m[1][1] * M.m[2][2] - M.m[1][2] * M.m[2][1] ) );
				Result.m[3][1] = RDet * ( M.m[0][0] * ( M.m[2][1] * M.m[3][2] - M.m[2][2] * M.m[3][1] ) -
										M.m[2][0] * ( M.m[0][1] * M.m[3][2] - M.m[0][2] * M.m[3][1] ) +
										M.m[3][0] * ( M.m[0][1] * M.m[2][2] - M.m[0][2] * M.m[2][1] ) );
				Result.m[3][2] = -RDet * ( M.m[0][0] * ( M.m[1][1] * M.m[3][2] - M.m[1][2] * M.m[3][1] ) -
										 M.m[1][0] * ( M.m[0][1] * M.m[3][2] - M.m[0][2] * M.m[3][1] ) +
										 M.m[3][0] * ( M.m[0][1] * M.m[1][2] - M.m[0][2] * M.m[1][1] ) );
				Result.m[3][3] = RDet * ( M.m[0][0] * ( M.m[1][1] * M.m[2][2] - M.m[1][2] * M.m[2][1] ) -
										M.m[1][0] * ( M.m[0][1] * M.m[2][2] - M.m[0][2] * M.m[2][1] ) +
										M.m[2][0] * ( M.m[0][1] * M.m[1][2] - M.m[0][2] * M.m[1][1] ) );
				return Result;
			}

		}
	}
}

_void Matrix4::DismantleViewMatrix( Vector3& translate, Matrix4& rotate ) const
{
	translate = Vector4::cOrigin;
	rotate = Matrix4::cZero;

	_float w = m[3][3];

	translate.x = m[3][0] / w;
	translate.y = m[3][1] / w;
	translate.z = m[3][2] / w;

	rotate.m[0][0] = m[0][0];
	rotate.m[0][1] = m[0][1];
	rotate.m[0][2] = m[0][2];

	rotate.m[1][0] = m[1][0];
	rotate.m[1][1] = m[1][1];
	rotate.m[1][2] = m[1][2];

	rotate.m[2][0] = m[2][0];
	rotate.m[2][1] = m[2][1];
	rotate.m[2][2] = m[2][2];

	rotate.m[3][3] = m[3][3];
}


Matrix4& Matrix4::Inverse( )
{
	_float d = Determinant( );

	if ( d != 0.0f )
	{
		Adjoint( );

		// Multiply 1/d is faster but may magnify margins.
		d = 1.0f / d;

		m[0][0] *= d; m[0][1] *= d; m[0][2] *= d; m[0][3] *= d;
		m[1][0] *= d; m[1][1] *= d; m[1][2] *= d; m[1][3] *= d;
		m[2][0] *= d; m[2][1] *= d; m[2][2] *= d; m[2][3] *= d;
		m[3][0] *= d; m[3][1] *= d; m[3][2] *= d; m[3][3] *= d;
	}

	return *this;
}

Matrix4& Matrix4::Adjoint( )
{
	_float m00 = m[0][0], m01 = m[0][1], m02 = m[0][2], m03 = m[0][3], m10 = m[1][0], m11 = m[1][1], m12 = m[1][2], m13 = m[1][3],
		m20 = m[2][0], m21 = m[2][1], m22 = m[2][2], m23 = m[2][3], m30 = m[3][0], m31 = m[3][1], m32 = m[3][2], m33 = m[3][3];

	m[0][0] =   Matrix3( m11, m12, m13, m21, m22, m23, m31, m32, m33 ).Determinant( );
	m[1][0] = - Matrix3( m10, m12, m13, m20, m22, m23, m30, m32, m33 ).Determinant( );
	m[2][0] =   Matrix3( m10, m11, m13, m20, m21, m23, m30, m31, m33 ).Determinant( );
	m[3][0] = - Matrix3( m10, m11, m12, m20, m21, m22, m30, m31, m32 ).Determinant( );

	m[0][1] = - Matrix3( m01, m02, m03, m21, m22, m23, m31, m32, m33 ).Determinant( );
	m[1][1] =   Matrix3( m00, m02, m03, m20, m22, m23, m30, m32, m33 ).Determinant( );
	m[2][1] = - Matrix3( m00, m01, m03, m20, m21, m23, m30, m31, m33 ).Determinant( );
	m[3][1] =   Matrix3( m00, m01, m02, m20, m21, m22, m30, m31, m32 ).Determinant( );

	m[0][2] =	Matrix3( m01, m02, m03, m11, m12, m13, m31, m32, m33 ).Determinant( );
	m[1][2] = - Matrix3( m00, m02, m03, m10, m12, m13, m30, m32, m33 ).Determinant( );
	m[2][2] =   Matrix3( m00, m01, m03, m10, m11, m13, m30, m31, m33 ).Determinant( );
	m[3][2] = - Matrix3( m00, m01, m02, m10, m11, m12, m30, m31, m32 ).Determinant( );

	m[0][3] = - Matrix3( m01, m02, m03, m11, m12, m13, m21, m22, m23 ).Determinant( );
	m[1][3] =   Matrix3( m00, m02, m03, m10, m12, m13, m20, m22, m23 ).Determinant( );
	m[2][3] = - Matrix3( m00, m01, m03, m10, m11, m13, m20, m21, m23 ).Determinant( );
	m[3][3] =   Matrix3( m00, m01, m02, m10, m11, m12, m20, m21, m22 ).Determinant( );

	return *this;
}

Matrix4& Matrix4::Translation( _float x, _float y, _float z )
{
	m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
	m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
	m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
	m[3][0] =    x; m[3][1] =    y; m[3][2] =    z; m[3][3] = 1.0f;

	return *this;
}

Matrix4& Matrix4::RotationX( _float r )
{
	_float sinvalue = Math::Sin( r ), cosvalue = Math::Cos( r );

	m[0][0]	= 1.0f; m[0][1] =       0.0f; m[0][2] =     0.0f; m[0][3] = 0.0f;
	m[1][0] = 0.0f; m[1][1] =   cosvalue; m[1][2] = sinvalue; m[1][3] = 0.0f;
	m[2][0] = 0.0f; m[2][1] = - sinvalue; m[2][2] = cosvalue; m[2][3] = 0.0f;
	m[3][0] = 0.0f; m[3][1] =       0.0f; m[3][2] =     0.0f; m[3][3] = 1.0f;

	return *this;
}

Matrix4& Matrix4::RotationY( _float r )
{
	_float sinvalue = Math::Sin( r ), cosvalue = Math::Cos( r );

	m[0][0]	= cosvalue; m[0][1] = 0.0f; m[0][2] = - sinvalue; m[0][3] = 0.0f;
	m[1][0] =     0.0f; m[1][1] = 1.0f; m[1][2] =       0.0f; m[1][3] = 0.0f;
	m[2][0] = sinvalue; m[2][1] = 0.0f; m[2][2] =   cosvalue; m[2][3] = 0.0f;
	m[3][0] =     0.0f; m[3][1] = 0.0f; m[3][2] =       0.0f; m[3][3] = 1.0f;

	return *this;
}

Matrix4& Matrix4::RotationZ( _float r )
{
	_float sinvalue = Math::Sin( r ), cosvalue = Math::Cos( r );

	m[0][0]	=   cosvalue; m[0][1] = sinvalue; m[0][2] = 0.0f; m[0][3] = 0.0f;
	m[1][0] = - sinvalue; m[1][1] = cosvalue; m[1][2] = 0.0f; m[1][3] = 0.0f;
	m[2][0] =       0.0f; m[2][1] =     0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
	m[3][0] =       0.0f; m[3][1] =     0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;

	return *this;
}

Matrix4& Matrix4::Rotation( const Vector3& a, _float r )
{
	_float sinvalue = Math::Sin( r ), cosvalue = Math::Cos( r ), cosreverse = 1.0f - cosvalue;

	Vector3 n( a );
	n.Normalize( );

	m[0][0] = cosreverse * n.x * n.x + cosvalue;
	m[0][1] = cosreverse * n.x * n.y + sinvalue * n.z;
	m[0][2] = cosreverse * n.x * n.z - sinvalue * n.y;
	m[0][3] = 0.0f;

	m[1][0] = cosreverse * n.x * n.y - sinvalue * n.z;
	m[1][1] = cosreverse * n.y * n.y + cosvalue;
	m[1][2] = cosreverse * n.y * n.z + sinvalue * n.x;
	m[1][3] = 0.0f;

	m[2][0] = cosreverse * n.x * n.z + sinvalue * n.y;
	m[2][1] = cosreverse * n.y * n.z - sinvalue * n.x;
	m[2][2] = cosreverse * n.z * n.z + cosvalue;
	m[2][3] = 0.0f;

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 0.0f;
	m[3][3] = 1.0f;

	return *this;
}

Matrix4& Matrix4::Rotation( const Quaternion& q )
{
	_float xx = q.x * q.x * 2.0f, yy = q.y * q.y * 2.0f, zz = q.z * q.z * 2.0f;
	_float xy = q.x * q.y * 2.0f, zw = q.z * q.w * 2.0f, xz = q.x * q.z * 2.0f;
	_float yw = q.y * q.w * 2.0f, yz = q.y * q.z * 2.0f, xw = q.x * q.w * 2.0f;

	m[0][0] = 1.0f - yy - zz; m[0][1] =        xy + zw; m[0][2] =        xz - yw; m[0][3] = 0.0f;
	m[1][0] =        xy - zw; m[1][1] = 1.0f - xx - zz; m[1][2] =        yz + xw; m[1][3] = 0.0f;
	m[2][0] =        xz + yw; m[2][1] =        yz - xw; m[2][2] = 1.0f - xx - yy; m[2][3] = 0.0f;
	m[3][0] =           0.0f; m[3][1] =           0.0f; m[3][2] =           0.0f; m[3][3] = 1.0f;

	return *this;
}

Matrix4& Matrix4::Scaling( _float x, _float y, _float z )
{
	m[0][0]	=    x; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
	m[1][0] = 0.0f; m[1][1] =    y; m[1][2] = 0.0f; m[1][3] = 0.0f;
	m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] =    z; m[2][3] = 0.0f;
	m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;

	return *this;
}

Matrix4& Matrix4::Scaling( const Vector3& v, _float f )
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

	m[0][0]	= 1.0f + k * xx; m[0][1] =        k * xy; m[0][2] =        k * zx; m[0][3] = 0.0f;
	m[1][0]	=        k * xy; m[1][1] = 1.0f + k * yy; m[1][2] =        k * yz; m[1][3] = 0.0f;
    m[2][0]	=        k * zx; m[2][1] =        k * yz; m[2][2] = 1.0f + k * zz; m[2][3] = 0.0f;
	m[3][0] =          0.0f; m[3][1] =          0.0f; m[3][2] =          0.0f; m[3][3] = 1.0f;

	return *this;
}

Vector3 Matrix4::TransformPosition( const Vector3& pos ) const
{
	Vector4 v( pos, 1.0f );
	v *= *this;
	return Vector3( v );
}

Vector3 Matrix4::TransformVector( const Vector3& vec ) const
{
	Vector4 v( vec, 0.0f );
	v *= *this;
	return Vector3( v );
}

Matrix4& Matrix4::Compose( const Vector3& x, const Vector3& y, const Vector3& z, const Vector3& o )
{
	Vector3 nx = x; nx.Normalize( );
	Vector3 ny = y; ny.Normalize( );
	Vector3 nz = z; nz.Normalize( );

	m[0][0] = nx.x; m[0][1] = nx.y; m[0][2] = nx.z; m[0][3] = 0.0f;
	m[1][0] = ny.x; m[1][1] = ny.y; m[1][2] = ny.z; m[1][3] = 0.0f;
	m[2][0] = nz.x; m[2][1] = nz.y; m[2][2] = nz.z; m[2][3] = 0.0f;
	m[3][0] =  o.x; m[3][1] =  o.y; m[3][2] =  o.z; m[3][3] = 1.0f;

	return *this;
}

Matrix4& Matrix4::Compose( const Vector3& t, const Matrix3& r, const Vector3& s )
{
	m[0][0] = r.m[0][0]; m[0][1] = r.m[0][1]; m[0][2] = r.m[0][2]; m[0][3] = 0.0f;
	m[1][0] = r.m[1][0]; m[1][1] = r.m[1][1]; m[1][2] = r.m[1][2]; m[1][3] = 0.0f;
	m[2][0] = r.m[2][0]; m[2][1] = r.m[2][1]; m[2][2] = r.m[2][2]; m[2][3] = 0.0f;
	m[3][0] =       t.x; m[3][1] =       t.y; m[3][2] =       t.z; m[3][3] = 1.0f;

	if ( s.x != 1.0f )
		{ m[0][0] *= s.x; m[0][1] *= s.x; m[0][2] *= s.x; }
	if ( s.y != 1.0f )
		{ m[1][0] *= s.y; m[1][1] *= s.y; m[1][2] *= s.y; }
	if ( s.z != 1.0f )
		{ m[2][0] *= s.z; m[2][1] *= s.z; m[2][2] *= s.z; }

	return *this;
}

_void Matrix4::Decompose( Vector3& x, Vector3& y, Vector3& z, Vector3& t )
{
	x.x = m[0][0]; x.y = m[0][1]; x.z = m[0][2];
	y.x = m[1][0]; y.y = m[1][1]; y.z = m[1][2];
	z.x = m[2][0]; z.y = m[2][1]; z.z = m[2][2];
	t.x = m[3][0]; t.y = m[3][1]; t.z = m[3][2];
}

_void Matrix4::Decompose( Vector3& t, Matrix3& r, Vector3& s ) const
{
	t.x = m[3][0];
	t.y = m[3][1];
	t.z = m[3][2];

	Vector3 cols[3] = { Vector3( m[0][0], m[0][1], m[0][2] ), Vector3( m[1][0], m[1][1], m[1][2] ), Vector3( m[2][0], m[2][1], m[2][2] ) };

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