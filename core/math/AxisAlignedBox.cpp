#include "AxisAlignedBox.h"
#include "Ray.h"

using namespace Xixels;

const AxisAlignedBox AxisAlignedBox::cNullBox( 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f );
const AxisAlignedBox AxisAlignedBox::cInitBox( Math::cMaxFloat, Math::cMaxFloat, Math::cMaxFloat, Math::cMinFloat, Math::cMinFloat, Math::cMinFloat );
const AxisAlignedBox AxisAlignedBox::cInfinityBox( Math::cMinFloat, Math::cMinFloat, Math::cMinFloat, Math::cMaxFloat, Math::cMaxFloat, Math::cMaxFloat );

AxisAlignedBox::AxisAlignedBox( const Vector3& pos, const Vector3& dir, _float range, _float semiConeAngle )
{
	semiConeAngle = Math::Clamp( semiConeAngle, 0.0f + Math::cEpsilon, Math::cPi * 0.5f - Math::cEpsilon );

	_float xx = Math::Abs( dir.x );
	_float yy = Math::Abs( dir.y );
	_float zz = Math::Abs( dir.z );

	Vector3 d = dir;
	d.Normalize( );

	Vector3 uu;

	if ( xx <= yy && xx <= zz )
		uu = Vector3::Plumb( Vector3::cXAxis, d );
	else if ( yy <= xx && yy <= zz )
		uu = Vector3::Plumb( Vector3::cYAxis, d );
	else
		uu = Vector3::Plumb( Vector3::cZAxis, d );

	uu.Normalize( );
	Vector3 vv = Vector3::Cross( d, uu );

	_float r = range * Math::Tan( semiConeAngle );
	Vector3 bottom = pos + d * range;
	Vector3 pts[4];

	pts[0] = bottom + uu * r + vv * r;
	pts[1] = bottom - uu * r + vv * r;
	pts[2] = bottom - uu * r - vv * r;
	pts[3] = bottom + uu * r - vv * r;

	vmin = pos;
	vmax = pos;

	for ( _dword i = 0; i < 4; i ++ )
	{
		vmin.x = Math::Min( vmin.x, pts[i].x );
		vmin.y = Math::Min( vmin.y, pts[i].y );
		vmin.z = Math::Min( vmin.z, pts[i].z );
		vmax.x = Math::Max( vmax.x, pts[i].x );
		vmax.y = Math::Max( vmax.y, pts[i].y );
		vmax.z = Math::Max( vmax.z, pts[i].z );
	}
}

AxisAlignedBox& AxisAlignedBox::operator *= ( const Matrix4& mat )
{
	// TODO.
	return *this;
}

_void AxisAlignedBox::GetVertices( Vector3 vertices[8] ) const
{
	// bottom
	vertices[0] = Vector3( vmin.x, vmin.y, vmin.z ); // lt
	vertices[1] = Vector3( vmin.x, vmax.y, vmin.z ); // lb
	vertices[2] = Vector3( vmax.x, vmax.y, vmin.z ); // rb
	vertices[3] = Vector3( vmax.x, vmin.y, vmin.z ); // rt

	// top
	vertices[4] = Vector3( vmin.x, vmin.y, vmax.z ); // lt
	vertices[5] = Vector3( vmin.x, vmax.y, vmax.z ); // lb
	vertices[6] = Vector3( vmax.x, vmax.y, vmax.z ); // rb
	vertices[7] = Vector3( vmax.x, vmin.y, vmax.z ); // rt
}

_void AxisAlignedBox::GetPlanes( Plane planes[6] ) const
{
	planes[0] = Plane( vmax, Vector3::cXAxis );
	planes[1] = Plane( vmin, -Vector3::cXAxis );
	planes[2] = Plane( vmax, Vector3::cYAxis );
	planes[3] = Plane( vmin, -Vector3::cYAxis );
	planes[4] = Plane( vmax, Vector3::cZAxis );
	planes[5] = Plane( vmin, -Vector3::cZAxis );
}

_bool AxisAlignedBox::Intersect( const AxisAlignedBox& box ) const
{
	_float x1 = Math::Max( vmin.x, box.vmin.x );
	if ( x1 >= vmax.x || x1 >= box.vmax.x )
		return _false;

	_float x2 = Math::Min( vmax.x, box.vmax.x );
	if ( x2 <= vmin.x || x2 <= box.vmin.x )
		return _false;

	_float y1 = Math::Max( vmin.y, box.vmin.y );
	if ( y1 >= vmax.y || y1 >= box.vmax.y )
		return _false;

	_float y2 = Math::Min( vmax.y, box.vmax.y );
	if ( y2 <= vmin.y || y2 <= box.vmin.y )
		return _false;

	_float z1 = Math::Max( vmin.z, box.vmin.z );
	if ( z1 >= vmax.z || z1 >= box.vmax.z )
		return _false;

	_float z2 = Math::Min( vmax.z, box.vmax.z );
	if ( z2 <= vmin.z || z2 <= box.vmin.z )
		return _false;

	return _true;
}

_bool AxisAlignedBox::Intersect( const Plane& p ) const
{
	_float d1 = p.Distance( Vector3( vmin.x, vmin.y, vmin.z ) );
	_float d2 = p.Distance( Vector3( vmax.x, vmax.y, vmax.z ) );

	_float t = d1 * d2;
	if ( t <= Math::cEpsilon )
		return _true;

	t *= p.Distance( Vector3( vmax.x, vmin.y, vmin.z ) );
	if ( t <= Math::cEpsilon )
		return _true;

	t *= p.Distance( Vector3( vmin.x, vmax.y, vmin.z ) );
	if ( t <= Math::cEpsilon )
		return _true;

	t *= p.Distance( Vector3( vmax.x, vmax.y, vmin.z ) );
	if ( t <= Math::cEpsilon )
		return _true;

	t *= p.Distance( Vector3( vmin.x, vmin.y, vmax.z ) );
	if ( t <= Math::cEpsilon )
		return _true;

	t *= p.Distance( Vector3( vmax.x, vmin.y, vmax.z ) );
	if ( t <= Math::cEpsilon )
		return _true;

	t *= p.Distance( Vector3( vmin.x, vmax.y, vmax.z ) );
	if ( t <= Math::cEpsilon )
		return _true;

	return _false;
}

_bool AxisAlignedBox::Intersect( const Plane& p, const Vector3& dir, _float& dist ) const
{
	dist = 0.0f;

	_float t, d[8];Vector3 vectors[8];
	d[0] = p.Distance( vectors[0] = Vector3( vmin.x, vmin.y, vmin.z ) );
	d[1] = p.Distance( vectors[1] = Vector3( vmax.x, vmax.y, vmax.z ) );

	if ( ( t = d[0] * d[1] ) <= Math::cEpsilon )
		return _true;

	d[2] = p.Distance( vectors[2] = Vector3( vmax.x, vmin.y, vmin.z ) );
	if ( ( t *= d[2] ) <= Math::cEpsilon )
		return _true;

	d[3] = p.Distance( vectors[3] = Vector3( vmin.x, vmax.y, vmin.z ) );
	if ( ( t *= d[3] ) <= Math::cEpsilon )
		return _true;

	d[4] = p.Distance( vectors[4] = Vector3( vmax.x, vmax.y, vmin.z ) );
	if ( ( t *= d[4] ) <= Math::cEpsilon )
		return _true;

	d[5] = p.Distance( vectors[5] = Vector3( vmin.x, vmin.y, vmax.z ) );
	if ( ( t *= d[5] ) <= Math::cEpsilon )
		return _true;

	d[6] = p.Distance( vectors[6] = Vector3( vmax.x, vmin.y, vmax.z ) );
	if ( ( t *= d[6] ) <= Math::cEpsilon )
		return _true;

	d[7] = p.Distance( vectors[7] = Vector3( vmin.x, vmax.y, vmax.z ) );
	if ( ( t *= d[7] ) <= Math::cEpsilon )
		return _true;

	// Not intersecte, find the nearest point.
	_dword n = 0;t = Math::Abs( d[0] );
	for ( _dword i = 1; i < 8; i ++ )
	{
		if ( Math::Abs( d[i] ) < t )
		{
			t = Math::Abs( d[i] );
			n = i;
		}
	}

	// Find the dist from the point to the p.
	return Ray( vectors[n], dir ).Intersect( p, dist );
}

_bool AxisAlignedBox::IntersectMoving( const AxisAlignedBox& box, const Vector3& dir, _float& dist1, _float& dist2 ) const
{
	// Exit early if initially overlapping.
	//if ( Intersect( box ) )
	//{
	//	dist1 = dist2 = 0.0f;
	//	return _true;
	//}

	// Initialize times of first and last contact
	dist1 = 0.0f;
	dist2 = Math::cMaxFloat;

	const _float* v = (const _float*) &dir;
	const _float* amin = (const _float*) &vmin;
	const _float* amax = (const _float*) &vmax;
	const _float* bmin = (const _float*) &box.vmin;
	const _float* bmax = (const _float*) &box.vmax;

	// For each axis, determine times of first and last contact.
	for ( _dword i = 0; i < 3; i ++ )
	{
		if ( v[i] < 0.0f )
		{
			// Nonintersecting and moving apart.
			if ( bmax[i] < amin[i] )
				return _false;

			if ( amax[i] < bmin[i] )
				dist1 = Math::Max( ( amax[i] - bmin[i] ) / v[i], dist1 );
			if ( bmax[i] > amin[i] )
				dist2 = Math::Min( ( amin[i] - bmax[i] ) / v[i], dist2 );
		}
		else if ( v[i] > 0.0f )
		{
			// Nonintersecting and moving apart.
			if ( bmin[i] > amax[i] )
				return _false;

			if ( bmax[i] < amin[i] )
				dist1 = Math::Max( ( amin[i] - bmax[i] ) / v[i], dist1 );
			if ( amax[i] > bmin[i] )
				dist2 = Math::Min( ( amax[i] - bmin[i] ) / v[i], dist2 );
		}

		// No overlap possible if time of first contact occurs after time of last contact.
		if ( dist1 > dist2 )
			return _false;
	}

	return _true;
}

_bool AxisAlignedBox::ClipLineWithBox( const Vector4& start, const Vector4& end, Vector4& intersectedstart, Vector4& intersectedend ) const
{
	intersectedstart = start;
	intersectedend = end;

	Vector4 dir;
	_float edgeofbox, linelength;
	_bool startculled, endculled;
	
	// Bound by neg X
	startculled = intersectedstart.x < vmin.x;
	endculled = intersectedend.x < vmin.x;
	if ( startculled && endculled )
	{
		intersectedstart = start;
		intersectedend = start;
		return _false;
	}
	else if ( startculled )
	{
		dir = intersectedstart - intersectedend;
		edgeofbox = vmin.x - intersectedend.x;
		linelength = intersectedstart.x - intersectedend.x;
		intersectedstart = intersectedend + dir*( edgeofbox/linelength );
	}
	else if ( endculled )
	{
		dir = intersectedend - intersectedstart;
		edgeofbox = vmin.x - intersectedstart.x;
		linelength = intersectedend.x - intersectedstart.x;
		intersectedend = intersectedstart + dir*( edgeofbox/linelength );
	}

	// Bound by pos X
	startculled = intersectedstart.x > vmax.x;
	endculled = intersectedend.x > vmax.x;
	if ( startculled && endculled )
	{
		intersectedstart = start;
		intersectedend = start;
		return _false;
	}
	else if ( startculled )
	{
		dir = intersectedstart - intersectedend;
		edgeofbox = vmax.x - intersectedend.x;
		linelength = intersectedstart.x - intersectedend.x;
		intersectedstart = intersectedend + dir*( edgeofbox/linelength );
	}
	else if ( endculled )
	{
		dir = intersectedend - intersectedstart;
		edgeofbox = vmax.x - intersectedstart.x;
		linelength = intersectedend.x - intersectedstart.x;
		intersectedend = intersectedstart + dir*( edgeofbox/linelength );
	}

	// Bound by neg Y
	startculled = intersectedstart.y < vmin.y;
	endculled = intersectedend.y < vmin.y;
	if ( startculled && endculled )
	{
		intersectedstart = start;
		intersectedend = start;
		return _false;
	}
	else if ( startculled )
	{
		dir = intersectedstart - intersectedend;
		edgeofbox = vmin.y - intersectedend.y;
		linelength = intersectedstart.y - intersectedend.y;
		intersectedstart = intersectedend + dir*( edgeofbox/linelength );
	}
	else if ( endculled )
	{
		dir = intersectedend - intersectedstart;
		edgeofbox = vmin.y - intersectedstart.y;
		linelength = intersectedend.y - intersectedstart.y;
		intersectedend = intersectedstart + dir*( edgeofbox/linelength );
	}

	// Bound by pos Y
	startculled = intersectedstart.y > vmax.y;
	endculled = intersectedend.y > vmax.y;
	if ( startculled && endculled )
	{
		intersectedstart = start;
		intersectedend = start;
		return _false;
	}
	else if ( startculled )
	{
		dir = intersectedstart - intersectedend;
		edgeofbox = vmax.y - intersectedend.y;
		linelength = intersectedstart.y - intersectedend.y;
		intersectedstart = intersectedend + dir*( edgeofbox/linelength );
	}
	else if ( endculled )
	{
		dir = intersectedend - intersectedstart;
		edgeofbox = vmax.y - intersectedstart.y;
		linelength = intersectedend.y - intersectedstart.y;
		intersectedend = intersectedstart + dir*( edgeofbox/linelength );
	}

	// Bound by neg Z
	startculled = intersectedstart.z < vmin.z;
	endculled = intersectedend.z < vmin.z;
	if ( startculled && endculled )
	{
		intersectedstart = start;
		intersectedend = start;
		return _false;
	}
	else if ( startculled )
	{
		dir = intersectedstart - intersectedend;
		edgeofbox = vmin.z - intersectedend.z;
		linelength = intersectedstart.z - intersectedend.z;
		intersectedstart = intersectedend + dir*( edgeofbox/linelength );
	}
	else if ( endculled )
	{
		dir = intersectedend - intersectedstart;
		edgeofbox = vmin.z - intersectedstart.z;
		linelength = intersectedend.z - intersectedstart.z;
		intersectedend = intersectedstart + dir*( edgeofbox/linelength );
	}

	// Bound by pos Z
	startculled = intersectedstart.z > vmax.z;
	endculled = intersectedend.z > vmax.z;
	if ( startculled && endculled )
	{
		intersectedstart = start;
		intersectedend = start;
		return _false;
	}
	else if ( startculled )
	{
		dir = intersectedstart - intersectedend;
		edgeofbox = vmax.z - intersectedend.z;
		linelength = intersectedstart.z - intersectedend.z;
		intersectedstart = intersectedend + dir*( edgeofbox/linelength );
	}
	else if ( endculled )
	{
		dir = intersectedend - intersectedstart;
		edgeofbox = vmax.z - intersectedstart.z;
		linelength = intersectedend.z - intersectedstart.z;
		intersectedend = intersectedstart + dir*( edgeofbox/linelength );
	}

	return _true;
}

AxisAlignedBox AxisAlignedBox::Intersect( const AxisAlignedBox& box1, const AxisAlignedBox& box2 )
{
	AxisAlignedBox box = box1;

	box.vmin.x = Math::Max( box.vmin.x, box2.vmin.x );
	box.vmin.y = Math::Max( box.vmin.y, box2.vmin.y );
	box.vmin.z = Math::Max( box.vmin.z, box2.vmin.z );

	box.vmax.x = Math::Min( box.vmax.x, box2.vmax.x );
	box.vmax.y = Math::Min( box.vmax.y, box2.vmax.y );
	box.vmax.z = Math::Min( box.vmax.z, box2.vmax.z );

	if ( box.vmin.x > box.vmax.x || box.vmin.y > box.vmax.y || box.vmin.z > box.vmax.z )
		box = AxisAlignedBox::cNullBox;

	return box;
}