#include "Ray.h"
#include "Frustum.h"

using namespace Xixels;

Frustum& Frustum::Build( const Matrix4& view, const Matrix4& proj )
{
	Matrix4 vp = view * proj;
	vp.Inverse( );

	vs[0] = Vector3( -1.0f, -1.0f, 0.0f ) * vp;
	vs[1] = Vector3( -1.0f,  1.0f, 0.0f ) * vp;
	vs[2] = Vector3(  1.0f,  1.0f, 0.0f ) * vp;
	vs[3] = Vector3(  1.0f, -1.0f, 0.0f ) * vp;
	vs[4] = Vector3( -1.0f, -1.0f, 1.0f ) * vp;
	vs[5] = Vector3( -1.0f,  1.0f, 1.0f ) * vp;
	vs[6] = Vector3(  1.0f,  1.0f, 1.0f ) * vp;
	vs[7] = Vector3(  1.0f, -1.0f, 1.0f ) * vp;

	ps[0] = Plane( vs[0], vs[1], vs[2] ); // Near
	ps[1] = Plane( vs[5], vs[7], vs[6] ); // Far
	ps[2] = Plane( vs[1], vs[4], vs[5] ); // Left
	ps[3] = Plane( vs[6], vs[7], vs[2] ); // Right
	ps[4] = Plane( vs[1], vs[5], vs[2] ); // Top
	ps[5] = Plane( vs[3], vs[4], vs[0] ); // Bottom

	return *this;
}

Frustum& Frustum::Build( const OrientedBox& box )
{
	for ( _dword i = 0; i < 8; i ++ )
		vs[i] = box.vs[i];

	ps[0] = Plane( vs[0], vs[2], vs[1] ); // Near
	ps[1] = Plane( vs[4], vs[5], vs[6] ); // Far
	ps[2] = Plane( vs[1], vs[5], vs[4] ); // Left
	ps[3] = Plane( vs[6], vs[7], vs[2] ); // Right
	ps[4] = Plane( vs[1], vs[3], vs[5] ); // Top
	ps[5] = Plane( vs[0], vs[4], vs[2] ); // Bottom

	return *this;
}

Frustum& Frustum::Scale( _float scale )
{
	vs[4] = ( vs[4] - vs[0] ) * scale + vs[0];
	vs[5] = ( vs[5] - vs[1] ) * scale + vs[1];
	vs[6] = ( vs[6] - vs[2] ) * scale + vs[2];
	vs[7] = ( vs[7] - vs[3] ) * scale + vs[3];

	ps[1] = Plane( vs[5], vs[7], vs[6] ); // Far
	ps[2] = Plane( vs[1], vs[4], vs[5] ); // Left
	ps[3] = Plane( vs[6], vs[7], vs[2] ); // Right
	ps[4] = Plane( vs[1], vs[5], vs[2] ); // Top
	ps[5] = Plane( vs[3], vs[4], vs[0] ); // Bottom

	return *this;
}

_bool Frustum::Inside( const Vector3& v ) const
{
	for ( _long i = 0; i < 6; i ++ )
	{
		if ( ps[i].Distance( v ) > 0.0f )
			return _false;
	}

	return _true;
}

_bool Frustum::Inside( const AxisAlignedBox& box ) const
{
	Vector3 vmin;

	for ( _dword i = 0; i < 6; i ++ )
	{
		// X axis.
		vmin.x = ps[i].a > 0.0f ? box.vmin.x : box.vmax.x;

		// Y axis.
		vmin.y = ps[i].b > 0.0f ? box.vmin.y : box.vmax.y;

		// Z axis.
		vmin.z = ps[i].c > 0.0f ? box.vmin.z : box.vmax.z;

		if ( ps[i].Distance( vmin ) > 0.0f )
			return _false;
	}

	return _true;
}

_bool Frustum::Inside( const OrientedBox& box ) const
{
	_byte outside[8] = { 0 };

	for ( _long i = 0; i < 8; i ++ )
	{
		for ( _long j = 0; j < 6; j ++ )
		{
			if ( ps[j].Distance( box.vs[i] ) > 0.0f )
				outside[i] |= 1 << j;
		}

		if ( outside[i] == 0 )
			return _true;
	}

	return ( outside[0] & outside[1] & outside[2] & outside[3] & outside[4] & outside[5] & outside[6] & outside[7] ) == 0;
}

_bool Frustum::FullInside( const AxisAlignedBox& box ) const
{
	// TODO.
	return FullInside( OrientedBox( box.vmin, box.vmax ) );
}

_bool Frustum::FullInside( const OrientedBox& box ) const
{
	for ( _long i = 0; i < 8; i ++ )
	{
		for ( _long j = 0; j < 6; j ++ )
		{
			if ( ps[j].Distance( box.vs[i] ) > 0.0f )
				return _false;
		}
	}

	return _true;
}

AxisAlignedBox Frustum::Intersect( const AxisAlignedBox& box ) const
{
	AxisAlignedBox box2 = box;

	_bool rayinbox = _true;

	// Build rays.
	Ray rays[4];
	_float dists[4];
	for ( _dword i = 0; i < 4; i ++ )
	{
		Vector3 dir = Vector3( vs[i + 4] - vs[i] );
		Vector3 ndir = Vector3( vs[i + 4] - vs[i] ).Normalize( );
		rays[i] = Ray( vs[i], ndir );
		dists[i] = dir.z / ndir.z;
		if ( box.VectorInBox( vs[i] ) == _false )
			rayinbox = _false;
	}

	// Build planes of bound box.
	OrientedBox obox( box.vmin, box.vmax );

	Plane planes[6] = {
		Plane( obox.vs[0], obox.vs[1], obox.vs[2] ),
		Plane( obox.vs[4], obox.vs[6], obox.vs[5] ),
		Plane( obox.vs[4], obox.vs[5], obox.vs[0] ),
		Plane( obox.vs[2], obox.vs[3], obox.vs[6] ),
		Plane( obox.vs[5], obox.vs[7], obox.vs[1] ),
		Plane( obox.vs[4], obox.vs[0], obox.vs[6] ),
	};
	
	Vector3 pts1[4], pts2[4];

	// Pick planes by rays, and intersect with current box.
	for ( _dword i = 0; i < 3; i ++ )
	{
		const Plane& p1 = planes[i * 2];
		const Plane& p2 = planes[i * 2 + 1];

		// Pick plane 1.
		_dword pick1 = 0;
		for ( _dword j = 0; j < 4; j ++ )
		{
			const Ray& r = rays[j];

			_float dist = 0.0f;
			if ( r.Intersect( p1, dist ) )
			{
				pick1 += 1 << j;
				dist = dist > dists[j] ? dists[j] : dist;
				pts1[j] = r.VectorOnRay( dist );
			}
		}

		// Pick plane 2.
		_dword pick2 = 0;
		for ( _dword j = 0; j < 4; j ++ )
		{
			const Ray& r = rays[j];

			_float dist = 0.0f;
			if ( r.Intersect( p2, dist ) )
			{
				pick2 += 1 << j;
				dist = dist > dists[j] ? dists[j] : dist;
				pts2[j] = r.VectorOnRay( dist );
			}
		}

		_bool allpicked = _false;

		// Both plane picked.
		if ( pick1 == 15 && pick2 == 15 )
		{
			allpicked = _true;
		}
		// Plane 1 picked, and ray inside box.
		else if ( pick1 == 15 && rayinbox )
		{
			for ( _dword j = 0; j < 4; j ++ )
				pts2[j] = rays[j].orig;

			allpicked = _true;
		}
		// Plane 2 picked, and ray inside box.
		else if ( pick2 == 15 && rayinbox )
		{
			for ( _dword j = 0; j < 4; j ++ )
				pts1[j] = rays[j].orig;

			allpicked = _true;
		}

		// Build intersect bound box.
		if ( allpicked )
		{
			AxisAlignedBox temp = AxisAlignedBox::cInitBox;
			for ( _dword j = 0; j < 4; j ++ )
			{
				temp += pts1[j];
				temp += pts2[j];
			}

			box2 = AxisAlignedBox::Intersect( temp, box2 );
		}
	}

	return box2;
}

_bool Frustum::IntersectMoving( const AxisAlignedBox& box, const Vector3& dir ) const
{
	Vector3 points[] = {
		Vector3( box.vmin.x, box.vmin.y, box.vmin.z ),
		Vector3( box.vmin.x, box.vmin.y, box.vmax.z ),
		Vector3( box.vmin.x, box.vmax.y, box.vmin.z ),
		Vector3( box.vmin.x, box.vmax.y, box.vmax.z ),
		Vector3( box.vmax.x, box.vmin.y, box.vmin.z ),
		Vector3( box.vmax.x, box.vmin.y, box.vmax.z ),
		Vector3( box.vmax.x, box.vmax.y, box.vmin.z ),
		Vector3( box.vmax.x, box.vmax.y, box.vmax.z )
	};

	for ( _dword i = 0; i < 8; i ++ )
	{
		Vector3 v1 = points[i] - dir * 5000.0f;
		Vector3 v2 = points[i] + dir * 5000.0f;
		Vector3 vpoint;
		
		ps[0].Intersect( v1, v2, vpoint );
		if ( Triangle( vs[0], vs[1], vs[2] ).Inside( vpoint ) ||
			Triangle( vs[0], vs[2], vs[3] ).Inside( vpoint ) )
			return _true;

		ps[1].Intersect( v1, v2, vpoint );
		if ( Triangle( vs[4], vs[5], vs[6] ).Inside( vpoint ) ||
			Triangle( vs[4], vs[6], vs[7] ).Inside( vpoint ) )
			return _true;

		ps[2].Intersect( v1, v2, vpoint );
		if ( Triangle( vs[0], vs[1], vs[4] ).Inside( vpoint ) ||
			Triangle( vs[1], vs[4], vs[5] ).Inside( vpoint ) )
			return _true;

		ps[3].Intersect( v1, v2, vpoint );
		if ( Triangle( vs[6], vs[7], vs[2] ).Inside( vpoint ) ||
			Triangle( vs[2], vs[7], vs[3] ).Inside( vpoint ) )
			return _true;

		ps[4].Intersect( v1, v2, vpoint );
		if ( Triangle( vs[1], vs[5], vs[2] ).Inside( vpoint ) ||
			Triangle( vs[5], vs[2], vs[6] ).Inside( vpoint ) )
			return _true;

		ps[5].Intersect( v1, v2, vpoint );
		if ( Triangle( vs[3], vs[4], vs[0] ).Inside( vpoint ) ||
			Triangle( vs[7], vs[3], vs[3] ).Inside( vpoint ) )
			return _true;
	}

	return _false;
}

HomogenousFrustum& HomogenousFrustum::Build( const Matrix4& projinv )
{
	// Corners of the projection frustum in homogenous space.
	const static Vector4 cHomogenousPoints[6] =
	{
		Vector4(  1.0f,  0.0f, 1.0f, 1.0f ),	// Right (at far plane)
		Vector4( -1.0f,  0.0f, 1.0f, 1.0f ),	// Left
		Vector4(  0.0f,  1.0f, 1.0f, 1.0f ),	// Top
		Vector4(  0.0f, -1.0f, 1.0f, 1.0f ),	// Bottom
		Vector4(  0.0f,  0.0f, 0.0f, 1.0f ),	// Near
		Vector4(  0.0f,  0.0f, 1.0f, 1.0f ),	// Far
	};

	// Compute the frustum corners in world space.
	Vector4 corners[6];
	for ( _dword i = 0; i < 6; i ++ )
		corners[i] = cHomogenousPoints[i] * projinv;

	// Compute the slopes.
	mRightSlope = corners[0].x / corners[0].z;
	mLeftSlope = corners[1].x / corners[1].z;
	mTopSlope = corners[2].y / corners[2].z;
	mBottomSlope = corners[3].y / corners[3].z;

	// Compute near and far.
	mNearZ = corners[4].z / corners[4].w;
	mFarZ = corners[5].z / corners[5].w;

	return *this;
}