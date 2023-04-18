#pragma once

namespace Xixels
{

class Skeleton : public ISkeleton, public ReferencedObject
{
private:
	Skeleton*				mResource;
	Array< Bone* >			mBones;

public:
	Skeleton( );
	Skeleton( Skeleton* skeleton );
	~Skeleton( );

	inline _void AttachResource( Skeleton* res )
		{ if ( mResource != _null ) return; mResource = res; if ( res != _null ) res->IncRefCount( ); }

	_void UpdateBones( _dword elapse = 0 );
};

};