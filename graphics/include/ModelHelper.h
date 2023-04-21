#pragma once

namespace Xixels
{

class ModelHelper
{
public:
	static _dword			GetVertexSize( _dword format );
	static _dword			GetVertexSrcSize( _dword format );
	static _dword			GetHelperSize( _dword format );
	static _dword			GetHelperRefSize( _dword format );
	static _dword			GetHelperBufferSize( _dword format, _dword vnumber );

	static _dword			GetTexcoordCount( _dword format );
	static _dword			GetTexcoordFlag( _dword index );
};

};