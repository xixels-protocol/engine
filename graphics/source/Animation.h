#pragma once

namespace Xixels
{

class Animation
{
protected:
	_dword	mPlayMode;
	_dword	mDuration;
	_dword	mCurrent;
	_float	mSpeed;

	_bool	mReachEnd;
	_float	mAdjustElapse;

protected:
	Animation( );
	Animation( Animation* anima );
	~Animation( );

	_bool	ReadyForUpdate( _dword& elapse );
	_void	Update( _dword elapse );
};

};

#define _IMPLEMENT_ANIMAION \
	virtual _void SetDuration( _dword duration ) \
		{ mDuration = duration; } \
	virtual _dword GetDuration( ) const \
		{ return mDuration; } \
	virtual _dword GetCurrent( ) const \
		{ return mCurrent; } \
	virtual _void SetPlayMode( _dword mode ) \
		{ mPlayMode = mode; } \
	virtual _dword GetPlayMode( ) const \
		{ return mPlayMode; } \
	virtual _void SetSpeed( _float speed ) \
		{ mSpeed = speed; } \
	virtual _float GetSpeed( ) const \
		{ return mSpeed; } \
	virtual _bool ReachEnd( ) const \
		{ return mReachEnd; } \
	virtual _void Reset( ) \
		{ mCurrent = 0; mReachEnd = _false; mAdjustElapse = 0.0f; }
