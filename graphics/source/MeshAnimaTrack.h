#pragma once

namespace Xixels
{

class MeshAnimaTrack : public IMeshAnimaTrack, public ReferencedObject
{
private:
	typedef SortArray< MeshAnimaKeyframeRef > KeyframeArray;

	struct ResourceData : public ReferencedObject
	{
		_dword			mTrackID;
		_dword			mVertexFormat;
		_dword			mVertexCount;
		KeyframeArray	mKeyframes;

		inline ResourceData( _dword trackid, _dword format, _dword vertex )
			: mTrackID( trackid ), mVertexFormat( format ), mVertexCount( vertex ) { }
	};

	ResourceData*	mResourceData;

	_bool			mEnabled;
	_dword			mLastKeyframe1;
	_dword			mLastKeyframe2;
	Geometry		mBindGeo;

public:
	MeshAnimaTrack( _dword trackid, _dword format, _dword vertex );
	MeshAnimaTrack( MeshAnimaTrack* track );
	~MeshAnimaTrack( );

	inline _void SetVertexFormat( _dword format )
		{ mResourceData->mVertexFormat = format; }
	inline _void SetVertexCount( _dword vertex )
		{ mResourceData->mVertexCount = vertex; }

	_void	ChangeResObject( );

	_bool	GetKeyframe( _float time, MeshAnimaKeyframe*& keyframe1, MeshAnimaKeyframe*& keyframe2 );
	_void	Update( _float time );

	IMeshAnimaKeyframe*	AddKeyframe( _float time );
	
public:
	virtual _dword GetTrackID( ) const
		{ return mResourceData->mTrackID; }
	virtual _dword GetVertexFormat( ) const
		{ return mResourceData->mVertexFormat; }
	virtual _dword GetVertexCount( ) const
		{ return mResourceData->mVertexCount; }

	virtual _dword GetKeyframeCount( ) const
		{ return mResourceData->mKeyframes.Length( ); }
	virtual IMeshAnimaKeyframe* GetKeyframe( _dword index ) const
		{ return mResourceData->mKeyframes.IsIndexValid( (_long) index ) ? mResourceData->mKeyframes[ index ].mRef : _null; }

	virtual _void EnableTrack( _bool enable )
		{ mEnabled = enable; }
	virtual _bool IsTrackEnabled( ) const
		{ return mEnabled; }

	virtual _void AttachGeometry( const Geometry& geo )
		{ GetGeometryFactory( ).ReleaseGeometry( mBindGeo ); mBindGeo = GetGeometryFactory( ).CloneGeometry( geo ); }
	virtual _void DetachGeometry( )
		{ GetGeometryFactory( ).ReleaseGeometry( mBindGeo ); }

	virtual IMeshAnimaKeyframe* CreateKeyframe( _float time );
	virtual _void				ReleaseKeyframe( IMeshAnimaKeyframe*& frame );
	virtual _void				ClearKeyframe( );
};

};