#include "Matrix4SSE.h"

const Matrix4SSE Matrix4SSE::cZero( 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f );
const Matrix4SSE Matrix4SSE::cIdentity( 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f );

Matrix4SSE& Matrix4SSE::operator += ( const Matrix4SSE& mat )
{
	*( start )     = _SSE_ADD_FLOAT4( *start, *mat.start );
	*( start + 1 ) = _SSE_ADD_FLOAT4( *( start + 1 ), *( mat.start + 1 ) );
	*( start + 2 ) = _SSE_ADD_FLOAT4( *( start + 2 ), *( mat.start + 2 ) );
	*( start + 3 ) = _SSE_ADD_FLOAT4( *( start + 3 ), *( mat.start + 3 ) );

	return *this;
}

Matrix4SSE& Matrix4SSE::operator *= ( _float s )
{
	_float4 temp = _SSE_LOAD_FLOAT( s );

	*( start )     = _SSE_MUL_FLOAT4( *( start ), temp );
	*( start + 1 ) = _SSE_MUL_FLOAT4( *( start + 1 ), temp );
	*( start + 2 ) = _SSE_MUL_FLOAT4( *( start + 2 ), temp );
	*( start + 3 ) = _SSE_MUL_FLOAT4( *( start + 3 ), temp );

	return *this;
}

Matrix4SSE& Matrix4SSE::operator *= ( const Matrix4SSE& mat )
{
	_float4 l1 = *( mat.start );
	_float4 l2 = *( mat.start + 1 );
	_float4 l3 = *( mat.start + 2 );
	_float4 l4 = *( mat.start + 3 );

	_float4 temp;

	temp = _SSE_MUL_FLOAT4( _SSE_LOAD_FLOAT( operator()( 0, 0 ) ), l1 );
	temp = _SSE_ADD_FLOAT4( temp, _SSE_MUL_FLOAT4( _SSE_LOAD_FLOAT( operator()( 0, 1 ) ), l2 ) );
	temp = _SSE_ADD_FLOAT4( temp, _SSE_MUL_FLOAT4( _SSE_LOAD_FLOAT( operator()( 0, 2 ) ), l3 ) );
	temp = _SSE_ADD_FLOAT4( temp, _SSE_MUL_FLOAT4( _SSE_LOAD_FLOAT( operator()( 0, 3 ) ), l4 ) );
	*( start ) = temp;

	temp = _SSE_MUL_FLOAT4( _SSE_LOAD_FLOAT( operator()( 1, 0 ) ), l1 );
	temp = _SSE_ADD_FLOAT4( temp, _SSE_MUL_FLOAT4( _SSE_LOAD_FLOAT( operator()( 1, 1 ) ), l2 ) );
	temp = _SSE_ADD_FLOAT4( temp, _SSE_MUL_FLOAT4( _SSE_LOAD_FLOAT( operator()( 1, 2 ) ), l3 ) );
	temp = _SSE_ADD_FLOAT4( temp, _SSE_MUL_FLOAT4( _SSE_LOAD_FLOAT( operator()( 1, 3 ) ), l4 ) );
	*( start + 1 ) = temp;

	temp = _SSE_MUL_FLOAT4( _SSE_LOAD_FLOAT( operator()( 2, 0 ) ), l1 );
	temp = _SSE_ADD_FLOAT4( temp, _SSE_MUL_FLOAT4( _SSE_LOAD_FLOAT( operator()( 2, 1 ) ), l2 ) );
	temp = _SSE_ADD_FLOAT4( temp, _SSE_MUL_FLOAT4( _SSE_LOAD_FLOAT( operator()( 2, 2 ) ), l3 ) );
	temp = _SSE_ADD_FLOAT4( temp, _SSE_MUL_FLOAT4( _SSE_LOAD_FLOAT( operator()( 2, 3 ) ), l4 ) );
	*( start + 2 ) = temp;

	temp = _SSE_MUL_FLOAT4( _SSE_LOAD_FLOAT( operator()( 3, 0 ) ), l1 );
	temp = _SSE_ADD_FLOAT4( temp, _SSE_MUL_FLOAT4( _SSE_LOAD_FLOAT( operator()( 3, 1 ) ), l2 ) );
	temp = _SSE_ADD_FLOAT4( temp, _SSE_MUL_FLOAT4( _SSE_LOAD_FLOAT( operator()( 3, 2 ) ), l3 ) );
	temp = _SSE_ADD_FLOAT4( temp, _SSE_MUL_FLOAT4( _SSE_LOAD_FLOAT( operator()( 3, 3 ) ), l4 ) );
	*( start + 3 ) = temp;

	return *this;
}

_bool Matrix4SSE::operator == ( const Matrix4SSE& mat ) const
{
	return	operator()( 0, 0 ) == mat( 0, 0 ) && operator()( 0, 1 ) == mat( 0, 1 ) && operator()( 0, 2 ) == mat( 0, 2 ) && operator()( 0, 3 ) == mat( 0, 3 ) &&
			operator()( 1, 0 ) == mat( 1, 0 ) && operator()( 1, 1 ) == mat( 1, 1 ) && operator()( 1, 2 ) == mat( 1, 2 ) && operator()( 1, 3 ) == mat( 1, 3 ) &&
			operator()( 2, 0 ) == mat( 2, 0 ) && operator()( 2, 1 ) == mat( 2, 1 ) && operator()( 2, 2 ) == mat( 2, 2 ) && operator()( 2, 3 ) == mat( 2, 3 ) &&
			operator()( 3, 0 ) == mat( 3, 0 ) && operator()( 3, 1 ) == mat( 3, 1 ) && operator()( 3, 2 ) == mat( 3, 2 ) && operator()( 3, 3 ) == mat( 3, 3 );
}