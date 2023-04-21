#pragma once

namespace Xixels
{

class ReferencedObject
{
private:
	_dword	mRefCount;

private:
	ReferencedObject( const ReferencedObject& );
	ReferencedObject& operator = ( const ReferencedObject& );

protected:
	inline ReferencedObject( )
		: mRefCount( 1 ) { }

public:
	inline _dword GetRefCount( ) const
		{ return mRefCount; }
	inline _dword IncRefCount( )
		{ mRefCount ++; return mRefCount; }
	inline _dword DecRefCount( )
		{ if ( mRefCount != 0 ) mRefCount --; return mRefCount; }
};

};