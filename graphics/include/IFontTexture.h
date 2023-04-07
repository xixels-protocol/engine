#pragma once

namespace Xixels
{

class IFontTexture
{
public:
	enum _FONT_ALIGN
	{
		_HALIGN_LEFT	= 0x00,
		_HALIGN_CENTER	= 0x01,
		_HALIGN_RIGHT	= 0x02,

		_VALIGN_TOP		= 0x00,
		_VALIGN_CENTER	= 0x10,
		_VALIGN_BOTTOM	= 0x20,
	};

public:
	virtual StringPtr	GetFontName( ) const = 0;
	virtual _dword		GetFontSize( ) const = 0;
	virtual _dword		GetFontGlow( ) const = 0;
	virtual _float		GetFontGlowPower( ) const = 0;
	virtual _dword		GetFontEdge( ) const = 0;
	virtual _float		GetFontEdgePower( ) const = 0;
	virtual _dword		GetFontHeight( ) const = 0;

	virtual _bool		IsBold( ) const = 0;
	virtual _bool		IsItalic( ) const = 0;
	virtual _bool		IsUnderline( ) const = 0;
	virtual _bool		IsStrikeOut( ) const = 0;
	virtual _bool		IsSharpen( ) const = 0;
	virtual _bool		IsBlur( ) const = 0;

	virtual _void		SetTextColor( _dword color ) = 0;
	virtual _dword		GetTextColor( ) const = 0;
	virtual _void		SetGlowColor( _dword color ) = 0;
	virtual _dword		GetGlowColor( ) const = 0;
	virtual _void		SetEdgeColor( _dword color ) = 0;
	virtual _dword		GetEdgeColor( ) const = 0;

	virtual _void		SetOffsetHorizontal( _long space ) = 0;
	virtual _long		GetOffsetHorizontal( ) const = 0;

	virtual _void		SetOffsetVertical( _long space ) = 0;
	virtual _long		GetOffsetVertical( ) const = 0;

	virtual _void		SetFontSpaceHorizontal( _long space ) = 0;
	virtual _long		GetFontSpaceHorizontal( ) const = 0;

	virtual _void		SetFontSpaceVertical( _long space ) = 0;
	virtual _long		GetFontSpaceVertical( ) const = 0;

	virtual _void		SetImageCode( _char code, _dword width, _dword height, const Vector2& texcoord1, const Vector2& texcoord2, ITexture* image ) = 0;
	virtual _void		ResetImageCode( ) = 0;

	virtual ITexture*	GetFontTexture( _char code, Vector2& texcoord1, Vector2& texcoord2 ) = 0;
};

};