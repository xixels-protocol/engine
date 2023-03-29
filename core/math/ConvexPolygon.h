#pragma once

#include "Vector2.h"
#include "..\base\Array.h"

namespace Xixels
{

class ConvexPolygon
{
public:
	_dword		pn;
	Vector2*	ps;

public:
	static _bool GenConvexPolygon( const Vector2* points, _dword number, Array< _dword >& hill );

public:
	inline ConvexPolygon( )
		: pn( 0 ), ps( _null ) { }
	inline ~ConvexPolygon( )
		{ delete[] ps; }

	inline _dword getCount( ) const
		{ return pn; }

	inline const Vector2& getPoint( _dword index ) const
		{
			return ps[index];
		}

	ConvexPolygon( _float ll, _float tt, _float rr, _float bb );
	ConvexPolygon( const Vector2* points, _dword number, _bool inorder = _false );
	ConvexPolygon( const ConvexPolygon& cp );
	ConvexPolygon& operator = ( const ConvexPolygon& cp );
	ConvexPolygon operator * ( const Matrix3& mat );

	// The convex polygon is clockwise when its area greater than zero. Otherwise it is counter-clockwise.
	_float	Area( ) const;
	Vector2	GetNormal( _dword side ) const;
	// CW or CCW
	_long	Clockwise( ) const;
	_void	Expansion( _float r );
	Vector2	Center( ) const;

	_bool	Inside( const Vector2& p, Vector2* cross = _null ) const;
	_bool	OnEdge( const Vector2& p ) const;
	_bool	OnSide( const Vector2& l1, const Vector2& l2 ) const;

	_bool	Intersect( const Vector2& p ) const;
	_bool	Intersect( const Vector2& l1, const Vector2& l2, Array< Vector2 >& cs ) const;
	_bool	Intersect( const Vector2& l1, const Vector2& l2, Vector2* point = _null , Vector2* normal = _null ) const;

	// The clipped line starts from ( l1 + (*tin) * (l2-l1) ), and ends with ( l1 + (*tout) * (l2-l1) ).
	// The line crosses the convex polygon from the side indexed with sidein to the side indexed sideout
	_bool	LineClipping( const Vector2& l1, const Vector2& l2, _float* tin = _null, _float* tout = _null, _dword* sidein = _null, _dword* sideout = _null  ) const;
};

};