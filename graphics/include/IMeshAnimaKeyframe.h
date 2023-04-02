#pragma once

namespace Xixels
{

class IMeshAnimaKeyframe
{
public:
	// Get time of keyframe, from 0 to 1.
	virtual _float			GetTime( ) const = 0;
	// Get vertex format of keyframe, same as parent track.
	virtual _dword			GetVertexFormat( ) const = 0;
	// Get vertex count of keyframe, same as parent track.
	virtual _dword			GetVertexCount( ) const = 0;

	// Set vertex position of keyframe.
	virtual _void			SetVertexPosition( _dword index, const Vector3& pos ) = 0;
	// Get vertex position of keyframe.
	virtual const Vector3&	GetVertexPosition( _dword index ) const = 0;

	// Set vertex normal of keyframe.
	virtual _void			SetVertexNormal( _dword index, const Vector3& nor ) = 0;
	// Get vertex normal of keyframe.
	virtual const Vector3&	GetVertexNormal( _dword index ) const = 0;

	// Set vertex diffuse of keyframe.
	virtual _void			SetVertexDiffuse( _dword index, _dword col ) = 0;
	// Get vertex diffuse of keyframe.
	virtual _dword			GetVertexDiffuse( _dword index ) const = 0;

	// Set vertex specular of keyframe.
	virtual _void			SetVertexSpecular( _dword index, _dword col ) = 0;
	// Get vertex specular of keyframe.
	virtual _dword			GetVertexSpecular( _dword index ) const = 0;

	// Set vertex texcoord of keyframe, 1 - 4.
	virtual _void			SetVertexTexcoord( _dword index, _dword tex, const Vector2& texc ) = 0;
	// Get vertex texcoord of keyframe, 1 - 4.
	virtual const Vector2&	GetVertexTexcoord( _dword index, _dword tex ) const = 0;

	// Set vertex tangent of keyframe.
	virtual _void			SetVertexTangent( _dword index, const Vector4& tan ) = 0;
	// Get vertex tangent of keyframe.
	virtual const Vector4&	GetVertexTangent( _dword index ) const = 0;

	// Get keyframe buffer length.
	virtual _dword			GetKeyframeLength( ) const = 0;
	// Get keyframe buffer pointer.
	virtual const _byte*	GetKeyframeBuffer( ) const = 0;

	// Lock keyframe buffer to write.
	virtual _byte*			LockKeyframeBuffer( ) = 0;
};

};