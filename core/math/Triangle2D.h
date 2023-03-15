#pragma once

#include "Vector2.h"

namespace Xixels
{

class Triangle2D
{
public:
	Vector2 v1;
	Vector2 v2;
	Vector2 v3;

public:
	inline Triangle2D( )
		{ }
	inline Triangle2D( const Vector2& vv1, const Vector2& vv2, const Vector2& vv3 )
		: v1( vv1 ), v2( vv2 ), v3( vv3 ) { }

	inline const Vector2& operator [] ( _dword index ) const
		{ return index == 0 ? v1 : ( index == 1 ? v2 : v3 ); }
	inline Vector2& operator [] ( _dword index )
		{ return index == 0 ? v1 : ( index == 1 ? v2 : v3 ); }

	inline Triangle2D& operator *= ( const Matrix3& mat )
		{ v1 *= mat; v2 *= mat; v3 *= mat; return *this; }
	inline Triangle2D operator * ( const Matrix3& mat ) const
		{ return Triangle2D( v1 * mat, v2 * mat, v3 * mat ); }

	inline _float Area( ) const
		{ return Math::Abs( Vector2::Cross( v3 - v1, v2 - v1 ) ) * 0.5f; }

	inline Vector2 Centroid( ) const
		{ return ( v1 + v2 + v3 ) / 3.0f; }

	Triangle2D&	Scale( _float scale );
	_bool		CheckIntersect( const Triangle2D& triangle ) const;
};

};