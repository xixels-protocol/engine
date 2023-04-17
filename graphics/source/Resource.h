#pragma once

namespace Xixels
{

class Resource
{
protected:
	String			mName;
	String			mResName;
	_ptr			mUserData;

public:
	inline Resource( )
		: mUserData( 0 ) { }

	~Resource( );
};