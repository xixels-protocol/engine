#pragma once

namespace Xixels
{

class IShaderConst
{
public:
	virtual _void	SetTransform( _dword index, _dword trans ) = 0;

	virtual _void	SetColor( _dword index, const Color& con, _bool gamma = _false ) = 0;
	virtual _void	SetFloat( _dword index, _float con ) = 0;
	virtual _void	SetVector2( _dword index, const Vector2& con ) = 0;
	virtual _void	SetVector3( _dword index, const Vector3& con ) = 0;
	virtual _void	SetVector4( _dword index, const Vector4& con ) = 0;
	virtual _void	SetMatrix4( _dword index, const Matrix4& con ) = 0;
	virtual _void	SetVector4Array( _dword index, const Vector4* vecs, _dword count ) = 0;
};

};