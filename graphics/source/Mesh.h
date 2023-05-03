#pragma once

namespace Xixels
{

class Mesh : public IMesh, public ReferencedObject
{
private:
	Mesh*				mResource;
	AxisAlignedBox		mBoundBox;

	MemoryBuffer		mMemoryBuffer;
	Array< SubMesh* >	mSubMeshs;
	Array< IMesh* >		mMeshResources;

public:
	Mesh( );
	Mesh( Mesh* mesh );
	Mesh( StringPtr name, const Geometry& geo, const Material& mtl, Mesh* mesh = _null );
	~Mesh( );

	inline _void AttachResource( Mesh* res )
		{ if ( mResource != _null ) return; mResource = res; if ( res != _null ) res->IncRefCount( ); }

	inline _void AllocateBuffer( _dword meshcount )
		{ mMemoryBuffer.CreateBuffer( meshcount * sizeof( SubMesh ) ); }

	inline Mesh* GetResource( ) const
		{ return mResource; }

	_void Reload( Mesh* mesh );

public:
	virtual _dword GetSubMeshCount( ) const
		{ return mSubMeshs.Length( ); }
	virtual ISubMesh* GetSubMesh( _dword index ) const
		{ return mSubMeshs.IsIndexValid( (_long) index ) ? mSubMeshs[ index ] : _null; }

	virtual _bool		IsReady( _bool checktex ) const;

	virtual ISubMesh*	CreateSubMesh( StringPtr name );
	virtual ISubMesh*	CreateSubMesh( StringPtr name, const Geometry& geo, const Material& mtl );
	virtual ISubMesh*	CreateSubMesh( StringPtr name, const Geometry& geo, IMeshMaterial* mtl );
	virtual ISubMesh*	CreateSubMesh( ISubMesh* submesh );
	virtual _void		AddMeshResource( IMesh* mesh );
	virtual _void		ReleaseSubMesh( ISubMesh*& submesh );
	virtual _void		ClearSubMesh( );

	virtual ISubMesh*	GetSubMesh( StringPtr name ) const;

	virtual _void		Update( ISkeleton* skeleton, _dword elapse );
};

};