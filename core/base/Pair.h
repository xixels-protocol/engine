#pragma once

namespace Xixels
{

template< typename Type1, typename Type2 > class Pair
{
public:
	Type1	obj1;
	Type2	obj2;

public:
	inline Pair( )
		{ }
	inline Pair( const Type1& o1, const Type2& o2 )
		: obj1( o1 ), obj2( o2 ) { }

	inline operator const Type1& ( ) const
		{ return obj1; }
};

};