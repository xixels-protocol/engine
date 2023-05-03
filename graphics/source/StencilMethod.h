#pragma once

namespace Xixels
{

class StencilMethod : public IStencilMethod, public ReferencedObject
{
private:
	struct StencilOP
	{
		_dword	mStencilFailOP;
		_dword	mStencilDepthFailedOP;
		_dword	mStencilPassOP;
		_dword	mStencilFunc;

		StencilOP( )
			: mStencilFailOP( _STENCILOP_KEEP ), mStencilDepthFailedOP( _STENCILOP_KEEP ), mStencilPassOP( _STENCILOP_KEEP ), mStencilFunc( _COMPAREFUNC_ALWAYS )
			{ }
	};

	_bool		mDefaultMethod;

	StencilOP	mFrontFaceStencilOP;
	StencilOP	mBackFaceStencilOP;
	_bool		mDoubleFace;

public:
	StencilMethod( _bool defmethod );
	~StencilMethod( );

	inline _bool IsDefaultMethod( ) const
		{ return mDefaultMethod; }

	inline _void DisableMethod( ) const
		{ GetRenderer( ).DisableStencil( ); }

	_void	EnableStencil( _dword ffunc, _dword fpass, _dword ffail, _dword fzfail );
	_void	EnableStencil( _dword ffunc, _dword fpass, _dword ffail, _dword fzfail, _dword bfunc, _dword bpass, _dword bfail, _dword bzfail );

	_void	EnableMethod( ) const;

};

};