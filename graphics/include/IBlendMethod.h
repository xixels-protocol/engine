#pragma once

namespace Xixels
{

class IBlendMethod
{
public:
	virtual _dword	GetRenderOrder( ) const = 0;
	virtual _void	SetRenderOrder( _dword value ) = 0;

	virtual _bool	IsColorBlendEnabled( ) const = 0;
	virtual _void	EnableColorBlend( _dword func, _dword src, _dword des ) = 0;
	virtual _void	DisableColorBlend( ) = 0;
	virtual _void	GetColorBlend( _dword& func, _dword& src, _dword& des ) const = 0;

	virtual _bool	IsAlphaBlendEnabled( ) const = 0;
	virtual _void	EnableAlphaBlend( _dword func, _dword src, _dword des ) = 0;
	virtual _void	DisableAlphaBlend( ) = 0;
	virtual _void	GetAlphaBlend( _dword& func, _dword& src, _dword& des ) const = 0;

	virtual _bool	IsColorWriteEnabled( ) const = 0;
	virtual _void	EnableColorWrite( ) = 0;
	virtual _void	DisableColorWrite( ) = 0;

	virtual _bool	IsAlphaWriteEnabled( ) const = 0;
	virtual _void	EnableAlphaWrite( ) = 0;
	virtual _void	DisableAlphaWrite( ) = 0;
};

};