#pragma once

namespace Xixels
{

class SkeletonAnima : public ISkeletonAnima, public ReferencedObject, public Animation
{
private:
	SkeletonAnima*	mResource;

	Array< SkeletonAnimaTrack* >	mTracks;
	Array< SkeletonAnimaKeyframe >	mKeyframes;

public:
	SkeletonAnima( );
	SkeletonAnima( SkeletonAnima* anima );
	~SkeletonAnima( );

	inline _void AttachResource( SkeletonAnima* res )
		{ if ( mResource != _null ) return; mResource = res; if ( res != _null ) res->IncRefCount( ); }

	inline _void Allocate( _dword trackcount, _dword keyframecount )
		{ if ( mTracks.Length( ) == 0 ) mTracks.Grow( trackcount ); if ( mKeyframes.Length( ) == 0 ) mKeyframes.Grow( keyframecount ); }

	inline Array< SkeletonAnimaKeyframe >& GetKeyframes( )
		{ return mKeyframes; }

	ISkeletonAnimaKeyframe* AddKeyframe( _dword index, _float time );
	_void					UpdateTracks( _float time, _float weight, ISkeleton* skeleton );
	_void					RemoveKeyframes( _dword trackid, _dword offset, _dword length );

public:
	virtual _dword GetType( ) const
		{ return _SKELETON_ANIMATION; }

	virtual _dword GetTrackCount( ) const
		{ return mTracks.Length( ); }
	virtual	ISkeletonAnimaTrack* GetTrack( _dword index ) const
		{ return mTracks.IsIndexValid( (_long) index ) ? mTracks[ index ] : _null; }

	virtual _bool						IsReady( _bool checktex ) const;

	virtual _void						SetCurrent( _dword current, ISkeleton* skeleton, _float weight );
	virtual _void						Update( _dword elapse, ISkeleton* skeleton, _float weight );

	virtual ISkeletonAnimaTrack*		CreateTrack( _dword trackid, _dword offset, _dword length );
	virtual _void						ReleaseTrack( _dword index );
	virtual _void						ClearTrack( );
};

};