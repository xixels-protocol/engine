#include "Math.h"
#include "Matrix2.h"
#include "Matrix3.h"
#include "Vector2.h"

const Vector2 Vector2::cOrigin( 0.0f, 0.0f );
const Vector2 Vector2::cIdentity( 1.0f, 1.0f );
const Vector2 Vector2::cXAxis( 1.0f, 0.0f );
const Vector2 Vector2::cYAxis( 0.0f, 1.0f );
const Vector2 Vector2::cMaxVector( Math::cMaxFloat, Math::cMaxFloat );
const Vector2 Vector2::cMinVector( Math::cMinFloat, Math::cMinFloat );

Vector2& Vector2::operator *= ( const Matrix2& mat )
{
	_float xx = x, yy = y;

	x = xx * mat.m[0][0] + yy * mat.m[1][0];
	y = xx * mat.m[0][1] + yy * mat.m[1][1];

	x = xx * mat.m[0][0] + yy * mat.m[1][0];
	y = xx * mat.m[0][1] + yy * mat.m[1][1];

	return *this;
}

Vector2& Vector2::operator *= ( const Matrix3& mat )
{
	_float xx = x, yy = y;

	x = xx * mat.m[0][0] + yy * mat.m[1][0] + mat.m[2][0];
	y = xx * mat.m[0][1] + yy * mat.m[1][1] + mat.m[2][1];

	return *this;
}