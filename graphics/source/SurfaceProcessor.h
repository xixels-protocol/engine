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

};