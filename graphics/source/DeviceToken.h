#pragma once

namespace Xixels
{

struct DeviceToken
{
	_dword	mViewportToken;
	_dword	mWorldTransToken;
	_dword	mViewTransToken;
	_dword	mProjTransToken;

	inline DeviceToken( )
		: mViewportToken( 0 ), mWorldTransToken( 0 ), mViewTransToken( 0 ), mProjTransToken( 0 ) { }
};

};