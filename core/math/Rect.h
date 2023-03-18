#pragma once

#include "Math.h"

namespace Xixels
{

template< typename Type, typename PType > class RectT
{
public:
	const static RectT< Type, PType > cNullRect;
	const static RectT< Type, PType > cInitRect;

public:
	Type	l;
	Type	t;
	Type	r;
	Type	b;

public:
	inline RectT( )
		{ }
	inline RectT( Type ll, Type tt, Type rr, Type bb )
		: l( ll ), t( tt ), r( rr ), b( bb ) { }
	inline RectT( const PType& lt, const PType& rb )
		: l( lt.x ), t( lt.y ), r( rb.x ), b( rb.y ) { }

	inline RectT< Type, PType >& operator = ( const RectT< Type, PType >& rect )
		{ l = rect.l; t = rect.t; r = rect.r; b = rect.b; return *this; }

	inline RectT< Type, PType > operator + ( ) const
		{ return RectT< Type, PType >( l, t, r, b ); }
	inline RectT< Type, PType > operator - ( ) const
		{ return RectT< Type, PType >( -r, -b, -l, -t ); }

	inline RectT< Type, PType >& operator += ( const RectT< Type, PType >& rect )
		{ l += rect.l; t += rect.t; r += rect.r; b += rect.b; return *this; }
	inline RectT< Type, PType >& operator -= ( const RectT< Type, PType >& rect )
		{ l -= rect.l; t -= rect.t; r -= rect.r; b -= rect.b; return *this; }

	inline RectT< Type, PType > operator + ( const RectT< Type, PType >& rect ) const
		{ return RectT< Type, PType >( l + rect.l, t + rect.t, r + rect.r, b + rect.b ); }
	inline RectT< Type, PType > operator - ( const RectT< Type, PType >& rect ) const
		{ return RectT< Type, PType >( l - rect.l, t - rect.t, r - rect.r, b - rect.b ); }

	inline RectT< Type, PType >& operator += ( const PType& pt )
		{ l += pt.x; t += pt.y; r += pt.x; b += pt.y; return *this; }
	inline RectT< Type, PType >& operator -= ( const PType& pt )
		{ l -= pt.x; t -= pt.y; r -= pt.x; b -= pt.y; return *this; }

	inline RectT< Type, PType > operator + ( const PType& pt ) const
		{ return RectT< Type, PType >( l + pt.x, t + pt.y, r + pt.x, b + pt.y ); }
	inline RectT< Type, PType > operator - ( const PType& pt ) const
		{ return RectT< Type, PType >( l - pt.x, t - pt.y, r - pt.x, b - pt.y ); }

	inline RectT< Type, PType >& operator *= ( Type s )
		{ l *= s; t *= s; r *= s; b *= s; return *this; }
	inline RectT< Type, PType >& operator /= ( Type s )
		{ l /= s; t /= s; r /= s; b /= s; return *this; }

	inline RectT< Type, PType > operator * ( Type s ) const
		{ return RectT< Type, PType >( l * s, t * s, r * s, b * s ); }
	inline RectT< Type, PType > operator / ( Type s ) const
		{ return RectT< Type, PType >( l / s, t / s, r / s, b / s ); }

	inline RectT< Type, PType >& operator *= ( const PType& pt )
		{ l *= pt.x; t *= pt.y; r *= pt.x; b *= pt.y; return *this; }
	inline RectT< Type, PType >& operator /= ( const PType& pt )
		{ l /= pt.x; t /= pt.y; r /= pt.x; b /= pt.y; return *this; }

	inline RectT< Type, PType > operator * ( const PType& pt ) const
		{ return RectT< Type, PType >( l * pt.x, t * pt.y, r * pt.x, b * pt.y ); }
	inline RectT< Type, PType > operator / ( const PType& pt ) const
		{ return RectT< Type, PType >( l / pt.x, t / pt.y, r / pt.x, b / pt.y ); }

	inline _bool operator == ( const RectT< Type, PType >& rect ) const
		{ return l == rect.l && t == rect.t && r == rect.r && b == rect.b; }
	inline _bool operator != ( const RectT< Type, PType >& rect ) const
		{ return l != rect.l || t != rect.t || r != rect.r || b != rect.b; }

	inline _bool IsEmpty( ) const
		{ return r < l || b < t; }

	inline Type Width( ) const
		{ return r - l; }
	inline Type Height( ) const
		{ return b - t; }

	inline PType Center( ) const
		{ return PType( ( l + r ) / 2, ( t + b ) / 2 ); }
	inline PType Size( ) const
		{ return PType( r - l, b - t ); }

	inline PType LeftTop( ) const
		{ return PType( l, t ); }
	inline PType LeftBottom( ) const
		{ return PType( l, b ); }
	inline PType RightTop( ) const
		{ return PType( r, t ); }
	inline PType RightBottom( ) const
		{ return PType( r, b ); }

	inline RectT< Type, PType >& Merge( const PType& pt )
		{ l = Math::Min( pt.x, l ); t = Math::Min( pt.y, t ); r = Math::Max( pt.x, r ); b = Math::Max( pt.y, b ); return *this; }

	inline RectT< Type, PType >& Inflate( Type w, Type h )
		{ l -= w; r += w; t -= h; b += h; return *this; }
	inline RectT< Type, PType >& Deflate( Type w, Type h )
		{ l += w; r -= w; t += h; b -= h; return *this; }

	inline RectT< Type, PType >& Inflate( const PType& size )
		{ l -= size.x; r += size.x; t -= size.y; b += size.y; return *this; }
	inline RectT< Type, PType >& Deflate( const PType& size )
		{ l += size.x; r -= size.x; t += size.y; b -= size.y; return *this; }

	inline _bool Inside( const PType& pt ) const
		{ return pt.x > l && pt.x < r && pt.y > t && pt.y < b; }
	inline _bool Inside( const RectT< Type, PType >& rect ) const
		{ return rect.l > l && rect.r < r && rect.t > t && rect.b < b; }
	inline _bool Inside( Type ll, Type tt, Type rr, Type bb )
		{ return ll > l && rr < r && tt > t && bb < b; }

	inline _void Expand( const PType& pt )
	{
		l = Math::Min( l, pt.x );
		r = Math::Max( r, pt.x );
		t = Math::Min( t, pt.y );
		b = Math::Max( b, pt.y );
	}

	inline _void Expand( const PType& p1, const PType& p2 )
	{
		l = Math::Min( l, Math::Min( p1.x, p2.x ) );
		t = Math::Min( t, Math::Min( p1.y, p2.y ) );
		r = Math::Max( r, Math::Max( p1.x, p2.x ) );
		b = Math::Max( b, Math::Max( p1.y, p2.y ) );
	}

	inline _void Expand( const PType& p1, const PType& p2, const PType& p3 )
	{
		l = Math::Min( l, Math::Min( p1.x, Math::Min( p2.x, p3.x ) ) );
		t = Math::Min( t, Math::Min( p1.y, Math::Min( p2.y, p3.y ) ) );
		r = Math::Max( r, Math::Max( p1.x, Math::Max( p2.x, p3.x ) ) );
		b = Math::Max( b, Math::Max( p1.y, Math::Max( p2.y, p3.y ) ) );
	}

	inline _void Expand( const PType& p1, const PType& p2, const PType& p3, const PType& p4 )
	{
		l = Math::Min( l, Math::Min( p1.x, Math::Min( p2.x, Math::Min( p3.x, p4.x ) ) ) );
		t = Math::Min( t, Math::Min( p1.y, Math::Min( p2.y, Math::Min( p3.y, p4.y ) ) ) );
		r = Math::Max( r, Math::Max( p1.x, Math::Max( p2.x, Math::Max( p3.x, p4.x ) ) ) );
		b = Math::Max( r, Math::Max( p1.y, Math::Max( p2.y, Math::Max( p3.y, p4.y ) ) ) );
	}

	// Determines whether the specified point, lies on side of the rectangle.
	inline _dword OnEdge( const PType& pt ) const
	{
		_dword ret = 0;

		// Left edge.
		if ( pt.x == l && pt.y >= t && pt.y <= b )
			ret |= 1;
		// Top edge.
		if ( pt.y == t && pt.x >= l && pt.x <= r )
			ret |= 2;
		// Right edge.
		if ( pt.x == r && pt.y >= t && pt.y <= b )
			ret |= 4;
		// Bottom edge.
		if ( pt.y == b && pt.x >= l && pt.x <= r )
			ret |= 8;

		return ret;
	}

	// Determines whether the specified line ( l1->l2 ), lies on side of the rectangle.
	_bool OnEdge( const PType& l1, const PType& l2 ) const
	{
		PType pts[4] = { PType( l, t ), PType( l, b ), PType( r, b ), PType( r, t ) };

		_long ret = 0, n1 = 0, n2 = 0;

		for ( _dword i = 0; i < 4; i ++ )
		{
			const PType& p = pts[i];

			ret = Math::PointVSLine( l1.x, l1.y, l2.x, l2.y, p.x, p.y );
			if ( ret > 0 )
				n1 ++;
			else if ( ret < 0 )
				n2 ++;
		}

		return ( n1 * n2 ) == 0;
	}

	// Determines whether the specified line ( l1->l2 ), intersect with the rectangle.
	_bool Cross( const PType& l1, const PType& l2, PType* cross = _null ) const
	{
		Type x1 = Math::Min( l1.x, l2.x );
		Type y1 = Math::Min( l1.y, l2.y );
		Type x2 = Math::Max( l1.x, l2.x );
		Type y2 = Math::Max( l1.y, l2.y );

		// Not intersect.
		if ( x2 < l || x1 > r || y2 < t || y1 > b )
			return _false;

		PType pts[4] = { PType( l, t ), PType( l, b ), PType( r, b ), PType( r, t ) };

		PType c1, c2; _bool b = _false;

		for ( _dword i = 0; i < 4; i ++ )
		{
			const PType& p1 = pts[ i ];
			const PType& p2 = pts[ ( i + 1 ) % 4 ];

			if ( Math::LineVSLine( l1.x, l1.y, l2.x, l2.y, p1.x, p1.y, p2.x, p2.y, &c2.x, &c2.y ) )
			{
				if ( cross == _null )
					return _true;

				if ( b )
				{
					Type xx = l1.x - c1.x;
					Type yy = l1.y - c1.y;
					_double t1 = xx * xx + yy * yy;

					xx = l1.x - c2.x;
					yy = l1.y - c2.y;
					_double t2 = xx * xx + yy * yy;

					if ( t1 > t2 )
						c1 = c2;
				}
				else
				{
					c1 = c2;
					b = _true;
				}
			}
		}

		if ( cross == _null )
			return b;

		return b ? *cross = c1, _true : _false;
	}

	// Makes a rectangle equal to the intersection of two existing ones.
	static RectT< Type, PType > Intersect( const RectT< Type, PType >& rect1, const RectT< Type, PType >& rect2 )
	{
		Type l = Math::Max( rect1.l, rect2.l );
		if ( l > rect1.r || l > rect2.r )
			return RectT< Type, PType >( 0, 0, 0, 0 );

		Type r = Math::Min( rect1.r, rect2.r );
		if ( r < rect1.l || r < rect2.l )
			return RectT< Type, PType >( 0, 0, 0, 0 );

		Type t = Math::Max( rect1.t, rect2.t );
		if ( t > rect1.b || t > rect2.b )
			return RectT< Type, PType >( 0, 0, 0, 0 );

		Type b = Math::Min( rect1.b, rect2.b );
		if ( b < rect1.t || b < rect2. t )
			return RectT< Type, PType >( 0, 0, 0, 0 );

		return RectT< Type, PType >( l, t, r, b );
	}

	// Makes a rectangle equal to the union of two existing ones.
	static RectT< Type, PType > Union( const RectT< Type, PType >& rect1, const RectT< Type, PType >& rect2 )
	{
		Type l = Math::Min( rect1.l, rect2.l );
		Type r = Math::Max( rect1.r, rect2.r );
		Type t = Math::Min( rect1.t, rect2.t );
		Type b = Math::Max( rect1.b, rect2.b );

		return RectT< Type, PType >( l, t, r, b );
	}

	static _void Correction( PType& lt, PType& rb )
	{
		if ( lt.x > rb.x )
			Math::Swap( lt.x, rb.x );

		if ( lt.y > rb.y )
			Math::Swap( lt.y, rb.y );
	}

	static _void Correction( PType& lt, PType& rb, PType& uvlt, PType& uvrb )
	{
		if ( lt.x > rb.x )
		{
			Math::Swap( lt.x, rb.x );
			Math::Swap( uvlt.x, uvrb.x );
		}

		if ( lt.y > rb.y )
		{
			Math::Swap( lt.y, rb.y );
			Math::Swap( uvlt.y, uvrb.y );
		}
	}
};

template< typename Type, typename PType > const RectT< Type, PType > RectT< Type, PType >::cNullRect( 0, 0, 0, 0 );
template< typename Type, typename PType > const RectT< Type, PType > RectT< Type, PType >::cInitRect( 16777216, 16777216, -16777216, -16777216 );

class Point;
typedef RectT< _long, Point > Rect;

class Vector2;
typedef RectT< _float, Vector2 > Region;

};