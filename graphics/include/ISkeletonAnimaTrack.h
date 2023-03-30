#pragma once

namespace Xixels
{

class ISkeletonAnimaTrack
{
public:
	// Get track id ( bone id of attached skeleton ).
	virtual _dword					GetTrackID( ) const = 0;
	// Set track id ( should only be used in RetargetAnima ).
	virtual _void					SetTrackID( _dword trackid ) = 0;

	// Create a keyframe of track.
	virtual ISkeletonAnimaKeyframe* CreateKeyframe( _float time ) = 0;
	// Clear all keyframe of track.
	virtual _void					ClearKeyframe( ) = 0;

	// Get count of keyframe.
	virtual _dword					GetKeyframeCount( ) const = 0;
	// Get keyframe by index.
	virtual ISkeletonAnimaKeyframe*	GetKeyframe( _dword index ) const = 0;
};

};