#pragma once

namespace Xixels
{

class Fog
{
public:
	struct LinearFog
	{
		_float	mNear;
		_float	mFar;
		_float	mUp;
		_float	mDown;
		_dword	mColor;
		_dword	mHeightColor;

		inline LinearFog( )
		{
			mNear = 0.0f;
			mFar = 0.0f;
			mUp = 0.0f;
			mDown = 0.0f;
			mColor = 0xFF000000;
			mHeightColor = 0xFF000000;
		}

		inline _bool operator == ( const LinearFog& rhs ) const
		{
			return mNear == rhs.mNear &&
				mFar == rhs.mFar &&
				mUp == rhs.mUp &&
				mDown == rhs.mDown &&
				mColor == rhs.mColor &&
				mHeightColor == rhs.mHeightColor;
		}
	};

public:
	const static Fog cNull;

public:
	LinearFog	mFog;

public:
	inline Fog( ) { }

	inline _bool operator == ( const Fog& f ) const
		{ return mFog == f.mFog; }

	_bool IsEnabled( ) const
		{ return !(mFog == Fog::cNull.mFog); }

public:
	static Fog Lerp( const Fog& f1, const Fog& f2, _float factor );
};

};