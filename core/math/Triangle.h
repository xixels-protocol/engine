#pragma once

#include "Vector3.h"

namespace Xixels
{

class Triangle
{
public:
	Vector3	v1;
	Vector3	v2;
	Vector3	v3;

public:
	inline Triangle( )
		{ }
	inline Triangle( const Vector3& vv1, const Vector3& vv2, const Vector3& vv3 )
		: v1( vv1 ), v2( vv2 ), v3( vv3 ) { }

	inline Triangle& operator *= ( const Matrix4& mat )
		{ v1 *= mat; v2 *= mat; v3 *= mat; return *this; }
	inline Triangle operator * ( const Matrix4& mat ) const
		{ return Triangle( v1 * mat, v2 * mat, v3 * mat ); }

	inline _float Area( ) const
		{ return Vector3::Cross( v2 - v1, v3 - v1 ).Magnitude( ) * 0.5f; }

	inline Vector3 Middle( ) const
		{ return ( v1 + v2 + v3 ) / 3.0f; }

	inline Vector3 Normal( ) const
	{
		Vector3 normal = Vector3::Cross( v2 - v1, v3 - v1 );
		normal.Normalize( );

		return normal;
	}

	_bool CheckIntersect( const Vector3& orig, const Vector3& dir, _float& dist, _bool backcull = _false ) const
	{
		Vector3 edge1 = v2 - v1;
		Vector3 edge2 = v3 - v1;

		Vector3 tvec, pvec = Vector3::Cross( dir, edge2 );

		_float det = Vector3::Dot( edge1, pvec );
		if ( det == 0.0f )
			return _false;

		if ( det > 0.0f )
		{
			tvec = orig - v1;
		}
		else
		{
			if ( backcull )
				return _false;

			tvec = v1 - orig;
			det = -det;
		}

		_float u = Vector3::Dot( tvec, pvec );
		if ( u < 0.0f || u > det )
			return _false;

		Vector3 qvec = Vector3::Cross( tvec, edge1 );

		_float v = Vector3::Dot( dir, qvec );
		if ( v < 0.0f || u + v > det )
			return _false;

		_float tdis = Vector3::Dot( edge2, qvec ) / det;
		if ( tdis < 0.0f )
			return _false;

		dist = tdis;
		return _true;
	}

	_bool	Inside( const Vector3& v ) const;
	Vector3	Closest( const Vector3& v ) const;
};

};