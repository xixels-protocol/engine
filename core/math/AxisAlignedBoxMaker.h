#pragma once

namespace Xixels
{

#ifdef _XX_OS_WIN32
__declspec( align(16) ) class AxisAlignedBoxMaker
#else
class __attribute__( (aligned(16)) ) AxisAlignedBoxMaker
#endif
{
public:
	_float4	min;
	_float4	max;

public:
	inline AxisAlignedBoxMaker( )
	{
		min = _SSE_LOAD_FLOATS( 0.0f, Math::cMaxFloat, Math::cMaxFloat, Math::cMaxFloat );
		max = _SSE_LOAD_FLOATS( 0.0f, Math::cMinFloat, Math::cMinFloat, Math::cMinFloat );
	}

	inline operator AxisAlignedBox ( ) const
		{ return AxisAlignedBox( *( (Vector3*) &min ), *( (Vector3*) &max ) ); }

	inline _void Expand( const Vector3& v )
	{
		_float4 a = _SSE_LOAD_FLOATS( 0.0f, v.z, v.y, v.x );
		min = _SSE_MIN_FLOAT4( min, a );
		max = _SSE_MAX_FLOAT4( max, a );
	}

	inline _void Expand( const _float4& a )
	{
		min = _SSE_MIN_FLOAT4( min, a );
		max = _SSE_MAX_FLOAT4( max, a );
	}

	inline _void Expand( const _float4& v0, const _float4& v1, const _float4& v2, const _float4& v3 )
	{
		min = _SSE_MIN5_FLOAT4( v0, v1, v2, v3, min );
		max = _SSE_MAX5_FLOAT4( v0, v1, v2, v3, max );
	}
};

};