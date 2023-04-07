#pragma once

namespace Xixels
{

class IGeometryFactory
{
public:
	virtual IVertexBuffer*	CreateVertexBuffer( _dword type, _dword length, _dword format, _dword align = 1 ) = 0;
	virtual IVertexBuffer*	CreateVertexBuffer( _dword type, const _void* buffer, _dword length, _dword format, _dword align = 1 ) = 0;
	virtual IVertexBuffer*	CloneVertexBuffer( IVertexBuffer* vertexbuffer, _bool ref = _true ) = 0;
	virtual _void			CopyVertexBuffer( IVertexBuffer* vbuffer1, IVertexBuffer* vbuffer2 ) = 0;
	virtual _void			FillVertexBuffer( IVertexBuffer* vertexbuffer, const _void* buffer, _dword length, _bool bufferowner ) = 0;
	virtual _void			ReleaseVertexBuffer( IVertexBuffer*& vertexbuffer ) = 0;

	virtual IIndexBuffer*	CreateIndexBuffer( _dword type, _dword length, _dword isize, _dword align = 1 ) = 0;
	virtual IIndexBuffer*	CreateIndexBuffer( _dword type, const _void* buffer, _dword length, _dword isize, _dword align = 1 ) = 0;
	virtual IIndexBuffer*	CloneIndexBuffer( IIndexBuffer* indexbuffer, _bool ref = _true ) = 0;
	virtual _void			CopyIndexBuffer( IIndexBuffer* indexbuffer1, IIndexBuffer* indexbuffer2 ) = 0;
	virtual _void			FillIndexBuffer( IIndexBuffer* indexbuffer, const _void* buffer, _dword length, _bool bufferowner ) = 0;
	virtual _void			ReleaseIndexBuffer( IIndexBuffer*& indexbuffer ) = 0;

	virtual Geometry		CreateGeometry( _dword format, _dword vnumber, _dword inumber, _dword geotype, _dword geonumber, _bool skipcache = _false ) = 0;
	virtual Geometry		CreatePlaneGeometry( _dword format, _dword gridx, _dword gridy, _bool doubleface = _false ) = 0;
	virtual Geometry		CreateCubeGeometry( _dword format ) = 0;
	virtual Geometry		CreatePyramidGeometry( _dword format ) = 0;
	virtual Geometry		CreateSphereGeometry( _dword format, _dword ring = 15, _dword segment = 20 ) = 0;
	virtual Geometry		CreateHemiSphereGeometry( _dword format, _dword ring = 15, _dword segment = 20 ) = 0;
	virtual Geometry		CreateCapsuleGeometry( _dword format, _float radius1 = 1.0f, _float radius2 = 1.0f, _float length = 2.0f, _dword ring = 15, _dword segment = 20 ) = 0;
	virtual Geometry		CreateCylinderGeometry( _dword format, _dword segment = 20 ) = 0;
	virtual Geometry		CreateConeGeometry( _dword format, _dword segment = 20 ) = 0;
	virtual Geometry		CreateTeapotGeometry( _dword format ) = 0;
	virtual Geometry		CreateOverlayGeometry( _dword width, _dword height, _bool usepool = _false ) = 0;
	virtual Geometry		CreateTriangleGeometry( _dword width, _dword height ) = 0;

	virtual Geometry		CloneGeometry( const Geometry& geo, _bool ref = _true ) = 0;
	virtual _void			ReleaseGeometry( Geometry& geo ) = 0;

	virtual _void			TransformGeometry( Geometry& geo, const Matrix4& mat ) = 0;
	virtual _void			TransformVertex( _dword format, _byte* vertex, const Matrix4& mat, const Matrix3& rot ) = 0;
	virtual _void			TransformGeometryTexcoord( Geometry& geo, const Matrix3& mat, _dword format ) = 0;
	virtual _void			TransformTexcoord( _byte* vertex, _dword offset, Vector4& uvtransform ) = 0;

	virtual _void			BuildGeometryBoundBox( Geometry& geo ) = 0;
	virtual _bool			BuildNormal( Geometry& geo ) = 0;
	virtual _bool			BuildTangent( Geometry& geo ) = 0;
	virtual _bool			BuildSkinBufferForGPU( Geometry& geo ) = 0;
	virtual _bool			BuildSkinBufferForCPU( Geometry& geo ) = 0;
};

};