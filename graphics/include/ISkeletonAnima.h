#pragma once

namespace Xixels
{

class ISkeletonAnima : public IAnimation
{
public:
	// Create an anima track, each track affect a bone of skeleton.
	virtual ISkeletonAnimaTrack*		CreateTrack( _dword trackid, _dword offset, _dword length ) = 0;
	// Remove a track.
	virtual _void						ReleaseTrack( _dword index ) = 0;
	// Clear all track.
	virtual _void						ClearTrack( ) = 0;

	// Get count of track.
	virtual _dword						GetTrackCount( ) const = 0;
	// Get track by index.
	virtual ISkeletonAnimaTrack*		GetTrack( _dword index ) const = 0;
};

};