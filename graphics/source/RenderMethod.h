#pragma once

namespace Xixels
{

class RenderMethod : public IRenderMethod, public ReferencedObject
{
private:
	_bool	mDefaultMethod;

	_dword	mCullMode;
	_dword	mFillMode;
	_dword	mDepthTestFunction;
	_bool	mDepthTestEnabled;
	_bool	mDepthWriteEnabled;
	_bool	mClippingEnabled;

public:
	RenderMethod( _bool defmethod );
	~RenderMethod( );

	inline _bool IsDefaultMethod( ) const
		{ return mDefaultMethod; }

	_void	EnableMethod( ) const;
	_void	DisableMethod( ) const;

public:
	virtual _void SetCullMode( _dword value )
		{ mCullMode = value; }

	virtual _void SetFillMode( _dword value )
		{ mFillMode = value; }
	virtual _dword GetFillMode( ) const
		{ return mFillMode; }

	virtual _void SetDepthTestFunction( _dword func )
		{ mDepthTestFunction = func; }
	virtual _dword GetDepthTestFunction( ) const
		{ return mDepthTestFunction; }

	virtual _bool IsDepthTestEnabled( ) const
		{ return mDepthTestEnabled; }
	virtual _void EnableDepthTest( _bool enable )
		{ mDepthTestEnabled = enable; }

	virtual _bool IsDepthWriteEnabled( ) const
		{ return mDepthWriteEnabled; }
	virtual _void EnableDepthWrite( _bool enable )
		{ mDepthWriteEnabled = enable; }

	virtual _bool IsClippingEnabled( ) const
		{ return mClippingEnabled; }
	virtual _void EnableClipping( _bool enable )
		{ mClippingEnabled = enable; }

	virtual _dword	GetCullMode( _bool mirror ) const;
};

};