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
// Handle to a win32 kernel object.
typedef void*				_handle;

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

};
