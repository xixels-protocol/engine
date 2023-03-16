#include "Sphere.h"

using namespace Xixels;

_bool Sphere::Intersect( const Plane& p, const Vector3& dir, _float& dist ) const
{
	dist = 0.0f;

	if ( Math::Abs( p.Distance( c ) ) <= Math::Abs( r ) )
		return _true;

	return Ray( c, dir ).Intersect( Plane( p.a, p.b, p.c, p.d - Math::Abs( r ) ), dist );
}