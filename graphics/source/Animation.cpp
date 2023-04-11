#include "Animation.h"

Animation::Animation( ) : mPlayMode( 0 ), mDuration( 0 ), mCurrent( 0 ),
	mSpeed( 1.0f ), mReachEnd( _false ), mAdjustElapse( 0.0f )
{
}

Animation::Animation( Animation* anima ) : mPlayMode( anima->mPlayMode ), mDuration( anima->mDuration ),
	mCurrent( 0 ), mSpeed( 1.0f ), mReachEnd( _false ), mAdjustElapse( 0.0f )
{
}

Animation::~Animation( )
{
}

_bool Animation::ReadyForUpdate( _dword& elapse )
{
	if ( mDuration == 0 )
		return _false;

	if ( elapse == -1 )
	{
		elapse			= 0;
		mAdjustElapse	= 0.0f;

		return _true;
	}

	if ( mPlayMode == IAnimation::_PLAY_PAUSE )
		return _false;

	if ( mPlayMode == IAnimation::_PLAY_FORWARD_ONCE )
	{
		if ( mCurrent == mDuration )
			return _false;
	}
	else if ( mPlayMode == IAnimation::_PLAY_BACKWARD_ONCE )
	{
		if ( mCurrent == 0 )
			return _false;
	}

	// Adjust by speed.
	if ( mSpeed != 1.0f )
	{
		_float e = elapse * mSpeed + mAdjustElapse;
		elapse = (_dword) e;
		mAdjustElapse = e - (_float) elapse;
	}

	return elapse > 0;
}

_void Animation::Update( _dword elapse )
{
	if ( mDuration == 0 )
		return;

	_bool backward = mPlayMode == IAnimation::_PLAY_BACKWARD_ONCE || mPlayMode == IAnimation::_PLAY_BACKWARD_LOOP;

	_dword current = backward ? mDuration - mCurrent : mCurrent;

	current += elapse;

	mReachEnd = current >= mDuration;
	if ( mReachEnd )
	{
		switch ( mPlayMode )
		{
			case IAnimation::_PLAY_FORWARD_ONCE:
			case IAnimation::_PLAY_BACKWARD_ONCE:
			{
				current = mDuration;
				break;
			}

			case IAnimation::_PLAY_FORWARD_LOOP:
			case IAnimation::_PLAY_BACKWARD_LOOP:
			{
				current %= mDuration;
				break;
			}
		}
	}

	mCurrent = backward ? mDuration - current : current;
}