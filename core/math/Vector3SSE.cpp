#include "Vector3SSE.h"

const Vector3SSE Vector3SSE::cOrigin( 0.0f, 0.0f, 0.0f );
const Vector3SSE Vector3SSE::cIdentity( 1.0f, 1.0f, 1.0f );
const Vector3SSE Vector3SSE::cXAxis( 1.0f, 0.0f, 0.0f );
const Vector3SSE Vector3SSE::cYAxis( 0.0f, 1.0f, 0.0f );
const Vector3SSE Vector3SSE::cZAxis( 0.0f, 0.0f, 1.0f );
const Vector3SSE Vector3SSE::cMaxVector( Math::cMaxFloat, Math::cMaxFloat, Math::cMaxFloat );
const Vector3SSE Vector3SSE::cMinVector( Math::cMinFloat, Math::cMinFloat, Math::cMinFloat );

Vector3SSE& Vector3SSE::operator *= ( const Matrix3SSE& mat )
{
	_float4 v = start[0];
	_float4 t1 = _SSE_MUL_FLOAT4( _SSE_SHUFFLE_FLOAT( v, v, _MM_SHUFFLE( 0, 0, 0, 0 ) ), v );
	_float4 t2 = _SSE_MUL_FLOAT4( _SSE_SHUFFLE_FLOAT( v, v, _MM_SHUFFLE( 1, 1, 1, 1 ) ), v );

	t1 = _SSE_ADD_FLOAT4( t1, t2 );
	t2 = _SSE_MUL_FLOAT4( _SSE_SHUFFLE_FLOAT( v, v, _MM_SHUFFLE( 2, 2, 2, 2 ) ), v );
	t1 = _SSE_ADD_FLOAT4( t1, t2 );

	start[0] = t1;

	return *this;
}

Vector3SSE& Vector3SSE::operator *= ( const Matrix4SSE& mat )
{
	_float4 temp, v = start[0];

	temp = _SSE_MUL_FLOAT4( _SSE_SHUFFLE_FLOAT( v, v, _MM_SHUFFLE( 0, 0, 0, 0 ) ), mat.start[0] );
	temp = _SSE_ADD_FLOAT4( temp, _SSE_MUL_FLOAT4( _SSE_SHUFFLE_FLOAT( v, v, _MM_SHUFFLE( 1, 1, 1, 1 ) ), mat.start[1] ) );
	temp = _SSE_ADD_FLOAT4( temp, _SSE_MUL_FLOAT4( _SSE_SHUFFLE_FLOAT( v, v, _MM_SHUFFLE( 2, 2, 2, 2 ) ), mat.start[2] ) );
	temp = _SSE_ADD_FLOAT4( temp, mat.start[3] );

	_float* w = (_float*) &temp;

	if ( w[3] != 0.0f )
	{
		temp = _SSE_DIV_FLOAT4( temp, _SSE_LOAD_FLOAT( w[3] ) );
		w[3] = 0.0f;
	}

	start[0] = temp;

	return *this;
}

Vector3SSE& Vector3SSE::operator *= ( const Quaternion& q )
{
	Quaternion temp = q;
	temp *= Quaternion( operator()( 0 ), operator()( 1 ), operator()( 2 ), 0.0f );
	temp *= - q;

	*start = _SSE_LOAD_FLOATS( 0.0f, temp.z, temp.y, temp.x );

	return *this;
}