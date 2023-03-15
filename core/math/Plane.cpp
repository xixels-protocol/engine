#include "Plane.h"

using namespace Xixels;

const Plane Plane::cXYPlane( 0.0f, 0.0f, 1.0f, 0.0f );
const Plane Plane::cYZPlane( 1.0f, 0.0f, 0.0f, 0.0f );
const Plane Plane::cZXPlane( 0.0f, 1.0f, 0.0f, 0.0f );

_bool Plane::Intersect( const Vector3& v1, const Vector3& v2, Vector3& p ) const
{
	// TODO.
	return _false;
}