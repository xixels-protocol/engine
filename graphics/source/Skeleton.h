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

	virtual _dword GetBoneCount( ) const
		{ return mBones.Length( ); }
	virtual IBone* GetBone( _dword index ) const
		{ return mBones.IsIndexValid( (_long) index ) ? mBones[ index ] : _null; }

	virtual IBone*			CreateBone( StringPtr name, _dword parentid, _bool dummy );
	virtual _void			ReleaseBone( IBone*& bone );
	virtual _void			ClearBone( );

	virtual IBone*			GetBone( StringPtr name ) const;

	virtual _void			Skinning( Geometry& geo );
};

};