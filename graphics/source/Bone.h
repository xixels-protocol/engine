#pragma once

namespace Xixels
{

class Skeleton;

class Bone : public IBone
{
	friend class Skeleton;
	friend class SkeletonAnima;
	friend class SkeletonAnimaTrack;

private:
	Skeleton*			mHostSkeleton;

	String				mName;
	_ptr				mUserData;
	_dword				mBoneID;
	_dword				mParentID;
	_bool				mDummy;
	_float				mSize;
	_float				mBoundSize;
	_bool				mScaled;

	Vector3				mInitTranslation;
	Quaternion			mInitRotation;

	Vector3				mRelativeTranslation;
	Quaternion			mRelativeRotation;

	Vector3				mBoneSpaceTranslation;
	Quaternion			mBoneSpaceRotation;

	Vector3				mLastScaling;

	Vector3				mTranslation;
	Quaternion			mRotation;
	Vector3				mScaling;

public:
	Bone( Skeleton* skl, StringPtr name, _dword boneid, _dword parentid, _bool dummy );

public:
	virtual _void SetName( StringPtr name )
		{ mName = name; }
	virtual StringPtr GetName( ) const
		{ return mName; }

	virtual _void SetUserData( _ptr userdata )
		{ mUserData = userdata; }
	virtual _ptr GetUserData( ) const
		{ return mUserData; }

	virtual _dword GetBoneID( ) const
		{ return mBoneID; }
	virtual _dword GetParentID( ) const
		{ return mParentID; }
	virtual _bool IsDummy( ) const
		{ return mDummy; }

	virtual _float GetSize( ) const
		{ return mSize; }
	virtual _float GetPickSize( ) const
		{ return mSize * ( mScaling.x + mScaling.y + mScaling.z ) / 3.0f; }

	virtual _void SetBoundSize( _float boundsize )
		{ mBoundSize = boundsize; }
	virtual _float GetBoundSize( ) const
		{ return mBoundSize; }

	virtual _void SetInitTranslation( const Vector3& t )
		{ mInitTranslation = t; }
	virtual const Vector3& GetInitTranslation( ) const
		{ return mInitTranslation; }

	virtual _void SetInitRotation( const Quaternion& r )
		{ mInitRotation = r; }
	virtual const Quaternion& GetInitRotation( ) const
		{ return mInitRotation; }

	virtual _void SetScaling( const Vector3& s )
		{ mScaling = mLastScaling = s; }

	virtual ISkeleton*			GetHostSkeleton( ) const;

	virtual _void				SetSize( _float size );

	virtual _void				SetRelativeTranslation( const Vector3& t );
	virtual const Vector3&		GetRelativeTranslation( ) const;

	virtual _void				SetRelativeRotation( const Quaternion& r );
	virtual const Quaternion&	GetRelativeRotation( ) const;

	virtual _void				SetBoneSpaceTranslation( const Vector3& t );
	virtual const Vector3&		GetBoneSpaceTranslation( ) const;

	virtual _void				SetBoneSpaceRotation( const Quaternion& r );
	virtual const Quaternion&	GetBoneSpaceRotation( ) const;

	virtual const Vector3&		GetTranslation( ) const;
	virtual const Quaternion&	GetRotation( ) const;
	virtual const Vector3&		GetScaling( ) const;
	virtual Matrix4				GetTransform( ) const;

	virtual ITagPoint*			CreateTagPoint( );
};

};