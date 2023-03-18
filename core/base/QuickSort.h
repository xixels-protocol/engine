#pragma once

#include "Typedef.h"

namespace Xixels
{

template< typename Type, typename Key = Type > class QuickSort
{
private:
	static _void SortAscendingHelper( Type elements[], _long l, _long r )
	{
		if ( l >= r )
			return;

		_long i = l - 1, j = r + 1, c = ( l + r ) / 2;

		Key center = (const Key&) elements[c];

		while ( _true )
		{
			// Find the element that less than center from left to right.
			while ( i < r && (const Key&) elements[ ++ i ] < center );
			// Find the element that greater than center from right to left.
			while ( j > l && (const Key&) elements[ -- j ] > center );

			if ( i >= j )
				break;

			// Swap two element.
			Math::Swap( elements[i], elements[j] );
		}

		SortAscendingHelper( elements, l, i - 1 );
		SortAscendingHelper( elements, j + 1, r );
	}

	static _void SortDescendingHelper( Type elements[], _long l, _long r )
	{
		if ( l >= r )
			return;

		_long i = l - 1, j = r + 1, c = ( l + r ) / 2;

		Key center = (const Key&) elements[c];

		while ( _true )
		{
			// Find the element that greater than center from left to right.
			while ( i < r && (const Key&) elements[ ++ i ] > center );
			// Find the element that less than center from right to left.
			while ( j > l && (const Key&) elements[ -- j ] < center );

			if ( i >= j )
				break;

			// Swap two element.
			Math::Swap( elements[i], elements[j] );
		}

		SortDescendingHelper( elements, l, i - 1 );
		SortDescendingHelper( elements, j + 1, r );
	}

public:
	inline static _void SortAscending( Type elements[], _dword n )
		{ if ( n > 0 ) SortAscendingHelper( elements, 0, n - 1 ); }

	inline static _void SortDescending( Type elements[], _dword n )
		{ if ( n > 0 ) SortDescendingHelper( elements, 0, n - 1 ); }
};

};