#pragma once

namespace Xixels
{

struct PrimaryKey;

class IVertexMethod
{
public:
	virtual _bool	IsReady( ) const = 0;
	virtual _bool	SetShader( _void* shaderobj = _null ) = 0;

	virtual _void				SetContext( ShaderContext* sc ) = 0;
	virtual ShaderContext*		GetContext( ) const = 0;
	virtual IShaderReflection*	GetReflection( ) = 0;

	virtual _void				SetPrimaryKey( const PrimaryKey& key ) = 0;
	virtual const PrimaryKey&	GetPrimaryKey( ) const = 0;
};

};