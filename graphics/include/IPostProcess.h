#pragma once

namespace Xixels
{

class IPostProcess
{
public:

	enum _RENDER_TYPE
	{
		// Effect.
		_COMMON			= 0,
		_QUADADD		= 1,
		_QUADBLD		= 2,
		_DISTORT		= 3,
		_OUTERGLOW		= 4,
		_VIGNETTE		= 5,
		_DOF			= 6,
		
		// Blur.
		_BLURPASS		= 10,
		_BLURLINE		= 11,
		_INRADIAL		= 12,

		// tonemap.
		_BRIGHT			= 30,
		_COMBINELUT		= 31,
		_TONEMAP		= 32,

		// bloom.
		_BLOOMSETUP_ES	= 40,
		_BLOOMDOWN_ES	= 41,
		_BLOOMUP_ES		= 42,
		_SUNMERGE		= 43,

		// dof.
		_DOFSETUPNEAR	= 50,
		_DOFSETUPFAR	= 51,
		_DOFRECOMBINE	= 52,

		// aa.
		_FXAA			= 60,
		_TAA			= 61,
	};

public:

	virtual _bool		Reset( _dword w, _dword h, _dword rt = ITextureFactory::_FORMAT_A8R8G8B8, _dword ds = 0 ) = 0;
	virtual _bool		Reset( _dword w, _dword h, _dword rt0, _dword rt1, _dword rt2, _dword rt3, _dword ds = 0 ) = 0;
	virtual _bool		Begin( _dword color = Color::cBlack ) = 0;
	virtual ITexture*	End( _bool flush = _true, _bool synch = _false ) = 0;

	virtual _void		Process( _dword type, _dword mode, const Vector4& param, ITexture* src0 = _null, ITexture* src1 = _null,  ITexture* src2 = _null, ITexture* src3 = _null, ITexture* src4 = _null,
								ITexture* src5 = _null ) = 0;
	virtual _void		Process( _dword type, const Vector4& param, ITexture* src0 = _null, ITexture* src1 = _null,  ITexture* src2 = _null, ITexture* src3 = _null, ITexture* src4 = _null,
								ITexture* src5 = _null ) = 0;
	virtual _void		Process( _dword type, const Vector4* params = _null, _dword paramcount = 0, ITexture* src0 = _null, ITexture* src1 = _null, ITexture* src2 = _null, ITexture* src3 = _null,
								ITexture* src4 = _null, ITexture* src5 = _null ) = 0;

	virtual _void		Release( ) = 0;
};

};
