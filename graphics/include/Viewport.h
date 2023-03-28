#pragma once

namespace Xixels
{

class Viewport
{
public:
	_long	x;
	_long	y;
	_long	w;
	_long	h;
	_float	minz;
	_float	maxz;

public:
	inline Viewport( )
		: x( 0 ), y( 0 ), w( 0 ), h( 0 ), minz( 0.0f ), maxz( 1.0f ) { }
	inline Viewport( _long xx, _long yy, _long ww, _long hh, _float minzz, _float maxzz )
		: x( xx ), y( yy ), w( ww ), h( hh ), minz( minzz ), maxz( maxzz ) { }

	inline _bool operator == ( const Viewport& vp ) const
		{ return x == vp.x && y == vp.y && w == vp.w && h == vp.h && minz == vp.minz && maxz == vp.maxz; }
	inline _bool operator != ( const Viewport& vp ) const
		{ return x != vp.x || y != vp.y || w != vp.w || h != vp.h || minz != vp.minz || maxz != vp.maxz; }

	inline _float AspectRatio( ) const
		{ return (_float) w / (_float) h; }
};

};