#pragma once

#include "Math.hpp"
#include "Matrix3.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Quaternion.h"

namespace Xixels
{

class Matrix4
{
public:
	// The zero matrix.
	const static Matrix4 cZero;
	// The identity matrix.
	const static Matrix4 cIdentity;
	// The clip space to image space matrix.
	const static Matrix4 cClip2Image;
	// The mirror matrix for x-axis.
	const static Matrix4 cMirrorX;
	// The mirror matrix for y-axis.
	const static Matrix4 cMirrorY;
	// The mirror matrix for z-axis.
	const static Matrix4 cMirrorZ;
	// The projection matrix by project onto xy-plane.
	const static Matrix4 cProjectXY;
	// The projection matrix by project onto yz-plane.
	const static Matrix4 cProjectYZ;
	// The projection matrix by project onto zx-plane.
	const static Matrix4 cProjectZX;
	// The reflection matrix by flip around xy-plane.
	const static Matrix4 cRefectionXY;
	// The reflection matrix by flip around yz-plane.
	const static Matrix4 cRefectionYZ;
	// The reflection matrix by flip around zx-plane.
	const static Matrix4 cRefectionZX;

	// Build a left-handed orthogonal projection matrix.
	static Matrix4 CreateOrthoLH( _float width, _float height, _float znear, _float zfar );
	// Build a left-handed orthogonal projection matrix.
	static Matrix4 CreateOrthoOffCenterLH( _float left, _float right, _float bottom, _float top, _float znear, _float zfar );

	// Build a right-handed orthogonal projection matrix.
	static Matrix4 CreateOrthoRH( _float width, _float height, _float znear, _float zfar );
	// Build a right-handed orthogonal projection matrix.
	static Matrix4 CreateOrthoOffCenterRH( _float left, _float right, _float bottom, _float top, _float znear, _float zfar );

	// Build a left-handed perspective projection matrix.
	static Matrix4 CreatePerspectiveLH( _float width, _float height, _float znear, _float zfar );
	// Build a left-handed perspective projection matrix.
	static Matrix4 CreatePerspectiveFovLH( _float fovy, _float aspect, _float znear, _float zfar );
	// Build a left-handed perspective projection matrix.
	static Matrix4 CreatePerspectiveOffCenterLH( _float left, _float right, _float bottom, _float top, _float znear, _float zfar );

	// Build a right-handed perspective projection matrix.
	static Matrix4 CreatePerspectiveRH( _float width, _float height, _float znear, _float zfar );
	// Build a right-handed perspective projection matrix.
	static Matrix4 CreatePerspectiveFovRH( _float fovy, _float aspect, _float znear, _float zfar );
	// Build a right-handed perspective projection matrix.
	static Matrix4 CreatePerspectiveOffCenterRH( _float left, _float right, _float bottom, _float top, _float znear, _float zfar );

	// Build a translate matrix.
	static Matrix4 CreateTranslate( const Vector3& translate );

	// Build a left-handed look-at matrix.
	static Matrix4 CreateLookAtLH( const Vector3& eye, const Vector3& lookat, const Vector3& upaxis );
	// Build a right-handed look-at matrix.
	static Matrix4 CreateLookAtRH( const Vector3& eye, const Vector3& lookat, const Vector3& upaxis );
	// Build a planar shadow transform, project object to a plane.
	static Matrix4 CreatePlanarShadow( const Vector3& L, const Vector3& N, _float D );

	// Calculates linear interpolation of two matrix.
	static Matrix4 Lerp( const Matrix4& mat1, const Matrix4& mat2, _float f );

public:
	_float	m[4][4];

public:
	inline Matrix4( )
		{ }

	inline Matrix4( _float m00, _float m01, _float m02, _float m03, _float m10, _float m11, _float m12, _float m13,
		_float m20, _float m21, _float m22, _float m23, _float m30, _float m31, _float m32, _float m33 )
	{
		m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
		m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
		m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
		m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
	}

	inline Matrix4( const Vector4& m003, const Vector4& m103, const Vector4& m203, const Vector4& m303 )
	{
		m[0][0] = m003.x; m[0][1] = m003.y; m[0][2] = m003.z; m[0][3] = m003.w;
		m[1][0] = m103.x; m[1][1] = m103.y; m[1][2] = m103.z; m[1][3] = m103.w;
		m[2][0] = m203.x; m[2][1] = m203.y; m[2][2] = m203.z; m[2][3] = m203.w;
		m[3][0] = m303.x; m[3][1] = m303.y; m[3][2] = m303.z; m[3][3] = m303.w;
	}

	inline Matrix4( const Matrix3& mat )
	{
		m[0][0] = mat.m[0][0]; m[0][1] = mat.m[0][1]; m[0][2] = mat.m[0][2]; m[0][3] = 0.0f;
		m[1][0] = mat.m[1][0]; m[1][1] = mat.m[1][1]; m[1][2] = mat.m[1][2]; m[1][3] = 0.0f;
		m[2][0] = mat.m[2][0]; m[2][1] = mat.m[2][1]; m[2][2] = mat.m[2][2]; m[2][3] = 0.0f;
		m[3][0] = 0.0f;        m[3][1] = 0.0f;        m[3][2] = 0.0f;        m[3][3] = 1.0f;
	}

	inline Matrix4& operator = ( const Matrix3& mat )
	{
		m[0][0] = mat.m[0][0]; m[0][1] = mat.m[0][1]; m[0][2] = mat.m[0][2]; m[0][3] = 0.0f;
		m[1][0] = mat.m[1][0]; m[1][1] = mat.m[1][1]; m[1][2] = mat.m[1][2]; m[1][3] = 0.0f;
		m[2][0] = mat.m[2][0]; m[2][1] = mat.m[2][1]; m[2][2] = mat.m[2][2]; m[2][3] = 0.0f;
		m[3][0] = 0.0f;	       m[3][1] = 0.0f;        m[3][2] = 0.0f;        m[3][3] = 1.0f;

		return *this;
	}

	inline const _float* operator [] ( _long r ) const
		{ return m[r]; }

	inline _float operator ( ) ( _long r, _long c ) const
		{ return m[r][c]; }
	inline _float& operator ( ) ( _long r, _long c )
		{ return m[r][c]; }

	inline Matrix4 operator + ( ) const
		{ return Matrix4( m[0][0], m[0][1], m[0][2], m[0][3], m[1][0], m[1][1], m[1][2], m[1][3], m[2][0], m[2][1], m[2][2], m[2][3], m[3][0], m[3][1], m[3][2], m[3][3] ); }
	inline Matrix4 operator - ( ) const
		{ return Matrix4( -m[0][0], -m[0][1], -m[0][2], -m[0][3], -m[1][0], -m[1][1], -m[1][2], -m[1][3], -m[2][0], -m[2][1], -m[2][2], -m[2][3], -m[3][0], -m[3][1], -m[3][2], -m[3][3] ); }

	inline Matrix4 operator + ( const Matrix4& mat ) const
		{ Matrix4 ret( *this ); return ret += mat; }
	inline Matrix4 operator - ( const Matrix4& mat ) const
		{ Matrix4 ret( *this ); return ret -= mat; }

	inline Matrix4 operator * ( _float s ) const
		{ Matrix4 ret( *this ); return ret *= s; }
	inline Matrix4 operator / ( _float s ) const
		{ Matrix4 ret( *this ); return ret /= s; }

	inline Matrix4 operator * ( const Matrix4& mat ) const
		{ Matrix4 ret( *this ); return ret *= mat; }

	inline Matrix4& operator -= ( const Matrix4& mat )
		{ return operator += ( - mat ); }
	inline Matrix4& operator /= ( _float s )
		{ return operator *= ( 1.0f / s ); }
	inline _bool operator != ( const Matrix4& mat ) const
		{ return ! operator == ( mat ); }

	inline _bool Equal( const Matrix4& mat, _float margin = Math::cEpsilon ) const
	{
		for ( _dword i = 0; i < 4; i ++ )
		{
			for ( _dword j = 0; j < 4; j ++ )
			{
				if ( Math::Abs( m[i][j] - mat.m[i][j] ) > margin )
					return _false;
			}
		}

		return _true;
	}

	inline Vector4 GetRow( _long r ) const
		{ return Vector4( m[r][0], m[r][1], m[r][2], m[r][3] ); }
	inline Vector4 GetColumn( _long c ) const
		{ return Vector4( m[0][c], m[1][c], m[2][c], m[3][c] ); }

	inline Vector3 GetTranslationVector( ) const
		{ return Vector3( m[3][0], m[3][1], m[3][2] ); }
	inline Matrix3 GetRotationMatrix( ) const
		{ return Matrix3( m[0][0], m[0][1], m[0][2], m[1][0], m[1][1], m[1][2], m[2][0], m[2][1], m[2][2] ); }
	inline Vector3 GetScalingVector( ) const
		{ return Vector3( Vector3( m[0][0], m[0][1], m[0][2] ).Magnitude( ), Vector3( m[1][0], m[1][1], m[1][2] ).Magnitude( ), Vector3( m[2][0], m[2][1], m[2][2] ).Magnitude( ) ); }

	inline Matrix4& Translation( const Vector3& v )
		{ return Translation( v.x, v.y, v.z ); }

	inline Matrix4& Rotation( const Vector3& v1, const Vector3& v2 )
		{ return Rotation( Quaternion( ).Rotation( v1, v2 ) ); }

	inline Matrix4& Scaling( _float s )
		{ return Scaling( s, s, s ); }
	inline Matrix4& Scaling( const Vector3& v )
		{ return Scaling( v.x, v.y, v.z ); }

	inline Matrix4& Project( const Vector3& v )
		{ return Scaling( v, 0.0f ); }

	inline Matrix4& Refection( const Vector3& v )
		{ return Scaling( v, -1.0f ); }

	inline Matrix4& Compose( const Vector3& t, const Quaternion& r, const Vector3& s )
		{ return Compose( t, Matrix3( ).Rotation( r ), s ); }
	inline _void Decompose( Vector3& t, Quaternion& r, Vector3& s ) const
		{ Matrix3 rr; Decompose( t, rr, s ); rr.Decompose( r ); }

	Matrix4&	operator += ( const Matrix4& mat );
	Matrix4&	operator *= ( _float s );
	Matrix4&	operator *= ( const Matrix4& mat );
	_bool		operator == ( const Matrix4& mat ) const;

	_bool		HasTranslation( ) const;
	_bool		HasRotation( ) const;
	_float		Determinant( ) const;

	Matrix4&	Identity( );
	Matrix4&	Transpose( );
	Matrix4&	Inverse( );
	Matrix4&	Adjoint( );

	Matrix4		InverseProjection( ) const;
	_void		DismantleViewMatrix( Vector3& translate, Matrix4& rotate ) const;

	Matrix4&	Translation( _float x, _float y, _float z );

	Matrix4&	RotationX( _float r );
	Matrix4&	RotationY( _float r );
	Matrix4&	RotationZ( _float r );
	Matrix4&	Rotation( const Vector3& a, _float r );
	Matrix4&	Rotation( const Quaternion& q );

	Matrix4&	Scaling( _float x, _float y, _float z );
	Matrix4&	Scaling( const Vector3& v, _float f );

	Vector3		TransformPosition( const Vector3& pos ) const;
	Vector3		TransformVector( const Vector3& vec ) const;

	Matrix4&	Compose( const Vector3& x, const Vector3& y, const Vector3& z, const Vector3& o );
	Matrix4&	Compose( const Vector3& t, const Matrix3& r, const Vector3& s );
	_void		Decompose( Vector3& x, Vector3& y, Vector3& z, Vector3& t );
	_void		Decompose( Vector3& t, Matrix3& r, Vector3& s ) const;
};

};