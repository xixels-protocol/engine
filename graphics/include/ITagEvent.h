#pragma once

namespace Xixels
{

class ITagEvent
{
public:
	// Get event time.
	virtual _float			GetTime( ) const = 0;

	// Set logic name.
	virtual _void			SetName( StringPtr name ) = 0;
	// Get logic name.
	virtual StringPtr		GetName( ) const = 0;

	// Set event position.
	virtual _void			SetPosition( const Vector3& pos ) = 0;
	// Get event position.
	virtual const Vector3&	GetPosition( ) const = 0;

	// Set userdata to event.
	virtual _void			SetUserData( _ptr userdata ) = 0;
	// Get userdata from event.
	virtual _ptr			GetUserData( ) const = 0;
};

};