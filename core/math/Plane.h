#pragma once

#include "Vector3.h"
#include "Triangle.h"
#include "Matrix4.h"

namespace Xixels
{

class Plane
{
public:
	// The x-y plane.
	const static Plane cXYPlane;
	// The y-z plane.
	const static Plane cYZPlane;
	// The z-x plane.
	const static Plane cZXPlane;

public:
	_float	a;
	_float	b;
	_float	c;
	_float	d;

public:
	inline Plane( )
		{ }
	inline Plane( _float aa, _float bb, _float cc, _float dd )
		: a( aa ), b( bb ), c( cc ), d( dd ) { }

	inline Plane( const Vector3& pos, const Vector3& nor )
	{
		Vector3 n = nor;
		n.Normalize( );

		a = n.x;
		b = n.y;
		c = n.z;
		d = - Vector3::Dot( pos, n );
	}

	inline Plane( const Vector3& v1, const Vector3& v2, const Vector3& v3 )
	{
		Vector3 n = Vector3::Cross( v2 - v1, v3 - v1 );
		n.Normalize( );

		a = n.x;
		b = n.y;
		c = n.z;
		d = - Vector3::Dot( v1, n );
	}

	inline Plane( const Triangle& triangle )
	{
		Vector3 n = Vector3::Cross( triangle.v2 - triangle.v1, triangle.v3 - triangle.v1 );
		n.Normalize( );

		a = n.x;
		b = n.y;
		c = n.z;
		d = - Vector3::Dot( triangle.v1, n );
	}

	inline Plane operator + ( ) const
		{ return Plane( a, b, c, d ); }
	inline Plane operator - ( ) const
		{ return Plane( -a, -b, -c, -d ); }

	inline _bool operator == ( const Plane& p ) const
		{ return a == p.a && b == p.b && c == p.c && d == p.d; }
	inline _bool operator != ( const Plane& p ) const
		{ return a != p.a || b != p.b || c != p.c || d != p.d; }

	inline Vector3 Normal( ) const
		{ return Vector3( a, b, c ); }

	inline _float Distance( const Vector3& v ) const
		{ return a * v.x + b * v.y + c * v.z + d; }

	inline Vector3 Project( const Vector3& v ) const
		{ return v - Normal( ) * Distance( v ); }

	inline Plane& operator *= ( const Matrix4& mat )
	{
		Vector3 n = Vector3( a, b, c );
		Vector3 nn = mat.TransformVector( n );
		nn.Normalize( );

		Vector3 v = mat.TransformPosition( n * -d );

		a = nn.x;
		b = nn.y;
		c = nn.z;
		d = - Vector3::Dot( v, nn );

		return *this;
	}

	inline Plane operator * ( const Matrix4& mat ) const
		{ Plane ret( *this ); return ret *= mat; }

	inline Vector3 Reflect( const Vector3& v ) const
		{ return ( Vector3( v ).Normalize( ) + Vector3( a, b, c ) * 2.0f ) * v.Magnitude( ); }

	_bool	Intersect( const Vector3& v1, const Vector3& v2, Vector3& p ) const;
};

};