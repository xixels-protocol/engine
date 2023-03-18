#pragma once

#include "Vector2.h"

namespace Xixels
{

template< typename Type >
class HermiteSpline
{
public:
	Type	a0;
	Type	a1;
	Type	a2;
	Type	a3;

public:
	inline HermiteSpline( )
		{ }

	inline HermiteSpline( const Type& p1, const Type& p2, const Type& p3, const Type& p4 )
		{ Set( p1, p2, p3, p4 ); }

	inline _void Set( const Type& p1, const Type& p2, const Type& p3, const Type& p4 )
	{
		a0 = p2;
		a1 = ( p3 - p1 ) * 0.5f;
		a2 = ( p3 * 4.0f - p2 * 5.0f + p1 * 2.0f - p4 ) * 0.5f;
		a3 = ( p2 * 3.0f - p3 * 3.0f - p1 + p4 ) * 0.5f;
	}

	inline Type GetValue( _float t ) const
		{ return a0 + a1 * t + a2 * ( t * t ) + a3 * ( t * t * t ); }
};

template< typename Type >
class BezierSpline
{
public:
	Type	a0;
	Type	a1;
	Type	a2;
	Type	a3;

public:
	inline BezierSpline( )
		{ }

	inline BezierSpline( const Type& p1, const Type& p2, const Type& p3, const Type& p4 )
		{ Set( p1, p2, p3, p4 ); }

	inline _void Set( const Type& p1, const Type& p2, const Type& p3, const Type& p4 )
	{
		a0 = p1;
		a1 = ( p2 - p1 ) * 3.0f;
		a2 = ( p3 - p2 ) * 3.0f - a1;
		a3 = p4 - p1 - a1 - a2;
	}

	inline Type GetValue( _float t ) const
		{ return a0 + a1 * t + a2 * ( t * t ) + a3 * ( t * t * t ); }
};

template< typename Type, typename Key = _float >
class Curve
{
private:
	_dword	mType;

	_dword	mLastIndex;
	Type	a0;
	Type	a1;
	Type	a2;
	Type	a3;

public:
	enum _LINE_TYPE
	{
		_STRAIGHT_LINE	= 0,
		_HERMITE_LINE	= 1,
		_BEZIER_LINE	= 2,
	};

	Array< Type, Key >		mPoints;
	Array< Type >			mHelperPoints;

public:
	inline Curve( )
		: mType( 0 ), mLastIndex( -1 ) { }
	inline ~Curve( )
		{ }

	inline _void SetType( _dword type )
		{ mType = type; mLastIndex = -1; }
	inline _dword GetType( ) const
		{ return mType; }

	inline _bool IsValid( ) const
		{ return mPoints.Length( ) > 1 && ( mType != _BEZIER_LINE || mHelperPoints.Length( ) > 1 ); }

	inline _void ResetIndex( )
		{ mLastIndex = -1; }

	inline Type GetValue( _dword index, _float t )
	{
		switch ( mType )
		{
			case _STRAIGHT_LINE:
			{
				a0 = mPoints[ index ];
				a1 = mPoints[ index + 1 ];

				return a0 + ( a1 - a0 ) * t;
			}

			case _HERMITE_LINE:
			{
				if ( index != mLastIndex )
				{
					Vector2 p1, p2, p3, p4;
					p1 = index > 0 ? mPoints[ index - 1 ] : mPoints[0];
					p2 = mPoints[ index ];
					p3 = mPoints[ index + 1 ];
					p4 = index < (_dword) mPoints.Length( ) - 2 ? mPoints[ index + 2 ] : mPoints[ index + 1 ];

					a0 = p2;
					a1 = ( p3 - p1 ) * 0.5f;
					a2 = ( p3 * 4.0f - p2 * 5.0f + p1 * 2.0f - p4 ) * 0.5f;
					a3 = ( p2 * 3.0f - p3 * 3.0f - p1 + p4 ) * 0.5f;

					mLastIndex = index;
				}

				return a0 + a1 * t + a2 * ( t * t ) + a3 * ( t * t * t );
			}

			case _BEZIER_LINE:
			{
				if ( index != mLastIndex )
				{
					Vector2 p1, p2, p3, p4;
					p1 = mPoints[ index ];
					p2 = mHelperPoints[ 2 * index ];
					p3 = mHelperPoints[ 2 * index + 1 ];
					p4 = mPoints[ index + 1 ];

					a0 = p1;
					a1 = ( p2 - p1 ) * 3.0f;
					a2 = ( p3 - p2 ) * 3.0f - a1;
					a3 = p4 - p1 - a1 - a2;

					mLastIndex = index;
				}

				return a0 + a1 * t + a2 * ( t * t ) + a3 * ( t * t * t );
			}
		}

		return Type::cOrigin;
	}

	inline _float GetValue( _float s )
	{
		if ( IsValid( ) )
		{
			_float x = Math::Lerp( mPoints[0].x, mPoints[mPoints.Length( ) - 1].x, s );

			_dword i = 0, j = 0;
			BinarySearch< Vector2, _float >::SearchAscending( ( const Vector2* ) mPoints, x, mPoints.Length( ), i, j );

			_float time = ( x - mPoints[i].x ) / ( mPoints[i + 1].x - mPoints[i].x );
			Vector2 value = GetValue( i, time );
			return value.y;
		}

		return 0;
	}

	inline _float Integral( Vector2& point1, Vector2& point2 )
	{
		switch ( mType )
		{
			case _STRAIGHT_LINE:
			{
				return ( point1.y + point2.y ) * ( point2.x - point1.x ) * 0.5f;
			}

			case _HERMITE_LINE:
			{
				_dword m = 0, n = 0;
				BinarySearch< Vector2, _float >::SearchAscending( (const Vector2*) mPoints, point1.x, mPoints.Length( ), m, n );
				if ( m == n )
					n = m + 1;

				_float factor = 1.0f / ( mPoints[n].x - mPoints[m].x );
				_float x1 = point1.x - mPoints[m].x;
				_float x2 = point2.x - mPoints[m].x;

				if ( m != mLastIndex )
				{
					Vector2 p1, p2, p3, p4;
					p1 = m > 0 ? mPoints[ m - 1 ] : mPoints[0];
					p2 = mPoints[m];
					p3 = mPoints[ m + 1 ];
					p4 = (_long) m < mPoints.Length( ) - 2 ? mPoints[ m + 2 ] : mPoints[ m + 1 ];

					a0 = p2;
					a1 = ( p3 - p1 ) * 0.5f;
					a2 = ( p3 * 4.0f - p2 * 5.0f + p1 * 2.0f - p4 ) * 0.5f;
					a3 = ( p2 * 3.0f - p3 * 3.0f - p1 + p4 ) * 0.5f;

					mLastIndex = m;
				}

				return a0.y * ( x2 - x1 ) + a1.y * ( Math::Pow( x2, 2.0f ) - Math::Pow( x1, 2.0f ) ) * 0.5f * factor
						+ a2.y * ( Math::Pow( x2, 3.0f ) - Math::Pow( x1, 3.0f ) ) / 3.0f * Math::Pow( factor, 2.0f )
						+ a3.y * ( Math::Pow( x2, 4.0f ) - Math::Pow( x1, 4.0f ) ) * 0.25f * Math::Pow( factor, 3.0f );

			}

			case _BEZIER_LINE:
			{
				_dword m = 0, n = 0;
				BinarySearch< Vector2, _float >::SearchAscending( (const Vector2*) mPoints, point1.x, mPoints.Length( ), m, n );
				if ( m == n )
					n = m + 1;

				_float factor = 1.0f / ( mPoints[n].x - mPoints[m].x );
				_float x1 = point1.x - mPoints[m].x;
				_float x2 = point2.x - mPoints[m].x;

				if ( m != mLastIndex )
				{
					Vector2 p1, p2, p3, p4;
					p1 = mPoints[m];
					p2 = mHelperPoints[ 2 * m - 1 ];
					p3 = mHelperPoints[ 2 * m ];
					p4 = mPoints[ m + 1 ];

					a0 = p1;
					a1 = ( p2 - p1 ) * 3.0f;
					a2 = ( p3 - p2 ) * 3.0f - a1;
					a3 = p4 - p1 - a1 - a2;

					mLastIndex = m;
				}

				return Math::Abs( a0.y * ( x2 - x1 ) + a1.y * ( Math::Pow( x2, 2.0f ) - Math::Pow( x1, 2.0f ) ) * 0.5f * factor
					+ a2.y * ( Math::Pow( x2, 3.0f ) - Math::Pow( x1, 3.0f ) ) / 3.0f * Math::Pow( factor, 2.0f )
					+ a3.y * ( Math::Pow( x2, 4.0f ) - Math::Pow( x1, 4.0f ) ) * 0.25f * Math::Pow( factor, 3.0f ) );
			}
		}

		return 0.0f;
	}

	inline _float GetArea( _float t1, _float t2 )
	{
		_float area = 0.0f;

		if ( mPoints.Length( ) > 0 )
		{
			if ( mPoints.Length( ) == 1 )
				return mPoints[0].y * ( t2 - t1 );

			Array< Vector2 > keypoints;
			_dword a = 0, b = 0, c = 0, d = 0;
			BinarySearch< Vector2, _float >::SearchAscending( (const Vector2*) mPoints, t1, mPoints.Length( ), a, b );
			BinarySearch< Vector2, _float >::SearchAscending( (const Vector2*) mPoints, t2, mPoints.Length( ), c, d );

			const Vector2& f1 = mPoints[a];
			const Vector2& f2 = mPoints[b];
			const Vector2& f3 = mPoints[c];
			const Vector2& f4 = mPoints[d];

			_float factor1 = f1.x == f2.x ? 0.0f : ( t1 - f1.x ) / ( f2.x - f1.x );
			_float factor2 = f3.x == f4.x ? 0.0f : ( t2 - f3.x ) / ( f4.x - f3.x );
			factor1 = Math::Clamp( factor1, 0.0f, 1.0f );
			factor2 = Math::Clamp( factor2, 0.0f, 1.0f );

			keypoints.Add( Vector2 ( t1, GetValue( a, factor1 ).y ) );

			if ( d > b )
			{
				for ( _dword i = 0; i < d - b; i ++ )
					keypoints.Add( mPoints[ b + i ] );
			}

			keypoints.Add( Vector2 ( t2, GetValue( c, factor2 ).y ) );

			for ( _long j = 0; j < keypoints.Length( ) - 1; j ++ )
				area += Integral( keypoints[j], keypoints[ j + 1 ] );
		}

		return area;
	}

};
};