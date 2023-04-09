#pragma once

namespace Xixels
{

class IRenderMethod
{
public:
	enum _CULLMODE
	{
		_CULLMODE_NONE				= 1,
		_CULLMODE_CW				= 2,
		_CULLMODE_CCW				= 3,
	};

	enum _FILLMODE
	{
		_FILLMODE_POINT				= 1,
		_FILLMODE_WIREFRAME			= 2,
		_FILLMODE_SOLID				= 3,
	};

	enum _COMPAREFUNC
	{
		_COMPAREFUNC_NEVER			= 1,
		_COMPAREFUNC_LESS			= 2,
		_COMPAREFUNC_EQUAL			= 3,
		_COMPAREFUNC_LESSEQUAL		= 4,
		_COMPAREFUNC_GREATER		= 5,
		_COMPAREFUNC_NOTEQUAL		= 6,
		_COMPAREFUNC_GREATEREQUAL	= 7,
		_COMPAREFUNC_ALWAYS			= 8,
	};

public:
	virtual _void	SetCullMode( _dword value ) = 0;
	virtual _dword	GetCullMode( _bool mirror ) const = 0;

	virtual _void	SetFillMode( _dword value ) = 0;
	virtual _dword	GetFillMode( ) const = 0;

	virtual _void	SetDepthTestFunction( _dword func ) = 0;
	virtual _dword	GetDepthTestFunction( ) const = 0;

	virtual _bool	IsDepthTestEnabled( ) const = 0;
	virtual _void	EnableDepthTest( _bool enable ) = 0;

	virtual _bool	IsDepthWriteEnabled( ) const = 0;
	virtual _void	EnableDepthWrite( _bool enable ) = 0;

	virtual _bool	IsClippingEnabled( ) const = 0;
	virtual _void	EnableClipping( _bool enable ) = 0;
};

};