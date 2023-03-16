#include "Plane.h"

using namespace Xixels;

const Plane Plane::cXYPlane( 0.0f, 0.0f, 1.0f, 0.0f );
const Plane Plane::cYZPlane( 1.0f, 0.0f, 0.0f, 0.0f );
const Plane Plane::cZXPlane( 0.0f, 1.0f, 0.0f, 0.0f );

_bool Plane::Intersect( const Vector3& v1, const Vector3& v2, Vector3& p ) const
{
	_float p1 = Distance( v1 ), p2 = Distance( v2 );
	if ( p1 * p2 >= 0.0f )
		return _false;

	Ray ray( v1, ( v2 - v1 ).Normalize( ) );
	_float dist;
	if ( ray.Intersect( *this, dist ) == _false )
		return _false;

	p = ray.VectorOnRay( dist );
	return _true;
}