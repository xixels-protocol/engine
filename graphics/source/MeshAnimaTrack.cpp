#include "MeshAnimaTrack.h"

MeshAnimaTrack::MeshAnimaTrack( _dword trackid, _dword format, _dword vertex )
	: mEnabled( _true ), mLastKeyframe1( -1 ), mLastKeyframe2( -1 )
{
	// Create resource data.
	mResourceData = new ResourceData( trackid, format, vertex );
}

MeshAnimaTrack::MeshAnimaTrack( MeshAnimaTrack* track )
	: mEnabled( _true ), mLastKeyframe1( -1 ), mLastKeyframe2( -1 )
{
	// Reference resource object.
	mResourceData = track->mResourceData;
	mResourceData->IncRefCount( );
}

MeshAnimaTrack::~MeshAnimaTrack( )
{
	// Release owned resource.
	if ( mResourceData->DecRefCount( ) == 0 )
	{
		KeyframeArray& keyframes = mResourceData->mKeyframes;
		for ( _long i = 0; i < keyframes.Length( ); i ++ )
			delete keyframes[i].mRef;

		delete mResourceData;
	}

	DetachGeometry( );
}

_void MeshAnimaTrack::ChangeResObject( )
{
	// Already owned resource, dont need to change.
	if ( mResourceData->GetRefCount( ) == 1 )
		return;
	
	// Copy track data.
	ResourceData* data = new ResourceData( mResourceData->mTrackID, mResourceData->mVertexFormat, mResourceData->mVertexCount );
	const KeyframeArray& keyframes = mResourceData->mKeyframes;
	for ( _long i = 0; i < keyframes.Length( ); i ++ )
		data->mKeyframes.Add( MeshAnimaKeyframeRef( new MeshAnimaKeyframe( keyframes[i].mRef ) ) );

	mResourceData->DecRefCount( );
	mResourceData = data;
}

_bool MeshAnimaTrack::GetKeyframe( _float time, MeshAnimaKeyframe*& frame1, MeshAnimaKeyframe*& frame2 )
{
	const KeyframeArray& keyframes = mResourceData->mKeyframes;
	if ( keyframes.Length( ) == 0 )
		return _false;

	if ( keyframes.Length( ) == 1 )
	{
		frame1 = frame2 = keyframes[0].mRef;
		return _true;
	}

	time = Math::Clamp( time, 0.0f, 1.0f );

	_dword i = 0, j = 0;

	if ( keyframes.IsIndexValid( (_long) mLastKeyframe1 ) == _false || keyframes.IsIndexValid( (_long) mLastKeyframe2 ) == _false )
	{
		// Get keyframe from array use binary search.
		BinarySearch< MeshAnimaKeyframeRef, _float >::SearchAscending( (const MeshAnimaKeyframeRef*) keyframes, time, keyframes.Length( ), i, j );
	}
	else
	{
		i = mLastKeyframe1;
		j = mLastKeyframe2;

		// Try to fast adjust time to keyframe.
		if ( time > (_float) keyframes[j] )
		{
			i ++;
			j ++;
		}
		else if ( time < (_float) keyframes[i] )
		{
			i = 0;
			j = 1;
		}

		if ( (_long) i >= keyframes.Length( ) )
			i = keyframes.Length( ) - 1;
		if ( (_long) j >= keyframes.Length( ) )
			j = keyframes.Length( ) - 1;

		// Still cant get right keyframe, use binary search.
		if ( time < (_float) keyframes[i] || time > (_float) keyframes[j] )
		{
			BinarySearch< MeshAnimaKeyframeRef, _float >::SearchAscending( (const MeshAnimaKeyframeRef*) keyframes, time, keyframes.Length( ), i, j );
		}
	}

	frame1 = keyframes[i].mRef;
	frame2 = keyframes[j].mRef;

	mLastKeyframe1 = i;
	mLastKeyframe2 = j;

	return _true;
}

_void MeshAnimaTrack::Update( _float time )
{
	if ( mEnabled == _false )
		return;

	Geometry& geo = mBindGeo;
	if ( geo.mRenderFlag & Geometry::_RENDER_STATIC )
		return;

	if ( geo.mVertexBuffer == _null )
		return;

	// Check vertex number.
	if ( mResourceData->mVertexCount != geo.mVertexNumber )
		return;

	_dword formatflag = geo.mVertexBuffer->GetVertexFormat( );

	// Check if the anima format is vaild for geometry format.
	if ( ModelHelper::CheckVertexFormatVSAnimationFormat( formatflag, mResourceData->mVertexFormat ) == _false )
		return;

	MeshAnimaKeyframe* frame1;
	MeshAnimaKeyframe* frame2;
	if ( GetKeyframe( time, frame1, frame2 ) == _false )
		return;

	// Lock vertex buffer, ready to update.
	_dword vsize = geo.mVertexBuffer->GetVertexSize( );
	_byte* vbuffer = (_byte*) geo.mVertexBuffer->Lock( geo.mStartVertex * vsize, geo.mVertexNumber * vsize, IGeometryFactory::_LOCK_SUBWRITE );
	if ( vbuffer == _null )
		return;

	_float time1 = (_float) *frame1, time2 = (_float) *frame2;
	_float factor = time1 != time2 ? ( time - time1 ) / ( time2 - time1 ) : 1.0f;

	const _byte* fbuffer1 = frame1->mKeyframeBuffer;
	const _byte* fbuffer2 = frame2->mKeyframeBuffer;

	_dword vformat = mResourceData->mVertexFormat;

	// Update each vertex data.
	for ( _dword i = 0; i < mResourceData->mVertexCount; i ++ )
	{
		// Update position.
		if ( vformat & IVertexBuffer::_FORMAT_POSITION )
		{
			*( (Vector3*) vbuffer ) = Vector3::Lerp( *( (const Vector3*) fbuffer1 ), *( (const Vector3*) fbuffer2 ), factor );

			fbuffer1 += sizeof( Vector3 );
			fbuffer2 += sizeof( Vector3 );
			vbuffer += sizeof( Vector3 );
		}
		// Skip position, vertex buffer will sure have position.
		else
		{
			vbuffer += sizeof( Vector3 );
		}

		// Update normal.
		if ( vformat & IVertexBuffer::_FORMAT_NORMAL )
		{
			*( (Vector3*) vbuffer ) = Vector3::Lerp( *( (const Vector3*) fbuffer1 ), *( (const Vector3*) fbuffer2 ), factor );

			fbuffer1 += sizeof( Vector3 );
			fbuffer2 += sizeof( Vector3 );
			vbuffer += sizeof( Vector3 );
		}
		// Skip normal.
		else if ( formatflag & IVertexBuffer::_FORMAT_NORMAL )
		{
			vbuffer += sizeof( Vector3 );
		}

		// Update diffuse.
		if ( vformat & IVertexBuffer::_FORMAT_DIFFUSE )
		{
			// TODO: Convert color in Opengl.
			*( (_dword*) vbuffer ) = Color::Lerp( Color( *( (const _dword*) fbuffer1 ) ), Color( *( (const _dword*) fbuffer2 ) ), factor );

			fbuffer1 += sizeof( _dword );
			fbuffer2 += sizeof( _dword );
			vbuffer += sizeof( _dword );
		}
		// Skip diffuse.
		else if ( formatflag & IVertexBuffer::_FORMAT_DIFFUSE )
		{
			vbuffer += sizeof( _dword );
		}

		// Update texcoord1.
		if ( vformat & IVertexBuffer::_FORMAT_TEXCOORD1 )
		{
			*( (Vector2*) vbuffer ) = Vector2::Lerp( *( (const Vector2*) fbuffer1 ), *( (const Vector2*) fbuffer2 ), factor );

			fbuffer1 += sizeof( Vector2 );
			fbuffer2 += sizeof( Vector2 );
			vbuffer += sizeof( Vector2 );
		}
		// Skip texcoord1.
		else if ( formatflag & IVertexBuffer::_FORMAT_TEXCOORD1 )
		{
			vbuffer += sizeof( Vector2 );
		}

		// Update texcoord2.
		if ( vformat & IVertexBuffer::_FORMAT_TEXCOORD2 )
		{
			*( (Vector2*) vbuffer ) = Vector2::Lerp( *( (const Vector2*) fbuffer1 ), *( (const Vector2*) fbuffer2 ), factor );

			fbuffer1 += sizeof( Vector2 );
			fbuffer2 += sizeof( Vector2 );
			vbuffer += sizeof( Vector2 );
		}
		// Skip texcoord2.
		else if ( formatflag & IVertexBuffer::_FORMAT_TEXCOORD2 )
		{
			vbuffer += sizeof( Vector2 );
		}

		// Update texcoord3.
		if ( vformat & IVertexBuffer::_FORMAT_TEXCOORD3 )
		{
			*( (Vector2*) vbuffer ) = Vector2::Lerp( *( (const Vector2*) fbuffer1 ), *( (const Vector2*) fbuffer2 ), factor );

			fbuffer1 += sizeof( Vector2 );
			fbuffer2 += sizeof( Vector2 );
			vbuffer += sizeof( Vector2 );
		}
		// Skip texcoord3.
		else if ( formatflag & IVertexBuffer::_FORMAT_TEXCOORD3 )
		{
			vbuffer += sizeof( Vector2 );
		}

		// Update texcoord4.
		if ( vformat & IVertexBuffer::_FORMAT_TEXCOORD4 )
		{
			*( (Vector2*) vbuffer ) = Vector2::Lerp( *( (const Vector2*) fbuffer1 ), *( (const Vector2*) fbuffer2 ), factor );

			fbuffer1 += sizeof( Vector2 );
			fbuffer2 += sizeof( Vector2 );
			vbuffer += sizeof( Vector2 );
		}
		// Skip texcoord4.
		else if ( formatflag & IVertexBuffer::_FORMAT_TEXCOORD4 )
		{
			vbuffer += sizeof( Vector2 );
		}

		// Skip tangent.
		if ( formatflag & IVertexBuffer::_FORMAT_TANGENT )
			vbuffer += sizeof( Vector4 );

		// Skip boneblend.
		if ( formatflag & IVertexBuffer::_FORMAT_BONEBLEND )
			vbuffer += sizeof( ModelInfluenceGroup );
	}

	// Update finished, unlock vertex buffer.
	geo.mVertexBuffer->Unlock( );
}

IMeshAnimaKeyframe* MeshAnimaTrack::AddKeyframe( _float time )
{
	MeshAnimaKeyframe* frame = new MeshAnimaKeyframe( time, mResourceData->mVertexFormat, mResourceData->mVertexCount );
	mResourceData->mKeyframes.Add( MeshAnimaKeyframeRef( frame ) );

	return frame;
}

IMeshAnimaKeyframe* MeshAnimaTrack::CreateKeyframe( _float time )
{
	ChangeResObject( );

	MeshAnimaKeyframe* frame = new MeshAnimaKeyframe( time, mResourceData->mVertexFormat, mResourceData->mVertexCount );
	mResourceData->mKeyframes.Add( MeshAnimaKeyframeRef( frame ) );

	return frame;
}

_void MeshAnimaTrack::ReleaseKeyframe( IMeshAnimaKeyframe*& frame )
{
	if ( frame == _null )
		return;

	_dword i = mResourceData->mKeyframes.IndexOf( MeshAnimaKeyframeRef( (MeshAnimaKeyframe*) frame ) );
	if ( i == -1 )
		return;

	ChangeResObject( );

	delete mResourceData->mKeyframes[i].mRef;
	mResourceData->mKeyframes.RemoveAt( i );

	frame = _null;
}

_void MeshAnimaTrack::ClearKeyframe( )
{
	ChangeResObject( );

	KeyframeArray& keyframes = mResourceData->mKeyframes;
	for ( _long i = 0; i < keyframes.Length( ); i ++ )
		delete keyframes[i].mRef;

	keyframes.Clear( _true );
}