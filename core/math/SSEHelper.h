#pragma once

#ifdef _EXTEND_INSTRUCTIONS

#if !defined( _XX_OS_IOS ) && !defined( _XX_OS_ANDROID )

// Some useful macro for sse misc.


#define _SSE_SELECT( a, p ) _SSE_SHUFFLE_FLOAT( a, a, _MM_SHUFFLE( p, p, p, p ) )


// Some useful macro for sse loader


#define _SSE_LOAD_ZERO( ) _mm_setzero_ps( )

#define _SSE_LOAD_FLOAT( a ) _mm_set_ps1( a )
#define _SSE_LOAD_FLOATS( a, b, c, d ) _mm_set_ps( a, b, c, d )

#define _SSE_LOAD_FLOAT4( a ) _mm_load_ps( a )
#define _SSE_STORE_FLOAT4( a, b ) _mm_store_ps( a, b )
#define _SSE_STOREL_FLOAT4( a, b ) _mm_storel_pi( a, b )
#define _SSE_STOREH_FLOAT4( a, b ) _mm_storeh_pi( a, b )

#define _SSE_LOAD_VECTOR3( a ) _mm_set_ps( 1.0f, a.z, a.y, a.x )
#define _SSE_STORE_VECTOR3( a, p ) \
	_mm_store_ss( p, a ); _mm_store_ss( p + 1, _SSE_SELECT( a, 1 ) ); _mm_store_ss( p + 2, _SSE_SELECT( a, 2 ) );

#define _SSE_LOAD_VECTOR4( a ) _mm_set_ps( a.w, a.z, a.y, a.x )
#define _SSE_STORE_VECTOR4( a, p ) \
	_mm_store_ss( p, a ); _mm_store_ss( p + 1, _SSE_SELECT( a, 1 ) ); _mm_store_ss( p + 2, _SSE_SELECT( a, 2 ) ); _mm_store_ss( p + 3, _SSE_SELECT( a, 3 ) );


// Some useful macro for sse comparison


#define _SSE_CMP_EQ_FLOAT4( a, b ) _mm_cmpeq_ps( a, b )
#define _SSE_CMP_NEQ_FLOAT4( a, b ) _mm_cmpneq_ps( a, b )
#define _SSE_CMP_LT_FLOAT4( a, b ) _mm_cmplt_ps( a, b )
#define _SSE_CMP_NLT_FLOAT4( a, b ) _mm_cmpnlt_ps( a, b )
#define _SSE_CMP_LE_FLOAT4( a, b ) _mm_cmple_ps( a, b )
#define _SSE_CMP_NLE_FLOAT4( a, b ) _mm_cmpnle_ps( a, b )
#define _SSE_CMP_GT_FLOAT4( a, b ) _mm_cmpgt_ps( a, b )
#define _SSE_CMP_NGT_FLOAT4( a, b ) _mm_cmpngt_ps( a, b )
#define _SSE_CMP_GE_FLOAT4( a, b ) _mm_cmpge_ps( a, b )
#define _SSE_CMP_NGE_FLOAT4( a, b ) _mm_cmpnge_ps( a, b )


// Some useful macro for sse math


#define _SSE_MIN_FLOAT4( a, b ) _mm_min_ps( a, b )
#define _SSE_MIN4_FLOAT4( a, b, c, d ) _mm_min_ps( _mm_min_ps( a, b ), _mm_min_ps( c, d ) )
#define _SSE_MIN5_FLOAT4( a, b, c, d, e ) _mm_min_ps( _mm_min_ps( _mm_min_ps( a, b ), _mm_min_ps( c, d ) ), e )

#define _SSE_MAX_FLOAT4( a, b ) _mm_max_ps( a, b )
#define _SSE_MAX4_FLOAT4( a, b, c, d ) _mm_max_ps( _mm_max_ps( a, b ), _mm_max_ps( c, d ) )
#define _SSE_MAX5_FLOAT4( a, b, c, d, e ) _mm_max_ps( _mm_max_ps( _mm_max_ps( a, b ), _mm_max_ps( c, d ) ), e )

#define _SSE_ADD_FLOAT4( a, b ) _mm_add_ps( a, b )
#define _SSE_ADD_FLOAT4S( a, b ) _mm_add_ss( a, b )
#define _SSE_ADD3_FLOAT4( a, b, c ) _mm_add_ps( _mm_add_ps( a, b ), c )
#define _SSE_ADD4_FLOAT4( a, b, c, d ) _mm_add_ps( _mm_add_ps( a, b ), _mm_add_ps( c, d ) )

#define _SSE_SUB_FLOAT4( a, b ) _mm_sub_ps( a, b )
#define _SSE_SUB_FLOAT4S( a, b ) _mm_sub_ss( a, b )
#define _SSE_MUL_FLOAT4( a, b ) _mm_mul_ps( a, b )
#define _SSE_DIV_FLOAT4( a, b ) _mm_div_ps( a, b )

#define _SSE_MADD_FLOAT4( a, b, c ) _mm_add_ps( _mm_mul_ps( a, b ), c )
#define _SSE_LERP_FLOAT4( a, b, t ) _SSE_MADD_FLOAT4( _mm_sub_ps( b, a ), t, a )

#define _SSE_DOT4x4_FLOAT4( a0, a1, a2, a3, b0, b1, b2, b3 ) \
	_SSE_ADD4_FLOAT4( _mm_mul_ps( a0, b0 ), _mm_mul_ps( a1, b1 ), _mm_mul_ps( a2, b2 ), _mm_mul_ps( a3, b3 ) )
#define _SSE_DOT4x3_FLOAT4( a0, a1, a2, a3, b0, b1, b2 ) \
	_SSE_ADD4_FLOAT4( _mm_mul_ps( a0, b0 ), _mm_mul_ps( a1, b1 ), _mm_mul_ps( a2, b2 ), a3 )
#define _SSE_DOT3x3_FLOAT4( a0, a1, a2, b0, b1, b2 ) \
	_SSE_ADD3_FLOAT4( _mm_mul_ps( a0, b0 ), _mm_mul_ps( a1, b1 ), _mm_mul_ps( a2, b2 ) )

#define _SSE_UNPACKL_FLOAT4( a, b ) _mm_unpacklo_ps( a, b )
#define _SSE_UNPACKH_FLOAT4( a, b ) _mm_unpackhi_ps( a, b )
#define _SSE_MOVELH_FLOAT4( a, b ) _mm_movelh_ps( a, b )
#define _SSE_MOVEHL_FLOAT4( a, b ) _mm_movehl_ps( a, b )
#define _SSE_SHUFFLE_FLOAT( a, b, c ) _mm_shuffle_ps( a, b, c )

#else

inline _stdcall Xixels::_float4 _NEON_GETFLOAT4( Xixels::_float f3, Xixels::_float f2, Xixels::_float f1, Xixels::_float f0 )
{
	Xixels::_float fa[4];
	fa[0] = f0; fa[1] = f1; fa[2] = f2; fa[3] = f3;
	return vld1q_f32( fa );
}

inline _stdcall Xixels::_float2 _NEON_GETFLOAT2( Xixels::_float f1, Xixels::_float f0 )
{
	Xixels::_float fa[2];
	fa[0] = f0; fa[1] = f1;
	return vld1_f32( fa );
}

inline _stdcall uint32x4_t _NEON_GETUINT4( unsigned int i3, unsigned int i2, unsigned int i1, unsigned int i0 )
{
	unsigned int ia[4];
	ia[0] = i0; ia[1] = i1; ia[2] = i2; ia[3] = i3;
	return vld1q_u32( ia );
}


// Some useful macro for sse misc.


#define _MM_SHUFFLE( fp3, fp2, fp1, fp0 ) (((fp3) << 6) | ((fp2) << 4) | ((fp1) << 2) | ((fp0)))
#define _SSE_SELECT( a, p ) _SSE_SHUFFLE_FLOAT( a, a, _MM_SHUFFLE( p, p, p, p ) )


// Some useful macro for sse loader


#define _SSE_LOAD_ZERO( ) vmovq_n_f32( 0 )

#define _SSE_LOAD_FLOAT( a ) vmovq_n_f32( a )
#define _SSE_LOAD_FLOATS( a, b, c, d ) _NEON_GETFLOAT4( a, b, c, d )

#define _SSE_LOAD_FLOAT4( a ) vld1q_f32( a )
#define _SSE_STORE_FLOAT4( a, b ) vst1q_f32( a, b )
#define _SSE_STOREL_FLOAT4( a, b ) *a = vget_low_f32( b )
#define _SSE_STOREH_FLOAT4( a, b ) *a = vget_high_f32( b )

#define _SSE_LOAD_VECTOR3( a ) _NEON_GETFLOAT4( 1.0f, a.z, a.y, a.x )
#define _SSE_STORE_VECTOR3( a, p ) \
	*p = vgetq_lane_f32( a, 0 ); *( p + 1 ) = vgetq_lane_f32( a, 1 ); *( p + 2 ) = vgetq_lane_f32( a, 2 );

#define _SSE_LOAD_VECTOR4( a ) _NEON_GETFLOAT4( a.w, a.z, a.y, a.x )
#define _SSE_STORE_VECTOR4( a, p ) vst1q_f32( p, a )


// Some useful macro for sse comparison


#define _SSE_CMP_EQ_FLOAT4( a, b ) vceqq_f32( a, b )
#define _SSE_CMP_NEQ_FLOAT4( a, b ) vmvnq_u32( vceqq_f32( a, b ) )
#define _SSE_CMP_LT_FLOAT4( a, b ) vcltq_f32( a, b )
#define _SSE_CMP_NLT_FLOAT4( a, b ) vmvnq_u32( vcltq_f32( a, b ) )
#define _SSE_CMP_LE_FLOAT4( a, b ) vcleq_f32( a, b )
#define _SSE_CMP_NLE_FLOAT4( a, b ) vmvnq_u32( vcleq_f32( a, b ) )
#define _SSE_CMP_GT_FLOAT4( a, b ) vcgtq_f32( a, b )
#define _SSE_CMP_NGT_FLOAT4( a, b ) vmvnq_u32( vcgtq_f32( a, b ) )
#define _SSE_CMP_GE_FLOAT4( a, b ) vcgeq_f32( a, b )
#define _SSE_CMP_NGE_FLOAT4( a, b ) vmvnq_u32( vcgeq_f32( a, b ) )


// Some useful macro for sse math


#define _SSE_MIN_FLOAT4( a, b ) vminq_f32( a, b )
#define _SSE_MIN4_FLOAT4( a, b, c, d ) vminq_f32( vminq_f32( a, b ), vminq_f32( c, d ) )
#define _SSE_MIN5_FLOAT4( a, b, c, d, e ) vminq_f32( vminq_f32( vminq_f32( a, b ), vminq_f32( c, d ) ), e )

#define _SSE_MAX_FLOAT4( a, b ) vmaxq_f32( a, b )
#define _SSE_MAX4_FLOAT4( a, b, c, d ) vmaxq_f32( vmaxq_f32( a, b ), vmaxq_f32( c, d ) )
#define _SSE_MAX5_FLOAT4( a, b, c, d, e ) vmaxq_f32( vmaxq_f32( vmaxq_f32( a, b ), vmaxq_f32( c, d ) ), e )

#define _SSE_ADD_FLOAT4( a, b ) vaddq_f32( a, b )
#define _SSE_ADD_FLOAT4S( a, b ) vbslq_f32( _NEON_GETUINT4( 0xffffffff, 0xffffffff, 0xffffffff, 0x0 ), a, vaddq_f32( a, b ) );
#define _SSE_ADD3_FLOAT4( a, b, c ) vaddq_f32( vaddq_f32( a, b ), c )
#define _SSE_ADD4_FLOAT4( a, b, c, d ) vaddq_f32( vaddq_f32( a, b ), vaddq_f32( c, d ) )

#define _SSE_SUB_FLOAT4( a, b ) vsubq_f32( a, b )
#define _SSE_SUB_FLOAT4S( a, b ) vbslq_f32( _NEON_GETUINT4( 0xffffffff, 0xffffffff, 0xffffffff, 0x0 ), a, vsubq_f32( a, b ) )
#define _SSE_MUL_FLOAT4( a, b ) vmulq_f32( a, b )
#define _SSE_DIV_FLOAT4( a, b ) vmulq_f32( a, vrecpeq_f32( b ) )

#define _SSE_MADD_FLOAT4( a, b, c ) vaddq_f32( vmulq_f32( a, b ), c )
#define _SSE_LERP_FLOAT4( a, b, t ) _SSE_MADD_FLOAT4( vsubq_f32( b, a ), t, a )

#define _SSE_DOT4x4_FLOAT4( a0, a1, a2, a3, b0, b1, b2, b3 ) \
	_SSE_ADD4_FLOAT4( vmulq_f32( a0, b0 ), vmulq_f32( a1, b1 ), vmulq_f32( a2, b2 ), vmulq_f32( a3, b3 ) )
#define _SSE_DOT4x3_FLOAT4( a0, a1, a2, a3, b0, b1, b2 ) \
	_SSE_ADD4_FLOAT4( vmulq_f32( a0, b0 ), vmulq_f32( a1, b1 ), vmulq_f32( a2, b2 ), a3 )
#define _SSE_DOT3x3_FLOAT4( a0, a1, a2, b0, b1, b2 ) \
	_SSE_ADD3_FLOAT4( vmulq_f32( a0, b0 ), vmulq_f32( a1, b1 ), vmulq_f32( a2, b2 ) )

#define _SSE_UNPACKL_FLOAT4( a, b ) vzipq_f32( a, b ).val[0]
#define _SSE_UNPACKH_FLOAT4( a, b ) vzipq_f32( a, b ).val[1]
#define _SSE_MOVELH_FLOAT4( a, b ) vcombine_f32( vget_low_f32( a ), vget_low_f32( b ) )
#define _SSE_MOVEHL_FLOAT4( a, b ) vcombine_f32( vget_high_f32( b ), vget_high_f32( a ) )

#define _SSE_SHUFFLE_FLOAT( a, b, c ) \
	vcombine_f32( _NEON_GETFLOAT2( vgetq_lane_f32( a, ( c >> 2 ) & 0x3 ), vgetq_lane_f32( a, c & 0x3 ) ), \
	_NEON_GETFLOAT2( vgetq_lane_f32( b, ( c >> 6 ) & 0x3 ), vgetq_lane_f32( b, ( c >> 4 ) & 0x3 ) ) )

#endif

#else


// Some useful macro for sse misc.


#define _MM_SHUFFLE( fp3, fp2, fp1, fp0 ) (((fp3) << 6) | ((fp2) << 4) | ((fp1) << 2) | ((fp0)))
#define _SSE_SELECT( a, p ) _SSE_SHUFFLE_FLOAT( a, a, _MM_SHUFFLE( p, p, p, p ) )


// Some useful macro for sse loader


#define _SSE_LOAD_ZERO( ) ( (_float4) { 0.0f, 0.0f, 0.0f, 0.0f } )

#define _SSE_LOAD_FLOAT( a ) ( (_float4) { a, a, a, a } )
#define _SSE_LOAD_FLOATS( a, b, c, d ) ( (_float4) { d, c, b, a } )

#define _SSE_LOAD_FLOAT4( a ) ( (_float4) { (a).x, (a).y, (a).z, (a).w } )
#define _SSE_STORE_FLOAT4( a, b ) (a).x = (b).x; (a).y = (b).y; (a).z = (b).z; (a).w = (b).w;
#define _SSE_STOREL_FLOAT4( a, b ) *a = { (b).x, (b).y }
#define _SSE_STOREH_FLOAT4( a, b ) *a = { (b).z, (b).w }

#define _SSE_LOAD_VECTOR3( a ) ( (_float4) { (a).x, (a).y, (a).z, 1.0f } )
#define _SSE_STORE_VECTOR3( a, p ) \
	*p = (a).x; *( p + 1 ) = _SSE_SELECT( a, 1 ).x; *( p + 2 ) = _SSE_SELECT( a, 2 ).x;

#define _SSE_LOAD_VECTOR4( a ) (_float4) { (a).x, (a).y, (a).z, (a).w }
#define _SSE_STORE_VECTOR4( a, p ) \
	*p = (a).x; *( p + 1 ) = _SSE_SELECT( a, 1 ).x; *( p + 2 ) = _SSE_SELECT( a, 2 ).x; *( p + 3 ) = _SSE_SELECT( a, 3 ).x;


// Some useful macro for sse comparison


#define _SSE_CMP_EQ_FLOAT4( a, b ) \
	( (_float4) { ( (a).x == (b).x ) ? 0xFFFFFFFF : 0x0, ( (a).y == (b).y ) ? 0xFFFFFFFF : 0x0, ( (a).z == (b).z ) ? 0xFFFFFFFF : 0x0, ( (a).w == (b).w ) ? 0xFFFFFFFF : 0x0 } )
#define _SSE_CMP_NEQ_FLOAT4( a, b ) \
	( (_float4) { ( (a).x != (b).x ) ? 0xFFFFFFFF : 0x0, ( (a).y != (b).y ) ? 0xFFFFFFFF : 0x0, ( (a).z != (b).z ) ? 0xFFFFFFFF : 0x0, ( (a).w != (b).w ) ? 0xFFFFFFFF : 0x0 } )
#define _SSE_CMP_LT_FLOAT4( a, b ) \
	( (_float4) { ( (a).x < (b).x ) ? 0xFFFFFFFF : 0x0, ( (a).y < (b).y ) ? 0xFFFFFFFF : 0x0, ( (a).z < (b).z ) ? 0xFFFFFFFF : 0x0, ( (a).w < (b).w ) ? 0xFFFFFFFF : 0x0 } )
#define _SSE_CMP_NLT_FLOAT4( a, b ) \
	( (_float4) { !( (a).x < (b).x ) ? 0xFFFFFFFF : 0x0, !( (a).y < (b).y ) ? 0xFFFFFFFF : 0x0, !( (a).z < (b).z ) ? 0xFFFFFFFF : 0x0, !( (a).w < (b).w ) ? 0xFFFFFFFF : 0x0 } )
#define _SSE_CMP_LE_FLOAT4( a, b ) \
	( (_float4) { ( (a).x <= (b).x ) ? 0xFFFFFFFF : 0x0, ( (a).y <= (b).y ) ? 0xFFFFFFFF : 0x0, ( (a).z <= (b).z ) ? 0xFFFFFFFF : 0x0, ( (a).w <= (b).w ) ? 0xFFFFFFFF : 0x0 } )
#define _SSE_CMP_NLE_FLOAT4( a, b ) \
	( (_float4) { !( (a).x <= (b).x ) ? 0xFFFFFFFF : 0x0, !( (a).y <= (b).y ) ? 0xFFFFFFFF : 0x0, !( (a).z <= (b).z ) ? 0xFFFFFFFF : 0x0, !( (a).w <= (b).w ) ? 0xFFFFFFFF : 0x0 } )
#define _SSE_CMP_GT_FLOAT4( a, b ) \
	( (_float4) { ( (a).x > (b).x ) ? 0xFFFFFFFF : 0x0, ( (a).y > (b).y ) ? 0xFFFFFFFF : 0x0, ( (a).z > (b).z ) ? 0xFFFFFFFF : 0x0, ( (a).w > (b).w ) ? 0xFFFFFFFF : 0x0 } )
#define _SSE_CMP_NGT_FLOAT4( a, b ) \
	( (_float4) { !( (a).x < (b).x ) ? 0xFFFFFFFF : 0x0, !( (a).y < (b).y ) ? 0xFFFFFFFF : 0x0, !( (a).z < (b).z ) ? 0xFFFFFFFF : 0x0, !( (a).w < (b).w ) ? 0xFFFFFFFF : 0x0 } )
#define _SSE_CMP_GE_FLOAT4( a, b ) \
	( (_float4) { ( (a).x >= (b).x ) ? 0xFFFFFFFF : 0x0, ( (a).y >= (b).y ) ? 0xFFFFFFFF : 0x0, ( (a).z >= (b).z ) ? 0xFFFFFFFF : 0x0, ( (a).w >= (b).w ) ? 0xFFFFFFFF : 0x0 } )
#define _SSE_CMP_NGE_FLOAT4( a, b ) \
	( (_float4) { !( (a).x >= (b).x ) ? 0xFFFFFFFF : 0x0, !( (a).y >= (b).y ) ? 0xFFFFFFFF : 0x0, !( (a).z >= (b).z ) ? 0xFFFFFFFF : 0x0, !( (a).w >= (b).w ) ? 0xFFFFFFFF : 0x0 } )


// Some useful macro for sse math


#define _SSE_MIN_FLOAT4( a, b ) ( (_float4) { Math::Min( (a).x, (b).x ), Math::Min( (a).y, (b).y ), Math::Min( (a).z, (b).z ), Math::Min( (a).w, (b).w ) } )
#define _SSE_MIN4_FLOAT4( a, b, c, d ) _SSE_MIN_FLOAT4( _SSE_MIN_FLOAT4( a, b ), _SSE_MIN_FLOAT4( c, d ) )
#define _SSE_MIN5_FLOAT4( a, b, c, d, e ) _SSE_MIN_FLOAT4( _SSE_MIN_FLOAT4( _SSE_MIN_FLOAT4( a, b ), _SSE_MIN_FLOAT4( c, d ) ), e )

#define _SSE_MAX_FLOAT4( a, b ) ( (_float4) { Math::Max( (a).x, (b).x ), Math::Max( (a).y, (b).y ), Math::Max( (a).z, (b).z ), Math::Max( (a).w, (b).w ) } )
#define _SSE_MAX4_FLOAT4( a, b, c, d ) _SSE_MAX_FLOAT4( _SSE_MAX_FLOAT4( a, b ), _SSE_MAX_FLOAT4( c, d ) )
#define _SSE_MAX5_FLOAT4( a, b, c, d, e ) _SSE_MAX_FLOAT4( _SSE_MAX_FLOAT4( _SSE_MAX_FLOAT4( a, b ), _SSE_MAX_FLOAT4( c, d ) ), e )

#define _SSE_ADD_FLOAT4( a, b ) ( (_float4) { (a).x + (b).x, (a).y + (b).y, (a).z + (b).z, (a).w + (b).w } )
#define _SSE_ADD_FLOAT4S( a, b ) ( (_float4) { (a).x + (b).x, (a).y, (a).z, (a).w } )
#define _SSE_ADD3_FLOAT4( a, b, c ) _SSE_ADD_FLOAT4( _SSE_ADD_FLOAT4( a, b ), c )
#define _SSE_ADD4_FLOAT4( a, b, c, d ) _SSE_ADD_FLOAT4( _SSE_ADD_FLOAT4( a, b ), _SSE_ADD_FLOAT4( c, d ) )

#define _SSE_SUB_FLOAT4( a, b ) ( (_float4) { (a).x - (b).x, (a).y - (b).y, (a).z - (b).z, (a).w - (b).w } )
#define _SSE_SUB_FLOAT4S( a, b ) ( (_float4) { (a).x - (b).x, (a).y, (a).z, (a).w } )
#define _SSE_MUL_FLOAT4( a, b ) ( (_float4) { (a).x * (b).x, (a).y * (b).y, (a).z * (b).z, (a).w * (b).w } )

#define _SSE_DIV_FLOAT4( a, b ) ( (_float4) { (a).x / (b).x, (a).y / (b).y, (a).z / (b).z, (a).w / (b).w } )

#define _SSE_MADD_FLOAT4( a, b, c ) _SSE_ADD_FLOAT4( _SSE_SUB_FLOAT4( a, b ), c )
#define _SSE_LERP_FLOAT4( a, b, t ) _SSE_MADD_FLOAT4( _SSE_SUB_FLOAT4( b, a ), t, a )

#define _SSE_DOT4x4_FLOAT4( a0, a1, a2, a3, b0, b1, b2, b3 ) \
	_SSE_ADD4_FLOAT4( _SSE_MUL_FLOAT4( a0, b0 ), _SSE_MUL_FLOAT4( a1, b1 ), _SSE_MUL_FLOAT4( a2, b2 ), _SSE_MUL_FLOAT4( a3, b3 ) )
#define _SSE_DOT4x3_FLOAT4( a0, a1, a2, a3, b0, b1, b2 ) \
	_SSE_ADD4_FLOAT4( _SSE_MUL_FLOAT4( a0, b0 ), _SSE_MUL_FLOAT4( a1, b1 ), _SSE_MUL_FLOAT4( a2, b2 ), a3 )
#define _SSE_DOT3x3_FLOAT4( a0, a1, a2, b0, b1, b2 ) \
	_SSE_ADD3_FLOAT4( _SSE_MUL_FLOAT4( a0, b0 ), _SSE_MUL_FLOAT4( a1, b1 ), _SSE_MUL_FLOAT4( a2, b2 ) )

#define _SSE_UNPACKL_FLOAT4( a, b ) ( (_float4) { (a).x, (b).x, (a).y, (b).y } )

#define _SSE_UNPACKH_FLOAT4( a, b ) ( (_float4) { (a).z, (b).z, (a).w, (b).w } )
#define _SSE_MOVELH_FLOAT4( a, b ) ( (_float4) { (a).x, (a).y, (b).x, (b).y } )
#define _SSE_MOVEHL_FLOAT4( a, b ) ( (_float4) { (b).z, (b).w, (a).z, (a).w } )

#define _SSE_SHUFFLE_FLOAT( a, b, c ) a

#endif

#define _SSE_ROR_FLOAT4( vec, i ) ( ( ( i ) % 4 ) ? ( _SSE_SHUFFLE_FLOAT ( vec, vec, \
	_MM_SHUFFLE( (_byte)( i + 3 ) % 4, (_byte)( i + 2 ) % 4, (_byte)( i + 1 ) % 4, (_byte) ( i + 0 ) % 4 ) ) ) : ( vec ) )


// Some useful macro for matrix


#define _SSE_TRANSPOSE_MATRIX4x3( v0, v1, v2 )											\
	{																					\
		_float4 t0, t1, t2;																\
																						\
																/* r00 r01 r02 r10 */	\
																/* r11 r12 r20 r21 */	\
																/* r22 r30 r31 r32 */	\
																						\
		t0 = _SSE_SHUFFLE_FLOAT( v0, v2, _MM_SHUFFLE(3,0,3,0) );/* r00 r10 r22 r32 */	\
		t1 = _SSE_SHUFFLE_FLOAT( v0, v1, _MM_SHUFFLE(1,0,2,1) );/* r01 r02 r11 r12 */	\
		t2 = _SSE_SHUFFLE_FLOAT( v1, v2, _MM_SHUFFLE(2,1,3,2) );/* r20 r21 r30 r31 */	\
																						\
		v0 = _SSE_SHUFFLE_FLOAT( t0, t2, _MM_SHUFFLE(2,0,1,0) );/* r00 r10 r20 r30 */	\
		v1 = _SSE_SHUFFLE_FLOAT( t1, t2, _MM_SHUFFLE(3,1,2,0) );/* r01 r11 r21 r31 */	\
		v2 = _SSE_SHUFFLE_FLOAT( t1, t0, _MM_SHUFFLE(3,2,3,1) );/* r02 r12 r22 r32 */	\
	}

#define _SSE_TRANSPOSE_MATRIX3x4( v0, v1, v2 )											\
	{																					\
		_float4 t0, t1, t2;																\
																						\
																/* r00 r10 r20 r30 */	\
																/* r01 r11 r21 r31 */	\
																/* r02 r12 r22 r32 */	\
																						\
		t0 = _SSE_SHUFFLE_FLOAT( v0, v2, _MM_SHUFFLE(2,0,3,1) );/* r10 r30 r02 r22 */	\
		t1 = _SSE_SHUFFLE_FLOAT( v1, v2, _MM_SHUFFLE(3,1,3,1) );/* r11 r31 r12 r32 */	\
		t2 = _SSE_SHUFFLE_FLOAT( v0, v1, _MM_SHUFFLE(2,0,2,0) );/* r00 r20 r01 r21 */	\
																						\
		v0 = _SSE_SHUFFLE_FLOAT( t2, t0, _MM_SHUFFLE(0,2,2,0) );/* r00 r01 r02 r10 */	\
		v1 = _SSE_SHUFFLE_FLOAT( t1, t2, _MM_SHUFFLE(3,1,2,0) );/* r11 r12 r20 r21 */	\
		v2 = _SSE_SHUFFLE_FLOAT( t0, t1, _MM_SHUFFLE(3,1,1,3) );/* r22 r30 r31 r32 */	\
	}

#define _SSE_TRANSPOSE_MATRIX4x4( r0, r1, r2, r3 )										\
	{																					\
		_float4 s3, s2, s1, s0;															\
																						\
																/* r00 r01 r02 r03 */	\
																/* r10 r11 r12 r13 */	\
																/* r20 r21 r22 r23 */	\
																/* r30 r31 r32 r33 */	\
																						\
		s0 = _SSE_UNPACKL_FLOAT4( r0, r1 );						/* r00 r10 r01 r11 */	\
		s2 = _SSE_UNPACKH_FLOAT4( r0, r1 );						/* r02 r12 r03 r13 */	\
		s1 = _SSE_UNPACKL_FLOAT4( r2, r3 );						/* r20 r30 r21 r31 */	\
		s3 = _SSE_UNPACKH_FLOAT4( r2, r3 );						/* r22 r32 r23 r33 */	\
																						\
		r0 = _SSE_MOVELH_FLOAT4( s0, s1 );						/* r00 r10 r20 r30 */	\
		r1 = _SSE_MOVEHL_FLOAT4( s1, s0 );						/* r01 r11 r21 r31 */	\
		r2 = _SSE_MOVELH_FLOAT4( s2, s3 );						/* r02 r12 r22 r32 */	\
		r3 = _SSE_MOVEHL_FLOAT4( s3, s2 );						/* r03 r13 r23 r33 */	\
	}

#define _SSE_LOAD_MATRIX3x4( row0, row1, row2, matrix )									\
	{																					\
		row0 = * (_float4*)( matrix[0] );												\
		row1 = * (_float4*)( matrix[1] );												\
		row2 = * (_float4*)( matrix[2] );												\
	}

#define _SSE_LOAD_MUL_MATRIX3x4( row0, row1, row2, matrix, weight )						\
	{																					\
		_float4 w = _SSE_LOAD_FLOAT( weight );											\
		row0 = _SSE_MUL_FLOAT4( * (_float4*)( matrix[0] ), w );							\
		row1 = _SSE_MUL_FLOAT4( * (_float4*)( matrix[1] ), w );							\
		row2 = _SSE_MUL_FLOAT4( * (_float4*)( matrix[2] ), w );							\
	}

#define _SSE_LOAD_MADD_MATRIX3x4( row0, row1, row2, matrix, weight )					\
	{																					\
		_float4 w = _SSE_LOAD_FLOAT( weight );											\
		row0 = _SSE_MADD_FLOAT4( * (_float4*)( matrix[0] ), w, row0 );					\
		row1 = _SSE_MADD_FLOAT4( * (_float4*)( matrix[1] ), w, row1 );					\
		row2 = _SSE_MADD_FLOAT4( * (_float4*)( matrix[2] ), w, row2 );					\
	}

#define _SSE_TRANSFORM_AABB( a1, a2, a3, a4, m0, m1, m2, min, max )						\
	{																					\
		_float4 a10 = _SSE_MUL_FLOAT4( a1, m0 ); /* sum x. */							\
		_float4 a11 = _SSE_MUL_FLOAT4( a1, m1 ); /* sum y. */							\
		_float4 a12 = _SSE_MUL_FLOAT4( a1, m2 ); /* sum z. */							\
																						\
		_float4 a20 = _SSE_MUL_FLOAT4( a2, m0 ); /* sum x. */							\
		_float4 a21 = _SSE_MUL_FLOAT4( a2, m1 ); /* sum y. */							\
		_float4 a22 = _SSE_MUL_FLOAT4( a2, m2 ); /* sum z. */							\
																						\
		_float4 a30 = _SSE_MUL_FLOAT4( a3, m0 ); /* sum x. */							\
		_float4 a31 = _SSE_MUL_FLOAT4( a3, m1 ); /* sum y. */							\
		_float4 a32 = _SSE_MUL_FLOAT4( a3, m2 ); /* sum z. */							\
																						\
		_float4 a40 = _SSE_MUL_FLOAT4( a4, m0 ); /* sum x. */							\
		_float4 a41 = _SSE_MUL_FLOAT4( a4, m1 ); /* sum y. */							\
		_float4 a42 = _SSE_MUL_FLOAT4( a4, m2 ); /* sum z. */							\
																						\
		_SSE_TRANSPOSE_MATRIX4x4( a10, a20, a30, a40 );									\
		_SSE_TRANSPOSE_MATRIX4x4( a11, a21, a31, a41 );									\
		_SSE_TRANSPOSE_MATRIX4x4( a12, a22, a32, a42 );									\
																						\
		_float4 x = _SSE_ADD3_FLOAT4( a10, a20, a30 ); /* X1, X2, X3, X4 */				\
		_float4 y = _SSE_ADD3_FLOAT4( a11, a21, a31 ); /* Y1, Y2, Y3, Y4 */				\
		_float4 z = _SSE_ADD3_FLOAT4( a12, a22, a32 ); /* Z1, Z2, Z3, Z4 */				\
		_float4 w = _SSE_LOAD_ZERO( );													\
																						\
		_SSE_TRANSPOSE_MATRIX4x4( x, y, z, w );											\
																						\
		min = _SSE_MIN4_FLOAT4( x, y, z, w );											\
		max = _SSE_MAX4_FLOAT4( x, y, z, w );											\
	}

namespace Xixels
{
#ifdef _EXTEND_INSTRUCTIONS

#if !defined( _XX_OS_IOS ) && !defined( _XX_OS_ANDROID )

const _float4 _VECTOR4_X_AXIS = _mm_set_ps( 0.0f, 0.0f, 0.0f, 1.0f );
const _float4 _VECTOR4_Y_AXIS = _mm_set_ps( 0.0f, 0.0f, 1.0f, 0.0f );
const _float4 _VECTOR4_Z_AXIS = _mm_set_ps( 0.0f, 1.0f, 0.0f, 0.0f );
const _float4 _VECTOR4_W_AXIS = _mm_set_ps( 1.0f, 0.0f, 0.0f, 0.0f );

#else

const _float4 _VECTOR4_X_AXIS = _NEON_GETFLOAT4( 0.0f, 0.0f, 0.0f, 1.0f );
const _float4 _VECTOR4_Y_AXIS = _NEON_GETFLOAT4( 0.0f, 0.0f, 1.0f, 0.0f );
const _float4 _VECTOR4_Z_AXIS = _NEON_GETFLOAT4( 0.0f, 1.0f, 0.0f, 0.0f );
const _float4 _VECTOR4_W_AXIS = _NEON_GETFLOAT4( 1.0f, 0.0f, 0.0f, 0.0f );

#endif

#endif

inline _bool _SSE_CMP_EQ( const _float4& a, const _float4& b )
{
	#ifdef _EXTEND_INSTRUCTIONS

	#if !defined( _XX_OS_IOS ) && !defined( _XX_OS_ANDROID )

	_float4 c = _mm_cmpeq_ps( a, b );
	return _mm_movemask_ps( c ) == 0x0F;

	#else

	uint32x4_t ret = vceqq_f32( a, b );
	return vgetq_lane_u32( ret, 0 ) == 0xffffffff && vgetq_lane_u32( ret, 1 ) == 0xffffffff && vgetq_lane_u32( ret, 2 ) == 0xffffffff && vgetq_lane_u32( ret, 3 ) == 0xffffffff;

	#endif

	#endif
}

inline _bool _SSE_CMP_NEQ( const _float4& a, const _float4& b )
{
	#ifdef _EXTEND_INSTRUCTIONS

	#if !defined( _XX_OS_IOS ) && !defined( _XX_OS_ANDROID )

	_float4 c = _mm_cmpeq_ps( a, b );
	return _mm_movemask_ps( c ) != 0x0F;

	#else

	uint32x4_t ret = vceqq_f32( a, b );
	return vgetq_lane_u32( ret, 0 ) != 0xffffffff || vgetq_lane_u32( ret, 1 ) != 0xffffffff || vgetq_lane_u32( ret, 2 ) != 0xffffffff || vgetq_lane_u32( ret, 3 ) != 0xffffffff;

	#endif

	#endif
}

inline _bool _SSE_CMP_EQ2( const _float4& a, const _float* b )
{
	#ifdef _EXTEND_INSTRUCTIONS

	#if !defined( _XX_OS_IOS ) && !defined( _XX_OS_ANDROID )

	_float4 c = _mm_cmpeq_ps( a, _SSE_LOAD_FLOATS( b[3], b[2], b[1], b[0] ) );
	return _mm_movemask_ps( c ) == 0x0F;

	#else

	uint32x4_t ret = vceqq_f32( a, _NEON_GETFLOAT4( b[3], b[2], b[1], b[0] ) );
	return vgetq_lane_u32( ret, 0 ) == 0xffffffff && vgetq_lane_u32( ret, 1 ) == 0xffffffff && vgetq_lane_u32( ret, 2 ) == 0xffffffff && vgetq_lane_u32( ret, 3 ) == 0xffffffff;

	#endif

	#endif
}

inline _bool _SSE_CMP_NEQ2( const _float4& a, const _float* b )
{
	#ifdef _EXTEND_INSTRUCTIONS

	#if !defined( _XX_OS_IOS ) && !defined( _XX_OS_ANDROID )

	_float4 c = _mm_cmpeq_ps( a, _SSE_LOAD_FLOATS( b[3], b[2], b[1], b[0] ) );
	return _mm_movemask_ps( c ) != 0x0F;

	#else

	uint32x4_t ret = vceqq_f32( a, _NEON_GETFLOAT4( b[3], b[2], b[1], b[0] ) );
	return vgetq_lane_u32( ret, 0 ) != 0xffffffff || vgetq_lane_u32( ret, 1 ) != 0xffffffff || vgetq_lane_u32( ret, 2 ) != 0xffffffff || vgetq_lane_u32( ret, 3 ) != 0xffffffff;

	#endif

	#endif
}

};
