#pragma once

namespace Xixels
{

struct Renderable
{
	enum _RENDERABLE_TYPE
	{
		_TYPE_GEOMETRY									=  1,

		_TYPE_OVERLAY_BEGIN								=  2,
			_TYPE_OVERLAY_POINT							=  2,
			_TYPE_OVERLAY_LINE							=  3,
			_TYPE_OVERLAY_TRIANGLE						=  4,
			_TYPE_OVERLAY_RECTANGLE						=  5,
			_TYPE_OVERLAY_QUADRANGLE					=  6,
			_TYPE_OVERLAY_TRIANGLE_IMAGE				=  7,
			_TYPE_OVERLAY_TRIANGLE_ONLYIMAGE			=  8,
			_TYPE_OVERLAY_RECTANGLE_IMAGE				=  9,
			_TYPE_OVERLAY_RECTANGLE_COLOR4_IMAGE		= 10,
			_TYPE_OVERLAY_RECTANGLE_ONLYIMAGE			= 11,
			_TYPE_OVERLAY_RECTANGLE_USERDATA			= 12,
			_TYPE_OVERLAY_QUADRANGLE_IMAGE				= 13,
			_TYPE_OVERLAY_QUADRANGLE_COLOR4_IMAGE		= 14,
			_TYPE_OVERLAY_QUADRANGLE_ONLYIMAGE			= 15,
			_TYPE_OVERLAY_CONVEXPOLYGON					= 16,
		_TYPE_OVERLAY_END								= 16,

		_TYPE_PRIMITIVE_BEGIN							= 17,
			_TYPE_PRIMITIVE_POINT						= 17,
			_TYPE_PRIMITIVE_LINE						= 18,
			_TYPE_PRIMITIVE_TRIANGLE					= 19,
			_TYPE_PRIMITIVE_TRIANGLE_FILL				= 20,
			_TYPE_PRIMITIVE_TRIANGLE_IMAGE				= 21,
			_TYPE_PRIMITIVE_TRIANGLE_ONLYIMAGE			= 22,
			_TYPE_PRIMITIVE_QUADRANGLE					= 23,
			_TYPE_PRIMITIVE_QUADRANGLE_FILL				= 24,
			_TYPE_PRIMITIVE_QUADRANGLE_IMAGE			= 25,
			_TYPE_PRIMITIVE_QUADRANGLE_ONLYIMAGE		= 26,
			_TYPE_PRIMITIVE_BOX							= 27,
			_TYPE_PRIMITIVE_CIRCLE						= 28,
			_TYPE_PRIMITIVE_SPHERE						= 29,
			_TYPE_PRIMITIVE_PYRAMID						= 30,
			_TYPE_PRIMITIVE_AXIS						= 31,
			_TYPE_PRIMITIVE_FRUSTUM						= 32,
		_TYPE_PRIMITIVE_END								= 32,

		_TYPE_BILLBOARD_BEGIN							= 33,
			_TYPE_BILLBOARD_SCREENALIGNED				= 33,
			_TYPE_BILLBOARD_SCREENALIGNED_ONLYIMAGE		= 34,
			_TYPE_BILLBOARD_WORLDORIENTED				= 35,
			_TYPE_BILLBOARD_WORLDORIENTED_ONLYIMAGE		= 36,
			_TYPE_BILLBOARD_AXIAL						= 37,
			_TYPE_BILLBOARD_AXIAL_ONLYIMAGE				= 38,
		_TYPE_BILLBOARD_END								= 38,

		_TYPE_MAX										= 39,
	};

	_dword	mType;

	inline Renderable( )
		: mType( 0 ) { }
};

//----------------------------------------------------------------------------
// Geometry
//----------------------------------------------------------------------------

struct Geometry : public Renderable
{
	typedef _void (*OnRender)( Geometry& geo );

	enum { _MAX_TEXTURE_COUNT = 4 };
	enum { _MAX_VER_TEXTURE_COUNT = 4 };

	enum _GEOMETRY_TYPE
	{
		_GEOMETRY_POINTLIST		= 1,
		_GEOMETRY_LINELIST		= 2,
		_GEOMETRY_LINESTRIP		= 3,
		_GEOMETRY_TRIANGLELIST	= 4,
		_GEOMETRY_TRIANGLESTRIP	= 5,
		_GEOMETRY_TRIANGLEFAN	= 6,
	};

	IVertexBuffer*		mVertexBuffer;
	IIndexBuffer*		mIndexBuffer;
	IVertexBuffer*		mHelperBuffer;
	IVertexBuffer*		mInstanceBuffer;
	
	ITexture*			mVertexMaps[ _MAX_VER_TEXTURE_COUNT ];
	ITexture*			mTextures[ _MAX_TEXTURE_COUNT ];
	ITexture*			mHelperMaps[ _MAX_TEXTURE_COUNT ];
	ITexture*			mAlphaLayer;
	ITexture*			mNormalMap;
	ITexture*			mSpecularMap;
	ITexture*			mEnvironmentMap;
	ITexture*			mLightMap;

	ISkeleton*			mSkeleton;

	_dword				mGeometryType;
	_dword				mGeometryNumber;
	_dword				mVertexNumber;
	_dword				mIndexNumber;

	_dword				mStartVertex;
	_dword				mStartIndex;

	_dword				mInstanceNumber;
	AxisAlignedBox		mInstanceBoundBox;
	
	_dword				mRenderFlag;
	OnRender			mOnRenderCallBack;
	_void*				mOnRenderUserData;

	inline Geometry( )
		{ Reset( ); }

	inline ~Geometry( )
		{ }

	inline _void Reset( )
	{
		mType				= _TYPE_GEOMETRY;

		mVertexBuffer		= _null;
		mHelperBuffer		= _null;
		mIndexBuffer		= _null;
		mInstanceBuffer		= _null;

		mTextures[0]		= _null;
		mTextures[1]		= _null;
		mTextures[2]		= _null;
		mTextures[3]		= _null;

		mHelperMaps[0]		= _null;
		mHelperMaps[1]		= _null;
		mHelperMaps[2]		= _null;
		mHelperMaps[3]		= _null;

		mAlphaLayer			= _null;
		mNormalMap			= _null;
		mSpecularMap		= _null;
		mEnvironmentMap		= _null;
		mLightMap			= _null;
		mVertexMaps[0]		= _null;
		mVertexMaps[1]		= _null;
		mVertexMaps[2]		= _null;
		mVertexMaps[3]		= _null;
		mSkeleton			= _null;

		mGeometryType		= 0;
		mGeometryNumber		= 0;

		mVertexNumber		= 0;
		mIndexNumber		= 0;
		mStartVertex		= 0;
		mStartIndex			= 0;
		mRenderFlag			= 0;

		mOnRenderCallBack	= _null;
		mOnRenderUserData	= _null;

		mInstanceNumber		= 0;
		mInstanceBoundBox	= AxisAlignedBox::cNullBox;
	}

	inline _dword GetVertexFormat( ) const
		{ return mVertexBuffer != _null ? mVertexBuffer->GetVertexFormat( ) : 0; }

	inline const AxisAlignedBox& GetBoundBox( ) const
		{ return mInstanceBuffer != _null ? mInstanceBoundBox : ( mVertexBuffer != _null ? mVertexBuffer->GetBoundBox( ): AxisAlignedBox::cNullBox ); }
};

struct OverlayImageBase : public Renderable
{
	ITexture*	mTexture;

	OverlayImageBase( ) : mTexture( _null ) { }
};

struct OverlayPoint : public Renderable
{
	Vector2		mPosition;
	Color		mColor;

	OverlayPoint( )
	{
		mType		= _TYPE_OVERLAY_POINT;
	}

	OverlayPoint( const Vector2& pos, const Color& color )
	{
		mType		= _TYPE_OVERLAY_POINT;
		mPosition	= pos;
		mColor		= color;
	}
};

struct OverlayLine : public Renderable
{
	Vector2		mPosition1;
	Vector2		mPosition2;
	Color		mColor1;
	Color		mColor2;

	OverlayLine( )
	{
		mType		= _TYPE_OVERLAY_LINE;
	}

	OverlayLine( const Vector2& pos1, const Vector2& pos2, const Color& color )
	{
		mType		= _TYPE_OVERLAY_LINE;
		mPosition1	= pos1;
		mPosition2	= pos2;
		mColor1		= color;
		mColor2		= color;
	}
};

struct OverlayTriangle : public Renderable
{
	Vector2		mPosition1;
	Vector2		mPosition2;
	Vector2		mPosition3;
	_dword		mColor1;
	_dword		mColor2;
	_dword		mColor3;

	OverlayTriangle( )
	{
		mType		= _TYPE_OVERLAY_TRIANGLE;
	}

	OverlayTriangle( const Vector2& pos1, const Vector2& pos2, const Vector2& pos3, _dword color )
	{
		mType		= _TYPE_OVERLAY_TRIANGLE;
		mPosition1	= pos1;
		mPosition2	= pos2;
		mPosition3	= pos3;
		mColor1		= color;
		mColor2		= color;
		mColor3		= color;
	}

	OverlayTriangle( const Vector2& pos1, const Vector2& pos2, const Vector2& pos3, _dword color1, _dword color2, _dword color3 )
	{
		mType = _TYPE_OVERLAY_TRIANGLE;
		mPosition1 = pos1;
		mPosition2 = pos2;
		mPosition3 = pos3;
		mColor1 = color1;
		mColor2 = color2;
		mColor3 = color3;
	}
};

struct OverlayTriangleImage : public OverlayImageBase
{
	Vector2		mPosition1;
	Vector2		mPosition2;
	Vector2		mPosition3;
	Vector2		mTexcoord1;
	Vector2		mTexcoord2;
	Vector2		mTexcoord3;
	_dword		mColor1;
	_dword		mColor2;
	_dword		mColor3;

	OverlayTriangleImage( )
	{
		mType		= _TYPE_OVERLAY_TRIANGLE_IMAGE;
	}

	OverlayTriangleImage( const Vector2& pos1, const Vector2& pos2, const Vector2& pos3,
		const Vector2& tex1, const Vector2& tex2, const Vector2& tex3, _dword color, ITexture* texture )
	{
		mType		= _TYPE_OVERLAY_TRIANGLE_IMAGE;
		mPosition1	= pos1;
		mPosition2	= pos2;
		mPosition3	= pos3;
		mTexcoord1	= tex1;
		mTexcoord2	= tex2;
		mTexcoord3	= tex3;
		mColor1		= color;
		mColor2		= color;
		mColor3		= color;
		mTexture	= texture;
	}
};

struct OverlayTriangleOnlyImage : public OverlayImageBase
{
	Vector2		mPosition1;
	Vector2		mPosition2;
	Vector2		mPosition3;
	Vector2		mTexcoord1;
	Vector2		mTexcoord2;
	Vector2		mTexcoord3;

	OverlayTriangleOnlyImage( )
	{
		mType		= _TYPE_OVERLAY_TRIANGLE_ONLYIMAGE;
	}

	OverlayTriangleOnlyImage( const Vector2& pos1, const Vector2& pos2, const Vector2& pos3,
		const Vector2& tex1, const Vector2& tex2, const Vector2& tex3, ITexture* texture )
	{
		mType		= _TYPE_OVERLAY_TRIANGLE_ONLYIMAGE;
		mPosition1	= pos1;
		mPosition2	= pos2;
		mPosition3	= pos3;
		mTexcoord1	= tex1;
		mTexcoord2	= tex2;
		mTexcoord3	= tex3;
		mTexture	= texture;
	}
};

};
