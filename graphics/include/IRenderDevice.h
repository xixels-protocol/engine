#pragma once

namespace Xixels
{

class IRenderDevice
{
public:
	enum _DEVICE_TYPE
	{
		_DEVICE_HARDWARE_NOVSYNC	= 0,
		_DEVICE_HARDWARE_VSYNC		= 1,
	};

	enum _RENDER_LAYER
	{
		_LAYER_BACKGROUND			= 1,
		_LAYER_ENVIRONMENT			= 2,
		_LAYER_DECAL				= 3,
		_LAYER_NORMAL				= 4,
		_LAYER_EFFECT				= 5,
		_LAYER_FOREGROUND			= 6,
		_LAYER_OVERLAY				= 7,
	};

	enum _RENDER_ORDER
	{
		_ORDER_NORMAL				= 0,
		_ORDER_DECAL				= 1,
		_ORDER_COLORKEY				= 2,
		_ORDER_ALPHA				= 3,
		_ORDER_NONE					= 4,
	};

	virtual _bool				SkipRender( ) const = 0;

	virtual _bool				CheckDeviceLost( ) = 0;
	virtual _bool				IsDeviceLost( ) const = 0;

	virtual _bool				ResizeDevice( _dword width, _dword height ) = 0;
	virtual _bool				ResetDevice( ) = 0;

	virtual _handle				GetDeviceHandle( ) const = 0;
	virtual _handle				GetDevicePointer( ) const = 0;
	virtual _handle				GetDeviceParam( ) const = 0;
	virtual _dword				GetDeviceType( ) const = 0;
	virtual _dword				GetDeviceWidth( ) const = 0;
	virtual _dword				GetDeviceHeight( ) const = 0;

	virtual _void				SetClearColor( _dword color ) = 0;
	virtual _dword				GetClearColor( ) const = 0;
	virtual _void				SetClearDepth( _float depth ) = 0;
	virtual _float				GetClearDepth( ) const = 0;
	virtual _void				SetClearStencil( _dword stencil ) = 0;
	virtual _dword				GetClearStencil( ) const = 0;

	virtual _void				ClearBuffer( _bool color = _true, _bool depth = _true, _bool stencil = _true ) = 0;
	virtual _void				Flush( _dword layermask = -1, _bool forceflush = _false, _bool synch = _false ) = 0;
	virtual _void				Present( _handle targetwindow = _null ) = 0;

	virtual _void				EnableMipSampler( _bool enable ) = 0;
	virtual _bool				IsMipSamplerEnabled( ) const = 0;

	virtual _void				SetResolution3DWidth( _dword width ) = 0;
	virtual _dword				GetResolution3DWidth( ) const = 0;
	virtual _void				SetResolution3DHeight( _dword height ) = 0;
	virtual _dword				GetResolution3DHeight( ) const = 0;

	virtual ClipperRegion		TransformClipRegion( const Region& region ) = 0;
	virtual _void				CombineOverlayClipRegion( const Region& region, const Matrix3& mat = Matrix3::cIdentity ) = 0;
	virtual _void				CombineOverlayClipRegion( const ClipperRegion& clipregion ) = 0;
	virtual _void				SetOverlayClipRegion( const Region& region, const Matrix3& mat = Matrix3::cIdentity ) = 0;
	virtual _void				SetOverlayClipRegion( const ClipperRegion& clipregion ) = 0;
	virtual const ClipperRegion&GetOverlayClipRegion( ) const = 0;
	virtual _void				PushOverlayClipRegion( ) = 0;
	virtual _void				PopOverlayClipRegion( ) = 0;

	virtual _void				SetOverlayTransform( const Matrix3& mat ) = 0;
	virtual const Matrix3&		GetOverlayTransform( ) const = 0;
	virtual _void				PushOverlayTransform( ) = 0;
	virtual _void				PopOverlayTransform( ) = 0;

	virtual _void				SetWorldTransform( const Matrix4& mat ) = 0;
	virtual const Matrix4&		GetWorldTransform( ) const = 0;
	virtual const Matrix3&		GetNormalTransform( ) const = 0;
	virtual const Vector3&		GetScaleTransform( ) const = 0;
	virtual _void				PushWorldTransform( ) = 0;
	virtual _void				PopWorldTransform( ) = 0;

	virtual _void				SetViewTransform( const Matrix4& mat ) = 0;
	virtual const Matrix4&		GetViewTransform( ) const = 0;
	virtual _void				PushViewTransform( ) = 0;
	virtual _void				PopViewTransform( ) = 0;

	virtual _void				SetDeviceJitterVec( const Vector2& jittervec ) = 0;

	virtual _void				SetProjectionTransform( const Matrix4& mat ) = 0;
	virtual Matrix4				GetProjectionTransform( ) const = 0;
	virtual const Vector2&		GetProjectionJitter( ) const = 0;
	virtual const Matrix4&		GetProjectionNoAATransform( ) const = 0;
	virtual _void				PushProjectionTransform( ) = 0;
	virtual _void				PopProjectionTransform( ) = 0;

	virtual _void				SetCamera( const Camera& cam ) = 0;
	virtual const Camera&		GetCamera( ) const = 0;
	virtual _void				PushCamera( ) = 0;
	virtual _void				PopCamera( ) = 0;

	virtual _void				SetViewport( const Viewport& vp ) = 0;
	virtual const Viewport&		GetViewport( _bool clip = _false ) const = 0;
	virtual _void				PushViewport( ) = 0;
	virtual _void				PopViewport( ) = 0;

	virtual const Matrix4&		GetViewMatrix( ) const = 0;
	virtual const Frustum&		GetViewFrustum( ) const = 0;

	virtual _void				SetViewRange( _float vnear, _float vfar ) = 0;
	virtual _void				GetViewRange( _float& vnear, _float& vfar ) const = 0;

	virtual _void				ResetClipRange( ) = 0;
	virtual _void				SetClipRange( _float range ) = 0;
	virtual _float				GetClipRange( ) const = 0;

	virtual Ray					GetPickRay( _long x, _long y, _bool ortho = _false ) const = 0;
	virtual Vector2				ProjectPoint2Screen( const Vector3& point ) const = 0;
	virtual Region				ProjectBox2Screen( const AxisAlignedBox& boundbox ) const = 0;

	virtual ITexture*			GetDefaultRenderTarget( ) const = 0;
	virtual _dword				GetRenderTargetFormat( ) const = 0;

	virtual ITexture*			GetDefaultDepthStencil( ) const = 0;
	virtual _dword				GetDepthStencilFormat( ) const = 0;
	virtual _void				EnableDepthStencilReadable( _bool enable ) = 0;

	virtual ITexture*			GetLastRenderTarget( ) const = 0;
	virtual ITexture*			GetLastDepthStencil( ) const = 0;

	virtual _void				SetRenderMethod( IRenderMethod* method ) = 0;
	virtual IRenderMethod*		GetRenderMethod( ) const = 0;
	virtual _void				SetStencilMethod( IStencilMethod* method ) = 0;
	virtual IStencilMethod*		GetStencilMethod( ) const = 0;
	virtual _void				SetBlendMethod( IBlendMethod* method ) = 0;
	virtual IBlendMethod*		GetBlendMethod( ) const = 0;
	virtual _void				SetVertexMethod( IVertexMethod* method ) = 0;
	virtual IVertexMethod*		GetVertexMethod( ) const = 0;
	virtual _void				SetSamplerMethod( ISamplerMethod* method ) = 0;
	virtual ISamplerMethod*		GetSamplerMethod( ) const = 0;
	virtual _void				SetPixelMethod( IPixelMethod* method ) = 0;
	virtual IPixelMethod*		GetPixelMethod( ) const = 0;

	virtual _void				SetVertexShaderConst( IShaderConst* sc ) = 0;
	virtual IShaderConst*		GetVertexShaderConst( ) const = 0;

	virtual _void				SetPixelShaderConst( IShaderConst* sc ) = 0;
	virtual IShaderConst*		GetPixelShaderConst( ) const = 0;


	virtual _void				SetVertexShaderReflection( IShaderReflection* isr ) = 0;
	virtual IShaderReflection*	GetVertexShaderReflection( ) const = 0;

	virtual _void				SetPixelShaderReflection( IShaderReflection* isr ) = 0;
	virtual IShaderReflection*	GetPixelShaderReflection( ) const = 0;

	virtual _void				PushAllRenderMethod( ) = 0;
	virtual _void				PopAllRenderMethod( ) = 0;

	virtual const IRenderSet*	GetDefaultRenderSet( ) const = 0;
	virtual _void				SetRenderSet( IRenderSet* rs ) = 0;
	virtual IRenderSet*			GetRenderSet( ) const = 0;
	virtual _void				PushRenderSet( ) = 0;
	virtual _void				PopRenderSet( ) = 0;

	virtual _void				SetRenderLayer( _dword layer ) = 0;
	virtual _void				ResetRenderLayer( ) = 0;
	virtual _void				BeginSubRenderLayer( _dword layer ) = 0;
	virtual _void				EndSubRenderLayer( ) = 0;

	virtual _bool				CheckRenderStack( ) = 0;
	virtual ITechniqueUnit&		GetTechniqueUnit( ) = 0;

	virtual _void				Render( const Geometry& geo ) = 0;
	virtual _void				Render( const Geometry& geo, const Matrix4& mat ) = 0;
	
	virtual _void				Render( const OverlayRectangleImage& ol ) = 0;

// TODO. Sprite will be rendered by policy, so these functions are private.
private:
	virtual _void				Render( const OverlayPoint& ol ) = 0;
	virtual _void				Render( const OverlayLine& ol ) = 0;
	virtual _void				Render( const OverlayTriangle& ol ) = 0;
	virtual _void				Render( const OverlayTriangleImage& ol ) = 0;
	virtual _void				Render( const OverlayTriangleOnlyImage& ol ) = 0;
	virtual _void				Render( const OverlayRectangle& ol ) = 0;

	virtual _void				Render( const OverlayRectangleColor4Image& ol ) = 0;
	virtual _void				Render( const OverlayRectangleOnlyImage& ol ) = 0;
	virtual _void				Render( const OverlayRectangleUserData& ol ) = 0;
	virtual _void				Render( const OverlayQuadrangle& ol ) = 0;
	virtual _void				Render( const OverlayQuadrangleImage& ol ) = 0;
	virtual _void				Render( const OverlayQuadrangleOnlyImage& ol ) = 0;
	virtual _void				Render( const OverlayConvexPolygon& ol ) = 0;

	virtual _void				Render( const PrimitivePoint& pm ) = 0;
	virtual _void				Render( const PrimitiveLine& pm ) = 0;
	virtual _void				Render( const PrimitiveTriangle& pm ) = 0;
	virtual _void				Render( const PrimitiveTriangleFill& pm ) = 0;
	virtual _void				Render( const PrimitiveTriangleImage& pm ) = 0;
	virtual _void				Render( const PrimitiveTriangleOnlyImage& pm ) = 0;
	virtual _void				Render( const PrimitiveQuadrangle& pm ) = 0;
	virtual _void				Render( const PrimitiveQuadrangleFill& pm ) = 0;
	virtual _void				Render( const PrimitiveQuadrangleImage& pm ) = 0;
	virtual _void				Render( const PrimitiveQuadrangleOnlyImage& pm ) = 0;
	virtual _void				Render( const PrimitiveBox& pm ) = 0;
	virtual _void				Render( const PrimitiveCircle& pm ) = 0;
	virtual _void				Render( const PrimitiveSphere& pm ) = 0;
	virtual _void				Render( const PrimitivePyramid& pm ) = 0;
	virtual _void				Render( const PrimitiveAxis& pm ) = 0;
	virtual _void				Render( const PrimitiveFrustum& pm ) = 0;

	virtual _void				Render( const BillboardScreenAligned& bb ) = 0;
	virtual _void				Render( const BillboardScreenAlignedOnlyImage& bb ) = 0;
	virtual _void				Render( const BillboardWorldOriented& bb ) = 0;
	virtual _void				Render( const BillboardWorldOrientedOnlyImage& bb ) = 0;
	virtual _void				Render( const BillboardAxial& bb ) = 0;
	virtual _void				Render( const BillboardAxialOnlyImage& bb ) = 0;

public:
	virtual _void				Render( IFontTexture* font, const Vector2& position, _char character ) = 0;
	virtual _void				Render( IFontTexture* font, const Vector2& position, _dword align, const _char* buffer ) = 0;
	virtual _void				Render( IFontTexture* font, const Vector2& position, const Vector2& scale, _dword align, const _char* buffer ) = 0;
	virtual _void				Render( IFontTexture* font, const Vector3& center, _float height, _char character ) = 0;
	virtual _void				Render( IFontTexture* font, const Vector3& center, _float height, const _char* buffer ) = 0;
	virtual _void				Render( IFontTexture* font, const Vector3& center, const Vector3& width, const Vector3& height, _char character ) = 0;
	virtual _void				Render( IFontTexture* font, const Vector3& center, const Vector3& width, const Vector3& height, const _char* buffer ) = 0;

	virtual _void				Render( IMesh* mesh ) = 0;
	virtual _void				Render( ISubMesh* submesh ) = 0;
	virtual _void				Render( ISkeleton* skeleton, _float size, const Color& parentcolor, const Color& childcolor, const Color& dummycolor, const Color& sizecolor = Color::cWhite ) = 0;
	virtual _void				Render( IScene* scene ) = 0;
};

};
