#include "ConvexPolygon.h"
#include "../base/Pair.h"
#include "../base/QuickSort.h"

using namespace Xixels;

_bool ConvexPolygon::GenConvexPolygon( const Vector2* points, _dword number, Array< _dword >& hill )
{
	hill.Clear( );

	if ( number < 3 )
		return _false;

	Vector2 pt = points[0];
	for ( _dword i = 1; i < number; i ++ )
	{
		const Vector2& q = points[i];
		if ( pt.y < q.y || ( pt.y == q.y && pt.x < q.x ) )
			pt = q;
	}

	Array< Pair< _float, _dword > > cosvs;
	cosvs.Grow( number );
	for ( _dword i = 0; i < number; i ++ )
	{
		Vector2 v1 = points[i] - pt;
		_float s1 = v1.Magnitude( );
		_float cosv1 = Math::Clamp( s1 < Math::cEpsilon ? 1.0f : v1.x / s1, -1.0f, 1.0f );
		cosvs.Add( Pair< _float, _dword >( cosv1, i ) );
	}

	QuickSort< Pair< _float, _dword >, _float >::SortDescending( cosvs, cosvs.Length( ) );

	_dword sn = 1;
	for ( ; sn < number; sn ++ )
	{
		if ( pt.Equal( points[ cosvs[sn].obj2 ] ) == _false )
			break;
	}

	sn -= 1;
	if ( cosvs.Length( ) - sn < 3 )
		return _false;

	_dword t = 0;
	hill.Insert( cosvs[sn + 0].obj2, t );
	hill.Insert( cosvs[sn + 1].obj2, ++t );
	hill.Insert( cosvs[sn + 2].obj2, ++t );

	for ( _long i = sn + 3; i < cosvs.Length( ); i ++ )
	{
		while ( _true )
		{
			if ( t < 1 )
			{
				hill.Insert( cosvs[i].obj2, ++t );
				break;
			}

			const Vector2& v1 = points[ hill[ t - 1 ] ];
			const Vector2& v2 = points[ hill[t] ];
			const Vector2& v0 = points[ cosvs[i].obj2 ];

			_long rot = Math::PointVSLine( v1.x, v1.y, v2.x, v2.y, v0.x, v0.y );
			if ( rot > 0 )
			{
				hill.Reduce( 1 );
				t --;
			}
			else if ( rot < 0 )
			{
				hill.Insert( cosvs[i].obj2, ++t );
				break;
			}
			else
			{
				Vector2 p = v2 - v1;
				Vector2 q = v0 - v1;
				if ( q.MagnitudeSquared( ) >= p.MagnitudeSquared( ) )
				{
					hill.Reduce( 1 );
					t --;
				}
				else
				{
					break;
				}
			}
		}
	}

	return hill.Length( ) >= 3;
}

ConvexPolygon::ConvexPolygon( _float ll, _float tt, _float rr, _float bb )
	: pn( 4 ), ps( _null )
{
	if ( ll > rr ) Math::Swap( ll, rr );
	if ( tt > bb ) Math::Swap( tt, bb );

	ps = new Vector2[pn];

	ps[0].x = ll; ps[0].y = tt;
	ps[1].x = ll; ps[1].y = bb;
	ps[2].x = rr; ps[2].y = bb;
	ps[3].x = rr; ps[3].y = tt;
}

ConvexPolygon::ConvexPolygon( const Vector2* points, _dword number, _bool inorder )
	: pn( 0 ), ps( _null )
{
	if ( number < 3 )
		return;

	if ( inorder )
	{
		ps = new Vector2[number];
		pn = number;

		for ( _dword i = 0; i < number; i ++ )
			ps[i] = points[i];

		return;
	}

	Array< _dword > hill;
	if ( GenConvexPolygon( points, number, hill ) == _false )
		return;

	pn = hill.Length( );
	ps = new Vector2[ hill.Length( ) ];
	for ( _long i = 0; i < hill.Length( ); i ++ )
		ps[i] = points[ hill[i] ];
}

ConvexPolygon::ConvexPolygon( const ConvexPolygon& cp )
	: pn( cp.pn ), ps( _null )
{
	if ( pn != 0 )
	{
		ps = new Vector2[pn];

		for ( _dword i = 0; i < pn; i ++ )
			ps[i] = cp.ps[i];
	}
}

ConvexPolygon& ConvexPolygon::operator = ( const ConvexPolygon& cp )
{
	delete[] ps;

	pn = cp.pn;
	ps = _null;

	if ( pn != 0 )
	{
		ps = new Vector2[pn];

		for ( _dword i = 0; i < pn; i ++ )
			ps[i] = cp.ps[i];
	}

	return *this;
}

ConvexPolygon ConvexPolygon::operator * ( const Matrix3& mat )
{
	ConvexPolygon ret = *this;
	for ( _dword i = 0; i < pn; i ++ )
		ret.ps[i] *= mat;
	
	return ret;
}

_float ConvexPolygon::Area( ) const
{
	_float area = 0;
	_dword j = 0;

	for ( _dword i = 0; i < pn; i ++ )
	{
		j = i + 1;
		j = j == pn ? 0 : j;

		Vector2& p1 = ps[i];
		Vector2& p2 = ps[j];

		area += p1.x * p2.y - p1.y * p2.x;
	}

	return area * 0.5f;
}

Vector2 ConvexPolygon::GetNormal( _dword side ) const
{
	_long clk = Clockwise( );

	const Vector2& p1 = ps[side];
	const Vector2& p2 = ps[ ( side + 1 ) % pn ];

	Vector2 n = p2 - p1;
	n.Normalize( );
	Math::Swap( n.x, n.y );
	if ( clk > 0 )
		n.y = - n.y;
	else
		n.x = - n.x;

	return n;
}

_long ConvexPolygon::Clockwise( ) const
{
	_long clk = 0;

	for ( _dword i = 0; i < pn; i ++ )
	{
		const Vector2& p0 = ps[i];
		const Vector2& p1 = ps[ ( i + 1 ) % pn ];
		const Vector2& p2 = ps[ ( i + 2 ) % pn ];

		_float t = Vector2::Cross( p1 - p0, p2 - p1 );
		clk = t > 0.0f ? 1 : ( t < 0.0f ? -1 : 0 );

		if ( clk != 0 )
			break;
	}

	return clk;
}

_void ConvexPolygon::Expansion( _float r )
{
	if ( r == 0.0f )
		return;

	Array< Vector2 > temp;
	for ( _dword i = 0; i < pn; i ++ )
	{
		Vector2 p = ps[i];
		const Vector2& p1 = ps[ i == 0 ? pn - 1 : i - 1 ];
		const Vector2& p2 = ps[ ( i + 1 ) % pn ];

		Vector2 v1 = ( p - p1 ).Normalize( );
		Vector2 v2 = ( p - p2 ).Normalize( );

		_float cosA = Math::Clamp( Vector2::Dot( v1, v2 ), -1.0f, 1.0f );
		_float sinA = Math::Sqrt( 1 - cosA * cosA );

		Vector2 v;
 		if ( sinA != 0.0f )
 			v = ( v1 + v2 ) * ( r / sinA );

		if ( v.Magnitude( ) > 5.0f * r )
			v = v.Normalize( ) * 5.0f * r;
		else if ( v.Magnitude( ) < r )
			v = v.Normalize( ) * r;

		p += v;

		temp.Add( p );
	}

	for ( _dword i = 0; i < pn; i ++ )
		ps[i] = temp[i];
}

Vector2	ConvexPolygon::Center( ) const
{
	if ( pn == 0 )
		return Vector2::cOrigin;

	Vector2 c = Vector2::cOrigin;
	for ( _dword i = 0; i < pn; i ++ )
		c += ps[i];

	c /= (_float) pn;

	return c;
}

_bool ConvexPolygon::Inside( const Vector2& p, Vector2* c ) const
{
	_long ret = 0, n1 = 0, n2 = 0;

	Vector2 c1, c2; _float dist = Math::cMaxFloat, dist2 = 0.0f;

	for ( _dword i = 0; i < pn; i ++ )
	{
		const Vector2& p1 = ps[i];
		const Vector2& p2 = ps[ ( i + 1 ) % pn ];

		ret = Math::PointVSLine( p1.x, p1.y, p2.x, p2.y, p.x, p.y );
		if ( ret == 0 )
			return _false;

		ret > 0 ? n1 ++ : n2 ++;
		if ( n1 * n2 != 0 )
			return _false;

		dist2 = Math::PointOnLine( p1.x, p1.y, p2.x, p2.y, p.x, p.y, c2.x, c2.y );
		if ( dist > dist2 )
		{
			dist = dist2;
			c1 = c2;
		}
	}

	if ( n1 * n2 != 0 )
		return _false;

	if ( c != _null )
		*c = c1;

	return _true;
}

_bool ConvexPolygon::OnEdge( const Vector2& p ) const
{
	for ( _dword i = 0; i < pn; i ++ )
	{
		const Vector2& p1 = ps[i];
		const Vector2& p2 = ps[ ( i + 1 ) % pn ];

		if ( Math::PointVSLine( p1.x, p1.y, p2.x, p2.y, p.x, p.y ) == 0 )
			return _true;
	}

	return _false;
}

_bool ConvexPolygon::OnSide( const Vector2& l1, const Vector2& l2 ) const
{
	_long ret = 0, n1 = 0, n2 = 0;

	for ( _dword i = 0; i < pn; i ++ )
	{
		const Vector2& p = ps[i];

		ret = Math::PointVSLine( l1.x, l1.y, l2.x, l2.y, p.x, p.y );
		if ( ret == 0 )
			continue;

		ret > 0 ? n1 ++ : n2 ++;
		if ( n1 * n2 != 0 )
			return _false;
	}

	return n1 * n2 == 0;
}

_bool ConvexPolygon::Intersect( const Vector2& p ) const
{
	_long ret = 0, n1 = 0, n2 = 0;
	for ( _dword i = 0; i < pn; i ++ )
	{
		const Vector2& p1 = ps[i];
		const Vector2& p2 = ps[ ( i + 1 ) % pn ];

		ret = Math::PointVSLine( p1.x, p1.y, p2.x, p2.y, p.x, p.y );
		if ( ret == 0 )
			return _true;

		ret > 0 ? n1 ++ : n2 ++;
		if ( n1 != 0 && n2 != 0 )
			return _false;
	}

	return _true;
}

_bool ConvexPolygon::Intersect( const Vector2& l1, const Vector2& l2, Array< Vector2 >& cs ) const
{
	cs.Clear( );

	for ( _dword i = 0; i < pn; i ++ )
	{
		const Vector2& p1 = ps[i];
		const Vector2& p2 = ps[ ( i + 1 ) % pn ];

		Vector2 c;
		if ( Math::LineVSLine( l1.x, l1.y, l2.x, l2.y, p1.x, p1.y, p2.x, p2.y, &c.x, &c.y ) )
		{
			if ( cs.IndexOf( c ) == -1 )
				cs.Add( c );
		}
	}

	return cs.Length( ) != 0;
}

_bool ConvexPolygon::Intersect( const Vector2& l1, const Vector2& l2, Vector2* point, Vector2* normal ) const
{
	_long clk = Clockwise( );

	_float tin = 0.0f;
	_float tout = 1.0f;
	_dword sidein = -1;
	_dword sideout = -1;

	if ( LineClipping( l1, l2, &tin, &tout, &sidein, &sideout ) == _false )
		return _false;

	if ( sidein == -1 && sideout == -1 )
		return _false;

	if ( point == _null && normal == _null )
		return _true;

	if ( point != _null )
	{
		if ( sidein != -1 )
			*point = l1 + ( l2 - l1 ) * tin;

		if ( sideout != -1 )
			*point = l1 + ( l2 - l1 ) * tout;
	}

	if ( normal != _null )
	{
		_dword line = sidein == -1 ? sideout : sidein;
		const Vector2& p0 = ps[line];
		const Vector2& p1 = ps[ ( line + 1 ) % pn ];

		*normal = p1 - p0;
		normal->Normalize( );
		Math::Swap( normal->x, normal->y );
		if ( clk > 0 )
			normal->y = - normal->y;
		else
			normal->x = - normal->x;
	}

	return _true;
}

// Line-Clipping using Cyrus-Beck algorithm.
_bool ConvexPolygon::LineClipping( const Vector2& l1, const Vector2& l2, _float* tin, _float* tout, _dword* sidein, _dword* sideout ) const
{
	_long clk = Clockwise( );

	_float lin = 0.0f;
	_float lout = 1.0f;
	_dword din = -1;
	_dword dout = -1;
	Vector2 d = l2 - l1;

	for ( _dword i = 0; i < pn; i ++ )
	{
		const Vector2& p0 = ps[i];
		const Vector2& p1 = ps[ ( i + 1 ) % pn ];

		Vector2 n = p1 - p0;
		Math::Swap( n.x, n.y );
		if ( clk == 1 )
			n.y = - n.y;
		else
			n.x = - n.x;

		_float u = Vector2::Dot( n, p0 - l1 );
		_float v = Vector2::Dot( n, d );

		if ( v < 0.0f )
		{
			_float t = u / v;

			if ( t > lout )
				return _false;

			if ( din == -1 && t == 0.0f )
				din = i;

			if ( t > lin )
			{
				lin = t;
				din = i;
			}
		}
		else if ( v > 0.0f )
		{
			_float t = u / v;

			if ( t < lin )
				return _false;

			if ( dout == -1 && t == 1.0f )
				dout = i;

			if ( t < lout )
			{
				lout = t;
				dout = i;
			}
		}
		else if ( u == 0.0f )
		{
			Vector2 pl0 = p0 - l1;
			Vector2 pl1 = p1 - l1;
			_float tp0 = Math::Abs( d.x ) > Math::Abs( d.y ) ? pl0.x / d.x : pl0.y / d.y;
			_float tp1 = Math::Abs( d.x ) > Math::Abs( d.y ) ? pl1.x / d.x : pl1.y / d.y;

			lin = Math::Max( 0.0f, Math::Min( tp0, tp1 ) );
			lout = Math::Min( 1.0f, Math::Max( tp0, tp1 ) );
			din = dout = i;
			break;
		}
		else if ( u < 0.0f )
		{
			return _false;
		}
	}

	if ( tin != _null )
		*tin = lin;

	if ( tout != _null )
		*tout = lout;

	if ( sidein != _null )
		*sidein = din;

	if ( sideout != _null )
		*sideout = dout;

	return _true;
}