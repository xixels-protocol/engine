#pragma once

namespace Xixels
{

class ShaderReflectionFactory
{
public:
	ShaderReflectionFactory( )
		{ }
	~ShaderReflectionFactory( );

	struct RefPoolNode
	{
		Stack< IShaderReflection* > mSta;
		_dword						mId = 0;

		inline operator _dword( ) const
			{ return mId; }
	};

	IShaderReflection* Pop( _dword id );
	_void Push( IShaderReflection* ref );

private:
	SortArray< RefPoolNode, _dword > mPool;
};

};