#include "SkeletonAnimaKeyframe.h"

_void SkeletonAnimaKeyframe::PrecomputeParams( const Vector3& t, const Quaternion& r, const Vector3& s )
{
	mPrecomputeTranslationLerp = t - mTranslation;
	Quaternion::PrecomputeSlerpParams( mRotation, r, mPrecomputeDot, mPrecomputeTheta, mPrecomputeRecipsqrt );
	if ( mScaling.Equal( s ) == _false )
	{
		mPrecomputeScalingLerp = s - mScaling;
		mNeedScaling = _true;
	}
}