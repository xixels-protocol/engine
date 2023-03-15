#pragma once

#include "Math.h"
#include "Matrix2.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Quaternion.h"

namespace Xixels
{

class Matrix3
{
public:
	// The zero matrix.
	const static Matrix3 cZero;
	// The identity matrix.
	const static Matrix3 cIdentity;
	// The projection matrix by project onto xy-plane
	const static Matrix3 cProjectXY;
	// The projection matrix by project onto yz-plane
	const static Matrix3 cProjectYZ;
	// The projection matrix by project onto zx-plane
	const static Matrix3 cProjectZX;
	// The reflection matrix by flip around xy-plane.
	const static Matrix3 cRefectionXY;
	// The reflection matrix by flip around yz-plane.
	const static Matrix3 cRefectionYZ;
	// The reflection matrix by flip around zx-plane.
	const static Matrix3 cRefectionZX;

public:
	_float	m[3][3];

public:
	inline Matrix3( )
		{ }

	inline Matrix3( _float m00, _float m01, _float m02, _float m10, _float m11, _float m12, _float m20, _float m21, _float m22 )
	{
		m[0][0] = m00; m[0][1] = m01; m[0][2] = m02;
		m[1][0] = m10; m[1][1] = m11; m[1][2] = m12;
		m[2][0] = m20; m[2][1] = m21; m[2][2] = m22;
	}

	inline Matrix3( const Vector3& v1, const Vector3& v2, const Vector3& v3 )
	{
		m[0][0] = v1.x; m[0][1] = v1.y; m[0][2] = v1.z;
		m[1][0] = v2.x; m[1][1] = v2.y; m[1][2] = v2.z;
		m[2][0] = v3.x; m[2][1] = v3.y; m[2][2] = v3.z;
	}

	inline Matrix3( const Matrix2& mat )
	{
		m[0][0] = mat.m[0][0]; m[0][1] = mat.m[0][1]; m[0][2] = 0.0f;
		m[1][0] = mat.m[1][0]; m[1][1] = mat.m[1][1]; m[1][2] = 0.0f;
		m[2][0] = 0.0f;        m[2][1] = 0.0f;        m[2][2] = 1.0f;
	}

	inline Matrix3& operator = ( const Matrix2& mat )
	{
		m[0][0] = mat.m[0][0]; m[0][1] = mat.m[0][1]; m[0][2] = 0.0f;
		m[1][0] = mat.m[1][0]; m[1][1] = mat.m[1][1]; m[1][2] = 0.0f;
		m[2][0] = 0.0f;        m[2][1] = 0.0f;        m[2][2] = 1.0f;

		return *this;
	}

	inline const _float* operator [] ( _long r ) const
		{ return m[r]; }

	inline _float operator ( ) ( _long r, _long c ) const
		{ return m[r][c]; }
	inline _float& operator ( ) ( _long r, _long c )
		{ return m[r][c]; }

	inline Matrix3 operator + ( ) const
		{ return Matrix3( m[0][0], m[0][1], m[0][2], m[1][0], m[1][1], m[1][2], m[2][0], m[2][1], m[2][2] ); }
	inline Matrix3 operator - ( ) const
		{ return Matrix3( -m[0][0], -m[0][1], -m[0][2], -m[1][0], -m[1][1], -m[1][2], -m[2][0], -m[2][1], -m[2][2] ); }

	inline Matrix3 operator + ( const Matrix3& mat ) const
		{ Matrix3 ret( *this ); return ret += mat; }
	inline Matrix3 operator - ( const Matrix3& mat ) const
		{ Matrix3 ret( *this ); return ret -= mat; }

    inline Matrix3 operator * ( _float s ) const
		{ Matrix3 ret( *this ); return ret *= s; }
    inline Matrix3 operator / ( _float s ) const
		{ Matrix3 ret( *this ); return ret /= s; }

    inline Matrix3 operator * ( const Matrix3& mat ) const
		{ Matrix3 ret( *this ); return ret *= mat; }

	inline Matrix3& operator -= ( const Matrix3& mat )
		{ return operator += ( - mat ); }
	inline Matrix3& operator /= ( _float s )
		{ return operator *= ( 1.0f / s ); }
	inline _bool operator != ( const Matrix3& mat ) const
		{ return ! operator == ( mat ); }

	inline Vector3 GetRow( _long r ) const
		{ return Vector3( m[r][0], m[r][1], m[r][2] ); }
	inline Vector3 GetColumn( _long c ) const
		{ return Vector3( m[0][c], m[1][c], m[2][c] ); }

	inline Matrix2 GetRotationMatrix( ) const
		{ return Matrix2( m[0][0], m[0][1], m[1][0], m[1][1] ); }
	inline Vector2 GetTranslationVector( ) const
		{ return Vector2( m[2][0], m[2][1] ); }
	inline Vector2 GetScalingVector( ) const
		{ return Vector2( Vector2( m[0][0], m[0][1] ).Magnitude( ), Vector2( m[1][0], m[1][1] ).Magnitude( ) ); }

	inline Matrix3& Translation( const Vector2& v )
		{ return Translation( v.x, v.y ); }

	inline Matrix3& Rotation( const Vector3& v1, const Vector3& v2 )
		{ return Rotation( Quaternion( ).Rotation( v1, v2 ) ); }

	inline Matrix3& Scaling( const Vector3& v )
		{ return Scaling( v.x, v.y, v.z ); }

	inline Matrix3& Project( const Vector3& v )
		{ return Scaling( v, 0.0f ); }

	inline Matrix3& Refection( const Vector3& v )
		{ return Scaling( v, -1.0f ); }

	Matrix3&	operator += ( const Matrix3& mat );
	Matrix3&	operator *= ( _float s );
	Matrix3&	operator *= ( const Matrix3& mat );
	_bool		operator == ( const Matrix3& mat ) const;

	_bool		HasTranslation( ) const;
	_bool		HasRotation( ) const;
	_float		Determinant( ) const;

	Matrix3&	Identity( );
	Matrix3&	Transpose( );
	Matrix3&	Inverse( );
	Matrix3&	Adjoint( );

	Matrix3&	Translation( _float x, _float y );

	Matrix3&	Rotation( _float r );
	Matrix3&	RotationX( _float r );
	Matrix3&	RotationY( _float r );
	Matrix3&	RotationZ( _float r );
	Matrix3&	Rotation( const Vector3& a, _float r );
	Matrix3&	Rotation( const Quaternion& q );
	Matrix3&	Rotation( const Vector3& x, const Vector3& y, const Vector3& z );

	Matrix3&	Scaling( _float x, _float y, _float z );
	Matrix3&	Scaling( const Vector3& v, _float f );

	Matrix3&	Compose( const Vector2& offset, const Vector3& scale, float angle );
	_void		Decompose( Quaternion& q ) const;
};

};