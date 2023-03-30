#pragma once

namespace Xixels
{

class ISkeleton : public IResource
{
public:
	// Create a bone.
	virtual IBone*					CreateBone( StringPtr name, _dword parentid = -1, _bool dummy = _false ) = 0;
	// Release a bone ( or dummy ).
	virtual _void					ReleaseBone( IBone*& bone ) = 0;
	// Clear all bone.
	virtual _void					ClearBone( ) = 0;

	// Get count of bone ( includes dummy ).
	virtual _dword					GetBoneCount( ) const = 0;
	// Get bone by index.
	virtual IBone*					GetBone( _dword index ) const = 0;
	// Get bone by name.
	virtual IBone*					GetBone( StringPtr name ) const = 0;
 
	// Set skeleton influence.
	virtual _void					SetInfluence( ISkeletonInf* inf ) = 0;
	// Get the skeleton influence current using.
	virtual ISkeletonInf*			GetInfluence( ) = 0;

	// Set frame token of skeleton ( used for clipping ).
	virtual _void					SetFrameToken( _dword token ) = 0;
	// Get frame token of skeleton.
	virtual _dword					GetFrameToken( ) const = 0;

	// Get the count of skin bone ( with skinning matrix, affect skin mesh ).
	virtual _dword					GetSkinBoneCount( ) const = 0;

	virtual _void					TransferSkinTransform( Geometry& geo ) const = 0;

	// Skining a geometry as skin.
	virtual _void					Skinning( Geometry& geo ) = 0;

	// Get the bound box of skeleton.
	virtual const AxisAlignedBox&	GetBoundBox( ) const = 0;
};

};