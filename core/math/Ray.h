#pragma once

#include "Vector3.h"
#include "Vector4.h"

namespace Xixels
{

class Sphere;
class Plane;
class Triangle;

class Ray
{
public:
	Vector3	orig;
	Vector3	dir;

public:
	inline Ray( )
		{ }
	inline Ray( _float ox, _float oy, _float oz, _float dx, _float dy, _float dz )
		: orig( ox, oy, oz ), dir( dx, dy, dz ) { }
	inline Ray( const Vector3& o, const Vector3& d )
		: orig( o ), dir( d ) { }

	inline Ray& operator *= ( const Matrix4& mat )
		{ orig *= mat; dir = Vector4( dir, 0.0f ) * mat; return *this; }
	inline Ray operator * ( const Matrix4& mat ) const
		{ return Ray( orig * mat, Vector4( dir, 0.0f ) * mat ); }

	inline _bool operator == ( const Ray& ray ) const
		{ return orig == ray.orig && dir == ray.dir; }
	inline _bool operator != ( const Ray& ray ) const
		{ return orig != ray.orig || dir != ray.dir; }

	inline _bool Equal( const Ray& ray, _float margin = Math::cEpsilon ) const
		{ return orig.Equal( ray.orig, margin ) && dir.Equal( ray.dir, margin ); }

	inline Vector3 VectorOnRay( _float dist ) const
		{ return orig + dir * dist; }

	_bool	Intersect( const Sphere& s, _float& dist ) const;
	_bool	Intersect( const Plane& p, _float& dist ) const;
	_bool	Intersect( const Triangle& triangle, _float& dist, _bool backcull = _false ) const;
	_bool	Intersect( const Triangle& triangle, _float& u, _float& v, _float& t, _bool backcull = _false ) const;
};

};