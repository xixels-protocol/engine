#include "String.h"
#include "StringFormatter.h"
#include <wchar.h>
#include "DataType.h"

using namespace Xixels;

Tiny::Tiny( StringPtr str )
{
	_char* temp = _null;
	mValue = _tiny( ::wcstol( str, &temp, 10 ) );
}

String Tiny::ToString( ) const
{
	return StringFormatter::FormatString( L"%d", mValue );
}

Short::Short( StringPtr str )
{
	_char* temp = _null;
	mValue = _short( ::wcstol( str, &temp, 10 ) );
}

String Short::ToString( ) const
{
	return StringFormatter::FormatString( L"%d", mValue );
}

Long::Long( StringPtr str )
{
	_char* temp = _null;
	mValue = _long( ::wcstol( str, &temp, 10 ) );
}

String Long::ToString( ) const
{
	return StringFormatter::FormatString( L"%d", mValue );
}

Large::Large( StringPtr str )
{
	_char* temp = _null;
	mValue = _large( ::_wcstoi64( str, &temp, 10 ) );
}

String Large::ToString( ) const
{
	return StringFormatter::FormatString( L"%d", (_long) mValue );
}

Byte::Byte( StringPtr str )
{
	_char* temp = _null;
	mValue = _byte( ::wcstoul( str, &temp, 16 ) );
}

String Byte::ToString( ) const
{
	return StringFormatter::FormatString( L"%.2x", mValue );
}

Word::Word( StringPtr str, _dword base )
{
	_char* temp = _null;
	mValue = _word( ::wcstoul( str, &temp, base ) );
}

String Word::ToString( ) const
{
	return StringFormatter::FormatString( L"%.4x", mValue );
}

Dword::Dword( StringPtr str )
{
	_char* temp = _null;
	mValue = (_dword) ::wcstoul( str, &temp, 16 );
}

String Dword::ToString( ) const
{
	return StringFormatter::FormatString( L"%.8x", mValue );
}

Qword::Qword( StringPtr str )
{
	_char* temp = _null;
	mValue = _qword( ::_wcstoui64( str, &temp, 16 ) );
}

Qword Qword::GetHashCode( _char* namebuffer, StringPtr resname, StringPtr path )
{
	StringPtr name = StringFormatter::FormatResName( namebuffer, path, resname );
	return Qword( name.HashCode1( ), name.HashCode2( ) );
}

String Qword::ToString( ) const
{
	return StringFormatter::FormatString( L"%.8x%.8x", ( (_dword*) this )[1], ( (_dword*) this )[0] );
}

Oword::Oword( StringPtr str )
{
	_char buffer[ 16 ];

	_long length = str.Length( );

	if ( length >= 32 )
	{
		mDword1 = Dword( str.SubStringPtr( length - 8 ) );
		mDword2	= Dword( StringPtr::Copy( buffer, str.SubStringPtr( length - 16 ), 8 ) );
		mDword3	= Dword( StringPtr::Copy( buffer, str.SubStringPtr( length - 24 ), 8 ) );
		mDword4	= Dword( StringPtr::Copy( buffer, str.SubStringPtr( length - 32 ), 8 ) );
	}
	else if ( length >= 24 )
	{
		mDword1 = Dword( str.SubStringPtr( length - 8 ) );
		mDword2	= Dword( StringPtr::Copy( buffer, str.SubStringPtr( length - 16 ), 8 ) );
		mDword3	= Dword( StringPtr::Copy( buffer, str.SubStringPtr( length - 24 ), 8 ) );
		mDword4	= Dword( StringPtr::Copy( buffer, str, length - 24 ) );
	}
	else if ( length >= 16 )
	{
		mDword1 = Dword( str.SubStringPtr( length - 8 ) );
		mDword2	= Dword( StringPtr::Copy( buffer, str.SubStringPtr( length - 16 ), 8 ) );
		mDword3	= Dword( StringPtr::Copy( buffer, str, length - 16 ) );
		mDword4	= 0;
	}
	else if ( length >= 8 )
	{
		mDword1 = Dword( str.SubStringPtr( length - 8 ) );
		mDword2	= Dword( StringPtr::Copy( buffer, str, length - 8 ) );
		mDword3	= 0;
		mDword4	= 0;
	}
	else
	{
		mDword1 = Dword( str );
		mDword2	= 0;
		mDword3	= 0;
		mDword4	= 0;
	}
}

String Oword::ToString( ) const
{
	return StringFormatter::FormatString( L"%.8x%.8x%.8x%.8x", mDword4, mDword3, mDword2, mDword1 );
}

_void Oword::SetBits( _dword value, _dword bitpos, _dword bitnum )
{
	// Set bits larger than bitnum to zero.
	value &=  bitnum < 31 ? ( 1 << bitnum ) - 1 : -1;

	if ( bitpos + bitnum > 64 )
	{
		if ( bitpos > 64 )
		{
			mQword2 |= (_qword) value << ( bitpos - 64 );
		}
		else
		{
			_dword lowbits = 64 - bitpos;
			_dword value2 = value >> lowbits;

			mQword1 |= (_qword) value << bitpos;
			mQword2 |= (_qword) value2;
		}
	}
	else
	{
		mQword1 |= (_qword) value << bitpos;
	}
}

_dword Oword::GetBits( _dword bitp, _dword bitn ) const
{
	_dword value = bitn < 31 ? ( 1 << bitn ) - 1 : -1;

	if ( bitp < 64 )
	{
		if ( ( bitp + bitn - 1 ) < 64 )
		{
			value &= mQword1 >> bitp;
		}
		else
		{
			_qword n1 = mQword1 >> bitp;
			_dword hn = bitp + bitn - 64;
			_qword n2 = mQword2 & ( (_qword) 1 << bitn );

			value &= n2 << ( bitn - hn ) | n1;
		}
	}
	else
	{
		value &= mQword2 >> ( bitp - 64 );
	}

	return value;
}

Float::Float( StringPtr str )
{
	_char* temp = _null;
	mValue = _float( ::wcstod( str, &temp ) );
}

String Float::ToString( ) const
{
	return StringFormatter::FormatString( L"%5.3f", mValue );
}

Double::Double( StringPtr str )
{
	_char* temp = _null;
	mValue = _double( ::wcstod( str, &temp ) );
}

String Double::ToString( ) const
{
	return StringFormatter::FormatString( L"%10.5f", (_float) mValue );
}