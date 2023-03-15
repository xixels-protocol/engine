#pragma once

#include "Vector3.h"

namespace Xixels
{

class Segment
{
public:
	Vector3	v1;
	Vector3	v2;

public:
	inline Segment( )
		{ }
	inline Segment( const Vector3& vv1, const Vector3& vv2 )
		: v1( vv1 ), v2( vv2 ) { }

	inline Segment& operator *= ( const Matrix4& mat )
		{ v1 *= mat; v2 *= mat; return *this; }
	inline Segment operator * ( const Matrix4& mat ) const
		{ return Segment( v1 * mat, v2 * mat ); }

	inline _float Length( ) const
		{ return Vector3( v2 - v1 ).Magnitude( ) * 0.5f; }

	inline Vector3 Middle( ) const
		{ return ( v1 + v2 ) * 0.5f; }

	Vector3	Closest( const Vector3& v ) const;
	Vector3 ClosestOverLine( const Vector3& v ) const;

	_float Closest( const Segment& seg, Vector3& pos1, Vector3& pos2 ) const;
};

};