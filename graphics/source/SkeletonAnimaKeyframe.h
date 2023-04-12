#pragma once

namespace Xixels
{

class SkeletonAnimaKeyframe : public ISkeletonAnimaKeyframe
{
public:
	_float		mTime;
	Vector3		mTranslation;
	Quaternion	mRotation;
	Vector3		mScaling;

	Vector3		mPrecomputeTranslationLerp;
	_float		mPrecomputeDot;
	_float		mPrecomputeTheta;
	_float		mPrecomputeRecipsqrt;
	Vector3		mPrecomputeScalingLerp;
	
	_bool		mNeedScaling;

public:
	inline SkeletonAnimaKeyframe( ) : mTime( 0.0f ), mTranslation( Vector3::cOrigin ), mRotation( Quaternion::cIdentity ), 
		mScaling( Vector3::cIdentity ), mPrecomputeTranslationLerp( Vector3::cOrigin ), mPrecomputeDot( 0.0f ), mPrecomputeTheta( 0.0f ), 
		mPrecomputeRecipsqrt( 0.0f ), mPrecomputeScalingLerp( Vector3::cOrigin ), mNeedScaling( _false ) { }

	inline SkeletonAnimaKeyframe( _float time ) : mTime( time ), mTranslation( Vector3::cOrigin ), mRotation( Quaternion::cIdentity ), 
		mScaling( Vector3::cIdentity ), mPrecomputeTranslationLerp( Vector3::cOrigin ), mPrecomputeDot( 0.0f ), mPrecomputeTheta( 0.0f ), 
		mPrecomputeRecipsqrt( 0.0f ), mPrecomputeScalingLerp( Vector3::cOrigin ), mNeedScaling( _false ) { }

	inline operator _float ( ) const
		{ return mTime; }

public:
	virtual _float GetTime( ) const
		{ return mTime; }

	virtual _void SetBoneTranslation( const Vector3& t )
		{ mTranslation = t; }
	virtual const Vector3& GetBoneTranslation( ) const
		{ return mTranslation; }

	virtual _void SetBoneRotation( const Quaternion& r )
		{ mRotation = r; }
	virtual const Quaternion& GetBoneRotation( ) const
		{ return mRotation; }

	virtual _void SetBoneScaling( const Vector3& s )
		{ mScaling = s; }
	virtual const Vector3& GetBoneScaling( ) const
		{ return mScaling; }

	virtual Matrix4 GetBoneTransform( ) const
		{ return Matrix4( ).Compose( mTranslation, mRotation, mScaling ); }

	virtual _void	PrecomputeParams( const Vector3& t, const Quaternion& r, const Vector3& s );
};

};