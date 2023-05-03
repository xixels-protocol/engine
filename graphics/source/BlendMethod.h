#pragma once

namespace Xixels
{

class BlendMethod : public IBlendMethod, public ReferencedObject
{
private:
	_bool	mDefaultMethod;
	_dword	mRenderOrder;

	_dword	mColorBlendFunc;
	_dword	mColorBlendSrc;
	_dword	mColorBlendDes;

	_dword	mAlphaBlendFunc;
	_dword	mAlphaBlendSrc;
	_dword	mAlphaBlendDes;

	_bool	mColorWrite;
	_bool	mAlphaWrite;

public:
	BlendMethod( _bool defmethod );
	~BlendMethod( );

	inline _bool IsDefaultMethod( ) const
		{ return mDefaultMethod; }

	_void	EnableMethod( ) const;
	_void	DisableMethod( ) const;

public:
	virtual _dword GetRenderOrder( ) const
		{ return mRenderOrder; }
	virtual _void SetRenderOrder( _dword value )
		{ mRenderOrder = value; }

	virtual _bool IsColorBlendEnabled( ) const
		{ return mColorBlendFunc != 0; }
	virtual _void EnableColorBlend( _dword func, _dword src, _dword des )
		{ mColorBlendFunc = func; mColorBlendSrc = src; mColorBlendDes = des; }
	virtual _void DisableColorBlend( )
		{ mColorBlendFunc = mColorBlendSrc = mColorBlendDes = 0; }
	virtual _void GetColorBlend( _dword& func, _dword& src, _dword& des ) const
		{ func = mColorBlendFunc; src = mColorBlendSrc; des = mColorBlendDes; }

	virtual _bool IsAlphaBlendEnabled( ) const
		{ return mAlphaBlendFunc != 0; }
	virtual _void EnableAlphaBlend( _dword func, _dword src, _dword des )
		{ mAlphaBlendFunc = func; mAlphaBlendSrc = src; mAlphaBlendDes = des; }
	virtual _void DisableAlphaBlend( )
		{ mAlphaBlendFunc = mAlphaBlendSrc = mAlphaBlendDes = 0; }
	virtual _void GetAlphaBlend( _dword& func, _dword& src, _dword& des ) const
		{ func = mAlphaBlendFunc; src = mAlphaBlendSrc; des = mAlphaBlendDes; }

	virtual _bool IsColorWriteEnabled( ) const
		{ return mColorWrite; }
	virtual _void EnableColorWrite( )
		{ mColorWrite = _true; }
	virtual _void DisableColorWrite( )
		{ mColorWrite = _false; }

	virtual _bool IsAlphaWriteEnabled( ) const
		{ return mAlphaWrite; }
	virtual _void EnableAlphaWrite( )
		{ mAlphaWrite = _true; }
	virtual _void DisableAlphaWrite( )
		{ mAlphaWrite = _false; }
};

};