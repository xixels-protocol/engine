#include "SkeletonAnima.h"

SkeletonAnima::SkeletonAnima( ) : mResource( _null )
{
}

SkeletonAnima::SkeletonAnima( SkeletonAnima* anima )
	: Animation( anima ), mResource( _null )
{
	// Attach to same resource of source anima.
	AttachResource( anima->mResource );

	mTracks.Grow( anima->mTracks.Length( ) );
	for ( _long i = 0; i < anima->mTracks.Length( ); i ++ )
		mTracks.Add( new SkeletonAnimaTrack( anima->mTracks[i] ) );
}

SkeletonAnima::~SkeletonAnima( )
{
	ClearTrack( );

	// This is uncached resource, try to delete host cached resource.
	if ( mResource != _null )
	{
		mResource->UsingResource( -1 );

		ISkeletonAnima* res = mResource;
		GetModelFactory( ).ReleaseSkeletonAnima( res );
	}
	// This is cached resource, remove from cache.
	else if ( IsResNameBlank( ) == _false )
	{
		GetResourceCache( ).ReleaseCache( IResourceCache::_RES_SKELETONANIMA, GetResName( ) );
	}
}

ISkeletonAnimaKeyframe* SkeletonAnima::AddKeyframe( _dword index, _float time )
{
	mKeyframes.Add( SkeletonAnimaKeyframe( time ) );

	return &mKeyframes.Tail( );
}

_void SkeletonAnima::UpdateTracks( _float time, _float weight, ISkeleton* skeleton )
{
	for ( _long i = 0; i < mTracks.Length( ); i ++ )
		mTracks[i]->Update( time, weight, skeleton );
}

_void SkeletonAnima::RemoveKeyframes( _dword trackid, _dword offset, _dword length )
{
	if ( offset == -1 || length == 0 )
		return;

	// Remove keyframes from array.
	mKeyframes.RemoveFromTo( offset, offset + length );

	// Update all tracks.
	for ( _long i = trackid + 1; i < mTracks.Length( ); i ++ )
		mTracks[i]->UpdateOffset( offset, length );
}

_bool SkeletonAnima::IsReady( _bool checktex ) const
{
	if ( mResource != _null )
		return mResource->IsReady( checktex );

	for ( _long i = 0; i < mTracks.Length( ); i ++ )
	{
		if ( mTracks[i]->GetKeyframeCount( ) == 0 )
			return _false;
	}

	return _true;
}

_void SkeletonAnima::SetCurrent( _dword current, ISkeleton* skeleton, _float weight )
{
	if ( mPlayMode == IAnimation::_PLAY_FORWARD_LOOP || mPlayMode == IAnimation::_PLAY_BACKWARD_LOOP )
		mCurrent = mDuration != 0 ? ( current % mDuration ) : 0;
	else
		mCurrent = Math::Clamp( current, (_dword) 0, mDuration );

	_float time = (_float) mCurrent / (_float) mDuration;

	// Affect on skeleton.
	if ( skeleton != _null )
		( (Skeleton*) skeleton )->AnimateBones( this, time, weight );
}

_void SkeletonAnima::Update( _dword elapse, ISkeleton* skeleton, _float weight )
{
	if ( mResource != _null )
		mResource->UsingResource( IDownloadTask::_LOAD_PRIORITY_HIGH );

	if ( Animation::ReadyForUpdate( elapse ) == _false )
		return;

	_float time1 = (_float) mCurrent / (_float) mDuration;

	Animation::Update( elapse );

	_float time2 = (_float) mCurrent / (_float) mDuration;

	// Affect on skeleton.
	if ( skeleton != _null && weight > 0.0f )
		( (Skeleton*) skeleton )->AnimateBones( this, time2, weight );
}

ISkeletonAnimaTrack* SkeletonAnima::CreateTrack( _dword trackid, _dword offset, _dword length )
{
	for ( _long i = 0; i < mTracks.Length( ); i ++ )
	{
		SkeletonAnimaTrack* track = mTracks[i];

		if ( track->GetTrackID( ) == trackid )
		{
			track->UpdateData( offset, length );
			return track;
		}
	}

	SkeletonAnimaTrack* track = new SkeletonAnimaTrack( this, trackid, offset, length );
	mTracks.Add( track );

	return track;
}

_void SkeletonAnima::ReleaseTrack( _dword index )
{
	if ( mTracks.IsIndexValid( (_long) index ) == _false )
		return;

	delete mTracks[ index ];
	mTracks.RemoveAt( index );
}

_void SkeletonAnima::ClearTrack( )
{
	for ( _long i = 0; i < mTracks.Length( ); i ++ )
		delete mTracks[i];

	mTracks.Clear( );
}