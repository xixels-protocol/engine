#pragma once

namespace Xixels
{

class Light
{
public:
	enum _LIGHT_TYPE
	{
		_TYPE_AMBIENT		= 0,
		_TYPE_DIRIECTIONAL	= 1,
		_TYPE_POINT			= 2,
		_TYPE_SPOT			= 3,
	};

public:
	_dword		type			= _TYPE_AMBIENT;

	Color		color			= Color::cBlack;
	Vector3		pos				= Vector3::cOrigin;
	Vector3		dir				= Vector3::cOrigin;
	_float		range			= 0.0f;
	_float		power			= 1.0f;

	_float		outerSemiCone	= 0.0f;
	_float		innerSemiCone	= 0.0f;

	_bool		castShadow		= _false;

public:
	inline Light( ) { }
	inline Light( const Color& c )
		: color( c ) { }
	inline Light( const Color& c, const Vector3& d )
		: type( _TYPE_SKY ), color( c ), dir( d ) { dir.Normalize( ); }
	inline Light( const Color& c, const Vector3& p, _float r )
		: type( _TYPE_POINT ), color( c ), pos( p ), range( r ) { }
	inline Light( const Color& c, const Vector3& p, const Vector3& d, _float r, _float osc, _float isc = 0.0f )
		: type( _TYPE_SPOT ), color( c ), pos( p ), dir( d ), range( r ), outerSemiCone( osc ), innerSemiCone( isc ) { }
	inline Light operator * ( const Matrix4& mat ) const
		{ Light ret = *this; ret.pos *= mat; ret.dir *= mat; return ret; }
};

};