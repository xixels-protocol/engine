#pragma once

namespace Xixels
{

class ILightNode
{
public:
	// Set user data to lightnode.
	virtual _void			SetUserData( _ptr userdata ) = 0;
	// Get user data from lightnode.
	virtual _ptr			GetUserData( ) const = 0;
	// Get light.
	virtual const Light*	GetLight( ) const = 0;
};

};