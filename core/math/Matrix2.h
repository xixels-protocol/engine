#pragma once

#include "Math.hpp"
#include "Vector2.h"

namespace Xixels
{

class Matrix2
{
public:
	// The zero matrix.
	const static Matrix2 cZero;
	// The identity matrix.
	const static Matrix2 cIdentity;

public:
	_float	m[2][2];

public:
	inline Matrix2( )
		{ }
	inline Matrix2( _float m00, _float m01, _float m10, _float m11 )
		{ m[0][0] = m00; m[0][1] = m01; m[1][0] = m10; m[1][1] = m11; }

	inline const _float* operator [] ( _long r ) const
		{ return m[r]; }

	inline _float operator ( ) ( _long r, _long c ) const
		{ return m[r][c]; }
	inline _float& operator ( ) ( _long r, _long c )
		{ return m[r][c]; }

	inline Matrix2 operator + ( ) const
		{ return Matrix2( m[0][0], m[0][1], m[1][0], m[1][1] ); }
	inline Matrix2 operator - ( ) const
		{ return Matrix2( - m[0][0], - m[0][1], - m[1][0], - m[1][1] ); }

	inline Matrix2 operator + ( const Matrix2& mat ) const
		{ Matrix2 ret( *this ); return ret += mat; }
	inline Matrix2 operator - ( const Matrix2& mat ) const
		{ Matrix2 ret( *this ); return ret -= mat; }

    inline Matrix2 operator * ( _float s ) const
		{ Matrix2 ret( *this ); return ret *= s; }
    inline Matrix2 operator / ( _float s ) const
		{ Matrix2 ret( *this ); return ret /= s; }

    inline Matrix2 operator * ( const Matrix2& mat ) const
		{ Matrix2 ret( *this ); return ret *= mat; }

	inline Matrix2& operator -= ( const Matrix2& mat )
		{ return operator += ( - mat ); }
	inline Matrix2& operator /= ( _float s )
		{ return operator *= ( 1.0f / s ); }
	inline _bool operator != ( const Matrix2& mat ) const
		{ return ! operator == ( mat ); }

	inline Vector2 GetRow( _long r ) const
		{ return Vector2( m[r][0], m[r][1] ); }
	inline Vector2 GetColumn( _long c ) const
		{ return Vector2( m[0][c], m[1][c] ); }

	inline Matrix2& Scaling( const Vector2& v )
		{ return Scaling( v.x, v.y ); }
	inline Matrix2& Project( const Vector2& v )
		{ return Scaling( v, 0.0f ); }
	inline Matrix2& Refection( const Vector2& v )
		{ return Scaling( v, -1.0f ); }

	Matrix2&	operator += ( const Matrix2& mat );
	Matrix2&	operator *= ( _float s );
	Matrix2&	operator *= ( const Matrix2& mat );
	_bool		operator == ( const Matrix2& mat ) const;

	_float		Determinant( ) const;

	Matrix2&	Identity( );
	Matrix2&	Transpose( );
	Matrix2&	Inverse( );
	Matrix2&	Adjoint( );

	Matrix2&	Rotation( _float r );

	Matrix2&	Scaling( _float x, _float y );
	Matrix2&	Scaling( const Vector2& v, _float f );
};

};