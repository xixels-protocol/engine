#pragma once

namespace Xixels
{

class Skeleton : public ISkeleton, public ReferencedObject
{
private:
	struct AffectAnima
	{
		ISkeletonAnima*	mAnima;
		_float			mTime;
		_float			mWeight;

		inline AffectAnima( )
			{ }
		inline AffectAnima( ISkeletonAnima* anima, _float time, _float weight )
			: mAnima( anima ), mTime( time ), mWeight( weight ) { }
	};

	Skeleton*				mResource;
	AxisAlignedBox			mBoundBox;

	MemoryBuffer			mMemoryBuffer;
	Array< Bone* >			mBones;

	_byte*					mSkinBuffer;
	Matrix3x4*				mSkinTransform;
	_dword					mSkinBoneCount;

	_dword					mFrameToken;
	_bool					mNeedToUpdate;
	Array< AffectAnima >	mAffectAnimas;
public:
	Skeleton( );
	Skeleton( Skeleton* skeleton );
	~Skeleton( );

	inline _void AttachResource( Skeleton* res )
		{ if ( mResource != _null ) return; mResource = res; if ( res != _null ) res->IncRefCount( ); }

	inline const Matrix3x4* GetSkinTransform( ) const
		{ return mSkinTransform; }
	inline _void NeedToUpdate( )
		{ mNeedToUpdate = _true; }

	inline _void AllocateBuffer( _dword bonecount )
		{ mMemoryBuffer.CreateBuffer( bonecount * sizeof( Bone ) ); }

	_void AnimateBones( ISkeletonAnima* anima, _float time, _float weight );
	_void UpdateSkinTransform( );
	_void UpdateBoundBox( );
	_void UpdateBones( _dword elapse = 0 );

public:
	virtual _dword GetBoneCount( ) const
		{ return mBones.Length( ); }
	virtual IBone* GetBone( _dword index ) const
		{ return mBones.IsIndexValid( (_long) index ) ? mBones[ index ] : _null; }

	virtual _void SetFrameToken( _dword token )
		{ mFrameToken = token; }
	virtual _dword GetFrameToken( ) const
		{ return mFrameToken; }

	virtual _dword GetSkinBoneCount( ) const
		{ return mSkinBoneCount; }
	virtual const AxisAlignedBox& GetBoundBox( ) const
		{ return mBoundBox; }
		
	virtual IBone*			CreateBone( StringPtr name, _dword parentid, _bool dummy );
	virtual _void			ReleaseBone( IBone*& bone );
	virtual _void			ClearBone( );

	virtual IBone*			GetBone( StringPtr name ) const;

	virtual _void			TransferSkinTransform( Geometry& geo ) const;

	virtual _void			UsingSkeleton( _dword priority );
	virtual _void			Skinning( Geometry& geo );

	virtual _void			ClearAnimas( );
};

};