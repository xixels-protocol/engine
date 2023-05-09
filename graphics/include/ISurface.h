#pragma once

namespace Xixels
{

class ISurface
{
public:
	// Get format of surface.
	virtual _dword	GetFormat( ) const = 0;

	// Get surface width.
	virtual _dword	GetWidth( ) const = 0;
	// Get surface height.
	virtual _dword	GetHeight( ) const = 0;
	// Get surface level.
	virtual _dword	GetLevel( ) const = 0;

	// Lock surface.
	virtual _void*	Lock( _dword& pitch, const Rect& lockrect = Rect::cNullRect, _dword flag = 0 ) = 0;
	// Unlock surface.
	virtual _void	Unlock( ) = 0;

	// Adjust with HSL, hue 0 - 360, saturation 0 - 100, lightness -100 - 100.
	virtual _void	ProcessHSL( _dword hue = -1, _dword saturation = -1, _long lightness = 0, const Rect& rect = Rect::cNullRect ) = 0;
	// Adjust with RGB.
	virtual _void	ProcessRGB( _dword modulate = -1, _dword additive = 0, _dword subtract = 0, const Rect& rect = Rect::cNullRect ) = 0;
	// Add border with blur process.
	virtual _void	ProcessBorder( _dword color, _dword bordersize = 1, _float blurrate = 1.0f, const Rect& rect = Rect::cNullRect ) = 0;
};

};