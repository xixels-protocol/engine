#include "Math.hpp"

using namespace Xixels;

const _float Math::cZero			= 0.0f;
const _float Math::cOne				= 1.0f;
const _float Math::cPi				= 3.141592654f;
const _float Math::c2Pi				= 6.283185308f;
const _float Math::cPiOver2			= 1.570796327f;
const _float Math::cPiOver4			= 0.785398164f;
const _float Math::cE				= 2.718281828f;
const _float Math::cEpsilon			= 0.00001f;
const _float Math::cMaxFloat		= 3.402823466e+38f;
const _float Math::cMinFloat		= -3.402823466e+38f;
const _float Math::cMinLowpFloat	= 3.90625e-3f;
const _float Math::cMaxLowpFloat	= 2.0f;
const _float Math::cMinMediumFloat	= 6.10351563e-5f;
const _float Math::cMaxMediumFloat	= 1.6384e+4f;

_float Math::Ceil( _float value )
{
	return ::ceilf( value );
}

_double Math::CeilD( _double value )
{
	return ::ceil( value );
}

_float Math::Floor( _float value )
{
	return ::floorf( value );
}

_double Math::FloorD( _double value )
{
	return ::floor( value );
}

_float Math::Round( _float value )
{
	return ( value > 0.0f ) ? ::floorf( value + 0.5f ) : ::ceilf( value - 0.5f );
}

_double Math::RoundD( _double value )
{
	return ( value > 0.0f ) ? ::floor( value + 0.5f ) : ::ceil( value - 0.5f );
}

_float Math::Fmod( _float valuex, _float valuey )
{
	return ::fmodf( valuex, valuey );
}

_double Math::FmodD( _double valuex, _double valuey )
{
	return ::fmod( valuex, valuey );
}

_float Math::Sqrt( _float value )
{
	return ::sqrtf( value );
}

_double Math::SqrtD( _double value )
{
	return ::sqrt( value );
}

_float Math::Exp( _float value )
{
	return ::expf( value );
}

_double Math::ExpD( _double value )
{
	return ::exp( value );
}

_float Math::Log( _float value )
{
	return ::logf( value );
}

_double Math::LogD( _double value )
{
	return ::log( value );
}

_float Math::Pow( _float base, _float exponent )
{
	return ::powf( base, exponent );
}

_double Math::PowD( _double base, _double exponent )
{
	return ::pow( base, exponent );
}

_void Math::Modf( _double number, _long& ipart, _double& fpart )
{
	_double i;
	fpart = ::modf( number, &i );
	ipart = (_long) i;
}

_bool Math::IsPowerOfTwo( _dword number )
{
	return ( number & -( (_long) number ) ) == number;
}

_dword Math::NextPowerOfTwo( _dword number )
{
	number -= 1;
	number |= number >> 16;
	number |= number >> 8;
	number |= number >> 4;
	number |= number >> 2;
	number |= number >> 1;
	number += 1;

	return number;
}

_dword Math::Align( _dword value, _dword alignment )
{
	if ( alignment <= 1 )
		return value;

	_dword a = alignment - 1;
	return ( value + a ) & ~a;
}

_float Math::Sin( _float radian )
{
	return ::sinf( radian );
}

_double Math::SinD( _double radian )
{
	return ::sin( radian );
}

_float Math::Cos( _float radian )
{
	return ::cosf( radian );
}

_double Math::CosD( _double radian )
{
	return ::cos( radian );
}

_float Math::Tan( _float radian )
{
	return ::tanf( radian );
}

_double Math::TanD( _double radian )
{
	return ::tan( radian );
}

_float Math::Cot( _float radian )
{
	return 1.0f / ::tanf( radian );
}

_double Math::CotD( _double radian )
{
	return 1.0 / ::tan( radian );
}

_float Math::Asin( _float value )
{
	if ( value > 1.0f )
		return cPi / 2.0f;

	if ( value < -1.0f )
		return cPi / -2.0f;

	return ::asinf( value );
}

_double Math::AsinD( _double value )
{
	if ( value > 1.0 )
		return cPi / 2.0;

	if ( value < -1.0 )
		return cPi / -2.0;

	return ::asin( value );
}

_float Math::Acos( _float value )
{
	if ( value > 1.0f )
		return 0.0f;

	if ( value < -1.0f )
		return cPi;

	return ::acosf( value );
}

_double Math::AcosD( _double value )
{
	if ( value > 1.0 )
		return 0.0;

	if ( value < -1.0f )
		return cPi;

	return ::acos( value );
}

_float Math::Atan( _float value )
{
	return ::atanf( value );
}

_double Math::AtanD( _double value )
{
	return ::atan( value );
}

_float Math::Atan( _float valuey, _float valuex )
{
	return ::atan2f( valuey, valuex );
}

_double Math::AtanD( _double valuey, _double valuex )
{
	return ::atan2( valuey, valuex );
}

_bool Math::Equal( _float valuex, _float valuey, _float margin )
{
	return ( Abs( valuex - valuey ) < margin );
}

_bool Math::EqualD( _double valuex, _double valuey, _double margin )
{
	return ( Abs( valuex - valuey ) < margin );
}