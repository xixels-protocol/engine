#include "Segment.h"

using namespace Xixels;

Vector3 Segment::Closest( const Vector3& v ) const
{
	Vector3 v12 = v2 - v1;

	_float t = Vector3::Dot( v - v1, v12 ) / Vector3::Dot( v12, v12 );
	t = Math::Clamp( t, 0.0f, 1.0f );

	return v1 + v12 * t;
}

Vector3 Segment::ClosestOverLine( const Vector3& v ) const
{
	Vector3 v12 = v2 - v1;

	_float t = Vector3::Dot( v - v1, v12 ) / Vector3::Dot( v12, v12 );

	return v1 + v12 * t;
}

_float Segment::Closest( const Segment& seg, Vector3& pos1, Vector3& pos2 ) const
{ 
	Vector3 d1 = v2 - v1;
	Vector3 d2 = seg.v2 - seg.v1;
	Vector3 e = seg.v1 - v1;

	Vector3 e_X_d2 = Vector3::Cross( e, d2 );
	Vector3 e_X_d1 = Vector3::Cross( e, d1 );
	Vector3 d1_X_d2 = Vector3::Cross( d1, d2 );

	_float t1 = Vector3::Dot( e_X_d2, d1_X_d2 );
	_float t2 = Vector3::Dot( e_X_d1, d1_X_d2 );
	_float dd = d1_X_d2.MagnitudeSquared( );

	if ( dd == 0.0f )
	{
		pos2 = seg.Closest( v1 );
		return ( pos2 - v1 ).MagnitudeSquared( );
	}

	t1 /= dd;
	t2 /= dd;

	pos1 = Vector3::Lerp( v1, v2, t1 );
	pos2 = Vector3::Lerp( seg.v1, seg.v2, t2 );

	return ( pos1 - pos2 ).MagnitudeSquared( );
}