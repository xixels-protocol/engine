#pragma once

namespace Xixels
{

class SubMesh : public ISubMesh, public Resource
{
private:
	Geometry			mGeo;
	IMeshMaterial*		mMtl;

public:
	SubMesh( );
	SubMesh( StringPtr name );
	SubMesh( StringPtr name, const Geometry& geo, const Material& mtl );
	SubMesh( StringPtr name, const Geometry& geo, IMeshMaterial* mtl );
	SubMesh( SubMesh* submesh );
	~SubMesh( );

public:
	virtual Geometry& GetGeometry( )
		{ return mGeo; }
	virtual IMeshMaterial* GetMaterial( )
		{ return mMtl; }

	virtual const AxisAlignedBox& GetBoundBox( ) const
		{ return mGeo.GetBoundBox( ); }

	virtual _bool		IsReady( _bool checktex ) const;

	virtual _void		SetMaterial( IMeshMaterial* mtl );
	virtual ITagPoint*	CreateTagPoint( );

	virtual _void		Update( ISkeleton* skeleton, _dword elpase );
};

};