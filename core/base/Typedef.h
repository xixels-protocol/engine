#pragma once

#include <stdint.h>

#define _true		1
#define _false		0

#define _null		0
#define _invalid	( (void*) -1 )

namespace Xixels
{

// 8-bits ansi character.
typedef char				_chara;
// 16-bits unicode character.
typedef wchar_t				_charw;
// 16-bits unicode character.
typedef wchar_t				_char;

// Boolean value, 0 indicates false, other values indicate true.
typedef bool				_bool;
// Any type.
typedef void				_void;
// Unsigned integer type capable of holding a pointer to void.
typedef uintptr_t           _ptr;

// Signed 8-bits integer.
typedef int8_t			    _tiny;
// Unsigned 8-bits integer.
typedef uint8_t				_byte;

// Signed 16-bits integer.
typedef int16_t		        _short;
// Unsigned 16-bits integer.
typedef uint16_t		    _word;

// Signed 32-bits integer.
typedef int32_t			    _long;
// Unsigned 32-bits integer.
typedef uint32_t		    _dword;

// Signed 64-bits integer.
typedef int64_t             _large;
// Unsigned 64-bits integer.
typedef uint64_t            _qword;

// 32-bits floating point number.
typedef float				_float;
// 64-bits floating point number.
typedef double				_double;

#ifdef _EXTEND_INSTRUCTIONS

#if !defined( _XX_OS_IOS ) && !defined( _XX_OS_ANDROID )

// 64-bits float list.
typedef __m64				_float2;
// 128-bits float list.
typedef __m128				_float4;

#else

// 64-bits float list.
typedef float32x2_t			_float2;
// 128-bits float list.
typedef float32x4_t			_float4;

#endif

#else

typedef struct float2
{
	_float x;
	_float y;
} _float2;

typedef struct float4
{
	_float x;
	_float y;
	_float z;
	_float w;
} _float4;

};
