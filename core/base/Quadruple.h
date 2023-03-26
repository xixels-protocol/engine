#pragma once

namespace Xixels
{

template< typename Type1, typename Type2, typename Type3, typename Type4 > class Quadruple
{
public:
	Type1	obj1;
	Type2	obj2;
	Type3	obj3;
	Type4	obj4;

public:
	inline Quadruple( )
		{ }
	inline Quadruple( const Type1& o1, const Type2& o2, const Type3& o3, const Type4& o4 )
		: obj1( o1 ), obj2( o2 ), obj3( o3 ), obj4( o4 ) { }

	inline operator const Type1& ( ) const
		{ return obj1; }
};

};