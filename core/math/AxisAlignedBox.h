#pragma once

#include "Vector3.h"
#include "Vector4.h"
#include "Sphere.h"
#include "Plane.h"

namespace Xixels
{

class AxisAlignedBox
{
public:
	const static AxisAlignedBox cNullBox;
	const static AxisAlignedBox cInitBox;
	const static AxisAlignedBox cInfinityBox;

public:
	Vector3	vmin;
	Vector3	vmax;

public:
	inline AxisAlignedBox( )
		: vmin( Vector3::cOrigin ), vmax( Vector3::cOrigin ) { }

	inline AxisAlignedBox( _float x, _float y, _float z )
		: vmin( x - Math::cEpsilon, y - Math::cEpsilon, z - Math::cEpsilon ), vmax( x + Math::cEpsilon, y + Math::cEpsilon, z + Math::cEpsilon ) { }
	inline AxisAlignedBox( _float x1, _float y1, _float z1, _float x2, _float y2, _float z2 )
		: vmin( x1, y1, z1 ), vmax( x2, y2, z2 ) { }

	inline AxisAlignedBox( const Vector3& v )
		: vmin( v.x - Math::cEpsilon, v.y - Math::cEpsilon, v.z - Math::cEpsilon ), vmax( v.x + Math::cEpsilon, v.y + Math::cEpsilon, v.z + Math::cEpsilon ) { }
	inline AxisAlignedBox( const Vector3& mmin, const Vector3& mmax )
		: vmin( mmin ), vmax( mmax ) { }

	AxisAlignedBox( const Vector3& pos, const Vector3& dir, _float range, _float semiConeAngle );

	inline AxisAlignedBox& operator += ( const AxisAlignedBox& box )
	{
		vmin.x = Math::Min( vmin.x, box.vmin.x );
		vmin.y = Math::Min( vmin.y, box.vmin.y );
		vmin.z = Math::Min( vmin.z, box.vmin.z );
		vmax.x = Math::Max( vmax.x, box.vmax.x );
		vmax.y = Math::Max( vmax.y, box.vmax.y );
		vmax.z = Math::Max( vmax.z, box.vmax.z );

		return *this;
	}

	inline AxisAlignedBox& operator += ( const Vector3& v )
	{
		vmin.x = Math::Min( vmin.x, v.x );
		vmin.y = Math::Min( vmin.y, v.y );
		vmin.z = Math::Min( vmin.z, v.z );
		vmax.x = Math::Max( vmax.x, v.x );
		vmax.y = Math::Max( vmax.y, v.y );
		vmax.z = Math::Max( vmax.z, v.z );

		return *this;
	}

	inline AxisAlignedBox operator + ( const AxisAlignedBox& box ) const
		{ AxisAlignedBox ret( *this ); return ret += box; }

	inline AxisAlignedBox operator + ( const Vector3& v ) const
		{ AxisAlignedBox ret( *this ); return ret += v; }

	inline AxisAlignedBox operator * ( const Matrix4& mat ) const
		{ AxisAlignedBox ret( *this ); return ret *= mat; }

	inline _bool operator == ( const AxisAlignedBox& box ) const
		{ return vmin == box.vmin && vmax == box.vmax; }
	inline _bool operator != ( const AxisAlignedBox& box ) const
		{ return vmin != box.vmin || vmax != box.vmax; }

	inline _bool Equal( const AxisAlignedBox& box, _float margin = Math::cEpsilon ) const
		{ return vmin.Equal( box.vmin, margin ) && vmax.Equal( box.vmax, margin ); }

	inline Vector3 Center( ) const
		{ return ( vmin + vmax ) / 2.0f; }
	inline Vector3 Size( ) const
		{ return ( vmax - vmin ).Absolute( ); }
	inline Vector3 Extents( ) const
		{ return Size( ) / 2.0f; }
	inline _float Volume( ) const
		{ Vector3 size = Size( ); return size.x * size.y * size.z; }

	inline _float SphereRadius( ) const
		{ return Size( ).Magnitude( ) / 2.0f; }

	inline _bool VectorInBox( const Vector3& v ) const
		{ return v.x >= vmin.x && v.x <= vmax.x && v.y >= vmin.y && v.y <= vmax.y && v.z >= vmin.z && v.z <= vmax.z; }

	inline _float DistanceSquared( const Vector3& v ) const
	{
		_float dis = 0.0f;

		if ( v.x < vmin.x )
			dis += ( vmin.x - v.x ) * ( vmin.x - v.x );
		else if ( v.x > vmax.x )
			dis += ( v.x - vmax.x ) * ( v.x - vmax.x );

		if ( v.y < vmin.y )
			dis += ( vmin.y - v.y ) * ( vmin.y - v.y );
		else if ( v.y > vmax.y )
			dis += ( v.y - vmax.y ) * ( v.y - vmax.y );

		if ( v.z < vmin.z )
			dis += ( vmin.z - v.z ) * ( vmin.z - v.z );
		else if ( v.z > vmax.z )
			dis += ( v.z - vmax.z ) * ( v.z - vmax.z );

		return dis;
	}

	inline _bool Intersect( const Sphere& s ) const
		{ return ( DistanceSquared( s.c ) <= s.r * s.r ); }
	inline _bool Intersect( const Vector3& pos, const _float& range ) const
		{ return ( DistanceSquared( pos ) < range * range ); }

	AxisAlignedBox& operator *= ( const Matrix4& mat );

	_void	GetVertices( Vector3 vertices[8] ) const;
	_void	GetPlanes( Plane planes[6] ) const;

	_bool	Intersect( const AxisAlignedBox& box ) const;
	_bool	Intersect( const Plane& p ) const;
	_bool	Intersect( const Plane& p, const Vector3& dir, _float& dist ) const;

	_bool	IntersectMoving( const AxisAlignedBox& box, const Vector3& dir, _float& dist1, _float& dist2 ) const;

	_bool	ClipLineWithBox( const Vector4& start, const Vector4& end, Vector4& intersectedstart, Vector4& intersectedend ) const;

	static AxisAlignedBox Intersect( const AxisAlignedBox& box1, const AxisAlignedBox& box2 );
};

};