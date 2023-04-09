#pragma once

namespace Xixels
{

class IRenderSet
{
public:
	virtual _void			SetRenderTarget( ITexture* rendertarget, ITexture* depthstencil ) = 0;
	virtual _void			SetRenderTargets( ITexture* rt1, ITexture* rt2, ITexture* rt3, ITexture* rt4, ITexture* depthstencil ) = 0;
	virtual _dword			GetRenderTargetCount( ) const = 0;

	virtual _void			SetMemoryAllocaterPageSize( _dword pagesize ) = 0;

	virtual ITexture*		GetRenderTarget( ) const = 0;
	virtual ITexture*		GetRenderTarget( _dword index ) const = 0;
	virtual ITexture*		GetDepthStencil( ) const = 0;

	virtual _void			SetClearFlag( _bool color = _true, _bool depth = _true, _bool stencil = _true ) = 0;
	virtual _void			SetClearColor( _dword color = 0 ) = 0;
	virtual _dword			GetClearColor( ) = 0;

	virtual _void			SetViewRect( const Rect& rect ) = 0;
	virtual const Rect&		GetViewRect( ) const = 0;

	virtual _void			Clear( ) = 0;

	virtual _bool			IsEmpty( ) const = 0;
};

};