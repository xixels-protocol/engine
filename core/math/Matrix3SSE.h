#pragma once

namespace Xixels
{

class Vector3SSE;

class Matrix3SSE
{
public:
	// The zero matrix.
	const static Matrix3SSE cZero;
	// The identity matrix.
	const static Matrix3SSE cIdentity;

public:
	_float		m[16];
	_float4*	start;

public:
	inline Matrix3SSE( )
		{ start = (_float4*) ( (_byte*) m + 16 - (_ptr) m % 16 ); }

	inline Matrix3SSE( _float m00, _float m01, _float m02, _float m10, _float m11, _float m12, _float m20, _float m21, _float m22 )
	{
		start = (_float4*) ( (_byte*) m + 16 - (_ptr) m % 16 );

		*( start )     = _SSE_LOAD_FLOATS( 0.0f, m02, m01, m00 );
		*( start + 1 ) = _SSE_LOAD_FLOATS( 0.0f, m12, m11, m10 );
		*( start + 2 ) = _SSE_LOAD_FLOATS( 0.0f, m22, m21, m20 );
	}

	inline Matrix3SSE( const _float* p )
	{
		start = (_float4*) ( (_byte*) m + 16 - (_ptr) m % 16 );

		for ( _long i = 0; i < 3; i ++ )
		{
			*( start + i ) = _SSE_LOAD_FLOATS( 0.0f, p[2], p[1], p[0] );
			p = p + 3;
		}
	}

	inline Matrix3SSE( const Matrix3& mat )
	{
		start = (_float4*) ( (_byte*) m + 16 - (_ptr) m % 16 );

		*( start )     = _SSE_LOAD_FLOATS( 0.0f, mat.m[0][2], mat.m[0][1], mat.m[0][0] );
		*( start + 1 ) = _SSE_LOAD_FLOATS( 0.0f, mat.m[1][2], mat.m[1][1], mat.m[1][0] );
		*( start + 2 ) = _SSE_LOAD_FLOATS( 0.0f, mat.m[2][2], mat.m[2][1], mat.m[2][0] );
	}

	inline Matrix3SSE( const Matrix3SSE& mat )
	{
		start = (_float4*) ( (_byte*) m + 16 - (_ptr) m % 16 );

		_float4* start2 = mat.start;

		*( start )     = *start2;
		*( start + 1 ) = *( start2 + 1 );
		*( start + 2 ) = *( start2 + 2 );
	}

	inline Matrix3SSE& operator = ( const Matrix3& mat )
	{
		*( start )     = _SSE_LOAD_FLOATS( 0.0f, mat.m[0][2], mat.m[0][1], mat.m[0][0] );
		*( start + 1 ) = _SSE_LOAD_FLOATS( 0.0f, mat.m[1][2], mat.m[1][1], mat.m[1][0] );
		*( start + 2 ) = _SSE_LOAD_FLOATS( 0.0f, mat.m[2][2], mat.m[2][1], mat.m[2][0] );

		return *this;
	}

	inline Matrix3SSE& operator = ( const Matrix3SSE& mat )
	{
		*( start )     = *mat.start;
		*( start + 1 ) = *( mat.start + 1 );
		*( start + 2 ) = *( mat.start + 2 );

		return *this;
	}

	inline operator Matrix3 ( ) const
	{
		return Matrix3(
			operator()( 0, 0 ), operator()( 0, 1 ), operator()( 0, 2 ),
			operator()( 1, 0 ), operator()( 1, 1 ), operator()( 1, 2 ),
			operator()( 2, 0 ), operator()( 2, 1 ), operator()( 2, 2 ) );
	}

	inline const _float* operator [] ( _long r ) const
		{ return (_float*) start + r; }

	inline _float operator ( ) ( _long r, _long c ) const
		{ return *( (_float*) ( start + r ) + c ); }
	inline _float& operator ( ) ( _long r, _long c )
		{ return *( (_float*) ( start + r ) + c ); }

	inline Matrix3SSE operator + ( ) const
	{
		return Matrix3SSE(
			operator()( 0, 0 ), operator()( 0, 1 ), operator()( 0, 2 ),
			operator()( 1, 0 ), operator()( 1, 1 ), operator()( 1, 2 ),
			operator()( 2, 0 ), operator()( 2, 1 ), operator()( 2, 2 ) );
	}

	inline Matrix3SSE operator - ( ) const
	{
		return Matrix3SSE(
			- operator()( 0, 0 ), - operator()( 0, 1 ), - operator()( 0, 2 ),
			- operator()( 1, 0 ), - operator()( 1, 1 ), - operator()( 1, 2 ),
			- operator()( 2, 0 ), - operator()( 2, 1 ), - operator()( 2, 2 ) );
	}

	inline Matrix3SSE operator + ( const Matrix3SSE& mat ) const
		{ Matrix3SSE ret( *this ); return ret += mat; }
	inline Matrix3SSE operator - ( const Matrix3SSE& mat ) const
		{ Matrix3SSE ret( *this ); return ret -= mat; }

	inline Matrix3SSE operator * ( _float s ) const
		{ Matrix3SSE ret( *this ); return ret *= s; }
	inline Matrix3SSE operator / ( _float s ) const
		{ Matrix3SSE ret( *this ); return ret /= s; }

	inline Matrix3SSE operator * ( const Matrix3SSE& mat ) const
		{ Matrix3SSE ret( *this ); return ret *= mat; }

	inline Matrix3SSE& operator -= ( const Matrix3SSE& mat )
		{ return operator += ( - mat ); }
	inline Matrix3SSE& operator /= ( _float s )
		{ return operator *= ( 1.0f / s ); }
	inline _bool operator != ( const Matrix3SSE& mat ) const
		{ return ! operator == ( mat ); }

	Matrix3SSE&	operator += ( const Matrix3SSE& mat );
	Matrix3SSE&	operator *= ( _float s );
	Matrix3SSE&	operator *= ( const Matrix3SSE& mat );
	_bool		operator == ( const Matrix3SSE& mat ) const;
};

};