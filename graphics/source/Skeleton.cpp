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
	ClearAnimas( );
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

_void Skeleton::UpdateSkinTransform( )
{
	// Set skin transform, must be align of 16.
	if ( mSkinTransform == _null )
	{
		mSkinBuffer = new _byte[sizeof( Matrix3x4 ) * mSkinBoneCount + sizeof( _float4 )];
		mSkinTransform = (Matrix3x4*) ( mSkinBuffer + sizeof( _float4 ) - (_ptr) mSkinBuffer % sizeof( _float4 ) );
	}

	for ( _long i = 0; i < mBones.Length( ); i ++ )
	{
		Bone* bone = mBones[i];
		if ( bone->mDummy )
			continue;

		if ( bone->mScaling.Equal( Vector3::cIdentity ) == _false )
		{
			// TODO, better way than matrix transform.

			Matrix4 mat1;
			mat1.Compose( bone->mBoneSpaceTranslation, bone->mBoneSpaceRotation, Vector3::cIdentity );

			Matrix4 mat2;
			mat2.Compose( bone->mTranslation, bone->mRotation, bone->mScaling );

			mSkinTransform[i].Compose( mat1 * mat2 );
		}
		else
		{
			Vector3 bonetranslation = bone->mBoneSpaceTranslation;
			bonetranslation *= bone->mRotation;
			bonetranslation += bone->mTranslation;

			mSkinTransform[i].Compose( bonetranslation, bone->mBoneSpaceRotation * bone->mRotation, Vector3::cIdentity );
		}
	}
}

_void Skeleton::UpdateBoundBox( )
{
}

_void Skeleton::UpdateBones( _dword elapse )
{
	// Skeleton dont need update.
	if ( mNeedToUpdate == _false && elapse == 0 )
		return;

	if ( mNeedToUpdate )
	{
		for ( _long i = 0; i < mBones.Length( ); i ++ )
			mBones[i]->mScaled = _false;

		// Update affecting animas.
		for ( _long i = 0; i < mAffectAnimas.Length( ); i ++ )
		{
			AffectAnima& aa = mAffectAnimas[i];

			// Skip empty animation.
			if ( aa.mAnima->IsReady( _true ) == _false )
				continue;

			( (SkeletonAnima*) aa.mAnima )->UpdateTracks( aa.mTime, aa.mWeight, this );

			GetModelFactory( ).ReleaseSkeletonAnima( aa.mAnima );
			mAffectAnimas.RemoveAt( i -- );
		}

		// If any animation left, need to update next time.
		mNeedToUpdate = mAffectAnimas.Length( ) != 0;

		// Update each bone.
		for ( _long i = 0; i < mBones.Length( ); i ++ )
		{
			Bone* bone = mBones[i];

			_bool root = mBones.IsIndexValid( (_long) bone->mParentID ) == _false;

			Vector3		retposition = bone->mRelativeTranslation;
			Quaternion	retrotation = bone->mRelativeRotation;
			Vector3		bonescaling = Vector3::cIdentity;
			Quaternion	worldrotation = Quaternion::cIdentity;

			// Root bone.
			if ( root )
			{
				bone->mTranslation = retposition;
				bone->mRotation = retrotation;
			}
			// Child bone, make absolute transform from parent bone.
			else
			{
				Bone* parent = mBones[bone->mParentID];

				bone->mTranslation = retposition * parent->mScaling;
				bone->mTranslation *= parent->mRotation;
				bone->mTranslation += parent->mTranslation;

				bone->mRotation = retrotation * parent->mRotation;
			}

			// Set scaling.
			if ( bone->mScaled )
				bone->mScaling *= bonescaling;
			else
				bone->mScaling = bonescaling;

			if ( mSklInfUsing != _null && worldrotation != Quaternion::cIdentity )
				bone->mRotation *= worldrotation;

			if ( bone->mDummy )
				continue;
		}
	}

	UpdateSkinTransform( );
	UpdateBoundBox( );
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

	// Bone changed, need to update.
	mNeedToUpdate = _true;

	if ( dummy == _false )
		mSkinBoneCount ++;

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
	if ( mBones[ boneid ]->IsDummy( ) == _false )
		mSkinBoneCount --;

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

_void Skeleton::UsingSkeleton( _dword priority )
{
	if ( mResource != _null )
	{
		mResource->UsingSkeleton( priority );
	}
	else
	{
		UsingResource( priority );

		for ( _long i = 0; i < mAffectAnimas.Length( ); i ++ )
		{
			AffectAnima& aa = mAffectAnimas[i];

			( (SkeletonAnima*) aa.mAnima )->UsingAnima( priority );
		}
	}
}

_void Skeleton::ClearAnimas( )
{
	// Unref affecting animas.
	for ( _long i = 0; i < mAffectAnimas.Length( ); i ++ )
		GetModelFactory( ).ReleaseSkeletonAnima( mAffectAnimas[i].mAnima );

	mAffectAnimas.Clear( _true );
}
