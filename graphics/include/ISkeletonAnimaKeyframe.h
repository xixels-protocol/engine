#pragma once

namespace Xixels
{

class ISkeletonAnimaKeyframe
{
public:
	// Get time of keyframe, from 0 to 1.
	virtual _float				GetTime( ) const = 0;

	// Set bone translation of keyframe.
	virtual _void				SetBoneTranslation( const Vector3& t ) = 0;
	// Get bone translation of keyframe.
	virtual const Vector3&		GetBoneTranslation( ) const = 0;

	// Set bone rotation of keyframe.
	virtual _void				SetBoneRotation( const Quaternion& r ) = 0;
	// Get bone rotation of keyframe.
	virtual const Quaternion&	GetBoneRotation( ) const = 0;

	// Set bone translation of keyframe.
	virtual _void				SetBoneScaling( const Vector3& s ) = 0;
	// Get bone translation of keyframe.
	virtual const Vector3&		GetBoneScaling( ) const = 0;

	// Get absolute transform of bone.
	virtual Matrix4				GetBoneTransform( ) const = 0;

	// Precompute params of interpolation.
	virtual _void				PrecomputeParams( const Vector3& t, const Quaternion& r, const Vector3& s ) = 0;
};

};