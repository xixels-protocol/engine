#pragma once

namespace Xixels
{

class Animation
{
protected:
	_dword	mDuration;
	_dword	mCurrent;
	_float	mSpeed;

protected:
	Animation( );
	Animation( Animation* anima );
	~Animation( );

	_void	Update( _dword elapse );
};

};
