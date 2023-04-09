#pragma once

namespace Xixels
{

class IGraphicsManager
{
public:
	virtual _void	Release( ) = 0;
	virtual _void	Update( ) = 0;
	virtual _bool	CreateRenderDevice( _handle window, _dword devicetype, _bool enablecapture = _false, _handle module = _null, _dword rhitype = 0 ) = 0;

};

};