#include "Matrix3SSE.h"

const Matrix3SSE Matrix3SSE::cZero( 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f );
const Matrix3SSE Matrix3SSE::cIdentity( 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f );

Matrix3SSE& Matrix3SSE::operator += ( const Matrix3SSE& mat )
{
	*( start )     = _SSE_ADD_FLOAT4( *start, *mat.start );
	*( start + 1 ) = _SSE_ADD_FLOAT4( *( start + 1 ), *( mat.start + 1 ) );
	*( start + 2 ) = _SSE_ADD_FLOAT4( *( start + 2 ), *( mat.start + 2 ) );

	return *this;
}

Matrix3SSE& Matrix3SSE::operator *= ( _float s )
{
	_float4 temp = _SSE_LOAD_FLOAT( s );

	*( start ) = _SSE_MUL_FLOAT4( *( start ), temp );
	*( start + 1 ) = _SSE_MUL_FLOAT4( *( start + 1 ), temp );
	*( start + 2 ) = _SSE_MUL_FLOAT4( *( start + 2 ), temp );

	return *this;
}

Matrix3SSE& Matrix3SSE::operator *= ( const Matrix3SSE& mat )
{
	_float4 l1 = *( mat.start );
	_float4 l2 = *( mat.start + 1 );
	_float4 l3 = *( mat.start + 2 );

	_float4 temp;

	temp = _SSE_MUL_FLOAT4( _SSE_LOAD_FLOAT( operator()( 0, 0 ) ), l1 );
	temp = _SSE_ADD_FLOAT4( temp, _SSE_MUL_FLOAT4( _SSE_LOAD_FLOAT( operator()( 0, 1 ) ), l2 ) );
	temp = _SSE_ADD_FLOAT4( temp, _SSE_MUL_FLOAT4( _SSE_LOAD_FLOAT( operator()( 0, 2 ) ), l3 ) );
	*( start ) = temp;

	temp = _SSE_MUL_FLOAT4( _SSE_LOAD_FLOAT( operator()( 1, 0 ) ), l1 );
	temp = _SSE_ADD_FLOAT4( temp, _SSE_MUL_FLOAT4( _SSE_LOAD_FLOAT( operator()( 1, 1 ) ), l2 ) );
	temp = _SSE_ADD_FLOAT4( temp, _SSE_MUL_FLOAT4( _SSE_LOAD_FLOAT( operator()( 1, 2 ) ), l3 ) );
	*( start + 1 ) = temp;

	temp = _SSE_MUL_FLOAT4( _SSE_LOAD_FLOAT( operator()( 2, 0 ) ), l1 );
	temp = _SSE_ADD_FLOAT4( temp, _SSE_MUL_FLOAT4( _SSE_LOAD_FLOAT( operator()( 2, 1 ) ), l2 ) );
	temp = _SSE_ADD_FLOAT4( temp, _SSE_MUL_FLOAT4( _SSE_LOAD_FLOAT( operator()( 2, 2 ) ), l3 ) );
	*( start + 2 ) = temp;

	return *this;
}

_bool Matrix3SSE::operator == ( const Matrix3SSE& mat ) const
{
	return	operator()( 0, 0 ) == mat( 0, 0 ) && operator()( 0, 1 ) == mat( 0, 1 ) && operator()( 0, 2 ) == mat( 0, 2 ) &&
			operator()( 1, 0 ) == mat( 1, 0 ) && operator()( 1, 1 ) == mat( 1, 1 ) && operator()( 1, 2 ) == mat( 1, 2 ) &&
			operator()( 2, 0 ) == mat( 2, 0 ) && operator()( 2, 1 ) == mat( 2, 1 ) && operator()( 2, 2 ) == mat( 2, 2 );
}