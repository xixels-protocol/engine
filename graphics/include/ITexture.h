#pragma once

namespace Xixels
{

class ITexture : public IResource
{
public:
	virtual _void*		GetSafeResObject( ) const = 0;
	// Set alphalayer.
	virtual _void		SetAlphaLayer( ITexture* tex ) = 0;
	// Get alphalayer.
	virtual ITexture*	GetAlphaLayer( ) const = 0;
	// Check if the texture is dummy ( red / white grids ).
	virtual _bool		IsDummy( ) const = 0;
	// Get format of texture surface.
	virtual _dword		GetFormat( ) const = 0;
	// Get original width.
	virtual _dword		GetOriginWidth( ) const = 0;
	// Get original height.
	virtual _dword		GetOriginHeight( ) const = 0;
	// Get original depth.
	virtual _dword		GetOriginDepth( ) const = 0;
	// Get texture usage.
	virtual _dword		GetUsage( ) const = 0;
	// Lock texture by level.
	virtual _void*		Lock( _dword level, _dword& pitch, const Rect& lockrect = Rect::cNullRect, _dword flag = 0, _dword face = 0 ) = 0;
	// Unlock texture.
	virtual _void		Unlock( _dword level, _bool force = _false, _dword face = 0 ) = 0;

	virtual _void		UsingTexture( _dword priority ) = 0;
	// Adjust with HSL, hue 0 - 360, saturation 0 - 100, lightness -100 - 100.
	virtual _void		ProcessHSL( _dword hue = -1, _dword saturation = -1, _long lightness = 0, const Rect& rect = Rect::cNullRect ) = 0;
	// Adjust with RGB.
	virtual _void		ProcessRGB( _dword modulate = -1, _dword additive = 0, _dword subtract = 0, const Rect& rect = Rect::cNullRect ) = 0;
	// Add border with blur process.
	virtual _void		ProcessBorder( _dword color, _dword bordersize = 1, _float blurrate = 1.0f, const Rect& rect = Rect::cNullRect ) = 0;
};

};
