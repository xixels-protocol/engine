#pragma once

namespace Xixels
{

class ISkeleton;

class IBone
{
public:
	// Set name of bone.
	virtual _void				SetName( StringPtr name ) = 0;
	// Get name of bone.
	virtual StringPtr			GetName( ) const = 0;

	// Set user data to bone.
	virtual _void				SetUserData( _ptr userdata ) = 0;
	// Get user data from bone.
	virtual _ptr				GetUserData( ) const = 0;

	// Get host skeleton.
	virtual ISkeleton*			GetHostSkeleton( ) const = 0;

	// Get id of bone.
	virtual _dword				GetBoneID( ) const = 0;
	// Get id of parent, root bone's parent id is -1.
	virtual _dword				GetParentID( ) const = 0;
	// Get if the bone is a dummy ( not affect skin ).
	virtual _bool				IsDummy( ) const = 0;

	// Set size of bone.
	virtual _void				SetSize( _float size ) = 0;
	// Get size of bone.
	virtual _float				GetSize( ) const = 0;

	// Set init translation of bone ( start pose ).
	virtual _void				SetInitTranslation( const Vector3& t ) = 0;
	// Get init translation of bone ( start pose ).
	virtual const Vector3&		GetInitTranslation( ) const = 0;

	// Set init rotation of bone ( start pose ).
	virtual _void				SetInitRotation( const Quaternion& r ) = 0;
	// Get init rotation of bone ( start pose ).
	virtual const Quaternion&	GetInitRotation( ) const = 0;

	// Set relative translation of bone.
	virtual _void				SetRelativeTranslation( const Vector3& t ) = 0;
	// Get relative translation of bone.
	virtual const Vector3&		GetRelativeTranslation( ) const = 0;

	// Set relative rotation of bone.
	virtual _void				SetRelativeRotation( const Quaternion& r ) = 0;
	// Get relative rotation of bone.
	virtual const Quaternion&	GetRelativeRotation( ) const = 0;

	// Set bone-space translation of bone, for skinning.
	virtual _void				SetBoneSpaceTranslation( const Vector3& t ) = 0;
	// Get bone-space translation of bone, for skinning.
	virtual const Vector3&		GetBoneSpaceTranslation( ) const = 0;

	// Set bone-space rotation of bone, for skinning.
	virtual _void				SetBoneSpaceRotation( const Quaternion& r ) = 0;
	// Get bone-space rotation of bone, for skinning.
	virtual const Quaternion&	GetBoneSpaceRotation( ) const = 0;

	// Get absolute translation of bone.
	virtual const Vector3&		GetTranslation( ) const = 0;
	// Get absolute rotation of bone.
	virtual const Quaternion&	GetRotation( ) const = 0;

	// Set absolute scaling of bone.
	virtual _void				SetScaling( const Vector3& s ) = 0;
	// Get absolute scaling of bone.
	virtual const Vector3&		GetScaling( ) const = 0;

	// Get absolute transform of bone.
	virtual Matrix4				GetTransform( ) const = 0;

};

};