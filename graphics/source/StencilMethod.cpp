#include "StencilMethod.h"

StencilMethod::StencilMethod( _bool defmethod ) : mDoubleFace( _false )
{
	mDefaultMethod		= defmethod;
}

StencilMethod::~StencilMethod( )
{
}

_void StencilMethod::EnableStencil( _dword ffunc, _dword fpass, _dword ffail, _dword fzfail )
{
	mFrontFaceStencilOP.mStencilFunc = ffunc;
	mFrontFaceStencilOP.mStencilPassOP = fpass;
	mFrontFaceStencilOP.mStencilFailOP = ffail;
	mFrontFaceStencilOP.mStencilDepthFailedOP = fzfail;

	mDoubleFace = _false;
}

_void StencilMethod::EnableStencil( _dword ffunc, _dword fpass, _dword ffail, _dword fzfail, _dword bfunc, _dword bpass, _dword bfail, _dword bzfail )
{
	mFrontFaceStencilOP.mStencilFunc = ffunc;
	mFrontFaceStencilOP.mStencilPassOP = fpass;
	mFrontFaceStencilOP.mStencilFailOP = ffail;
	mFrontFaceStencilOP.mStencilDepthFailedOP = fzfail;
	mBackFaceStencilOP.mStencilFunc = bfunc;
	mBackFaceStencilOP.mStencilPassOP = bpass;
	mBackFaceStencilOP.mStencilFailOP = bfail;
	mBackFaceStencilOP.mStencilDepthFailedOP = bzfail;

	mDoubleFace = _true;
}

_void StencilMethod::EnableMethod( ) const
{
	if ( mDoubleFace )
		GetRenderer( ).EnableStencil( mFrontFaceStencilOP.mStencilFunc, mFrontFaceStencilOP.mStencilPassOP, mFrontFaceStencilOP.mStencilFailOP, mFrontFaceStencilOP.mStencilDepthFailedOP,
			mBackFaceStencilOP.mStencilFunc, mBackFaceStencilOP.mStencilPassOP, mBackFaceStencilOP.mStencilFailOP, mBackFaceStencilOP.mStencilDepthFailedOP);
	else
		GetRenderer( ).EnableStencil( mFrontFaceStencilOP.mStencilFunc, mFrontFaceStencilOP.mStencilPassOP, mFrontFaceStencilOP.mStencilFailOP, mFrontFaceStencilOP.mStencilDepthFailedOP );
}