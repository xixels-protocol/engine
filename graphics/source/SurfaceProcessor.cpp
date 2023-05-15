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

_void SurfaceProcessor::ProcessHSL( _byte* buffer, _dword pitch, _dword hue, _dword saturation, _long lightness, const Rect& rect )
{
	for ( _long y = rect.t; y < rect.b; y ++ )
	{
		_dword* pointer = (_dword*)( buffer + y * pitch );
		for ( _long x = rect.l; x < rect.r; x ++ )
		{
			Color color( pointer[x] );

			_float h, s, l;
			color.ToHSL( h, s, l );

			if ( hue != -1 )
				h = hue / 360.0f;

			if ( saturation != -1 )
				s = saturation / 100.0f;

			if ( lightness != 0 )
			{
				l = l + lightness / 100.0f;

				if ( l > 1.0f )
					l = 1.0f;

				if ( l < 0.0f )
					l = 0.0f;
			}

			color.FromHSL( h, s, l );

			pointer[x] = color;
		}
	}
}

_void SurfaceProcessor::ProcessRGB( _byte* buffer, _dword pitch, _dword modulate, _dword additive, _dword subtract, const Rect& rect )
{
	Color m( modulate ), a( additive ), s( subtract );

	for ( _long y = rect.t; y < rect.b; y ++ )
	{
		_dword* pointer = (_dword*)( buffer + y * pitch );
		for ( _long x = rect.l; x < rect.r; x ++ )
		{
			Color color( pointer[x] );

			if ( modulate != 0xFFFFFFFF )
				color *= m;
			if ( additive != 0x00000000 )
				color += a;
			if ( subtract != 0x00000000 )
				color -= s;

			pointer[x] = color;
		}
	}
}

_void SurfaceProcessor::ProcessBorder( _byte* buffer, _dword pitch, _dword color, _dword bordersize, _float blurrate, const Rect& rect )
{
	// TODO, optimize.

	_long w = rect.Width( ), h = rect.Height( );

	// Border Parameters
	_dword realbordercolor	= color & 0x00FFFFFF;

	// Blur Parameters
	_long blurradius	= (_long) bordersize;
	_long blursize		= ( blurradius * 2 ) + 1;
	_long blursize2		= blursize * blursize;

	_float* blurkernel	= new _float[ blursize2 ];
	_dword* oricolors	= new _dword[ blursize2 ];
	_dword* blurimage	= new _dword[ w * h ];

	Memory::MemSet( oricolors, 0, blursize2 * 2 );
	MakeGaussianBlurKernel( blurkernel, blurradius );

	for ( _long y = rect.t; y < rect.b; y ++ )
	{
		for ( _long x = rect.l; x < rect.r; x ++ )
		{
			// Ori color
			GetDwordMatrix( buffer, pitch, rect, x, y, oricolors, blurradius, blurradius );

			// Blur
			_float alpha = 0.0f;
			for ( _long m = 0; m < blursize2; m ++ )
			{
				_float aa = ( ( oricolors[m] & 0xFF000000 ) >> 24 ) / 255.0f;
				alpha += aa * blurkernel[m];
			}

			alpha *= blurrate;

			if ( alpha > 1.0f )
				alpha = 1.0f;

			_dword aa = (_dword) ( alpha * 255.0f );		
			_dword final = ( aa << 24 ) | realbordercolor;

			blurimage[ ( y - rect.t ) * w + ( x - rect.l ) ] = final;
		}
	}

	for ( _long y = rect.t; y < rect.b; y ++ )
	{
		for ( _long x = rect.l; x < rect.r; x ++ )
		{
			// Set back
			*( ( (_dword*)( buffer + y * pitch ) ) + x ) = blurimage[ ( y - rect.t ) * w + ( x - rect.l ) ];
		}
	}

	delete[] blurimage;
	delete[] blurkernel;
	delete[] oricolors;
}
