#include "Matrix4.h"

using namespace Xixels;

const Vector4 Vector4::cOrigin( 0.0f, 0.0f, 0.0f, 0.0f );
const Vector4 Vector4::cIdentity( 1.0f, 1.0f, 1.0f, 1.0f );
const Vector4 Vector4::cXAxis( 1.0f, 0.0f, 0.0f, 0.0f );
const Vector4 Vector4::cYAxis( 0.0f, 1.0f, 0.0f, 0.0f );
const Vector4 Vector4::cZAxis( 0.0f, 0.0f, 1.0f, 0.0f );
const Vector4 Vector4::cWAxis( 0.0f, 0.0f, 0.0f, 1.0f );
const Vector4 Vector4::cMaxVector( Math::cMaxFloat, Math::cMaxFloat, Math::cMaxFloat, Math::cMaxFloat );
const Vector4 Vector4::cMinVector( Math::cMinFloat, Math::cMinFloat, Math::cMinFloat, Math::cMinFloat );

Vector4& Vector4::operator *= ( const Matrix4& mat )
{
	_float xx = x, yy = y, zz = z, ww = w;

	x = xx * mat.m[0][0] + yy * mat.m[1][0] + zz * mat.m[2][0] + ww * mat.m[3][0];
	y = xx * mat.m[0][1] + yy * mat.m[1][1] + zz * mat.m[2][1] + ww * mat.m[3][1];
	z = xx * mat.m[0][2] + yy * mat.m[1][2] + zz * mat.m[2][2] + ww * mat.m[3][2];
	w = xx * mat.m[0][3] + yy * mat.m[1][3] + zz * mat.m[2][3] + ww * mat.m[3][3];

	return *this;
}