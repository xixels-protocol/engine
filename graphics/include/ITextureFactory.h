#pragma once

namespace Xixels
{

class ITextureFactory
{
public:
	enum _SURFACE_FORMAT
	{
		_FORMAT_UNKNOWN			=  0,

		_FORMAT_R8G8B8			=  1,
		_FORMAT_A8R8G8B8		=  2,
		_FORMAT_X8R8G8B8		=  3,
		_FORMAT_A4R4G4B4		=  4,
		_FORMAT_X4R4G4B4		=  5,
		_FORMAT_R5G6B5			=  6,
		_FORMAT_A1R5G5B5		=  7,
		_FORMAT_X1R5G5B5		=  8,
		_FORMAT_A16B16G16R16	=  9,

		_FORMAT_DXT1			= 10,
		_FORMAT_DXT2			= 11,
		_FORMAT_DXT3			= 12,
		_FORMAT_DXT4			= 13,
		_FORMAT_DXT5			= 14,

		_FORMAT_L8				= 16,

		_FORMAT_D24S8			= 19,
		_FORMAT_D16				= 20,
		_FORMAT_D24				= 21,

		_FORMAT_R16F			= 22,
		_FORMAT_A16B16G16R16F	= 23,
		_FORMAT_R32F			= 24,
		_FORMAT_A32B32G32R32F	= 25,

		_FORMAT_A8B8G8R8		= 26,
		_FORMAT_E8R8G8B8		= 27,

		_FORMAT_MSAA_TEXTURE	= 41,
		_FORMAT_MSAA_DEPTH		= 42,
		_FORMAT_MSAA_D24S8		= 43,

		_FORMAT_PVRT_BEGIN		= 51,
		_FORMAT_PVRT_RGB_2BPP	= 51,
		_FORMAT_PVRT_RGBA_2BPP	= 52,
		_FORMAT_PVRT_RGB_4BPP	= 53,
		_FORMAT_PVRT_RGBA_4BPP	= 54,
		_FORMAT_PVRT_END		= 54,

		_FORMAT_ETC_BEGIN		= 60,
		_FORMAT_ETC1			= 60,
		_FORMAT_ETC2_RGB		= 61,
		_FORMAT_ETC2_RGBA		= 62,
		_FORMAT_ETC2_RGB_PT		= 63,
		_FORMAT_ETC_END			= 63,

		_FORMAT_ASTC_BEGIN		= 70,
		_FORMAT_ASTC_4X4_RGB	= 70,
		_FORMAT_ASTC_4X4_RGBA	= 71,
		_FORMAT_ASTC_6X6_RGB	= 72,
		_FORMAT_ASTC_6X6_RGBA	= 73,
		_FORMAT_ASTC_8X8_RGB	= 74,
		_FORMAT_ASTC_8X8_RGBA	= 75,
		_FORMAT_ASTC_12X12_RGB	= 76,
		_FORMAT_ASTC_12X12_RGBA	= 77,
		_FORMAT_ASTC_END		= 77,

		_FORMAT_R11G11B10F		= 78,

		_FORMAT_R8G8			= 79,

		_FORMAT_SRGB_MASK		= 0x10000000,
	};

	enum _LOCK_FLAG
	{
		_LOCK_WRITEONLY	= 1,
		_LOCK_READONLY	= 2,
	};

	enum _USAGE
	{
		_USAGE_UNKNOWN			= 0x00,
		_USAGE_RENDERTARGET		= 0x01,
		_USAGE_DEPTHSTENCIL		= 0x02,
		_USAGE_SHADERRESOURCE	= 0x04,
	};

public:
	virtual _void			Update( _dword elapse ) = 0;

	virtual _void			SetLoadTextureMipmap( _dword mipmap ) = 0;
	virtual _dword			GetLoadTextureMipmap( ) const = 0;

	virtual ITexture*		GetDefaultTexture( ) = 0;

	virtual ITexture*		CreateTexture( _dword width, _dword height, _dword format, _dword mip = 1 ) = 0;
	virtual ITexture*		CreateTexture( StringPtr resname ) = 0;
	virtual ITexture*		CreateTexture( StringPtr resname, BinFile& datafile, TextureSetting* texsetting = _null ) = 0;
	virtual ITexture*		CreateTexture( const _void* buffer, _dword length, TextureSetting& setting, _dword width = 0, _dword height = 0, const _void* alphabuffer = _null, _dword alphtlength = 0 ) = 0;
	virtual ITexture*		CreateCubeTexture( _dword width, _dword format, _dword mip = 1 ) = 0;
	virtual ITexture*		CreateCubeTexture( StringPtr resname, TextureSetting* texsetting = _null ) = 0;
	virtual ITexture*		CreateCubeTexture( ITexture* texx1, ITexture* texx2, ITexture* texy1, ITexture* texy2, ITexture* texz1, ITexture* texz2, TextureSetting& setting ) = 0;
	virtual ITexture*		CreateCubeTexture( ITexture* texx1, ITexture* texx2, ITexture* texy1, ITexture* texy2, ITexture* texz1, ITexture* texz2,
												BinFile& data1, BinFile& data2, BinFile& data3, BinFile& data4, BinFile& data5, BinFile& data6, TextureSetting& setting ) = 0;
	virtual ITexture*		CreateVolumeTexture( _dword width, _dword height, _dword depth, _dword format, _dword mip = 1, const _void* buffer = _null ) = 0;

	virtual ITexture*		CreateRenderTexture( _dword width, _dword height, _dword format, _dword usage = 0 ) = 0;
	virtual ITexture*		CreateRenderTargetTexture( _dword width, _dword height, _dword format = 0 ) = 0;
	virtual ITexture*		CreateDepthStencilTexture( _dword width, _dword height, _dword format = ITextureFactory::_FORMAT_D24S8 ) = 0;
	virtual ITexture*		CloneTexture( ITexture* texture, _bool ref = _true ) = 0;
	virtual _void			CopyTexture( ITexture* texture1, ITexture* texture2 ) = 0;
	virtual _void			CopyDepth( ITexture* desdepth, ITexture* srcdepth ) = 0;
	virtual _void			SaveTexture( ITexture* texture, StringPtr filename, _dword imgformat = 0 ) = 0;
	virtual _void			ReleaseTexture( ITexture*& texture ) = 0;

	virtual IFontTexture*	CreateFontTexture( StringPtr fontname, _dword size, _dword glow = 0, _float glowpower = 1.0f, _dword edge = 0, _float edgepower = 1.0f, _bool bold = _false, _bool italic = _false, _bool underline = _false, _bool strikeout = _false, _bool sharpen = _false, _bool blur = _false, _dword fontroomvertical = 0 ) = 0;
	virtual IFontTexture*	CreateFontTexture( StringPtr fontname, StringPtr filename, _dword size, _dword glow = 0, _float glowpower = 1.0f, _dword edge = 0, _float edgepower = 1.0f, _bool bold = _false, _bool italic = _false, _bool underline = _false, _bool strikeout = _false, _bool sharpen = _false, _bool blur = _false, _dword fontroomvertical = 0 ) = 0;
	virtual IFontTexture*	CloneFontTexture( IFontTexture* fonttexture, _bool ref = _true ) = 0;
	virtual _void			ReleaseFontTexture( IFontTexture*& fonttexture ) = 0;
	
	virtual ITexture*		CreateRawTexture( _void* tex ) = 0;
	virtual _void*			GetRawTexture( ITexture* texture ) = 0;

	virtual _bool			LoadTextureSetting( StringPtr resname, TextureSetting& setting ) const = 0;
};

};
