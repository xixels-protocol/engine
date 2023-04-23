#include "Vector4SSE.h"

const Vector4SSE Vector4SSE::cOrigin( 0.0f, 0.0f, 0.0f, 0.0f );
const Vector4SSE Vector4SSE::cIdentity( 1.0f, 1.0f, 1.0f, 1.0f );
const Vector4SSE Vector4SSE::cXAxis( 1.0f, 0.0f, 0.0f, 0.0f );
const Vector4SSE Vector4SSE::cYAxis( 0.0f, 1.0f, 0.0f, 0.0f );
const Vector4SSE Vector4SSE::cZAxis( 0.0f, 0.0f, 1.0f, 0.0f );
const Vector4SSE Vector4SSE::cWAxis( 0.0f, 0.0f, 0.0f, 1.0f );
const Vector4SSE Vector4SSE::cMaxVector( Math::cMaxFloat, Math::cMaxFloat, Math::cMaxFloat, Math::cMaxFloat );
const Vector4SSE Vector4SSE::cMinVector( Math::cMinFloat, Math::cMinFloat, Math::cMinFloat, Math::cMinFloat );

Vector4SSE& Vector4SSE::operator *= ( const Quaternion& q )
{
	Quaternion temp = q;
	temp *= Quaternion( operator()( 0 ), operator()( 1 ), operator()( 2 ), 0.0f );
	temp *= - q;

	*start = _SSE_LOAD_FLOATS( 0.0f, temp.z, temp.y, temp.x );

	return *this;
}

Vector4SSE& Vector4SSE::operator *= ( const Matrix4SSE& mat )
{
	_float4 temp;

	temp = _SSE_MUL_FLOAT4( _SSE_LOAD_FLOAT( operator()( 0 ) ), *( mat.start ) );
	temp = _SSE_ADD_FLOAT4( temp, _SSE_MUL_FLOAT4( _SSE_LOAD_FLOAT( operator()( 1 ) ), *( mat.start + 1 ) ) );
	temp = _SSE_ADD_FLOAT4( temp, _SSE_MUL_FLOAT4( _SSE_LOAD_FLOAT( operator()( 2 ) ), *( mat.start + 2 ) ) );
	temp = _SSE_ADD_FLOAT4( temp, _SSE_MUL_FLOAT4( _SSE_LOAD_FLOAT( operator()( 3 ) ), *( mat.start + 3 ) ) );

	*start = temp;

	return *this;
}