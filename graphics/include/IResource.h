#pragma once

namespace Xixels
{

class IResource
{
public:
	// Set logic name.
	virtual _void		SetName( StringPtr name ) = 0;
	// Get logic name.
	virtual StringPtr	GetName( ) const = 0;

	// Set resource name.
	virtual _void		SetResName( StringPtr name ) = 0;
	// Get resource name.
	virtual StringPtr	GetResName( ) const = 0;

	// Set user data to resource.
	virtual _void		SetUserData( _ptr userdata ) = 0;
	// Get user data from resource.
	virtual _ptr		GetUserData( ) const = 0;

	// Check if resource is ready.
	virtual _bool		IsReady( _bool checktex = _true ) const = 0;
};

};