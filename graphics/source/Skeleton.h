#pragma once

namespace Xixels
{

class Skeleton : public ISkeleton, public ReferencedObject
{
private:
	Skeleton*				mResource;
	AxisAlignedBox			mBoundBox;
	Array< Bone* >			mBones;

	_dword					mFrameToken;
public:
	Skeleton( );
	Skeleton( Skeleton* skeleton );
	~Skeleton( );

	inline _void AttachResource( Skeleton* res )
		{ if ( mResource != _null ) return; mResource = res; if ( res != _null ) res->IncRefCount( ); }

	_void UpdateBones( _dword elapse = 0 );

public:
	virtual _dword GetBoneCount( ) const
		{ return mBones.Length( ); }
	virtual IBone* GetBone( _dword index ) const
		{ return mBones.IsIndexValid( (_long) index ) ? mBones[ index ] : _null; }

	virtual IBone*			CreateBone( StringPtr name, _dword parentid, _bool dummy );
	virtual _void			ReleaseBone( IBone*& bone );
	virtual _void			ClearBone( );

	virtual IBone*			GetBone( StringPtr name ) const;

	virtual _void			SetFrameToken( _dword token );
	virtual _dword			GetFrameToken( ) const;

	virtual _dword			GetSkinBoneCount( ) const;
	virtual _void			TransferSkinTransform( Geometry& geo ) const;

	virtual _void			Skinning( Geometry& geo );
	virtual const AxisAlignedBox&	GetBoundBox( ) const;
};

};