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

struct OverlayRectangle : public Renderable
{
	Vector2			mPositionLT;
	Vector2			mPositionRB;
	Color			mColor;

	OverlayRectangle( )
	{
		mType			= _TYPE_OVERLAY_RECTANGLE;
	}

	OverlayRectangle( const Vector2& poslt, const Vector2& posrb, _dword color )
	{
		mType			= _TYPE_OVERLAY_RECTANGLE;
		mPositionLT		= poslt;
		mPositionRB		= posrb;
		mColor			= color;
	}
};

struct OverlayRectangleImage : public OverlayImageBase
{
	Vector2		mPositionLT;
	Vector2		mPositionRB;
	Vector2		mTexcoordLT;
	Vector2		mTexcoordRT;
	Vector2		mTexcoordLB;
	Vector2		mTexcoordRB;
	_dword		mColor;

	OverlayRectangleImage( )
	{
		mType			= _TYPE_OVERLAY_RECTANGLE_IMAGE;
	}

	OverlayRectangleImage( const Vector2& poslt, const Vector2& posrb, _dword color, ITexture* texture )
	{
		mType			= _TYPE_OVERLAY_RECTANGLE_IMAGE;
		mPositionLT		= poslt;
		mPositionRB		= posrb;
		mTexcoordLT		= Vector2::cOrigin;
		mTexcoordRT		= Vector2( 1.0f, 0.0f );
		mTexcoordLB		= Vector2( 0.0f, 1.0f );
		mTexcoordRB		= Vector2( 1.0f, 1.0f );
		mColor			= color;
		mTexture		= texture;
	}

	OverlayRectangleImage( const Vector2& poslt, const Vector2& posrb, const Vector2& texlt, const Vector2& texrb, _dword color, ITexture* texture )
	{
		mType			= _TYPE_OVERLAY_RECTANGLE_IMAGE;
		mPositionLT		= poslt;
		mPositionRB		= posrb;
		mTexcoordLT		= texlt;
		mTexcoordRT		= Vector2( texrb.x, texlt.y );
		mTexcoordLB		= Vector2( texlt.x, texrb.y );
		mTexcoordRB		= texrb;
		mColor			= color;
		mTexture		= texture;
	}

	OverlayRectangleImage( const Vector2& poslt, const Vector2& posrb, const Vector2& texlt, const Vector2& texrt,
		const Vector2& texlb, const Vector2& texrb, _dword color, ITexture* texture )
	{
		mType			= _TYPE_OVERLAY_RECTANGLE_IMAGE;
		mPositionLT		= poslt;
		mPositionRB		= posrb;
		mTexcoordLT		= texlt;
		mTexcoordRT		= texrt;
		mTexcoordLB		= texlb;
		mTexcoordRB		= texrb;
		mColor			= color;
		mTexture		= texture;
	}
};

struct OverlayRectangleOnlyImage : public OverlayImageBase
{
	Vector2		mPositionLT;
	Vector2		mPositionRB;
	Vector2		mTexcoordLT;
	Vector2		mTexcoordRB;

	OverlayRectangleOnlyImage( )
	{
		mType			= _TYPE_OVERLAY_RECTANGLE_ONLYIMAGE;
	}

	OverlayRectangleOnlyImage( const Vector2& poslt, const Vector2& posrb, ITexture* texture )
	{
		mType			= _TYPE_OVERLAY_RECTANGLE_ONLYIMAGE;
		mPositionLT		= poslt;
		mPositionRB		= posrb;
		mTexcoordLT		= Vector2::cOrigin;
		mTexcoordRB		= Vector2( 1.0f, 1.0f );
		mTexture		= texture;
	}

	OverlayRectangleOnlyImage( const Vector2& poslt, const Vector2& posrb, const Vector2& texlt, const Vector2& texrb, ITexture* texture )
	{
		mType			= _TYPE_OVERLAY_RECTANGLE_ONLYIMAGE;
		mPositionLT		= poslt;
		mPositionRB		= posrb;
		mTexcoordLT		= texlt;
		mTexcoordRB		= texrb;
		mTexture		= texture;
	}
};

struct OverlayQuadrangle : public Renderable
{
	Vector2		mPositionLT;
	Vector2		mPositionRT;
	Vector2		mPositionLB;
	Vector2		mPositionRB;
	_dword		mColorLT;
	_dword		mColorRT;
	_dword		mColorLB;
	_dword		mColorRB;

	OverlayQuadrangle( )
	{
		mType		= _TYPE_OVERLAY_QUADRANGLE;
	}

	OverlayQuadrangle( const Vector2& poslt, const Vector2& posrt, const Vector2& poslb, const Vector2& posrb, _dword color )
	{
		mType			= _TYPE_OVERLAY_QUADRANGLE;
		mPositionLT		= poslt;
		mPositionRT		= posrt;
		mPositionLB		= poslb;
		mPositionRB		= posrb;
		mColorLT		= color;
		mColorRT		= color;
		mColorLB		= color;
		mColorRB		= color;
	}
};

struct OverlayQuadrangleImage : public OverlayImageBase
{
	Vector2		mPositionLT;
	Vector2		mPositionRT;
	Vector2		mPositionLB;
	Vector2		mPositionRB;
	Vector2		mTexcoordLT;
	Vector2		mTexcoordRT;
	Vector2		mTexcoordLB;
	Vector2		mTexcoordRB;
	_dword		mColorLT;
	_dword		mColorRT;
	_dword		mColorLB;
	_dword		mColorRB;

	OverlayQuadrangleImage( )
	{
		mType			= _TYPE_OVERLAY_QUADRANGLE_IMAGE;
	}

	OverlayQuadrangleImage( const Vector2& poslt, const Vector2& posrt, const Vector2& poslb, const Vector2& posrb, _dword color, ITexture* texture )
	{
		mType			= _TYPE_OVERLAY_QUADRANGLE_IMAGE;
		mPositionLT		= poslt;
		mPositionRT		= posrt;
		mPositionLB		= poslb;
		mPositionRB		= posrb;
		mTexcoordLT		= Vector2::cOrigin;
		mTexcoordRT		= Vector2( 1.0f, 0.0f );
		mTexcoordLB		= Vector2( 0.0f, 1.0f );
		mTexcoordRB		= Vector2( 1.0f, 1.0f );
		mColorLT		= color;
		mColorRT		= color;
		mColorLB		= color;
		mColorRB		= color;
		mTexture		= texture;
	}

	OverlayQuadrangleImage( const Vector2& poslt, const Vector2& posrt, const Vector2& poslb, const Vector2& posrb,
		const Vector2& texlt, const Vector2& texrb, _dword color, ITexture* texture )
	{
		mType			= _TYPE_OVERLAY_QUADRANGLE_IMAGE;
		mPositionLT		= poslt;
		mPositionRT		= posrt;
		mPositionLB		= poslb;
		mPositionRB		= posrb;
		mTexcoordLT		= texlt;
		mTexcoordRT		= Vector2( texrb.x, texlt.y );
		mTexcoordLB		= Vector2( texlt.x, texrb.y );
		mTexcoordRB		= texrb;
		mColorLT		= color;
		mColorRT		= color;
		mColorLB		= color;
		mColorRB		= color;
		mTexture		= texture;
	}

	OverlayQuadrangleImage( const Vector2& poslt, const Vector2& posrt, const Vector2& poslb, const Vector2& posrb,
		const Vector2& texlt, const Vector2& texrt, const Vector2& texlb, const Vector2& texrb, _dword color, ITexture* texture )
	{
		mType			= _TYPE_OVERLAY_QUADRANGLE_IMAGE;
		mPositionLT		= poslt;
		mPositionRT		= posrt;
		mPositionLB		= poslb;
		mPositionRB		= posrb;
		mTexcoordLT		= texlt;
		mTexcoordRT		= texrt;
		mTexcoordLB		= texlb;
		mTexcoordRB		= texrb;
		mColorLT		= color;
		mColorRT		= color;
		mColorLB		= color;
		mColorRB		= color;
		mTexture		= texture;
	}
};

struct OverlayQuadrangleOnlyImage : public OverlayImageBase
{
	Vector2		mPositionLT;
	Vector2		mPositionRT;
	Vector2		mPositionLB;
	Vector2		mPositionRB;
	Vector2		mTexcoordLT;
	Vector2		mTexcoordRT;
	Vector2		mTexcoordLB;
	Vector2		mTexcoordRB;

	OverlayQuadrangleOnlyImage( )
	{
		mType           = _TYPE_OVERLAY_QUADRANGLE_ONLYIMAGE;
	}

	OverlayQuadrangleOnlyImage( const Vector2& poslt, const Vector2& posrt, const Vector2& poslb, const Vector2& posrb, ITexture* texture )
	{
		mType			= _TYPE_OVERLAY_QUADRANGLE_ONLYIMAGE;
		mPositionLT		= poslt;
		mPositionRT		= posrt;
		mPositionLB		= poslb;
		mPositionRB		= posrb;
		mTexcoordLT		= Vector2::cOrigin;
		mTexcoordRT		= Vector2( 1.0f, 0.0f );
		mTexcoordLB		= Vector2( 0.0f, 1.0f );
		mTexcoordRB		= Vector2( 1.0f, 1.0f );
		mTexture		= texture;
	}

	OverlayQuadrangleOnlyImage( const Vector2& poslt, const Vector2& posrt, const Vector2& poslb, const Vector2& posrb,
		const Vector2& texlt, const Vector2& texrb, ITexture* texture )
	{
		mType			= _TYPE_OVERLAY_QUADRANGLE_ONLYIMAGE;
		mPositionLT		= poslt;
		mPositionRT		= posrt;
		mPositionLB		= poslb;
		mPositionRB		= posrb;
		mTexcoordLT		= texlt;
		mTexcoordRT		= Vector2( texrb.x, texlt.y );
		mTexcoordLB		= Vector2( texlt.x, texrb.y );
		mTexcoordRB		= texrb;
		mTexture		= texture;
	}

	OverlayQuadrangleOnlyImage( const Vector2& poslt, const Vector2& posrt, const Vector2& poslb, const Vector2& posrb,
		const Vector2& texlt, const Vector2& texrt, const Vector2& texlb, const Vector2& texrb, ITexture* texture )
	{
		mType			= _TYPE_OVERLAY_QUADRANGLE_ONLYIMAGE;
		mPositionLT		= poslt;
		mPositionRT		= posrt;
		mPositionLB		= poslb;
		mPositionRB		= posrb;
		mTexcoordLT		= texlt;
		mTexcoordRT		= texrt;
		mTexcoordLB		= texlb;
		mTexcoordRB		= texrb;
		mTexture		= texture;
	}
};

struct OverlayConvexPolygon : public Renderable
{
	const Vector2*	mPoints;
	_dword			mCount;
	_dword			mColor;

	OverlayConvexPolygon( )
	{
		mType		= _TYPE_OVERLAY_CONVEXPOLYGON;
		mCount		= 0;
	}

	OverlayConvexPolygon( const Vector2* points, _dword count, _dword color )
	{
		mType		= _TYPE_OVERLAY_CONVEXPOLYGON;
		mPoints		= points;
		mCount		= count;
		mColor		= color;
	}
};

struct PrimitiveImageBase : public Renderable
{
	ITexture*	mTexture;

	PrimitiveImageBase( ) : mTexture( _null ) { }
};

struct PrimitivePoint : public Renderable
{
	Vector3		mPosition;
	Color		mColor;

	PrimitivePoint( )
	{
		mType		= _TYPE_PRIMITIVE_POINT;
	}

	PrimitivePoint( const Vector3& pos, const Color& color )
	{
		mType		= _TYPE_PRIMITIVE_POINT;
		mPosition	= pos;
		mColor		= color;
	}
};

struct PrimitiveLine : public Renderable
{
	Vector3		mPosition1;
	Vector3		mPosition2;
	Color		mColor1;
	Color		mColor2;

	PrimitiveLine( )
	{
		mType		= _TYPE_PRIMITIVE_LINE;
	}

	PrimitiveLine( const Vector3& pos1, const Vector3& pos2, const Color& color )
	{
		mType		= _TYPE_PRIMITIVE_LINE;
		mPosition1	= pos1;
		mPosition2	= pos2;
		mColor1		= color;
		mColor2		= color;
	}

	PrimitiveLine( const Vector3& pos1, const Vector3& pos2, const Color& color1, const Color& color2 )
	{
		mType		= _TYPE_PRIMITIVE_LINE;
		mPosition1	= pos1;
		mPosition2	= pos2;
		mColor1		= color1;
		mColor2		= color2;
	}
};

struct PrimitiveTriangle : public Renderable
{
	Vector3		mPosition1;
	Vector3		mPosition2;
	Vector3		mPosition3;
	Color		mColor1;
	Color		mColor2;
	Color		mColor3;

	PrimitiveTriangle( )
	{
		mType		= _TYPE_PRIMITIVE_TRIANGLE;
	}

	PrimitiveTriangle( const Vector3& pos1, const Vector3& pos2, const Vector3& pos3, const Color& color )
	{
		mType		= _TYPE_PRIMITIVE_TRIANGLE;
		mPosition1	= pos1;
		mPosition2	= pos2;
		mPosition3	= pos3;
		mColor1		= color;
		mColor2		= color;
		mColor3		= color;
	}

	PrimitiveTriangle( const Vector3& pos1, const Vector3& pos2, const Vector3& pos3, const Color& color1, const Color& color2, const Color& color3 )
	{
		mType		= _TYPE_PRIMITIVE_TRIANGLE;
		mPosition1	= pos1;
		mPosition2	= pos2;
		mPosition3	= pos3;
		mColor1		= color1;
		mColor2		= color2;
		mColor3		= color3;
	}
};

struct PrimitiveTriangleFill : public Renderable
{
	Vector3		mPosition1;
	Vector3		mPosition2;
	Vector3		mPosition3;
	Color		mColor1;
	Color		mColor2;
	Color		mColor3;

	PrimitiveTriangleFill( )
	{
		mType		= _TYPE_PRIMITIVE_TRIANGLE_FILL;
	}

	PrimitiveTriangleFill( const Vector3& pos1, const Vector3& pos2, const Vector3& pos3, const Color& color )
	{
		mType		= _TYPE_PRIMITIVE_TRIANGLE_FILL;
		mPosition1	= pos1;
		mPosition2	= pos2;
		mPosition3	= pos3;
		mColor1		= color;
		mColor2		= color;
		mColor3		= color;
	}

	PrimitiveTriangleFill( const Vector3& pos1, const Vector3& pos2, const Vector3& pos3, const Color& color1, const Color& color2, const Color& color3 )
	{
		mType		= _TYPE_PRIMITIVE_TRIANGLE_FILL;
		mPosition1	= pos1;
		mPosition2	= pos2;
		mPosition3	= pos3;
		mColor1		= color1;
		mColor2		= color2;
		mColor3		= color3;
	}
};

struct PrimitiveTriangleImage : public PrimitiveImageBase
{
	Vector3		mPosition1;
	Vector3		mPosition2;
	Vector3		mPosition3;
	Vector2		mTexcoord1;
	Vector2		mTexcoord2;
	Vector2		mTexcoord3;
	Color		mColor1;
	Color		mColor2;
	Color		mColor3;

	PrimitiveTriangleImage( )
	{
		mType		= _TYPE_PRIMITIVE_TRIANGLE_IMAGE;
	}

	PrimitiveTriangleImage( const Vector3& pos1, const Vector3& pos2, const Vector3& pos3,
		const Vector2& tex1, const Vector2& tex2, const Vector2& tex3, const Color& color, ITexture* texture )
	{
		mType		= _TYPE_PRIMITIVE_TRIANGLE_IMAGE;
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

	PrimitiveTriangleImage( const Vector3& pos1, const Vector3& pos2, const Vector3& pos3,
		const Vector2& tex1, const Vector2& tex2, const Vector2& tex3, const Color& color1, const Color& color2, const Color& color3, ITexture* texture )
	{
		mType		= _TYPE_PRIMITIVE_TRIANGLE_IMAGE;
		mPosition1	= pos1;
		mPosition2	= pos2;
		mPosition3	= pos3;
		mTexcoord1	= tex1;
		mTexcoord2	= tex2;
		mTexcoord3	= tex3;
		mColor1		= color1;
		mColor2		= color2;
		mColor3		= color3;
		mTexture	= texture;
	}
};

struct PrimitiveTriangleOnlyImage : public PrimitiveImageBase
{
	Vector3		mPosition1;
	Vector3		mPosition2;
	Vector3		mPosition3;
	Vector2		mTexcoord1;
	Vector2		mTexcoord2;
	Vector2		mTexcoord3;

	PrimitiveTriangleOnlyImage( )
	{
		mType		= _TYPE_PRIMITIVE_TRIANGLE_ONLYIMAGE;
	}

	PrimitiveTriangleOnlyImage( const Vector3& pos1, const Vector3& pos2, const Vector3& pos3,
		const Vector2& tex1, const Vector2& tex2, const Vector2& tex3, ITexture* texture )
	{
		mType		= _TYPE_PRIMITIVE_TRIANGLE_ONLYIMAGE;
		mPosition1	= pos1;
		mPosition2	= pos2;
		mPosition3	= pos3;
		mTexcoord1	= tex1;
		mTexcoord2	= tex2;
		mTexcoord3	= tex3;
		mTexture	= texture;
	}
};

struct PrimitiveQuadrangle : public Renderable
{
	Vector3		mCenter;
	Vector3		mWidth;
	Vector3		mHeight;
	Color		mColor;

	PrimitiveQuadrangle( )
	{
		mType		= _TYPE_PRIMITIVE_QUADRANGLE;
	}

	PrimitiveQuadrangle( const Vector3& center, const Vector3& width, const Vector3& height, const Color& color )
	{
		mType		= _TYPE_PRIMITIVE_QUADRANGLE;
		mCenter		= center;
		mWidth		= width;
		mHeight		= height;
		mColor		= color;
	}
};

struct PrimitiveQuadrangleFill : public Renderable
{
	Vector3		mCenter;
	Vector3		mWidth;
	Vector3		mHeight;
	Color		mColor;

	PrimitiveQuadrangleFill( )
	{
		mType		= _TYPE_PRIMITIVE_QUADRANGLE_FILL;
	}

	PrimitiveQuadrangleFill( const Vector3& center, const Vector3& width, const Vector3& height, const Color& color )
	{
		mType		= _TYPE_PRIMITIVE_QUADRANGLE_FILL;
		mCenter		= center;
		mWidth		= width;
		mHeight		= height;
		mColor		= color;
	}
};

struct PrimitiveQuadrangleImage : public PrimitiveImageBase
{
	Vector3		mCenter;
	Vector3		mWidth;
	Vector3		mHeight;
	Vector2		mTexcoordLT;
	Vector2		mTexcoordRT;
	Vector2		mTexcoordLB;
	Vector2		mTexcoordRB;
	Color		mColor;

	PrimitiveQuadrangleImage( )
	{
		mType		= _TYPE_PRIMITIVE_QUADRANGLE_IMAGE;
	}

	PrimitiveQuadrangleImage( const Vector3& center, const Vector3& width, const Vector3& height, const Color& color, ITexture* texture )
	{
		mType		= _TYPE_PRIMITIVE_QUADRANGLE_IMAGE;
		mCenter		= center;
		mWidth		= width;
		mHeight		= height;
		mTexcoordLT	= Vector2::cOrigin;
		mTexcoordRT	= Vector2( 1.0f, 0.0f );
		mTexcoordLB	= Vector2( 0.0f, 1.0f );
		mTexcoordRB	= Vector2( 1.0f, 1.0f );
		mColor		= color;
		mTexture	= texture;
	}

	PrimitiveQuadrangleImage( const Vector3& center, const Vector3& width, const Vector3& height, const Vector2& texlt,
		const Vector2& texrt, const Vector2& texlb, const Vector2& texrb, const Color& color, ITexture* texture )
	{
		mType		= _TYPE_PRIMITIVE_QUADRANGLE_IMAGE;
		mCenter		= center;
		mWidth		= width;
		mHeight		= height;
		mTexcoordLT	= texlt;
		mTexcoordRT	= texrt;
		mTexcoordLB	= texlb;
		mTexcoordRB	= texrb;
		mColor		= color;
		mTexture	= texture;
	}
};

struct PrimitiveQuadrangleOnlyImage : public PrimitiveImageBase
{
	Vector3		mCenter;
	Vector3		mWidth;
	Vector3		mHeight;
	Vector2		mTexcoordLT;
	Vector2		mTexcoordRT;
	Vector2		mTexcoordLB;
	Vector2		mTexcoordRB;

	PrimitiveQuadrangleOnlyImage( )
	{
		mType		= _TYPE_PRIMITIVE_QUADRANGLE_ONLYIMAGE;
	}

	PrimitiveQuadrangleOnlyImage( const Vector3& center, const Vector3& width, const Vector3& height, ITexture* texture )
	{
		mType		= _TYPE_PRIMITIVE_QUADRANGLE_ONLYIMAGE;
		mCenter		= center;
		mWidth		= width;
		mHeight		= height;
		mTexcoordLT	= Vector2::cOrigin;
		mTexcoordRT	= Vector2( 1.0f, 0.0f );
		mTexcoordLB	= Vector2( 0.0f, 1.0f );
		mTexcoordRB	= Vector2( 1.0f, 1.0f );
		mTexture	= texture;
	}

	PrimitiveQuadrangleOnlyImage( const Vector3& center, const Vector3& width, const Vector3& height, const Vector2& texlt,
		const Vector2& texrt, const Vector2& texlb, const Vector2& texrb, ITexture* texture )
	{
		mType		= _TYPE_PRIMITIVE_QUADRANGLE_ONLYIMAGE;
		mCenter		= center;
		mWidth		= width;
		mHeight		= height;
		mTexcoordLT	= texlt;
		mTexcoordRT	= texrt;
		mTexcoordLB	= texlb;
		mTexcoordRB	= texrb;
		mTexture	= texture;
	}
};

struct PrimitiveBox : public Renderable
{
	Vector3		mCenter;
	Vector3		mWidth;
	Vector3		mHeight;
	Vector3		mDepth;
	_dword		mColor;

	PrimitiveBox( )
	{
		mType		= _TYPE_PRIMITIVE_BOX;
	}

	PrimitiveBox( const AxisAlignedBox& boundbox, _dword color )
	{
		Vector3 Size = boundbox.Size( ) * 0.5f;

		mType		= _TYPE_PRIMITIVE_BOX;
		mCenter		= boundbox.Center( );
		mWidth		= Vector3( Size.x, 0.0f, 0.0f );
		mHeight		= Vector3( 0.0f, Size.y, 0.0f );
		mDepth		= Vector3( 0.0f, 0.0f, Size.z );
		mColor		= color;
	}

	PrimitiveBox( const Vector3& center, const Vector3& width, const Vector3& height, const Vector3& depth, _dword color )
	{
		mType		= _TYPE_PRIMITIVE_BOX;
		mCenter		= center;
		mWidth		= width;
		mHeight		= height;
		mDepth		= depth;
		mColor		= color;
	}
};

struct PrimitiveCircle : public Renderable
{
	Vector3		mCenter;
	Vector3		mNormal;
	_float		mRadius;
	_dword		mColor;
	_dword		mSegment;

	PrimitiveCircle( )
	{
		mType		= _TYPE_PRIMITIVE_CIRCLE;
	}

	PrimitiveCircle( const Vector3& center, const Vector3& normal, _float radius, _dword segment, _dword color )
	{
		mType		= _TYPE_PRIMITIVE_CIRCLE;
		mCenter		= center;
		mNormal		= normal;
		mRadius		= radius;
		mSegment	= segment;
		mColor		= color;
	}
};

struct PrimitiveSphere : public Renderable
{
	Vector3		mCenter;
	_float		mRadius;
	_dword		mSegment;
	_dword		mColor;

	PrimitiveSphere( )
	{
		mType		= _TYPE_PRIMITIVE_SPHERE;
	}

	PrimitiveSphere( const Vector3& center, _float radius, _dword segment, _dword color )
	{
		mType		= _TYPE_PRIMITIVE_SPHERE;
		mCenter		= center;
		mRadius		= radius;
		mSegment	= segment;
		mColor		= color;
	}
};

struct PrimitivePyramid : public Renderable
{
	Vector3		mBase;
	Vector3		mPeak;
	_float		mRadius;
	_dword		mColor;

	PrimitivePyramid( )
	{
		mType		= _TYPE_PRIMITIVE_PYRAMID;
	}

	PrimitivePyramid( const Vector3& base, const Vector3& peak, _dword color )
	{
		mType		= _TYPE_PRIMITIVE_PYRAMID;
		mBase		= base;
		mPeak		= peak;
		mRadius		= ( mPeak - mBase ).Magnitude( ) / 8;
		mColor		= color;
	}

	PrimitivePyramid( const Vector3& base, const Vector3& peak, _float radius, _dword color )
	{
		mType		= _TYPE_PRIMITIVE_PYRAMID;
		mBase		= base;
		mPeak		= peak;
		mRadius		= radius;
		mColor		= color;
	}
};

struct PrimitiveAxis : public Renderable
{
	Vector3		mOrigin;
	Vector3		mXAxis;
	Vector3		mYAxis;
	Vector3		mZAxis;
	_float		mLength;

	PrimitiveAxis( )
	{
		mType		= _TYPE_PRIMITIVE_AXIS;
	}

	PrimitiveAxis( const Vector3& origin, _float length )
	{
		mType		= _TYPE_PRIMITIVE_AXIS;
		mOrigin		= origin;
		mXAxis		= Vector3::cXAxis;
		mYAxis		= Vector3::cYAxis;
		mZAxis		= Vector3::cZAxis;
		mLength		= length;
	}

	PrimitiveAxis( const Matrix4& mat, _float length )
	{
		mType		= _TYPE_PRIMITIVE_AXIS;
		mOrigin		= mat.GetTranslationVector( );
		mXAxis		= Vector3::cXAxis * mat.GetRotationMatrix( );
		mYAxis		= Vector3::cYAxis * mat.GetRotationMatrix( );
		mZAxis		= Vector3::cZAxis * mat.GetRotationMatrix( );
		mLength		= length;
	}
};

struct PrimitiveFrustum : public Renderable
{
	OrientedBox	mFrustum;
	_dword		mColor;

	PrimitiveFrustum( )
	{
		mType		= _TYPE_PRIMITIVE_FRUSTUM;
	}

	PrimitiveFrustum( const Frustum& frustum, _dword color )
	{
		mType		= _TYPE_PRIMITIVE_FRUSTUM;
		mColor		= color;

		Memory::MemCpy( mFrustum.vs, frustum.vs, sizeof( mFrustum.vs ) );
	}

	PrimitiveFrustum( const OrientedBox& frustum, _dword color )
	{
		mType		= _TYPE_PRIMITIVE_FRUSTUM;
		mFrustum	= frustum;
		mColor		= color;
	}
};

};
