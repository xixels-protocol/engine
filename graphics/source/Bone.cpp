#include "Bone.h"

Bone::Bone( Skeleton* skl, StringPtr name, _dword boneid, _dword parentid, _bool dummy )
	: mHostSkeleton( skl ), mName( name ), mUserData( 0 ), mBoneID( boneid ), mParentID( parentid ), mDummy( dummy ), 
	mSize( 0.0f ), mBoundSize( 0.0f ), mScaled( _false )
{
	mInitTranslation = mRelativeTranslation = mBoneSpaceTranslation = mTranslation = Vector3::cOrigin;
	mInitRotation = mRelativeRotation = mBoneSpaceRotation = mRotation = Quaternion::cIdentity;
	mScaling = mLastScaling = Vector3::cIdentity;
}

ISkeleton* Bone::GetHostSkeleton( ) const
{
	return mHostSkeleton;
}

_void Bone::SetSize( _float size )
{
	if ( size > 0.0f && mSize <= 0.0f )
		mHostSkeleton->AddBigBone( );

	if ( mSize > 0.0f && size <= 0.0f )
		mHostSkeleton->DelBigBone( );

	mSize = size;
}

_void Bone::SetRelativeTranslation( const Vector3& t )
{
	mHostSkeleton->NeedToUpdate( );
	mTranslation = mRelativeTranslation = t;
}

const Vector3& Bone::GetRelativeTranslation( ) const
{
	mHostSkeleton->UpdateBones( );
	return mRelativeTranslation;
}

_void Bone::SetRelativeRotation( const Quaternion& r )
{
	mHostSkeleton->NeedToUpdate( );
	mRotation = mRelativeRotation = r;
}

const Quaternion& Bone::GetRelativeRotation( ) const
{
	mHostSkeleton->UpdateBones( );
	return mRelativeRotation;
}

_void Bone::SetBoneSpaceTranslation( const Vector3& t )
{
	mHostSkeleton->NeedToUpdate( );
	mBoneSpaceTranslation = t;
}

const Vector3& Bone::GetBoneSpaceTranslation( ) const
{
	mHostSkeleton->UpdateBones( );
	return mBoneSpaceTranslation;
}

_void Bone::SetBoneSpaceRotation( const Quaternion& r )
{
	mHostSkeleton->NeedToUpdate( );
	mBoneSpaceRotation = r;
}

const Quaternion& Bone::GetBoneSpaceRotation( ) const
{
	mHostSkeleton->UpdateBones( );
	return mBoneSpaceRotation;
}

const Vector3& Bone::GetTranslation( ) const
{
	mHostSkeleton->UpdateBones( );
	return mTranslation;
}

const Quaternion& Bone::GetRotation( ) const
{
	mHostSkeleton->UpdateBones( );
	return mRotation;
}

const Vector3& Bone::GetScaling( ) const
{
	mHostSkeleton->UpdateBones( );
	return mScaling;
}

Matrix4 Bone::GetTransform( ) const
{
	mHostSkeleton->UpdateBones( );
	return Matrix4( ).Compose( mTranslation, mRotation, mScaling );
}

ITagPoint* Bone::CreateTagPoint( )
{
	ITagPoint* tp = GetPhysicsFactory( ).CreateTagPoint( );
	tp->BindSkeleton( mHostSkeleton, mBoneID );

	return tp;
}
