#pragma once

namespace Xixels
{

class Vector4SSE;

class Matrix4SSE
{
public:
	// The zero matrix.
	const static Matrix4SSE cZero;
	// The identity matrix.
	const static Matrix4SSE cIdentity;

public:
	_float		m[20];
	_float4*	start;

public:
	inline Matrix4SSE( )
		{ start = (_float4*) ( (_byte*) m + 16 - (_ptr) m % 16 ); }

	inline Matrix4SSE( _float m00, _float m01, _float m02, _float m03, _float m10, _float m11, _float m12, _float m13,
		_float m20, _float m21, _float m22, _float m23, _float m30, _float m31, _float m32, _float m33 )
	{
		start = (_float4*) ( (_byte*) m + 16 - (_ptr) m % 16 );

		*( start )     = _SSE_LOAD_FLOATS( m03, m02, m01, m00 );
		*( start + 1 ) = _SSE_LOAD_FLOATS( m13, m12, m11, m10 );
		*( start + 2 ) = _SSE_LOAD_FLOATS( m23, m22, m21, m20 );
		*( start + 3 ) = _SSE_LOAD_FLOATS( m33, m32, m31, m30 );
	}

	inline Matrix4SSE( const _float* p )
	{
		start = (_float4*) ( (_byte*) m + 16 - (_ptr) m % 16 );

		for ( _long i = 0; i < 4; i ++ )
		{
			*( start + i ) = _SSE_LOAD_FLOATS( 0.0f, p[2], p[1], p[0] );
			p = p + 3;
		}
	}

	inline Matrix4SSE( const Matrix3& mat )
	{
		start = (_float4*) ( (_byte*) m + 16 - (_ptr) m % 16 );

		*( start )     = _SSE_LOAD_FLOATS( 0.0f, mat.m[0][2], mat.m[0][1], mat.m[0][0] );
		*( start + 1 ) = _SSE_LOAD_FLOATS( 0.0f, mat.m[1][2], mat.m[1][1], mat.m[1][0] );
		*( start + 2 ) = _SSE_LOAD_FLOATS( 0.0f, mat.m[2][2], mat.m[2][1], mat.m[2][0] );
		*( start + 3 ) = _SSE_LOAD_FLOATS( 1.0f, 0.0f, 0.0f, 0.0f );
	}

	inline Matrix4SSE( const Matrix4& mat )
	{
		start = (_float4*) ( (_byte*) m + 16 - (_ptr) m % 16 );

		*( start )     = _SSE_LOAD_FLOATS( mat.m[0][3], mat.m[0][2], mat.m[0][1], mat.m[0][0] );
		*( start + 1 ) = _SSE_LOAD_FLOATS( mat.m[1][3], mat.m[1][2], mat.m[1][1], mat.m[1][0] );
		*( start + 2 ) = _SSE_LOAD_FLOATS( mat.m[2][3], mat.m[2][2], mat.m[2][1], mat.m[2][0] );
		*( start + 3 ) = _SSE_LOAD_FLOATS( mat.m[3][3], mat.m[3][2], mat.m[3][1], mat.m[3][0] );
	}

	inline Matrix4SSE( const Matrix4SSE& mat )
	{
		start = (_float4*) ( (_byte*) m + 16 - (_ptr) m % 16 );

		*( start )     = *mat.start;
		*( start + 1 ) = *( mat.start + 1 );
		*( start + 2 ) = *( mat.start + 2 );
		*( start + 3 ) = *( mat.start + 3 );
	}

	inline Matrix4SSE& operator = ( const Matrix3& mat )
	{
		*( start )     = _SSE_LOAD_FLOATS( 0.0f, mat.m[0][2], mat.m[0][1], mat.m[0][0] );
		*( start + 1 ) = _SSE_LOAD_FLOATS( 0.0f, mat.m[1][2], mat.m[1][1], mat.m[1][0] );
		*( start + 2 ) = _SSE_LOAD_FLOATS( 0.0f, mat.m[2][2], mat.m[2][1], mat.m[2][0] );
		*( start + 3 ) = _SSE_LOAD_FLOATS( 1.0f, 0.0f, 0.0f, 0.0f );

		return *this;
	}

	inline Matrix4SSE& operator = ( const Matrix4& mat )
	{
		*( start )     = _SSE_LOAD_FLOATS( mat.m[0][3], mat.m[0][2], mat.m[0][1], mat.m[0][0] );
		*( start + 1 ) = _SSE_LOAD_FLOATS( mat.m[1][3], mat.m[1][2], mat.m[1][1], mat.m[1][0] );
		*( start + 2 ) = _SSE_LOAD_FLOATS( mat.m[2][3], mat.m[2][2], mat.m[2][1], mat.m[2][0] );
		*( start + 3 ) = _SSE_LOAD_FLOATS( mat.m[3][3], mat.m[3][2], mat.m[3][1], mat.m[3][0] );

		return *this;
	}

	inline Matrix4SSE& operator = ( const Matrix4SSE& mat )
	{
		*( start )     = *mat.start;
		*( start + 1 ) = *( mat.start + 1 );
		*( start + 2 ) = *( mat.start + 2 );
		*( start + 3 ) = *( mat.start + 3 );

		return *this;
	}

	inline operator Matrix4 ( ) const
	{
		return Matrix4(
			operator()( 0, 0 ), operator()( 0, 1 ), operator()( 0, 2 ), operator()( 0, 3 ),
			operator()( 1, 0 ), operator()( 1, 1 ), operator()( 1, 2 ), operator()( 1, 3 ),
			operator()( 2, 0 ), operator()( 2, 1 ), operator()( 2, 2 ), operator()( 2, 3 ),
			operator()( 3, 0 ), operator()( 3, 1 ), operator()( 3, 2 ), operator()( 3, 3 ) );
	}

	inline const _float* operator [] ( _long r ) const
		{ return (_float*) start + r; }

	inline _float operator ( ) ( _long r, _long c ) const
		{ return *( (_float*)( start + r ) + c ); }
	inline _float& operator ( ) ( _long r, _long c )
		{ return *( (_float*)( start + r ) + c ); }

	inline Matrix4SSE operator + ( ) const
	{
		return Matrix4SSE(
			operator()( 0, 0 ), operator()( 0, 1 ), operator()( 0, 2 ), operator()( 0, 3 ),
			operator()( 1, 0 ), operator()( 1, 1 ), operator()( 1, 2 ), operator()( 1, 3 ),
			operator()( 2, 0 ), operator()( 2, 1 ), operator()( 2, 2 ), operator()( 2, 3 ),
			operator()( 3, 0 ), operator()( 3, 1 ), operator()( 3, 2 ), operator()( 3, 3 ) );
	}

	inline Matrix4SSE operator - ( ) const
	{
		return Matrix4SSE(
			- operator()( 0, 0 ), - operator()( 0, 1 ), - operator()( 0, 2 ), - operator()( 0, 3 ),
			- operator()( 1, 0 ), - operator()( 1, 1 ), - operator()( 1, 2 ), - operator()( 1, 3 ),
			- operator()( 2, 0 ), - operator()( 2, 1 ), - operator()( 2, 2 ), - operator()( 2, 3 ),
			- operator()( 3, 0 ), - operator()( 3, 1 ), - operator()( 3, 2 ), - operator()( 3, 3 ) );
	}

	inline Matrix4SSE operator + ( const Matrix4SSE& mat ) const
		{ Matrix4SSE ret( *this ); return ret += mat; }
	inline Matrix4SSE operator - ( const Matrix4SSE& mat ) const
		{ Matrix4SSE ret( *this ); return ret -= mat; }

	inline Matrix4SSE operator * ( _float s ) const
		{ Matrix4SSE ret( *this ); return ret *= s; }
	inline Matrix4SSE operator / ( _float s ) const
		{ Matrix4SSE ret( *this ); return ret /= s; }

	inline Matrix4SSE operator * ( const Matrix4SSE& mat ) const
		{ Matrix4SSE ret( *this ); return ret *= mat; }

	inline Matrix4SSE& operator -= ( const Matrix4SSE& mat )
		{ return operator += ( - mat ); }
	inline Matrix4SSE& operator /= ( _float s )
		{ return operator *= ( 1.0f / s ); }
	inline _bool operator != ( const Matrix4SSE& mat ) const
		{ return ! operator == ( mat ); }

	Matrix4SSE&	operator += ( const Matrix4SSE& mat );
	Matrix4SSE&	operator *= ( _float s );
	Matrix4SSE&	operator *= ( const Matrix4SSE& mat );
	_bool		operator == ( const Matrix4SSE& mat ) const;
};

};