#pragma once

#include "Vector3.h"
#include "Matrix4.h"

namespace Xixels
{

class Area
{
public:
	enum _Area_TYPE
	{
		_TYPE_UNKNOW	= 0,
		_TYPE_RECT		= 1,
		_TYPE_SPHERE	= 2,
	};

	_dword	type;

	union
	{
		struct
		{
			_float l, t, r, b;
		};

		struct
		{
			_float x, y, z, r1;
		};
	};

public:
	inline Area( )
		: type( _TYPE_RECT ), l( 0.0f ), t( 0.0f ), r( 0.0f ), b( 0.0f ) { }
	inline Area( _float ll, _float tt, _float rr, _float bb )
		: type( _TYPE_RECT ), l( ll ), t( tt ), r( rr ), b( bb ) { }

	inline Area& operator *= ( _float s )
		{ l *= s; t *= s; r *= s; b *= s; return *this; }
	inline Area& operator /= ( _float s )
		{ l /= s; t /= s; r /= s; b /= s; return *this; }

	inline Area operator * ( _float s ) const
		{ return Area( l * s, t * s, r * s, b * s ); }

	inline Area operator * ( const Matrix4& mat ) const
	{
		Area ret = *this;
		if ( type == _TYPE_RECT )
		{
			Vector3 lt( ret.l, ret.t, 0.0f );
			Vector3 rb( ret.r, ret.b, 0.0f );

			lt *= mat;
			rb *= mat;

			ret.l = Math::Min( lt.x, rb.x );
			ret.t = Math::Min( lt.y, rb.y );
			ret.r = Math::Max( lt.x, rb.x );
			ret.b = Math::Max( lt.y, rb.y );
		}
		else if ( type == _TYPE_SPHERE )
		{
			Vector3 p( x, y, z );
			p *= mat;

			ret.x = p.x;
			ret.y = p.y;
			ret.z = p.z;
		}

		return ret;
	}

	inline Area operator / ( _float s ) const
		{ return Area( l / s, t / s, r / s, b / s ); }

	inline _bool Inside( const Vector3& p ) const
	{
		if ( type == _TYPE_RECT )
			return p.x > l && p.x < r && p.y > t && p.y < b;
		else if ( type == _TYPE_SPHERE )
			return ( p - Vector3( x, y, z ) ).Magnitude( ) < r1;

		return _false;
	}
};

};