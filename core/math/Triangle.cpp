#include "Triangle.h"

using namespace Xixels;

_bool Triangle::Inside( const Vector3& v ) const
{
	_float a1 = Area( );
	_float a2 = Triangle( v, v1, v2 ).Area( ) +
		Triangle( v, v2, v3 ).Area( ) +
		Triangle( v, v3, v1 ).Area( );

	return Math::Abs( a1 - a2 ) < Math::cEpsilon;
}

Vector3	Triangle::Closest( const Vector3& v ) const
{
	Vector3 v12 = v2 - v1;
	Vector3 v13 = v3 - v1;

	// Check if v in vertex region outside v1.
	Vector3 v10 = v - v1;
	_float d1 = Vector3::Dot( v12, v10 );
	_float d2 = Vector3::Dot( v13, v10 );
	if ( d1 <= 0.0f && d2 <= 0.0f )
		return v1;

	// Check if v in vertex region outside v2.
	Vector3 v20 = v - v2;
	_float d3 = Vector3::Dot( v12, v20 );
	_float d4 = Vector3::Dot( v13, v20 );
	if ( d3 >= 0.0f && d4 <= d3 )
		return v2;

	// Check if v in edge region of v12, if so return projection of v onto v12.
	_float vc = d1 * d4 - d3 * d2;
	if ( vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f )
		return v1 + v12 * ( d1 / ( d1 - d3 ) );

	// Check if v in vertex region outside v3.
	Vector3 v30 = v - v3;
	_float d5 = Vector3::Dot( v12, v30 );
	_float d6 = Vector3::Dot( v13, v30 );
	if ( d6 >= 0.0f && d5 <= d6 )
		return v3;

	// Check if v in edge region of v13, if so return projection of v onto v13.
	_float vb = d5 * d2 - d1 * d6;
	if ( vb <= 0.0f && d2 >= 0.0f && d6 <= 0.0f )
		return v1 + v13 * ( d2 / ( d2 - d6 ) );

	// Check if v in edge region of v23, if so return projection of v onto v23.
	_float va = d3 * d6 - d5 * d4;
	if ( va <= 0.0f && ( d4 - d3 ) >= 0.0f && ( d5 - d6 ) >= 0.0f )
		return v2 + ( v3 - v2 ) * ( ( d4 - d3 ) / ( ( d4 - d3 ) + ( d5 - d6 ) ) );

	// v inside face region.
	_float denom = 1.0f / ( va + vb + vc );
	vb *= denom;
	vc *= denom;

	return v1 + v12 * vb + v13 * vc;
}