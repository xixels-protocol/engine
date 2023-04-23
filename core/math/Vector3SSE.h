#pragma once

namespace Xixels
{

class Quaternion;
class Matrix3SSE;
class Matrix4SSE;

class Vector3SSE
{
public:
	// The origin vector.
	const static Vector3SSE cOrigin;
	// The identity vector.
	const static Vector3SSE cIdentity;
	// The x-axis vector.
	const static Vector3SSE cXAxis;
	// The y-axis vector.
	const static Vector3SSE cYAxis;
	// The z-axis vector.
	const static Vector3SSE cZAxis;
	// The maximal vector.
	const static Vector3SSE cMaxVector;
	// The minimal vector.
	const static Vector3SSE cMinVector;

	inline static _float Dot( const Vector3SSE& v1, const Vector3SSE& v2 )
	{
		_float4 r = _SSE_MUL_FLOAT4( *v1.start, *v2.start );
		r = _SSE_ADD_FLOAT4( _SSE_MOVEHL_FLOAT4( r, r ), r );

		_float4 ret = _SSE_ADD_FLOAT4S( _SSE_SHUFFLE_FLOAT( r, r, 1 ), r );
		return *(_float*)( &ret );
	}

	inline static Vector3SSE Cross( const Vector3SSE& v1, const Vector3SSE& v2 )
	{
		Vector3SSE ret;

		_float4 l1, l2, m1, m2;
		l1 = _SSE_SHUFFLE_FLOAT( *v1.start, *v1.start, _MM_SHUFFLE( 3, 1, 0, 2 ) );
		l2 = _SSE_SHUFFLE_FLOAT( *v2.start, *v2.start, _MM_SHUFFLE( 3, 0, 2, 1 ) );
		m2 = _SSE_MUL_FLOAT4( l1, l2 );
		*( (_float*) &m2 + 3 ) = 0.0f;

		l1 = _SSE_SHUFFLE_FLOAT( *v1.start, *v1.start, _MM_SHUFFLE( 3, 0, 2, 1 ) );
		l2 = _SSE_SHUFFLE_FLOAT( *v2.start, *v2.start, _MM_SHUFFLE( 3, 1, 0, 2 ) );
		m1 = _SSE_MUL_FLOAT4( l1, l2 );

		*ret.start = _SSE_SUB_FLOAT4( m1, m2 );

		return ret;
	}

	inline static Vector3SSE Project( const Vector3SSE& v1, const Vector3SSE& v2 )
		{ Vector3SSE n = v2; n.Normalize( ); return n * Dot( v1, n ); }

	inline static Vector3SSE Plumb( const Vector3SSE& v1, const Vector3SSE& v2 )
		{ return v1 - Project( v1, v2 ); }

	inline static Vector3SSE Lerp( const Vector3SSE& v1, const Vector3SSE& v2, _float f )
		{ return v1 + ( v2 - v1 ) * Math::Clamp( f, 0.0f, 1.0f ); }

public:
	_float		m[8];
	_float4*	start;

public:
	inline Vector3SSE( )
		{ start = (_float4*) ( (_byte*) m + 16 - (_ptr) m % 16 ); *start = _SSE_LOAD_ZERO( ); }
	inline Vector3SSE( _float xx, _float yy, _float zz )
		{ start = (_float4*) ( (_byte*) m + 16 - (_ptr) m % 16 ); *start = _SSE_LOAD_FLOATS( 0.0f, zz, yy, xx ); }
	inline Vector3SSE( const Vector3& v )
		{ start = (_float4*) ( (_byte*) m + 16 - (_ptr) m % 16 ); *start = _SSE_LOAD_FLOATS( 0.0f, v.z, v.y, v.x ); }
	inline Vector3SSE( const Vector3SSE& v )
		{ start = (_float4*) ( (_byte*) m + 16 - (_ptr) m % 16 ); *start = *v.start; }

	inline _float operator ( ) ( _long i ) const
		{ return *( (_float*) start + i ); }
	inline _float& operator ( ) ( _long i )
		{ return *( (_float*) start + i ); }

	inline operator Vector3 ( ) const
		{ _float* p = (_float*) start; return Vector3( *p, *( p + 1 ), *( p + 2 ) ); }

	inline Vector3SSE& operator = ( const Vector3 &v )
		{ *start = _SSE_LOAD_FLOATS( 0.0f, v.z, v.y, v.x ); return *this; }
	inline Vector3SSE& operator = ( const Vector3SSE &v )
		{ *start = *v.start; return *this; }

	inline Vector3SSE operator + ( ) const
		{ return Vector3SSE( (Vector3) *this ); }
	inline Vector3SSE operator - ( ) const
		{ return Vector3SSE( - (Vector3) *this ); }

	inline Vector3SSE& operator += ( const Vector3SSE& v )
		{ *start = _SSE_ADD_FLOAT4( *start, *v.start ); return *this; }
	inline Vector3SSE& operator -= ( const Vector3SSE& v )
		{ *start = _SSE_SUB_FLOAT4( *start, *v.start ); return *this; }

	inline Vector3SSE operator + ( const Vector3SSE& v ) const
		{ Vector3SSE ret( *this ); return ret += v; }
	inline Vector3SSE operator - ( const Vector3SSE& v ) const
		{ Vector3SSE ret( *this ); return ret -= v; }

	inline Vector3SSE& operator *= ( _float s )
		{ *start = _SSE_MUL_FLOAT4( *start, _SSE_LOAD_FLOAT( s ) ); return *this; }
	inline Vector3SSE& operator /= ( _float s )
		{ *start = _SSE_DIV_FLOAT4( *start, _SSE_LOAD_FLOAT( s ) ); return *this; }

	inline Vector3SSE operator * ( _float s ) const
		{ Vector3SSE ret( *this ); return ret *= s; }
	inline Vector3SSE operator / ( _float s ) const
		{ Vector3SSE ret( *this ); return ret *= s; }

	inline Vector3SSE& operator *= ( const Vector3SSE& v )
		{ *start = _SSE_MUL_FLOAT4( *start, *v.start ); return *this; }
	inline Vector3SSE& operator /= ( const Vector3SSE& v )
		{ *start = _SSE_DIV_FLOAT4( *start, *v.start ); return *this; }

	inline Vector3SSE operator * ( const Vector3SSE& v ) const
		{ Vector3SSE ret( *this ); return ret *= v; }
	inline Vector3SSE operator / ( const Vector3SSE& v ) const
		{ Vector3SSE ret( *this ); return ret /= v; }

	inline Vector3SSE operator * ( const Matrix3SSE& mat ) const
		{ Vector3SSE ret( *this ); return ret *= mat; }
	inline Vector3SSE operator * ( const Matrix4SSE& mat ) const
		{ Vector3SSE ret( *this ); return ret *= mat; }

	inline _bool operator == ( const Vector3SSE& v ) const
	{
		_float* start1 = (_float*) start;
		_float* start2 = (_float*) v.start;
		return *start1 ++ == *start2 ++ && *start1 ++ == *start2 ++ && *start1 == *start2;
	}

	inline _bool operator != ( const Vector3SSE& v ) const
	{
		_float* start1 = (_float*) start;
		_float* start2 = (_float*) v.start;

		return *start1 ++ != *start2 ++ || *start1 ++ != *start2 ++ || *start1 != *start2;
	}

	inline _bool Equal( const Vector3SSE& v, _float margin = Math::cEpsilon ) const
	{
		_float4 sub = _SSE_SUB_FLOAT4( *start, *v.start );
		_float* temp = (_float*) &sub;

		return Math::Abs( *temp ++ ) <= margin && Math::Abs( *temp ++ ) <= margin && Math::Abs( *temp ) <= margin;
	}

	inline Vector3SSE& Absolute( )
	{
		_float* temp = (_float*) start;

		*temp = Math::Abs( *temp ); temp ++;
		*temp = Math::Abs( *temp ); temp ++;
		*temp = Math::Abs( *temp );

		return *this;
	}

	inline Vector3SSE& Normalize( )
		{ _float m = Magnitude( ); if ( m > 0.0f ) *start = _SSE_DIV_FLOAT4( *start, _SSE_LOAD_FLOAT( m ) ); return *this; }

	inline _float Magnitude( ) const
		{ return Math::Sqrt( Dot( *this, *this ) ); }

	inline _float MagnitudeSquared( ) const
		{ return Dot( *this, *this ); }

	Vector3SSE&	operator *= ( const Matrix3SSE& mat );
	Vector3SSE&	operator *= ( const Matrix4SSE& mat );
	Vector3SSE&	operator *= ( const Quaternion& q );
};

};