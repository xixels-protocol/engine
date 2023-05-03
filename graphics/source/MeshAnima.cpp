#include "MeshAnima.h"

MeshAnima::MeshAnima( ) : mResource( _null )
{
}

MeshAnima::MeshAnima( MeshAnima* anima ) : Animation( anima ), mResource( _null )
{	
	// Attach to same resource of source anima.
	AttachResource( anima->mResource );

	for ( _long i = 0; i < anima->mTracks.Length( ); i ++ )
		mTracks.Add( new MeshAnimaTrack( anima->mTracks[i] ) );
}

MeshAnima::~MeshAnima( )
{
	ClearTrack( );

	// This is uncached resource, try to delete host cached resource.
	if ( mResource != _null )
	{
		IMeshAnima* res = mResource;
		GetModelFactory( ).ReleaseMeshAnima( res );
	}
	// This is cached resource, remove from cache.
	else if ( IsResNameBlank( ) == _false )
	{
		GetResourceCache( ).ReleaseCache( IResourceCache::_RES_MESHANIMA, GetResName( ) );
	}
}

_void MeshAnima::UpdateTracks( _float time )
{
	for ( _long i = 0; i < mTracks.Length( ); i ++ )
		mTracks[i]->Update( time );
}

_bool MeshAnima::IsReady( _bool checktex ) const
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

_void MeshAnima::SetCurrent( _dword current, ISkeleton* skeleton, _float weight )
{
	if ( mPlayMode == IAnimation::_PLAY_FORWARD_LOOP || mPlayMode == IAnimation::_PLAY_BACKWARD_LOOP )
		mCurrent = mDuration != 0 ? ( current % mDuration ) : 0;
	else
		mCurrent = Math::Clamp( current, (_dword) 0, mDuration );

	UpdateTracks( (_float) mCurrent / (_float) mDuration );
}

_void MeshAnima::Update( _dword elapse, ISkeleton* skeleton, _float weight )
{
	if ( Animation::ReadyForUpdate( elapse ) == _false )
		return;

	// Update for logic.
	Animation::Update( elapse );

	if ( weight <= 0.0f )
		return;

	// Update for render.
	UpdateTracks( (_float) mCurrent / (_float) mDuration );
}

IMeshAnimaTrack* MeshAnima::CreateTrack( _dword trackid, _dword format, _dword vertex )
{
	for ( _long i = 0; i < mTracks.Length( ); i ++ )
	{
		MeshAnimaTrack* track = mTracks[i];

		if ( track->GetTrackID( ) == trackid )
		{
			track->SetVertexFormat( format );
			track->SetVertexCount( vertex );
			return track;
		}
	}

	MeshAnimaTrack* track = new MeshAnimaTrack( trackid, format, vertex );
	mTracks.Add( track );

	return track;
}

_void MeshAnima::ReleaseTrack( IMeshAnimaTrack*& track )
{
	if ( track == _null )
		return;

	_dword i = mTracks.IndexOf( (MeshAnimaTrack*) track );
	if ( i == -1 )
		return;

	delete mTracks[i];
	mTracks.RemoveAt( i );

	track = _null;
}

_void MeshAnima::ClearTrack( )
{
	for ( _long i = 0; i < mTracks.Length( ); i ++ )
		delete mTracks[i];

	mTracks.Clear( );
}

_void MeshAnima::AttachMesh( IMesh* mesh )
{
	if ( mesh == _null )
		return;

	for ( _long i = 0; i < mTracks.Length( ); i ++ )
	{
		MeshAnimaTrack* track = mTracks[i];

		ISubMesh* submesh = mesh->GetSubMesh( track->GetTrackID( ) );
		if ( submesh == _null )
			continue;

		track->AttachGeometry( submesh->GetGeometry( ) );
	}
}

_void MeshAnima::DetachMesh( )
{
	for ( _long i = 0; i < mTracks.Length( ); i ++ )
	{
		MeshAnimaTrack* track = mTracks[i];

		track->DetachGeometry( );
	}
}