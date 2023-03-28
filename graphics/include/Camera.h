#pragma once

namespace Xixels
{

class Camera
{
public:
	Vector3	eye;
	Vector3	look;
	Vector3	up;
	_float	fov;

public:
	inline Camera( )
		: eye( 100.0f, 100.0f, 100.0f ), look( 0.0f, 0.0f, 0.0f ), up( 0.0f, 0.0f, 1.0f ), fov( 58.0f ) { }
	inline Camera( const Vector3& ceye, const Vector3& clook, const Vector3& cup, _float cfov = 58.0f )
		: eye( ceye ), look( clook ), up( cup ), fov( cfov ) { }

};

};