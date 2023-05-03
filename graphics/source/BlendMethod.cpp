#include "BlendMethod.h"

BlendMethod::BlendMethod( _bool defmethod )
{
	mDefaultMethod	= defmethod;
	mRenderOrder	= IRenderDevice::_ORDER_NORMAL;

	mColorBlendFunc	= 0;
	mColorBlendSrc	= 0;
	mColorBlendDes	= 0;

	mAlphaBlendFunc	= 0;
	mAlphaBlendSrc	= 0;
	mAlphaBlendDes	= 0;

	mColorWrite		= _true;
	mAlphaWrite		= _true;
}

BlendMethod::~BlendMethod( )
{
}

_void BlendMethod::EnableMethod( ) const
{
	if ( mColorBlendFunc != 0 )
		GetRenderer( ).EnableColorBlend( mColorBlendFunc, mColorBlendSrc, mColorBlendDes );

	if ( mAlphaBlendFunc != 0 )
		GetRenderer( ).EnableAlphaBlend( mAlphaBlendFunc, mAlphaBlendSrc, mAlphaBlendDes );

	if ( mColorWrite == _false )
		GetRenderer( ).DisableColorWrite( mAlphaWrite );
	else
		GetRenderer( ).EnableColorWrite( mAlphaWrite );
}

_void BlendMethod::DisableMethod( ) const
{
	if ( mColorBlendFunc != 0 )
		GetRenderer( ).DisableColorBlend( );

	if ( mAlphaBlendFunc != 0 )
		GetRenderer( ).DisableAlphaBlend( );

	if ( mColorWrite == _false || mAlphaWrite == _false )
		GetRenderer( ).EnableColorWrite( _true );
}