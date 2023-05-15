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

_void SurfaceProcessor::MakeGaussianBlurKernel( _float* matrix, _long radius )
{
	_long	rows		 = radius * 2 + 1;
	_float	sigma		 = radius / 1.2f;
	_float	sigma22		 = 2.0f * sigma * sigma;
	_float	sigmaPi2	 = 2.0f * Math::cPi * sigma;
	_float	sqrtSigmaPi2 = Math::Sqrt( sigmaPi2 );
	_float	total		 = 0;
	_long	index		 = 0;

	for ( _long row = -radius; row <= radius; row ++ )
	{
		for ( _long col = -radius; col <= radius; col ++ )
		{
			_float dist = _float( row * row + col * col );
			matrix[index] = Math::Exp(-dist/sigma22) / sqrtSigmaPi2;

			total += matrix[index];
			index ++;
		}
	}

	for ( _long i = 0; i < rows * rows; i ++ )
		matrix[i] /= total;
}

_void SurfaceProcessor::GetDwordMatrix( _byte* buffer, _dword pitch, const Rect& rect, _long xx, _long yy, _dword* data, _long dx, _long dy )
{
	//_long y1 = Math::Max( rect.t, y - dy ), y2 = Math::Min( rect.b - 1, y + dy );
	//_long x1 = Math::Max( rect.l, x - dx ), x2 = Math::Min( rect.r - 1, x + dx );

	_dword k = 0;

	for ( _long y = yy - dy; y <= yy + dy; y ++ )
	{
		for ( _long x = xx - dx; x <= xx + dx; x ++ )
		{
			if ( x < rect.l || x >= rect.r || y < rect.t || y >= rect.b )
				data[ k ++ ] = 0;
			else
				data[ k ++ ] = *( (_dword*)( buffer + y * pitch ) + x );
		}
	}
}
