#include "RenderMethod.h"

RenderMethod::RenderMethod( _bool defmethod )
{
	mDefaultMethod		= defmethod;

	mCullMode			= _CULLMODE_CCW;
	mFillMode			= _FILLMODE_SOLID;

	mDepthTestFunction	= _COMPAREFUNC_LESSEQUAL;

	mDepthTestEnabled	= _true;
	mDepthWriteEnabled	= _true;
	mClippingEnabled	= _true;
}

RenderMethod::~RenderMethod( )
{
}

_void RenderMethod::EnableMethod( ) const
{
	if ( mFillMode != _FILLMODE_SOLID )
		GetRenderer( ).SetFillMode( mFillMode );

	if ( mDepthTestFunction != _COMPAREFUNC_LESSEQUAL )
		GetRenderer( ).SetDepthTestFunction( mDepthTestFunction );

	if ( mDepthTestEnabled == _false )
		GetRenderer( ).EnableDepthTest( _false );

	if ( mDepthWriteEnabled == _false )
		GetRenderer( ).EnableDepthWrite( _false );

	if ( mClippingEnabled == _false )
		GetRenderer( ).EnableClipping( _false );
}

_void RenderMethod::DisableMethod( ) const
{
	if ( mFillMode != _FILLMODE_SOLID )
		GetRenderer( ).SetFillMode( _FILLMODE_SOLID );

	if ( mDepthTestFunction != _COMPAREFUNC_LESSEQUAL )
		GetRenderer( ).SetDepthTestFunction( _COMPAREFUNC_LESSEQUAL );

	if ( mDepthTestEnabled == _false )
		GetRenderer( ).EnableDepthTest( _true );

	if ( mDepthWriteEnabled == _false )
		GetRenderer( ).EnableDepthWrite( _true );

	if ( mClippingEnabled == _false )
		GetRenderer( ).EnableClipping( _true );
}

_dword RenderMethod::GetCullMode( _bool mirror ) const
{
	if ( mCullMode == _CULLMODE_NONE )
		return _CULLMODE_NONE;

	if ( mCullMode == _CULLMODE_CW )
		return mirror ? _CULLMODE_CCW : _CULLMODE_CW;
	else
		return mirror ? _CULLMODE_CW : _CULLMODE_CCW;
}