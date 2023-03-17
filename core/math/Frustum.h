#pragma once

#include "Vector3.h"
#include "Matrix4.h"
#include "Plane.h"
#include "Rect.h"
#include "AxisAlignedBox.h"
#include "OrientedBox.h"

namespace Xixels
{

class Frustum
{
public:
	Vector3	vs[8];
	Plane	ps[6];

public:
	inline Frustum( )
		{ }
	inline Frustum( const Matrix4& view, const Matrix4& proj )
		{ Build( view, proj ); }
	inline Frustum( const OrientedBox& box )
		{ Build( box ); }

	inline _bool operator == ( const Frustum& frustum ) const
		{ return ps[0] == frustum.ps[0] && ps[1] == frustum.ps[1] && ps[2] == frustum.ps[2] && ps[3] == frustum.ps[3] && ps[4] == frustum.ps[4] && ps[5] == frustum.ps[5]; }
	inline _bool operator != ( const Frustum& frustum ) const
		{ return ps[0] != frustum.ps[0] || ps[1] != frustum.ps[1] || ps[2] != frustum.ps[2] || ps[3] != frustum.ps[3] || ps[4] != frustum.ps[4] || ps[5] != frustum.ps[5]; }

	inline _float Depth( ) const
		{ return Math::Abs( ps[1].Distance( vs[0] ) ); }

	Frustum&		Build( const Matrix4& view, const Matrix4& proj );
	Frustum&		Build( const OrientedBox& box );
	Frustum&		Build( const Vector3& eye, const Region& reg, _float height, _float depth );
	Frustum&		Scale( _float scale );

	_bool			Inside( const Vector3& v ) const;

	_bool			Inside( const AxisAlignedBox& box ) const;
	_bool			Inside( const OrientedBox& box ) const;

	_bool			FullInside( const AxisAlignedBox& box ) const;
	_bool			FullInside( const OrientedBox& box ) const;

	AxisAlignedBox	Intersect( const AxisAlignedBox& box ) const;
	_bool			IntersectMoving( const AxisAlignedBox& box, const Vector3& dir ) const;
};


class HomogenousFrustum
{
public:
	_float	mRightSlope;
	_float	mLeftSlope;
	_float	mTopSlope;
	_float	mBottomSlope;

	_float	mNearZ;
	_float	mFarZ;

public:
	inline HomogenousFrustum( )
		{ }
	inline HomogenousFrustum( const Matrix4& projinv )
		{ Build( projinv ); }

	HomogenousFrustum& Build( const Matrix4& projinv );
};

};