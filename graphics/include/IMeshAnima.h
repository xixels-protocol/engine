#pragma once

namespace Xixels
{

class IMeshAnima : public IAnimation
{
public:
	// Create an anima track, each track affect a geometry.
	virtual IMeshAnimaTrack*	CreateTrack( _dword trackid, _dword format, _dword vertex ) = 0;
	// Release an anima track.
	virtual _void				ReleaseTrack( IMeshAnimaTrack*& track ) = 0;
	// Clear all track.
	virtual _void				ClearTrack( ) = 0;

	// Get count of track.
	virtual _dword				GetTrackCount( ) const = 0;
	// Get track by index.
	virtual IMeshAnimaTrack*	GetTrack( _dword index ) const = 0;

	// Attach animation to mesh.
	virtual _void				AttachMesh( IMesh* mesh ) = 0;
	// Detach animation from mesh.
	virtual _void				DetachMesh( ) = 0;
};

};