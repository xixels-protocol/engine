#include "SubMesh.h"

SubMesh::SubMesh( ) : mMtl( _null )
{
}

SubMesh::SubMesh( StringPtr name ) : mMtl( _null )
{
	SetName( name );
}

SubMesh::SubMesh( StringPtr name, const Geometry& geo, const Material& mtl ) : mMtl( _null )
{
	SetName( name );

	mGeo = GetGeometryFactory( ).CloneGeometry( geo );
	if ( mtl != Material::cNull )
	{
		mMtl = GetModelFactory( ).CreateMeshMaterial( );
		mMtl->SetMaterial( mtl );
		mMtl->SetRenderFlag( geo.mRenderFlag );
	}
}

SubMesh::SubMesh( StringPtr name, const Geometry& geo, IMeshMaterial* mtl )
{
	SetName( name );
	mGeo = GetGeometryFactory( ).CloneGeometry( geo );
	mMtl = GetModelFactory( ).CloneMeshMaterial( mtl );
}

SubMesh::SubMesh( SubMesh* submesh )
{
	SetName( submesh->GetName( ) );

	// Must clone here.
	mGeo = GetGeometryFactory( ).CloneGeometry( submesh->mGeo, _false );
	mMtl = GetModelFactory( ).CloneMeshMaterial( submesh->mMtl, _false );

	// For debug.
	ModelFactory::NewSubMesh( );
}

SubMesh::~SubMesh( )
{
	GetGeometryFactory( ).ReleaseGeometry( mGeo );
	GetModelFactory( ).ReleaseMeshMaterial( mMtl );
}

_bool SubMesh::IsReady( _bool checktex ) const
{
	return GetGeometryFactory( ).IsGeometryReady( mGeo, checktex ) && ( mMtl == _null || mMtl->IsReady( checktex ) );
}

_void SubMesh::SetMaterial( IMeshMaterial* mtl )
{
	GetModelFactory( ).ReleaseMeshMaterial( mMtl );
	mMtl = GetModelFactory( ).CloneMeshMaterial( mtl );
}

ITagPoint* SubMesh::CreateTagPoint( )
{
	ITagPoint* tp = GetPhysicsFactory( ).CreateTagPoint( );
	tp->BindGeometry( mGeo );

	return tp;
}

_void SubMesh::Update( ISkeleton* skeleton, _dword elapse )
{
	if ( skeleton == _null )
		return;

	// Update bones before skinning.
	( (Skeleton*) skeleton )->UpdateBones( elapse );

	if ( ( mGeo.GetVertexFormat( ) & IVertexBuffer::_FORMAT_INFLUENCE ) != 0 )
	{
		if ( mGeo.mVertexBuffer != _null && ( (VertexBuffer*) mGeo.mVertexBuffer )->GetResObject( ) != _null )
			skeleton->Skinning( mGeo );
	}
}
