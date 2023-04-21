#pragma once

namespace Xixels
{

class Matrix3x4
{
public:
	// The zero matrix.
	const static Matrix3x4 cZero;
	// The identity matrix.
	const static Matrix3x4 cIdentity;

public:
	_float	m[3][4];

public:
	inline Matrix3x4( )
		{ }

	inline Matrix3x4( _float m00, _float m01, _float m02, _float m03, _float m10, _float m11, _float m12, _float m13, _float m20, _float m21, _float m22, _float m23 )
	{
		m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
		m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
		m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
	}

	inline const _float* operator [] ( _long r ) const
		{ return m[r]; }

	inline _float operator ( ) ( _long r, _long c ) const
		{ return m[r][c]; }
	inline _float& operator ( ) ( _long r, _long c )
		{ return m[r][c]; }

	inline Matrix3x4 operator + ( ) const
		{ return Matrix3x4( m[0][0], m[0][1], m[0][2], m[0][3], m[1][0], m[1][1], m[1][2], m[1][3], m[2][0], m[2][1], m[2][2], m[2][3] ); }
	inline Matrix3x4 operator - ( ) const
		{ return Matrix3x4( -m[0][0], -m[0][1], -m[0][2], -m[0][3], -m[1][0], -m[1][1], -m[1][2], -m[1][3], -m[2][0], -m[2][1], -m[2][2], -m[2][3] ); }

	inline Matrix3x4& operator = ( const Matrix4& mat )
	{
		m[0][0] = mat.m[0][0]; m[0][1] = mat.m[1][0]; m[0][2] = mat.m[2][0]; m[0][3] = mat.m[3][0];
		m[1][0] = mat.m[0][1]; m[1][1] = mat.m[1][1]; m[1][2] = mat.m[2][1]; m[1][3] = mat.m[3][1];
		m[2][0] = mat.m[0][2]; m[2][1] = mat.m[1][2]; m[2][2] = mat.m[2][2]; m[2][3] = mat.m[3][2];

		return *this;
	}

	inline Matrix3x4 operator + ( const Matrix3x4& mat ) const
		{ Matrix3x4 ret( *this ); return ret += mat; }
	inline Matrix3x4 operator - ( const Matrix3x4& mat ) const
		{ Matrix3x4 ret( *this ); return ret -= mat; }

	inline Matrix3x4 operator * ( _float s ) const
		{ Matrix3x4 ret( *this ); return ret *= s; }
	inline Matrix3x4 operator / ( _float s ) const
		{ Matrix3x4 ret( *this ); return ret /= s; }

	inline Matrix3x4& operator -= ( const Matrix3x4& mat )
		{ return operator += ( - mat ); }
	inline Matrix3x4& operator /= ( _float s )
		{ return operator *= ( 1.0f / s ); }
	inline _bool operator != ( const Matrix3x4& mat ) const
		{ return ! operator == ( mat ); }

	inline Matrix3 GetRotationMatrix( ) const
		{ return Matrix3( m[0][0], m[1][0], m[2][0], m[0][1], m[1][1], m[2][1], m[0][2], m[1][2], m[2][2] ); }
	inline Vector3 GetTranslationVector( ) const
		{ return Vector3( m[0][3], m[1][3], m[2][3] ); }

	inline Matrix3x4& Translation( const Vector3& v )
		{ return Translation( v.x, v.y, v.z ); }

	inline Matrix3x4& Rotation( const Vector3& v1, const Vector3& v2 )
		{ return Rotation( Quaternion( ).Rotation( v1, v2 ) ); }

	inline Matrix3x4& Scaling( const Vector3& v )
		{ return Scaling( v.x, v.y, v.z ); }

	inline Matrix3x4& Project( const Vector3& v )
		{ return Scaling( v, 0.0f ); }

	inline Matrix3x4& Refection( const Vector3& v )
		{ return Scaling( v, -1.0f ); }

	inline Matrix3x4& Compose( const Vector3& t, const Quaternion& r, const Vector3& s )
		{ return Compose( t, Matrix3( ).Rotation( r ), s ); }
	inline _void Decompose( Vector3& t, Quaternion& r, Vector3& s ) const
		{ Matrix3 rr; Decompose( t, rr, s ); rr.Decompose( r ); }

	Matrix3x4&	operator += ( const Matrix3x4& mat );
	Matrix3x4&	operator *= ( _float s );
	_bool		operator == ( const Matrix3x4& mat ) const;

	Matrix3x4&	Translation( _float x, _float y, _float z );

	Matrix3x4&	RotationX( _float r );
	Matrix3x4&	RotationY( _float r );
	Matrix3x4&	RotationZ( _float r );
	Matrix3x4&	Rotation( const Vector3& a, _float r );
	Matrix3x4&	Rotation( const Quaternion& q );

	Matrix3x4&	Scaling( _float x, _float y, _float z );
	Matrix3x4&	Scaling( const Vector3& v, _float f );

	Matrix3x4&	Compose( const Vector3& t, const Matrix3& r, const Vector3& s );
	_void		Decompose( Vector3& t, Matrix3& r, Vector3& s ) const;

	Matrix3x4&	Compose( const Matrix4& mat );
	_void		Decompose( Matrix4& mat ) const;
};

};