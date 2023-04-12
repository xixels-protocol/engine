#include "SkeletonAnimaTrack.h"

SkeletonAnimaTrack::SkeletonAnimaTrack( SkeletonAnima* anima, _dword trackid, _dword offset, _dword length ) 
	: mSkeletonAnima( anima ), mEnabled( _true ), mTransEnabled( _false ), mLastKeyframe1( -1 ), mLastKeyframe2( -1 )
{
	// Create resource data.
	mResourceData = new ResourceData( trackid, offset, length );
}

SkeletonAnimaTrack::SkeletonAnimaTrack( SkeletonAnimaTrack* track ) : mEnabled( _true ), mTransEnabled( _false ),
	mLastKeyframe1( -1 ), mLastKeyframe2( -1 )
{
	// Reference resource object.
	mResourceData = track->mResourceData;
	mResourceData->IncRefCount( );

	mSkeletonAnima = track->mSkeletonAnima;
}

SkeletonAnimaTrack::~SkeletonAnimaTrack( )
{
	// Release owned resource.
	if ( mResourceData->DecRefCount( ) == 0 )
		delete mResourceData;
}

_void SkeletonAnimaTrack::ChangeResObject( )
{
	// Already owned resource, dont need to change.
	if ( mResourceData->GetRefCount( ) == 1 )
		return;

	// Copy track data.
	ResourceData* data = new ResourceData( mResourceData->mTrackID );

	// Copy keyframes.
	if ( mResourceData->mOffset == -1 )
		data->mKeyframes = mResourceData->mKeyframes;
	else
		data->mKeyframes.CopyFrom( (SkeletonAnimaKeyframe*) mSkeletonAnima->GetKeyframes( ) + mResourceData->mOffset, mResourceData->mLength );

	// Remove old data.
	mSkeletonAnima->RemoveKeyframes( mResourceData->mTrackID, mResourceData->mOffset, mResourceData->mLength );

	// Set new data.
	mResourceData->DecRefCount( );
	mResourceData = data;
}

_bool SkeletonAnimaTrack::GetKeyframe( _float time, SkeletonAnimaKeyframe*& frame1, SkeletonAnimaKeyframe*& frame2 )
{
	KeyframeArray& keyframes = mResourceData->mOffset == -1 ? mResourceData->mKeyframes : mSkeletonAnima->GetKeyframes( );
	if ( keyframes.Length( ) == 0 )
		return _false;

	_dword st = mResourceData->mOffset == -1 ? 0 : mResourceData->mOffset;
	_dword ed = st + GetKeyframeCount( );
	if ( keyframes.Length( ) == 1 )
	{
		frame1 = frame2 = &keyframes[st];
		return _true;
	}

	time = Math::Clamp( time, 0.0f, 1.0f );

	_dword i = st, j = st;

	if ( keyframes.IsIndexValid( (_long) mLastKeyframe1 ) == _false || keyframes.IsIndexValid( (_long) mLastKeyframe2 ) == _false )
	{
		// Get keyframe from array using binary search.
		BinarySearch< SkeletonAnimaKeyframe, _float >::SearchAscendingWithRange( keyframes, time, st, ed, i, j );
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
			i = st;
			j = st + 1;
		}

		if ( i >= ed )
			i = ed - 1;
		if ( j >= ed )
			j = ed - 1;

		// Still cant get right keyframe, use binary search.
		if ( time < (_float) keyframes[i] || time > (_float) keyframes[j] )
		{
			// Get keyframe from array using binary search.
			BinarySearch< SkeletonAnimaKeyframe, _float >::SearchAscendingWithRange( keyframes, time, st, ed, i, j );
		}
	}

	frame1 = &keyframes[i];
	frame2 = &keyframes[j];

	mLastKeyframe1 = i;
	mLastKeyframe2 = j;

	return _true;
}

_void SkeletonAnimaTrack::Update( _float time, _float weight, ISkeleton* skeleton )
{
	if ( mEnabled == _false )
		return;

	Bone* bone = (Bone*) skeleton->GetBone( mResourceData->mTrackID );
	if ( bone == _null || bone->mDummy )
		return;

	SkeletonAnimaKeyframe* frame1;
	SkeletonAnimaKeyframe* frame2;
	if ( GetKeyframe( time, frame1, frame2 ) == _false )
		return;

	_float ftime1 = (_float) *frame1, ftime2 = (_float) *frame2;
	_float factor = ftime1 != ftime2 ? ( time - ftime1 ) / ( ftime2 - ftime1 ) : 1.0f;

	// Linear interpolation bone translation.
	Vector3 t = frame1->mTranslation + frame1->mPrecomputeTranslationLerp * factor;

	// Spherical linear interpolation bone roation use precomputed parameters.
	Quaternion r = Quaternion::Slerp( frame1->mRotation, frame2->mRotation,
		frame1->mPrecomputeDot, frame1->mPrecomputeTheta, frame1->mPrecomputeRecipsqrt, factor );

	// Blend to previous anima with weight.
	if ( weight >= 1.0f )
	{
		bone->mRelativeTranslation	= t;
		bone->mRelativeRotation		= r;
	}
	else
	{
		bone->mRelativeTranslation	= Vector3::Lerp( bone->mRelativeTranslation, t, weight );
		bone->mRelativeRotation		= Quaternion::Slerp( bone->mRelativeRotation, r, weight );
	}
}

_void SkeletonAnimaTrack::UpdateTransform( _float time1, _float time2 )
{
	if ( mTransEnabled == _false )
		return;

	SkeletonAnimaKeyframe* frame1;
	SkeletonAnimaKeyframe* frame2;

	// If delta transform enabled for the track, get prev key frame.
	if ( GetKeyframe( time1, frame1, frame2 ) == _false )
		return;

	_float ftime1 = (_float) *frame1, ftime2 = (_float) *frame2;
	_float factor = ftime1 != ftime2 ? ( time1 - ftime1 ) / ( ftime2 - ftime1 ) : 1.0f;

	// Linear interpolation bone translation.
	Vector3 t1 = frame1->mTranslation + frame1->mPrecomputeTranslationLerp * factor;

	// Spherical linear interpolation bone roation use precomputed parameters.
	Quaternion r1 = Quaternion::Slerp( frame1->mRotation, frame2->mRotation,
		frame1->mPrecomputeDot, frame1->mPrecomputeTheta, frame1->mPrecomputeRecipsqrt, factor );

	if ( GetKeyframe( time2, frame1, frame2 ) == _false )
		return;

	ftime1 = (_float) *frame1, ftime2 = (_float) *frame2;
	factor = ftime1 != ftime2 ? ( time2 - ftime1 ) / ( ftime2 - ftime1 ) : 1.0f;

	// Linear interpolation bone translation.
	Vector3 t2 = frame1->mTranslation + frame1->mPrecomputeTranslationLerp * factor;

	// Spherical linear interpolation bone roation use precomputed parameters.
	Quaternion r2 = Quaternion::Slerp( frame1->mRotation, frame2->mRotation,
		frame1->mPrecomputeDot, frame1->mPrecomputeTheta, frame1->mPrecomputeRecipsqrt, factor );

	mDeltaTransform.Compose( t2 - t1, r2 * - r1, Vector3::cIdentity );
}

ISkeletonAnimaKeyframe*	SkeletonAnimaTrack::AddKeyframe( _float time )
{
	mResourceData->mKeyframes.Add( SkeletonAnimaKeyframe( time ) );

	return &mResourceData->mKeyframes.Tail( );
}

ISkeletonAnimaKeyframe* SkeletonAnimaTrack::CreateKeyframe( _float time )
{
	ChangeResObject( );

	_long i = 0;
	for ( ; i < mResourceData->mKeyframes.Length( ); i ++ )
	{
		if ( time < mResourceData->mKeyframes[i].mTime )
		{
			mResourceData->mKeyframes.Insert( SkeletonAnimaKeyframe( time ), i );
			break;
		}
	}

	return &mResourceData->mKeyframes[i];
}

ISkeletonAnimaKeyframe* SkeletonAnimaTrack::GetKeyframe( _dword index ) const
{
	if ( index >= GetKeyframeCount( ) )
		return _null;

	if ( mResourceData->mOffset == -1 )
		return &mResourceData->mKeyframes[ index ];
	else
		return &( mSkeletonAnima->GetKeyframes( )[ index + mResourceData->mOffset ] );
}

_void SkeletonAnimaTrack::ClearKeyframe( )
{
	ChangeResObject( );
	
	mResourceData->mKeyframes.Clear( _true );
}