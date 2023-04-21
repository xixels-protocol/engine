#include "Skeleton.h"

Skeleton::Skeleton( ) : mResource( _null ), mFrameToken( 0 )
{
}

Skeleton::Skeleton( Skeleton* skeleton ) : mResource( _null ), mFrameToken( 0 )
{
	// Attach to same resource of source skeleton.
	AttachResource( skeleton->mResource );

	for ( _long i = 0; i < skeleton->mBones.Length( ); i ++ )
	{
		// Create bone use memory buffer.
		Bone* bone = new ( mMemoryBuffer.BufferAlloc( sizeof( Bone ) ) ) Bone( *skeleton->mBones[i] );
		bone->mHostSkeleton = this;

		mBones.Add( bone );
	}
}

Skeleton::~Skeleton( )
{
	ClearBone( );
	
	// This is uncached resource, try to delete host cached resource.
	if ( mResource != _null )
	{
		ISkeleton* res = mResource;
		GetModelFactory( ).ReleaseSkeleton( res );
	}
	// This is cached resource, remove from cache.
	else if ( IsResNameBlank( ) == _false )
	{
		GetResourceCache( ).ReleaseCache( IResourceCache::_RES_SKELETON, GetResName( ) );
	}
}

IBone* Skeleton::CreateBone( StringPtr name, _dword parentid, _bool dummy )
{
	if ( parentid != -1 )
	{
		// Bad parent id.
		if ( mBones.IsIndexValid( (_long) parentid ) == _false )
			return _null;
	}

	// Create bone use memory buffer.
	Bone* bone = new ( mMemoryBuffer.BufferAlloc( sizeof( Bone ) ) ) Bone( this, name, mBones.Length( ), parentid, dummy );
	mBones.Add( bone );

	return bone;
}

_void Skeleton::ReleaseBone( IBone*& bone )
{
	if ( bone == _null )
		return;

	_dword boneid = bone->GetBoneID( );

	if ( GetBone( boneid ) != bone )
		return;

	// Remove child of this bone.
	for ( _long i = boneid + 1; i < mBones.Length( ); i ++ )
	{
		if ( mBones[i]->mParentID == boneid )
		{
			IBone* c = mBones[i];
			ReleaseBone( c );
		}
	}

	// Delete use memory buffer.
	mBones[ boneid ]->Bone::~Bone( );
	mMemoryBuffer.BufferFree( mBones[ boneid ] );

	// Remove from bone array.
	mBones.RemoveAt( boneid );

	bone = _null;

	// Adjust parent ID.
	for ( _long i = boneid; i < mBones.Length( ); i ++ )
	{
		if ( mBones[i]->mParentID != -1 && mBones[i]->mParentID > boneid )
			mBones[i]->mParentID --;
	}
}

_void Skeleton::ClearBone( )
{
	for ( _long i = 0; i < mBones.Length( ); i ++ )
	{
		// Delete use memory buffer.
		mBones[i]->Bone::~Bone( );
		mMemoryBuffer.BufferFree( mBones[i] );
	}

	mBones.Clear( );
}

IBone* Skeleton::GetBone( StringPtr name ) const
{
	for ( _long i = 0; i < mBones.Length( ); i ++ )
	{
		if ( mBones[i]->GetName( ) == name )
			return mBones[i];
	}

	return _null;
}
