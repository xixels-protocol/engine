#pragma once

namespace Xixels
{

class ImageBlurWrapper
{
private:
	_byte*	mBuffer;
	_dword	mPitch;
	_dword	mWidth;
	_dword	mHeight;
	_bool	mHorizontal;

public:
	ImageBlurWrapper( _byte* img, _dword pitch, _dword w, _dword h, _bool horizotal = _false ) :
		mBuffer( img ), mPitch( pitch ), mWidth( w ), mHeight( h ), mHorizontal( horizotal ) { }

	~ImageBlurWrapper( ) { }

	inline _dword GetWidth( ) const
		{ return mHorizontal ? mWidth : mHeight; }
	inline _dword GetHeight( ) const
		{ return mHorizontal ? mHeight : mWidth; }

	_byte GetPixel( _dword x, _dword y ) const;
	_void CopyFrom( _dword x, _dword y, const _byte* buf, _dword length );
};

class SurfaceProcessor
{
public:
	static _void	ProcessHSL( _byte* buffer, _dword pitch, _dword hue, _dword saturation, _long lightness, const Rect& rect );
	static _void	ProcessRGB( _byte* buffer, _dword pitch, _dword modulate, _dword additive, _dword subtract, const Rect& rect );
	static _void	ProcessBorder( _byte* buffer, _dword pitch, _dword color, _dword bordersize, _float blurrate, const Rect& rect );
	static _void	ProcessBorder( _byte* buffer, _dword pitch, const Rect& rect );
};

};