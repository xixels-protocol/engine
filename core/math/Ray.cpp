#include "Ray.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"

using namespace Xixels;

_bool Ray::Intersect( const Sphere& s, _float& dist ) const
{
	Vector3 o = orig - s.c;

	_float a = Vector3::Dot( dir, dir );
	_float b = Vector3::Dot( dir, o ) * 2.0f;
	_float c = Vector3::Dot( o, o ) - s.r * s.r;

	_float d = b * b - 4 * a * c;
	if ( d < 0.0f )
		return _false;

	_float ds = Math::Sqrt( d );
	_float q = ( b < 0.0f ? ( -b - ds ) : ( -b + ds ) ) * 0.5f;

	_float t0 = q / a, t1 = c / q;

	if ( t0 > t1 )
		Math::Swap( t0, t1 );

	if ( t1 < 0.0f )
		return _false;

	dist = t0 < 0.0f ? t1 : t0;

	return _true;
}

_bool Ray::Intersect( const Plane& p, _float& dist ) const
{
	_float dot = Vector3::Dot( p.Normal( ), dir );
	if ( Math::Abs( dot ) < Math::cEpsilon )
		return _false;

	_float temp = p.Distance( orig ) / -dot;
	if ( temp < 0.0f )
		return _false;

	dist = temp;

	return _true;
}

_bool Ray::Intersect( const Triangle& triangle, _float& dist, _bool backcull ) const
{
	Vector3 edge1 = triangle.v2 - triangle.v1;
	Vector3 edge2 = triangle.v3 - triangle.v1;

	Vector3 tvec, pvec = Vector3::Cross( dir, edge2 );

	_float det = Vector3::Dot( edge1, pvec );
	if ( det == 0.0f )
		return _false;

	if ( det > 0.0f )
	{
		tvec = orig - triangle.v1;
	}
	else
	{
		if ( backcull )
			return _false;

		tvec = triangle.v1 - orig;
		det = -det;
	}

	_float u = Vector3::Dot( tvec, pvec );
	if ( u < 0.0f || u > det )
		return _false;

	Vector3 qvec = Vector3::Cross( tvec, edge1 );

	_float v = Vector3::Dot( dir, qvec );
	if ( v < 0.0f || u + v > det )
		return _false;

	_float tdis = Vector3::Dot( edge2, qvec ) / det;
	if ( tdis < 0.0f )
		return _false;

	dist = tdis;
	return _true;
}

_bool Ray::Intersect( const Triangle& triangle, _float& u, _float& v, _float& t, _bool backcull ) const
{
	Vector3 edge1 = triangle.v2 - triangle.v1;
	Vector3 edge2 = triangle.v3 - triangle.v1;

	Vector3 tvec, pvec = Vector3::Cross( dir, edge2 );

	_float det = Vector3::Dot( edge1, pvec );

	if ( det >= 0.0f )
	{
		tvec = orig - triangle.v1;
	}
	else
	{
		if ( backcull )
			return _false;

		tvec = triangle.v1 - orig;
		det = -det;
	}

	if ( det < Math::cEpsilon )
		return _false;

	u = Vector3::Dot( tvec, pvec );
	if ( u < 0.0f || u > det )
		return _false;

	Vector3 qvec = Vector3::Cross( tvec, edge1 );

	v = Vector3::Dot( dir, qvec );
	if ( v < 0.0f || u + v > det )
		return _false;

	t = Vector3::Dot( edge2, qvec );

	_float invdet = 1.0f / det;
	u *= invdet;
	v *= invdet;
	t *= invdet;

	return _true;
}