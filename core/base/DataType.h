#pragma once

#include "Typedef.h"
#include "Memory.h"

namespace Xixels
{

class String;
class StringPtr;

class Tiny
{
private:
	_tiny	mValue;

public:
	inline explicit Tiny( _tiny value )
		: mValue( value ) { }

	explicit Tiny( StringPtr str );

	inline operator _tiny ( ) const
		{ return mValue; }
	inline operator _tiny& ( )
		{ return mValue; }

	String	ToString( ) const;
};

class Short
{
private:
	_short	mValue;

public:
	inline explicit Short( _short value )
		: mValue( value ) { }

	explicit Short( StringPtr str );

	inline operator _short ( ) const
		{ return mValue; }
	inline operator _short& ( )
		{ return mValue; }

	String	ToString( ) const;
};

class Long
{
private:
	_long	mValue;

public:
	inline explicit Long( _long value )
		: mValue( value ) { }

	explicit Long( StringPtr str );

	inline operator _long ( ) const
		{ return mValue; }
	inline operator _long& ( )
		{ return mValue; }

	String	ToString( ) const;
};

class Large
{
private:
	_large	mValue;

public:
	inline explicit Large( _large value )
		: mValue( value ) { }

	explicit Large( StringPtr str );

	inline operator _large ( ) const
		{ return mValue; }
	inline operator _large& ( )
		{ return mValue; }

	String	ToString( ) const;
};

class Byte
{
private:
	_byte	mValue;

public:
	inline explicit Byte( _byte value )
		: mValue( value ) { }

	explicit Byte( StringPtr str );

	inline operator _byte ( ) const
		{ return mValue; }
	inline operator _byte& ( )
		{ return mValue; }

	String	ToString( ) const;
};

class Word
{
private:
	_word	mValue;

public:
	inline explicit Word( _word value )
		: mValue( value ) { }
	inline explicit Word( _byte lobyte, _byte hibyte )
		{ ( (_byte*) this )[0] = lobyte; ( (_byte*) this )[1] = hibyte; }

	explicit Word( StringPtr str, _dword base = 16 );

	inline operator _word ( ) const
		{ return mValue; }
	inline operator _word& ( )
		{ return mValue; }

	inline Word InverseByteOrder( ) const
		{ return Word( ( (_byte*) this )[1], ( (_byte*) this )[0] ); }

	inline _byte LoByte( ) const
		{ return ( (_byte*) this )[0]; }
	inline _byte HiByte( ) const
		{ return ( (_byte*) this )[1]; }

	String	ToString( ) const;
};

class Dword
{
private:
	_dword	mValue;

public:
	#ifdef _Xixels_ARCH_64BIT

	inline explicit Dword( _ptr value )
		: mValue( (_dword) value ) { }

	#endif

	inline explicit Dword( _dword value )
		: mValue( value ) { }
	inline explicit Dword( _word loword, _word hiword )
		{ ( (_word*) this )[0] = loword; ( (_word*) this )[1] = hiword; }
	inline explicit Dword( _byte byte1, _byte byte2, _byte byte3, _byte byte4 )
		{ ( (_byte*) this )[0] = byte1; ( (_byte*) this )[1] = byte2; ( (_byte*) this )[2] = byte3; ( (_byte*) this )[3] = byte4; }

	explicit Dword( StringPtr str );

	inline operator _dword ( ) const
		{ return mValue; }
	inline operator _dword& ( )
		{ return mValue; }

	inline Dword InverseByteOrder( ) const
		{ return Dword( ( (_byte*) this )[3], ( (_byte*) this )[2], ( (_byte*) this )[1], ( (_byte*) this )[0] ); }

	inline Dword CircleShift1( ) const
		{ return Dword( ( (_byte*) this )[3], ( (_byte*) this )[0], ( (_byte*) this )[1], ( (_byte*) this )[2] ); }
	inline Dword CircleShift2( ) const
		{ return Dword( ( (_byte*) this )[2], ( (_byte*) this )[3], ( (_byte*) this )[0], ( (_byte*) this )[1] ); }
	inline Dword CircleShift3( ) const
		{ return Dword( ( (_byte*) this )[1], ( (_byte*) this )[2], ( (_byte*) this )[3], ( (_byte*) this )[0] ); }

	inline _byte Byte1( ) const
		{ return ( (_byte*) this )[0]; }
	inline _byte Byte2( ) const
		{ return ( (_byte*) this )[1]; }
	inline _byte Byte3( ) const
		{ return ( (_byte*) this )[2]; }
	inline _byte Byte4( ) const
		{ return ( (_byte*) this )[3]; }
	inline _word LoWord( ) const
		{ return ( (_word*) this )[0]; }
	inline _word HiWord( ) const
		{ return ( (_word*) this )[1]; }

	String	ToString( ) const;
};

class Qword
{
private:
	_qword	mValue;

public:
	inline explicit Qword( )
		: mValue( 0 ) { }
	inline explicit Qword( _qword value )
		: mValue( value ) { }
	inline explicit Qword( _dword lodword, _dword hidword )
		{ ( (_dword*) this )[0] = lodword; ( (_dword*) this )[1] = hidword; }

	explicit Qword( StringPtr str );

	inline operator _qword ( ) const
		{ return mValue; }
	inline operator _qword& ( )
		{ return mValue; }

	inline Qword InverseByteOrder( ) const
		{ return Qword( Dword( ( (_dword*) this )[1] ).InverseByteOrder( ), Dword( ( (_dword*) this )[0] ).InverseByteOrder( ) ); }

	inline _dword LoDword( ) const
		{ return ( (_dword*) this )[0]; }
	inline _dword HiDword( ) const
		{ return ( (_dword*) this )[1]; }

	static	Qword GetHashCode( _char* namebuffer, StringPtr resname, StringPtr path );

	String	ToString( ) const;
};

class Oword
{
private:
	union
	{
		struct
		{
			_dword	mDword1;
			_dword	mDword2;
			_dword	mDword3;
			_dword	mDword4;
		};

		struct
		{
			_qword	mQword1;
			_qword	mQword2;
		};
	};

public:
	inline explicit Oword( )
		: mDword1( 0 ), mDword2( 0 ), mDword3( 0 ), mDword4( 0 ) { }
	inline explicit Oword( _dword dword1, _dword dword2, _dword dword3, _dword dword4 )
		: mDword1( dword1 ), mDword2( dword2 ), mDword3( dword3 ), mDword4( dword4 ) { }
	inline explicit Oword( _qword qword1, _qword qword2 )
		: mQword1( qword1 ), mQword2( qword2 ) { }

	explicit Oword( StringPtr str );

	inline operator _dword ( ) const
		{ return mDword1; }
	inline operator _qword ( ) const
		{ return mQword1; }

	inline Oword InverseByteOrder( ) const
		{ return Oword( Qword( mQword2 ).InverseByteOrder( ), Qword( mQword1 ).InverseByteOrder( ) ); }

	inline _dword Dword1( ) const
		{ return mDword1; }
	inline _dword Dword2( ) const
		{ return mDword2; }
	inline _dword Dword3( ) const
		{ return mDword3; }
	inline _dword Dword4( ) const
		{ return mDword4; }
	inline _qword Qword1( ) const
		{ return mQword1; }
	inline _qword Qword2( ) const
		{ return mQword2; }

	inline _bool operator == ( const Oword& oword ) const
		{ return mQword1 == oword.mQword1 && mQword2 == oword.mQword2; }
	inline _bool operator != ( const Oword& oword ) const
		{ return mQword1 != oword.mQword1 || mQword2 != oword.mQword2; }
	inline _bool operator > ( const Oword& oword ) const
		{ return mQword2 > oword.mQword2 || ( mQword2 == oword.mQword2 && mQword1 > oword.mQword1 ); }
	inline _bool operator < ( const Oword& oword ) const
		{ return mQword2 < oword.mQword2 || ( mQword2 == oword.mQword2 && mQword1 < oword.mQword1 ); }

	String	ToString( ) const;
	_void	SetBits( _dword value, _dword bitp, _dword bitn );
	_dword	GetBits( _dword bitp, _dword bitn ) const;
};

class Float
{
private:
	_float	mValue;

public:
	inline explicit Float( _float value )
		: mValue( value ) { }

	explicit Float( StringPtr str );

	inline operator _float ( ) const
		{ return mValue; }
	inline operator _float& ( )
		{ return mValue; }

	String	ToString( ) const;
};

class Double
{
private:
	_double	mValue;

public:
	inline explicit Double( _double value )
		: mValue( value ) { }

	explicit Double( StringPtr str );

	inline operator _double ( ) const
		{ return mValue; }
	inline operator _double& ( )
		{ return mValue; }

	String	ToString( ) const;
};

class Buffer
{
public:
	_byte*	mBuffer;
	_dword	mLength;

public:
	inline Buffer( )
		: mBuffer( _null ), mLength( 0 ) { }
	inline Buffer( const _void* buf, _dword length )
		{ mBuffer = new _byte[ mLength = length ]; Memory::MemCpy( mBuffer, buf, mLength ); }
	inline Buffer( const Buffer& buf )
		{ mBuffer = new _byte[ mLength = buf.mLength ]; Memory::MemCpy( mBuffer, buf.mBuffer, mLength ); }
	inline Buffer& operator = ( const Buffer& buf )
	{
		if ( &buf == this )
			return *this;

		delete[] mBuffer;
		mBuffer = new _byte[ mLength = buf.mLength ];
		Memory::MemCpy( mBuffer, buf.mBuffer, mLength );
		return *this;
	}
	inline ~Buffer( )
		{ delete[] mBuffer; }
};

};