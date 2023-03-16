#pragma once

#include "Vector3.h"
#include "Matrix4.h"

namespace Xixels
{

class OrientedBox
{
public:
	Vector3	vs[8];

public:
	inline OrientedBox( )
		{ }
	inline OrientedBox( const Vector3& vmin, const Vector3& vmax )
		{ Build( vmin, vmax ); }
	inline OrientedBox( const Matrix4& projinv, _float begin, _float end )
		{ Build( projinv, begin, end ); }

	inline OrientedBox& operator *= ( const Matrix4& mat )
	{
		vs[0] *= mat;
		vs[1] *= mat;
		vs[2] *= mat;
		vs[3] *= mat;
		vs[4] *= mat;
		vs[5] *= mat;
		vs[6] *= mat;
		vs[7] *= mat;
		return *this;
	}

	inline OrientedBox operator * ( const Matrix4& mat ) const
		{ OrientedBox ret( *this ); return ret *= mat; }

	OrientedBox& Build( const Vector3& vmin, const Vector3& vmax );
	OrientedBox& Build( const Matrix4& projinv, _float begin, _float end );

	_void		ComputeMinMax( Vector3& frustummin, Vector3& frustummax );
};

};