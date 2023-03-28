#pragma once

namespace Xixels
{

class Color
{
public:
	// The null color, has RGBA as 0.0f, 0.0f, 0.0f, 0.0f.
	const static Color cNull;

	// Red, #FF0000
	const static Color cRed;
	// Dark red, #8B0000
	const static Color cDarkRed;
	// Indian red, #CD5C5C
	const static Color cIndianRed;
	// Orange red, #FF4500
	const static Color cOrangeRed;

	// Green, #00FF00
	const static Color cGreen;
	// Dark green, #008B00
	const static Color cDarkGreen;
	// Lawn green, #7CFC00
	const static Color cLawnGreen;
	// Sea green, #2E8B57
	const static Color cSeaGreen;

	// Blue, #0000FF
	const static Color cBlue;
	// Dark blue, #00008B
	const static Color cDarkBlue;
	// Sky blue, #00BFFF
	const static Color cSkyBlue;
	// Midnight blue, #191970
	const static Color cMidnightBlue;

	// White, #FFFFFF
	const static Color cWhite;
	// Black, #000000
	const static Color cBlack;
	// Gray, #808080
	const static Color cGray;
	// LinearGray #373737
	const static Color cLinearGray;
	// Silver, #C0C0C0
	const static Color cSilver;

	// Yellow, #FFFF00
	const static Color cYellow;
	// Purple, #800080
	const static Color cPurple;
	// Teal, #008080
	const static Color cTeal;
	// Lime, #00FF00
	const static Color cLime;
	// Tomato, #FF6347
	const static Color cTomato;
	// Orange, #FFA500
	const static Color cOrange;
	// Brown, #A52A2A
	const static Color cBrown;
	// Bisque, #FFE4C4
	const static Color cBisque;
	// Pink, #FFC0CB
	const static Color cPink;
	// Violet, #EE82EE
	const static Color cViolet;
	// Magenta, #FF00FF
	const static Color cMagenta;
	// Orchid, #DA70D6
	const static Color cOrchid;
	// Chocolate, #D2691E
	const static Color cChocolate;

public:
	_float	r;
	_float	g;
	_float	b;
	_float	a;

public:
	inline Color( )
		{ }
	inline Color( _float rr, _float gg, _float bb, _float aa = 1.0f )
		: r( rr ), g( gg ), b( bb ), a( aa ) { }
	inline Color( _dword c )
		{ Dword cc( c ); a = cc.Byte4( ) / 255.0f; r = cc.Byte3( ) / 255.0f; g = cc.Byte2( ) / 255.0f; b = cc.Byte1( ) / 255.0f; }

	inline operator _dword ( ) const
	{
		_dword rr = (_byte) ( Math::Clamp( r, 0.0f, 1.0f ) * 255.0f );
		_dword gg = (_byte) ( Math::Clamp( g, 0.0f, 1.0f ) * 255.0f );
		_dword bb = (_byte) ( Math::Clamp( b, 0.0f, 1.0f ) * 255.0f );
		_dword aa = (_byte) ( Math::Clamp( a, 0.0f, 1.0f ) * 255.0f );
		return ( aa << 24 ) | ( rr << 16 ) | ( gg << 8 ) | ( bb );
	}

	inline Color operator + ( ) const
		{ return Color( r, g, b, a ); }
	inline Color operator - ( ) const
		{ return Color( 1.0f - r, 1.0f - g, 1.0f - b, 1.0f - a ); }

	inline Color& operator += ( const Color& c )
		{ r += c.r; g += c.g; b += c.b; a += c.a; return *this; }
	inline Color& operator -= ( const Color& c )
		{ r -= c.r; g -= c.g; b -= c.b; a -= c.a; return *this; }

	inline Color operator + ( const Color& c ) const
		{ return Color( r + c.r, g + c.g, b + c.b, a + c.a ); }
	inline Color operator - ( const Color& c ) const
		{ return Color( r - c.r, g - c.g, b - c.b, a - c.a ); }

	inline Color& operator *= ( _float s )
		{ r *= s; g *= s; b *= s; a *= s; return *this; }
	inline Color& operator /= ( _float s )
		{ r /= s; g /= s; b /= s; a /= s; return *this; }

	inline Color operator * ( _float s ) const
		{ return Color( r * s, g * s, b * s, a * s ); }
	inline Color operator / ( _float s ) const
		{ return Color( r / s, g / s, b / s, a / s ); }

	inline Color& operator *= ( const Color& c )
		{ r *= c.r; g *= c.g; b *= c.b; a *= c.a; return *this; }
	inline Color& operator /= ( const Color& c )
		{ r /= c.r; g /= c.g; b /= c.b; a /= c.a; return *this; }

	inline Color operator * ( const Color& c ) const
		{ return Color( r * c.r, g * c.g, b * c.b, a * c.a ); }
	inline Color operator / ( const Color& c ) const
		{ return Color( r / c.r, g / c.g, b / c.b, a / c.a ); }

	inline _bool operator == ( const Color& c ) const
		{ return r == c.r && g == c.g && b == c.b && a == c.a; }
	inline _bool operator != ( const Color& c ) const
		{ return r != c.r || g != c.g || b != c.b || a != c.a; }

};

};