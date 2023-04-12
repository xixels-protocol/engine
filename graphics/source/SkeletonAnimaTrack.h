#pragma once

namespace Xixels
{

class SkeletonAnima;

class SkeletonAnimaTrack : public ISkeletonAnimaTrack
{
private:
	typedef Array< SkeletonAnimaKeyframe > KeyframeArray;

	struct ResourceData : public ReferencedObject
	{
		_dword			mTrackID;
		_dword			mOffset;
		_dword			mLength;
		KeyframeArray	mKeyframes;

		inline ResourceData( _dword trackid )
			: mTrackID( trackid ), mOffset( -1 ), mLength( 0 ) { }

		inline ResourceData( _dword trackid, _dword offset, _dword length )
			: mTrackID( trackid ), mOffset( offset ), mLength( length ) 
		{
			if ( offset == -1 )
				mKeyframes.Grow( length ); 
		}
	};

	ResourceData*	mResourceData;

	SkeletonAnima*	mSkeletonAnima;

	_bool			mEnabled;
	_bool			mTransEnabled;
	_dword			mLastKeyframe1;
	_dword			mLastKeyframe2;

public:
	SkeletonAnimaTrack( SkeletonAnima* anima, _dword trackid, _dword offset, _dword length );
	SkeletonAnimaTrack( SkeletonAnimaTrack* track );
	~SkeletonAnimaTrack( );

	inline _void UpdateData( _dword offset, _dword length )
		{ mResourceData->mOffset = offset; mResourceData->mLength = length; }

	inline _void UpdateOffset( _dword offset, _dword length )
		{ if ( mResourceData->mOffset != -1 && mResourceData->mOffset >= offset ) mResourceData->mOffset -= length; }

	_void	ChangeResObject( );

	_bool	GetKeyframe( _float time, SkeletonAnimaKeyframe*& frame1, SkeletonAnimaKeyframe*& frame2 );
	_void	Update( _float time, _float weight, ISkeleton* skeleton );
	_void	UpdateTransform( _float time1, _float time2 );

	ISkeletonAnimaKeyframe*	AddKeyframe( _float time );

public:
	virtual _dword GetTrackID( ) const
		{ return mResourceData->mTrackID; }
	virtual _void SetTrackID( _dword trackid )
		{ mResourceData->mTrackID = trackid; }

	virtual _dword GetKeyframeCount( ) const
		{ return mResourceData->mOffset == -1 ? mResourceData->mKeyframes.Length( ) : mResourceData->mLength; }

	virtual _void EnableTrack( _bool enable )
		{ mEnabled = enable; }
	virtual _bool IsTrackEnabled( ) const
		{ return mEnabled; }

	virtual ISkeletonAnimaKeyframe* CreateKeyframe( _float time );
	virtual ISkeletonAnimaKeyframe* GetKeyframe( _dword index ) const;
	virtual _void					ClearKeyframe( );
};

};