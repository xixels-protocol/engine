#pragma once

#include "Vector3.h"
#include "Segment.h"
#include "Plane.h"
#include "Triangle.h"

namespace Xixels
{

class Sphere
{
public:
	Vector3	c;
	_float	r;

public:
	inline Sphere( )
		{ }
	inline Sphere( const Vector3& cc, _float rr )
		: c( cc ), r( rr ) { }

	inline Sphere& operator *= ( const Matrix4& mat )
		{ c *= mat; return *this; }
	inline Sphere operator * ( const Matrix4& mat ) const
		{ return Sphere( c * mat, r ); }

	inline _bool Inside( const Vector3& v ) const
		{ return Vector3( v - c ).MagnitudeSquared( ) <= r * r; }

	inline _bool Intersect( const Sphere& s ) const
		{ return Math::Abs( r ) + Math::Abs( s.r ) > ( c - s.c ).Magnitude( ); }
	inline _bool Intersect( const Plane& p ) const
		{ return Math::Abs( p.Distance( c ) ) <= Math::Abs( r ); }

	inline _bool Intersect( const Segment& segment ) const
		{ return ( segment.Closest( c ) - c ).MagnitudeSquared( ) <= r * r; }
	inline _bool Intersect( const Triangle& triangle ) const
		{ return ( triangle.Closest( c ) - c ).MagnitudeSquared( ) <= r * r; }

	_bool	Intersect( const Plane& p, const Vector3& dir, _float& dist ) const;
};

};