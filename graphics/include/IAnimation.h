#pragma once

namespace Xixels
{

class IAnimation : public IResource
{
public:
	enum _ANIMATION_TYPE
	{
		_MESH_ANIMATION		= 1,
		_SKELETON_ANIMATION	= 2,
	};

	enum _PLAY_MODE
	{
		_PLAY_FORWARD_ONCE	= 0,
		_PLAY_FORWARD_LOOP	= 1,
		_PLAY_BACKWARD_ONCE	= 2,
		_PLAY_BACKWARD_LOOP	= 3,
		_PLAY_PAUSE			= 4,
	};

public:
	// Get type of animation.
	virtual _dword			GetType( ) const = 0;

	// Set duration of animation.
	virtual _void			SetDuration( _dword duration ) = 0;
	// Get duration of animation.
	virtual _dword			GetDuration( ) const = 0;

	// Set current time of animation.
	virtual _void			SetCurrent( _dword current, ISkeleton* skeleton = _null, _float weight = 1.0f ) = 0;
	// Get current time of animation.
	virtual _dword			GetCurrent( ) const = 0;

	// Set play mode of animation.
	virtual _void			SetPlayMode( _dword mode ) = 0;
	// Get play mode of animation.
	virtual _dword			GetPlayMode( ) const = 0;

	// Set speed of animation.
	virtual _void			SetSpeed( _float speed ) = 0;
	// Get speed of animation.
	virtual _float			GetSpeed( ) const = 0;

	// Get if animation reached end after update.
	virtual _bool			ReachEnd( ) const = 0;

	// Reset animation.
	virtual _void			Reset( ) = 0;

	// Update animation, and affect on skeleton or geometry.
	virtual _void			Update( _dword elapse, ISkeleton* skeleton = _null, _float weight = 1.0f ) = 0;
};

};