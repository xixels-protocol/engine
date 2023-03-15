#include "Triangle2D.h"

using namespace Xixels;

Triangle2D& Triangle2D::Scale( _float scale )
{
	Vector2 centroid = Centroid( );
	v1 = centroid + ( v1 - centroid ) * scale;
	v2 = centroid + ( v2 - centroid ) * scale;
	v3 = centroid + ( v3 - centroid ) * scale;
	return *this;
}

_bool Triangle2D::CheckIntersect( const Triangle2D& triangle ) const
{
	Triangle2D t1 = *this;

	// Check edge.
	static const _float err = 0.0f;
	for ( _dword i = 0; i < 3; i ++ )
	{
		Vector2 a = t1[i];
		Vector2 b = t1[ ( i + 1 ) % 3 ];
		for ( _dword j = 0; j < 3; j ++ )
		{
			Vector2 c = triangle[j];
			Vector2 d = triangle[ ( j + 1 ) % 3 ];

			if ( Vector2::Cross( b - a, c - a ) * Vector2::Cross( b - a, d - a ) <= err &&
				 Vector2::Cross( d - c, a - c ) * Vector2::Cross( d - c, b - c ) <= err )
				return _true;
		}
	}

	// Check include.
	_float a1 = Area( );
	_float a2 = triangle.Area( );
	Triangle2D t2 = triangle;
	if ( a1 < a2 )
		Math::Swap( t1, t2 );

	_float totalarea = Math::Max( a1, a2 );
	_float area = 0.0f;
	_bool in = _true;
	for ( _dword i = 0; i < 3; i ++ )
	{
		area = 0.0f;
		area += Triangle2D( t2[i], t1[0], t1[1] ).Area( );
		area += Triangle2D( t2[i], t1[1], t1[2] ).Area( );
		area += Triangle2D( t2[i], t1[2], t1[0] ).Area( );

		if ( area - totalarea > err )
		{
			in = _false;
			break;
		}
	}

	return in;
}