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
	// ClearBones.
	
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