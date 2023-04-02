#pragma once

namespace Xixels
{

class IMeshAnimaTrack
{
public:
	// Get track id.
	virtual _dword				GetTrackID( ) const = 0;
	// Get vertex format of track.
	virtual _dword				GetVertexFormat( ) const = 0;
	// Get vertex count of track.
	virtual _dword				GetVertexCount( ) const = 0;

	// Create a keyframe of track.
	virtual IMeshAnimaKeyframe* CreateKeyframe( _float time ) = 0;
	// Release a keyframe of track.
	virtual _void				ReleaseKeyframe( IMeshAnimaKeyframe*& frame ) = 0;
	// Clear all keyframe of track.
	virtual _void				ClearKeyframe( ) = 0;

	// Get count of keyframe.
	virtual _dword				GetKeyframeCount( ) const = 0;
	// Get keyframe by index.
	virtual IMeshAnimaKeyframe*	GetKeyframe( _dword index ) const = 0;

	// Attach track to geometry.
	virtual _void				AttachGeometry( const Geometry& geo ) = 0;
	// Detach track from geometry.
	virtual _void				DetachGeometry( ) = 0;
};

};