#pragma once

namespace Xixels
{

template< typename Type1, typename Type2, typename Type3 > class Triple
{
public:
	Type1	obj1;
	Type2	obj2;
	Type3	obj3;

public:
	inline Triple( )
		{ }
	inline Triple( const Type1& o1, const Type2& o2, const Type3& o3 )
		: obj1( o1 ), obj2( o2 ), obj3( o3 ) { }

	inline operator const Type1& ( ) const
		{ return obj1; }
};

};