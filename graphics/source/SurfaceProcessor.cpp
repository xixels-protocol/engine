#include "SurfaceProcessor.h"

_byte ImageBlurWrapper::GetPixel( _dword x, _dword y ) const
{
	_byte alpha = 0;
	if ( mHorizontal )
		alpha = *( mBuffer + mPitch * y + x );
	else
		alpha = *( mBuffer + mPitch * x + y );

	return alpha;
}

_void ImageBlurWrapper::CopyFrom( _dword x, _dword y, const _byte* buf, _dword length )
{
	for ( _dword i = 0; i < length; i ++ )
	{
		_byte* color = _null;
		if ( mHorizontal )
			color = mBuffer + mPitch * y + ( x + i );
		else
			color = mBuffer + mPitch * ( x + i ) + y;

		*color = buf[i];
	}
}