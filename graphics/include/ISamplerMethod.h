#pragma once

namespace Xixels
{

class ISamplerMethod
{
public:
	enum _TEXTUREADDR
	{
		_TEXTUREADDR_WRAP			= 1,
		_TEXTUREADDR_MIRROR			= 2,
		_TEXTUREADDR_CLAMP			= 3,
		_TEXTUREADDR_BORDER			= 4,
		_TEXTUREADDR_MIRROR_ONCE	= 5,
	};

	enum _TEXTUREFILTER
	{
		_TEXTUREFILTER_NONE		= 0,
		_TEXTUREFILTER_POINT	= 1,
		_TEXTUREFILTER_LINEAR	= 2,
	};

public:
	virtual _bool	IsMipEnabled( ) const = 0;

	virtual _void	SetSamplerAddress( _dword stage, _dword addru, _dword addrv, _dword addrw ) = 0;
	virtual _void	SetSamplerFilter( _dword stage, _dword mag, _dword min, _dword mip ) = 0;
};

};