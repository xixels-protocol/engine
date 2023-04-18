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
};

};