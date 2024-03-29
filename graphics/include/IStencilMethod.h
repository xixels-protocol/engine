#pragma once

namespace Xixels
{

class IStencilMethod
{
public:
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

	enum _STENCILOP
	{
		_STENCILOP_KEEP				= 1,
		_STENCILOP_ZERO				= 2,
		_STENCILOP_REPLACE			= 3,
		_STENCILOP_INCREASE_CLAMP	= 4,
		_STENCILOP_DECREASE_CLAMP	= 5,
		_STENCILOP_INVERT			= 6,
		_STENCILOP_INCREASE_WRAP	= 7,
		_STENCILOP_DECREASE_WRAP	= 8,
	};
};

};