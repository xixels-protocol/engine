#pragma once

namespace Xixels
{

class IPhysicsFactory
{
public:
	virtual ITagPoint*			CreateTagPoint( ) = 0;
	virtual ITagPoint*			CreateTagPoint( const Matrix4& mat ) = 0;
	virtual ITagPoint*			CloneTagPoint( ITagPoint* tp, _bool ref = _true ) = 0;
	virtual _void				ReleaseTagPoint( ITagPoint*& tp ) = 0;
};

};