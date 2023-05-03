#include "Mesh.h"

Mesh::Mesh( ) : mResource( _null )
{
}

Mesh::Mesh( Mesh* mesh ) : ResourceGraData( mesh ), mResource( _null ), mBoundBox( mesh->mBoundBox )
{
	// Attach to same resource of source mesh.
	AttachResource( mesh->mResource );

	if ( GetGraphicsManager( ).IsMemoryBufferEnabled( ) )
		AllocateBuffer( mesh->mSubMeshs.Length( ) );

	// Create sub mesh use memory buffer.
	mSubMeshs.Grow( mesh->mSubMeshs.Length( ) );
	for ( _long i = 0; i < mesh->mSubMeshs.Length( ); i ++ )
	{
		SubMesh* m = new ( mMemoryBuffer.BufferAlloc( sizeof( SubMesh ) ) ) SubMesh( (SubMesh*) mesh->mSubMeshs[i] );
		mSubMeshs.Add( m );
	}
}

Mesh::Mesh( StringPtr name, const Geometry& geo, const Material& mtl, Mesh* mesh ) : mResource( _null )
{
	// Attach to same resource of source mesh.
	if ( mesh != _null )
		AttachResource( mesh->mResource );

	SubMesh * newmesh = new ( mMemoryBuffer.BufferAlloc( sizeof( SubMesh ) ) ) SubMesh( name, geo, mtl );
	mSubMeshs.Add( newmesh );
	mBoundBox = geo.GetBoundBox( );
}

Mesh::~Mesh( )
{
	ClearSubMesh( );

	for ( _long i = 0; i < mMeshResources.Length( ); i ++ )
		GetModelFactory( ).ReleaseMesh( mMeshResources[i] );

	// This is uncached resource, try to delete host cached resource.
	if ( mResource != _null )
	{
		IMesh* res = mResource;
		GetModelFactory( ).ReleaseMesh( res );
	}
	// This is cached resource, remove from cache.
	else if ( IsResNameBlank( ) == _false )
	{
		GetResourceCache( ).ReleaseCache( IResourceCache::_RES_MESH, GetResName( ) );
	}
}

_void Mesh::Reload( Mesh* mesh )
{
	if ( mesh == _null )
		return;

	if ( mSubMeshs.Length( ) != mesh->mSubMeshs.Length( ) )
	{
		FG_LOG( L"[MF] Reload mesh failed : %ls", (const _char*) GetResName( ) )
		return;
	}

	for ( _long i = 0; i < mSubMeshs.Length( ); i ++ )
	{
		Geometry& geo = mSubMeshs[i]->GetGeometry( );
		Geometry& ogeo = mesh->mSubMeshs[i]->GetGeometry( );

		// TODO : Remove redundance data in Geometry and keep the data consistency.
		geo.mVertexNumber = ogeo.mVertexNumber;

		( (VertexBuffer*) geo.mVertexBuffer )->ResetResObject( GetRenderer( ).CloneVertexBuffer( ( (VertexBuffer*) ogeo.mVertexBuffer )->GetResObject( ) ), (VertexBuffer*) ogeo.mVertexBuffer );

		if ( geo.mIndexBuffer != _null )
		{
			( (IndexBuffer*) geo.mIndexBuffer )->ResetResObject( GetRenderer( ).CloneIndexBuffer( ( (IndexBuffer*) ogeo.mIndexBuffer )->GetResObject( ) ), (IndexBuffer*) ogeo.mIndexBuffer );
			geo.mIndexNumber = ogeo.mIndexNumber;
		}

		geo.mGeometryNumber = ogeo.mGeometryNumber;

		if ( geo.mHelperBuffer != _null )
			( (VertexBuffer*) geo.mHelperBuffer )->ResetResObject( GetRenderer( ).CloneVertexBuffer( ( (VertexBuffer*) ogeo.mHelperBuffer )->GetResObject( ) ), (VertexBuffer*) ogeo.mHelperBuffer );
	}

	if ( mResource != _null )
		mResource->Reload( mesh );
}

_bool Mesh::IsReady( _bool checktex ) const
{
	if ( mResource != _null )
		return mResource->IsReady( checktex );

	for ( _long i = 0; i < mSubMeshs.Length( ); i ++ )
	{
		if ( mSubMeshs[i]->IsReady( checktex ) == _false )
			return _false;
	}

	return _true;
}

ISubMesh* Mesh::CreateSubMesh( StringPtr name )
{
	// Create sub mesh use memory buffer.
	SubMesh* newmesh = new ( mMemoryBuffer.BufferAlloc( sizeof( SubMesh ) ) ) SubMesh( name );
	mSubMeshs.Add( newmesh );

	return newmesh;
}

ISubMesh* Mesh::CreateSubMesh( StringPtr name, const Geometry& geo, const Material& mtl )
{
	// Create sub mesh use memory buffer.
	SubMesh* newmesh = new ( mMemoryBuffer.BufferAlloc( sizeof( SubMesh ) ) ) SubMesh( name, geo, mtl );
	mSubMeshs.Add( newmesh );

	if ( mBoundBox == AxisAlignedBox::cNullBox )
		mBoundBox = newmesh->GetBoundBox( );
	else
		mBoundBox += newmesh->GetBoundBox( );

	return newmesh;
}

ISubMesh* Mesh::CreateSubMesh( StringPtr name, const Geometry& geo, IMeshMaterial* mtl )
{
	// Create sub mesh use memory buffer.
	SubMesh* newmesh = new ( mMemoryBuffer.BufferAlloc( sizeof( SubMesh ) ) ) SubMesh( name, geo, mtl );
	mSubMeshs.Add( newmesh );

	if ( mBoundBox == AxisAlignedBox::cNullBox )
		mBoundBox = newmesh->GetBoundBox( );
	else
		mBoundBox += newmesh->GetBoundBox( );

	return newmesh;
}

ISubMesh* Mesh::CreateSubMesh( ISubMesh* submesh )
{
	// Create sub mesh use memory buffer.
	SubMesh* newmesh = new ( mMemoryBuffer.BufferAlloc( sizeof( SubMesh ) ) ) SubMesh( (SubMesh*) submesh );
	mSubMeshs.Add( newmesh );

	if ( mBoundBox == AxisAlignedBox::cNullBox )
		mBoundBox = newmesh->GetBoundBox( );
	else
		mBoundBox += newmesh->GetBoundBox( );

	return newmesh;
}

_void Mesh::AddMeshResource( IMesh* mesh )
{
	mMeshResources.Add( mesh );
}

_void Mesh::ReleaseSubMesh( ISubMesh*& submesh )
{
	if ( submesh == _null )
		return;

	_dword i = mSubMeshs.IndexOf( (SubMesh*) submesh );
	if ( i == -1 )
		return;

	// Delete use memory buffer.
	mSubMeshs[i]->SubMesh::~SubMesh( );
	mMemoryBuffer.BufferFree( mSubMeshs[i] );

	// Remove from mesh array.
	mSubMeshs.RemoveAt( i );

	submesh = _null;
}

_void Mesh::ClearSubMesh( )
{
	// Delete use memory buffer.
	for ( _long i = 0; i < mSubMeshs.Length( ); i ++ )
	{
		mSubMeshs[i]->SubMesh::~SubMesh( );
		mMemoryBuffer.BufferFree( mSubMeshs[i] );
	}

	mSubMeshs.Clear( );

	mBoundBox = AxisAlignedBox::cNullBox;
}

ISubMesh* Mesh::GetSubMesh( StringPtr name ) const
{
	for ( _long i = 0; i < mSubMeshs.Length( ); i ++ )
	{
		if ( mSubMeshs[i]->GetName( ) == name )
			return mSubMeshs[i];
	}

	return _null;
}

_void Mesh::Update( ISkeleton* skeleton, _dword elapse )
{
	if ( skeleton == _null )
		return;

	for ( _long i = 0; i < mSubMeshs.Length( ); i ++ )
		mSubMeshs[i]->Update( skeleton, elapse );
}