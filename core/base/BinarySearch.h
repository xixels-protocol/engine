#pragma once

namespace Xixels
{

template< typename Type, typename Key = Type > class BinarySearch
{
public:
	static _dword SearchAscending( const Type elements[], const Key& key, _dword n, _dword& l, _dword& r )
	{
		if ( n == 0 )
			return -1;

		_long i = 0, j = n - 1;

		while ( i < j - 1 )
		{
			_long m = ( i + j ) / 2;

			if ( key == (const Key&) elements[m] )
			{
				l = m;
				r = m;

				return m;
			}

			if ( key > (const Key&) elements[m] )
				i = m;
			else
				j = m;
		}

		l = (_dword) i;
		r = (_dword) j;

		return (_dword) i;
	}

	static _dword SearchAscendingWithRange( const Type elements[], const Key& key, _dword s, _dword n, _dword& l, _dword& r )
	{
		if ( n == 0 )
			return -1;

		_long i = s, j = n - 1;

		while ( i < j - 1 )
		{
			_long m = ( i + j ) / 2;

			if ( key == (const Key&) elements[m] )
			{
				l = m;
				r = m;

				return m;
			}

			if ( key > (const Key&) elements[m] )
				i = m;
			else
				j = m;
		}

		l = (_dword) i;
		r = (_dword) j;

		return (_dword) i;
	}

	static _dword SearchDescending( const Type elements[], const Key& key, _dword n, _dword& l, _dword& r )
	{
		if ( n == 0 )
			return -1;

		_long i = 0, j = n - 1;

		while ( i < j - 1 )
		{
			_long m = ( i + j ) / 2;

			if ( key == (const Key&) elements[m] )
			{
				l = m;
				r = m;

				return m;
			}

			if ( key < (const Key&) elements[m] )
				i = m;
			else
				j = m;
		}

		l = (_dword) i;
		r = (_dword) j;

		return (_dword) i;
	}
};

};