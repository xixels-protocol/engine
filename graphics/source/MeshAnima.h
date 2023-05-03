#pragma once

namespace Xixels
{

class MeshAnima : public IMeshAnima, public ReferencedObject, public Resource, public Animation
{
private:
	MeshAnima*					mResource;
	Array< MeshAnimaTrack* >	mTracks;

public:
	MeshAnima( );
	MeshAnima( MeshAnima* anima );
	~MeshAnima( );

	inline _void AttachResource( MeshAnima* res )
		{ if ( mResource != _null ) return; mResource = res; if ( res != _null ) res->IncRefCount( ); }

	_void	UpdateTracks( _float time );

public:
	virtual _dword GetType( ) const
		{ return _MESH_ANIMATION; }

	virtual _dword GetTrackCount( ) const
		{ return mTracks.Length( ); }
	virtual	IMeshAnimaTrack* GetTrack( _dword index ) const
		{ return mTracks.IsIndexValid( (_long) index ) ? mTracks[ index ] : _null; }

	virtual _bool				IsReady( _bool checktex ) const;

	virtual _void				SetCurrent( _dword current, ISkeleton* skeleton, _float weight );

	virtual _void				Update( _dword elapse, ISkeleton* skeleton, _float weight );

	virtual IMeshAnimaTrack*	CreateTrack( _dword trackid, _dword format, _dword vertex );
	virtual _void				ReleaseTrack( IMeshAnimaTrack*& track );
	virtual _void				ClearTrack( );

	virtual _void				AttachMesh( IMesh* mesh );
	virtual _void				DetachMesh( );
};

};