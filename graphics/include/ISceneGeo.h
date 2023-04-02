#pragma once

namespace Xixels
{

class ISceneGeo
{
public:

public:
	virtual const Light**	GetPointLights( ) = 0;

	virtual ISceneNode*		GetParent( ) = 0;
	virtual const Geometry&	GetGeometry( ) const = 0;
	virtual ISkeleton*		GetSkeleton( ) = 0;
	virtual Matrix4			GetMatrix( ) const = 0;

	// Set user data to resource.
	virtual _void SetUserData( _ptr userdata ) = 0;
	// Get user data from resource.
	virtual _ptr GetUserData( ) const = 0;
};

};