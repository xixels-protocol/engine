namespace Xixels
{

class IRenderStatistics
{
public:
	virtual _dword	GetPolygonNumber( ) const = 0;
	virtual _dword	GetVertexNumber( ) const = 0;
	virtual _dword	GetDrawPrimitiveTimes( ) const = 0;
	virtual _dword	GetDrawMiniPrimitiveTimes( ) const = 0;

	virtual _float	GetFramePerSecond( ) const = 0;
	virtual _float	GetRenderFramePerSecond( ) const = 0;

	virtual _dword	GetTextureMemoryUsed( ) const = 0;
	virtual _dword	GetVertexMemoryUsed( ) const = 0;
	virtual _dword	GetIndexMemoryUsed( ) const = 0;
};

};