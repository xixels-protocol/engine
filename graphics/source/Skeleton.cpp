#include "Skeleton.h"

#define _COLLAPSE_SKINMATRIX( row0, row1, row2, gi, mat, maxbone ) \
	{ \
		_dword boneid = gi.mBoneIDList[0]; \
		if ( boneid < maxbone ) \
		{ \
			_float weight = gi.mWeightList[0]; \
			if ( weight >= 1.0f ) \
			{ \
				_SSE_LOAD_MATRIX3x4( row0, row1, row2, mat[ boneid ] ); \
			} \
			else \
			{ \
				_SSE_LOAD_MUL_MATRIX3x4( row0, row1, row2, mat[ boneid ], weight ); \
				boneid = gi.mBoneIDList[1];	\
				if ( boneid < maxbone ) \
				{ \
					weight = gi.mWeightList[1]; \
					_SSE_LOAD_MADD_MATRIX3x4( row0, row1, row2, mat[ boneid ], weight ); \
					boneid = gi.mBoneIDList[2];	\
					if ( boneid < maxbone ) \
					{ \
						weight = gi.mWeightList[2]; \
						_SSE_LOAD_MADD_MATRIX3x4( row0, row1, row2, mat[ boneid ], weight ); \
						boneid = gi.mBoneIDList[3];	\
						if ( boneid < maxbone ) \
						{ \
							weight = gi.mWeightList[3]; \
							_SSE_LOAD_MADD_MATRIX3x4( row0, row1, row2, mat[ boneid ], weight ); \
						} \
					} \
				} \
			} \
		} \
	}

//----------------------------------------------------------------------------
// Skeleton Implementation
//----------------------------------------------------------------------------

Skeleton::Skeleton( ) : mResource( _null ), mSkinBuffer( _null ), mSkinTransform( _null ), mBigBoneCount( 0 ), 
	mSkinBoneCount( 0 ), mFrameToken( 0 ), mNeedToUpdate( _true )
{
}

Skeleton::Skeleton( Skeleton* skeleton ) : mResource( _null ), mBoundBox( skeleton->mBoundBox ), mSkinBuffer( _null ),
	mSkinTransform( _null ), mBigBoneCount( skeleton->mBigBoneCount ), mSkinBoneCount( skeleton->mSkinBoneCount ),
	mFrameToken( 0 ), mNeedToUpdate( _true )
{
	// Attach to same resource of source skeleton.
	AttachResource( skeleton->mResource );

	for ( _long i = 0; i < skeleton->mBones.Length( ); i ++ )
	{
		// Create bone use memory buffer.
		Bone* bone = new ( mMemoryBuffer.BufferAlloc( sizeof( Bone ) ) ) Bone( *skeleton->mBones[i] );
		bone->mHostSkeleton = this;

		mBones.Add( bone );
	}
}

Skeleton::~Skeleton( )
{
	ClearBone( );
	ClearAnimas( );
	// This is uncached resource, try to delete host cached resource.
	if ( mResource != _null )
	{
		ISkeleton* res = mResource;
		GetModelFactory( ).ReleaseSkeleton( res );
	}
	// This is cached resource, remove from cache.
	else if ( IsResNameBlank( ) == _false )
	{
		GetResourceCache( ).ReleaseCache( IResourceCache::_RES_SKELETON, GetResName( ) );
	}
}

_void Skeleton::SSESkinning( _byte* vbuffer, _byte* nbuffer, _byte* tbuffer, _byte* hbuffer, _dword vnumber, _dword vsize, Matrix3x4* skinmat, _dword bonecount, AxisAlignedBoxMaker& boxmaker )
{
	// Prepare for skin transform.
	_float4 m00, m01, m02;
	_float4 m10, m11, m12;
	_float4 m20, m21, m22;
	_float4 m30, m31, m32;

	//#ifdef _DEBUG
	m00 = _SSE_LOAD_ZERO( ); m01 = _SSE_LOAD_ZERO( ); m02 = _SSE_LOAD_ZERO( );
	m10 = _SSE_LOAD_ZERO( ); m11 = _SSE_LOAD_ZERO( ); m12 = _SSE_LOAD_ZERO( );
	m20 = _SSE_LOAD_ZERO( ); m21 = _SSE_LOAD_ZERO( ); m22 = _SSE_LOAD_ZERO( );
	m30 = _SSE_LOAD_ZERO( ); m31 = _SSE_LOAD_ZERO( ); m32 = _SSE_LOAD_ZERO( );
	//#endif

	// Prepare for skin position and normal.
	_float4 s0, s1, s2, n0, n1, n2, t0, t1, t2, t3;
	_float4 d0, d1, d2, d3 = _SSE_LOAD_ZERO( );

	// Get influence offset for each vertex group.
	_dword infoffset = sizeof( _float4 ) * 3;
	if ( nbuffer )
		infoffset += sizeof( _float4 ) * 3;

	if ( tbuffer )
		infoffset += sizeof( _float4 ) * 4;

	// Compute the group number of vertex.
	_dword gnumber = ( vnumber + 3 ) / 4;

	// Process groups, except last one.
	gnumber --;

	// Process vertex by group, each group is 4 vertex.
	for ( _dword i = 0; i < gnumber; i ++ )
	{
		_float4* srcvertex = (_float4*) hbuffer;

		s0 = srcvertex[0];
		s1 = srcvertex[1];
		s2 = srcvertex[2];

		// Get influence group from helper buffer.
		const ModelInfluenceGroup* infgroup = (ModelInfluenceGroup*) ( hbuffer + infoffset );

		_COLLAPSE_SKINMATRIX( m00, m01, m02, infgroup[0], skinmat, bonecount );
		_COLLAPSE_SKINMATRIX( m10, m11, m12, infgroup[1], skinmat, bonecount );
		_COLLAPSE_SKINMATRIX( m20, m21, m22, infgroup[2], skinmat, bonecount );
		_COLLAPSE_SKINMATRIX( m30, m31, m32, infgroup[3], skinmat, bonecount );

		// Transform X components - X0 X1 X2 X3
		_SSE_TRANSPOSE_MATRIX4x4( m00, m10, m20, m30 )
		d0 = _SSE_DOT4x3_FLOAT4( m00, m10, m20, m30, s0, s1, s2 );

		// Transform Y components - Y0 Y1 Y2 Y3
		_SSE_TRANSPOSE_MATRIX4x4( m01, m11, m21, m31 )
		d1 = _SSE_DOT4x3_FLOAT4( m01, m11, m21, m31, s0, s1, s2 );

		// Transform Z components - Z0 Z1 Z2 Z3
		_SSE_TRANSPOSE_MATRIX4x4( m02, m12, m22, m32 )
		d2 = _SSE_DOT4x3_FLOAT4( m02, m12, m22, m32, s0, s1, s2 );

		// Arrange back to 4x3 continuous format.
		_SSE_TRANSPOSE_MATRIX4x4( d0, d1, d2, d3 );

		// Save vertex 1.
		_SSE_STORE_VECTOR3( d0, (_float*) vbuffer );
		vbuffer += vsize;

		// Save vertex 2.
		_SSE_STORE_VECTOR3( d1, (_float*) vbuffer );
		vbuffer += vsize;

		// Save vertex 3.
		_SSE_STORE_VECTOR3( d2, (_float*) vbuffer );
		vbuffer += vsize;

		// Save vertex 4.
		_SSE_STORE_VECTOR3( d3, (_float*) vbuffer );
		vbuffer += vsize;

		// Combine bound box with a new vertex.
		boxmaker.Expand( d0, d1, d2, d3 );

		// Process normal.
		if ( nbuffer )
		{
			_float4* norvertex = (_float4*) ( hbuffer + sizeof( _float4 ) * 3 );

			n0 = norvertex[0];
			n1 = norvertex[1];
			n2 = norvertex[2];

			d0 = _SSE_DOT3x3_FLOAT4( m00, m10, m20, n0, n1, n2 );
			d1 = _SSE_DOT3x3_FLOAT4( m01, m11, m21, n0, n1, n2 );
			d2 = _SSE_DOT3x3_FLOAT4( m02, m12, m22, n0, n1, n2 );

			// Arrange back to 4x3 continuous format.
			_SSE_TRANSPOSE_MATRIX4x4( d0, d1, d2, d3 );

			// Save normal 1.
			_SSE_STORE_VECTOR3( d0, (_float*) nbuffer );
			nbuffer += vsize;

			// Save normal 2.
			_SSE_STORE_VECTOR3( d1, (_float*) nbuffer );
			nbuffer += vsize;

			// Save normal 3.
			_SSE_STORE_VECTOR3( d2, (_float*) nbuffer );
			nbuffer += vsize;

			// Save normal 4.
			_SSE_STORE_VECTOR3( d3, (_float*) nbuffer );
			nbuffer += vsize;
		}

		// Process tangent.
		if ( tbuffer )
		{
			_float4* tanvertex = (_float4*) ( hbuffer + sizeof( _float4 ) * 6 );

			t0 = tanvertex[0];
			t1 = tanvertex[1];
			t2 = tanvertex[2];
			t3 = tanvertex[3];

			d0 = _SSE_DOT3x3_FLOAT4( m00, m10, m20, t0, t1, t2 );
			d1 = _SSE_DOT3x3_FLOAT4( m01, m11, m21, t0, t1, t2 );
			d2 = _SSE_DOT3x3_FLOAT4( m02, m12, m22, t0, t1, t2 );

			// Arrange back to 4x3 continuous format.
			_SSE_TRANSPOSE_MATRIX4x4( d0, d1, d2, t3 );

			// Save tangent 1.
			_SSE_STORE_VECTOR4( d0, (_float*) tbuffer );
			tbuffer += vsize;

			// Save tangent 2.
			_SSE_STORE_VECTOR4( d1, (_float*) tbuffer );
			tbuffer += vsize;

			// Save tangent 3.
			_SSE_STORE_VECTOR4( d2, (_float*) tbuffer );
			tbuffer += vsize;

			// Save tangent 4.
			_SSE_STORE_VECTOR4( t3, (_float*) tbuffer );
			tbuffer += vsize;
		}

		// Move helper buffer to next vertex group.
		hbuffer += infoffset + sizeof( ModelInfluenceGroup ) * 4;
	}

	// Last group, some vertex maybe not there in vertex buffer.
	{
		_float4* srcvertex = (_float4*) hbuffer;

		s0 = srcvertex[0];
		s1 = srcvertex[1];
		s2 = srcvertex[2];

		// Get influence group from helper buffer.
		const ModelInfluenceGroup* infgroup = (ModelInfluenceGroup*) ( hbuffer + infoffset );

		_COLLAPSE_SKINMATRIX( m00, m01, m02, infgroup[0], skinmat, bonecount );
		_COLLAPSE_SKINMATRIX( m10, m11, m12, infgroup[1], skinmat, bonecount );
		_COLLAPSE_SKINMATRIX( m20, m21, m22, infgroup[2], skinmat, bonecount );
		_COLLAPSE_SKINMATRIX( m30, m31, m32, infgroup[3], skinmat, bonecount );

		// Transform X components - X0 X1 X2 X3
		_SSE_TRANSPOSE_MATRIX4x4( m00, m10, m20, m30 )
		d0 = _SSE_DOT4x3_FLOAT4( m00, m10, m20, m30, s0, s1, s2 );

		// Transform Y components - Y0 Y1 Y2 Y3
		_SSE_TRANSPOSE_MATRIX4x4( m01, m11, m21, m31 )
		d1 = _SSE_DOT4x3_FLOAT4( m01, m11, m21, m31, s0, s1, s2 );

		// Transform Z components - Z0 Z1 Z2 Z3
		_SSE_TRANSPOSE_MATRIX4x4( m02, m12, m22, m32 )
		d2 = _SSE_DOT4x3_FLOAT4( m02, m12, m22, m32, s0, s1, s2 );

		// Arrange back to 4x3 continuous format.
		d3 = _SSE_LOAD_ZERO( );
		_SSE_TRANSPOSE_MATRIX4x4( d0, d1, d2, d3 );

		// Save vertex 1.
		_SSE_STORE_VECTOR3( d0, (_float*) vbuffer );
		vbuffer += vsize;

		if ( ( gnumber << 2 ) + 1 < vnumber )
		{
			// Save vertex 2.
			_SSE_STORE_VECTOR3( d1, (_float*) vbuffer );
			vbuffer += vsize;
		}
		else
		{
			d1 = d0;
		}

		if ( ( gnumber << 2 ) + 2 < vnumber )
		{
			// Save vertex 3.
			_SSE_STORE_VECTOR3( d2, (_float*) vbuffer );
			vbuffer += vsize;
		}
		else
		{
			d2 = d0;
		}

		if ( ( gnumber << 2 ) + 3 < vnumber )
		{
			// Save vertex 4.
			_SSE_STORE_VECTOR3( d3, (_float*) vbuffer );
		}
		else
		{
			d3 = d0;
		}

		// Combine bound box with a new vertex.
		boxmaker.Expand( d0, d1, d2, d3 );

		if ( nbuffer )
		{
			_float4* norvertex = (_float4*) ( hbuffer + sizeof( _float4 ) * 3 );

			n0 = norvertex[0];
			n1 = norvertex[1];
			n2 = norvertex[2];

			d0 = _SSE_DOT3x3_FLOAT4( m00, m10, m20, n0, n1, n2 );
			d1 = _SSE_DOT3x3_FLOAT4( m01, m11, m21, n0, n1, n2 );
			d2 = _SSE_DOT3x3_FLOAT4( m02, m12, m22, n0, n1, n2 );

			// Arrange back to 4x3 continuous format.
			_SSE_TRANSPOSE_MATRIX4x4( d0, d1, d2, d3 );

			// Save normal 1.
			_SSE_STORE_VECTOR3( d0, (_float*) nbuffer );
			nbuffer += vsize;

			if ( ( gnumber << 2 ) + 1 < vnumber )
			{
				// Save normal 2.
				_SSE_STORE_VECTOR3( d1, (_float*) nbuffer );
				nbuffer += vsize;
			}

			if ( ( gnumber << 2 ) + 2 < vnumber )
			{
				// Save normal 3.
				_SSE_STORE_VECTOR3( d2, (_float*) nbuffer );
				nbuffer += vsize;
			}

			if ( ( gnumber << 2 ) + 3 < vnumber )
			{
				// Save normal 4.
				_SSE_STORE_VECTOR3( d3, (_float*) nbuffer );
			}
		}

		if ( tbuffer )
		{
			_float4* tanvertex = (_float4*) ( hbuffer + sizeof( _float4 ) * 6 );

			t0 = tanvertex[0];
			t1 = tanvertex[1];
			t2 = tanvertex[2];
			t3 = tanvertex[3];

			d0 = _SSE_DOT3x3_FLOAT4( m00, m10, m20, t0, t1, t2);
			d1 = _SSE_DOT3x3_FLOAT4( m01, m11, m21, t0, t1, t2);
			d2 = _SSE_DOT3x3_FLOAT4( m02, m12, m22, t0, t1, t2);

			// Arrange back to 4x3 continuous format.
			_SSE_TRANSPOSE_MATRIX4x4( d0, d1, d2, t3 );

			// Save tangent 1.
			_SSE_STORE_VECTOR4( d0, (_float*) tbuffer );
			tbuffer += vsize;

			if ( ( gnumber << 2 ) + 1 < vnumber )
			{
				// Save tangent 2.
				_SSE_STORE_VECTOR4( d1, (_float*) tbuffer );
				tbuffer += vsize;
			}

			if ( ( gnumber << 2 ) + 2 < vnumber )
			{
				// Save tangent 3.
				_SSE_STORE_VECTOR4( d2, (_float*) tbuffer );
				tbuffer += vsize;
			}

			if ( ( gnumber << 2 ) + 3 < vnumber )
			{
				// Save tangent 4.
				_SSE_STORE_VECTOR4( t3, (_float*) tbuffer );
			}
		}
	}
}

_void Skeleton::CPUSkinning( _byte* vbuffer, _byte* nbuffer, _byte* tbuffer, _byte* hbuffer, _dword vnumber, _dword vsize, Matrix3x4* skinmat, _dword bonecount, AxisAlignedBoxMaker& boxmaker )
{
	// Get influence offset for each vertex group.
	_dword infoffset = sizeof( _float ) * 12;
	if ( nbuffer )
		infoffset += sizeof( _float ) * 12;

	if ( tbuffer )
		infoffset += sizeof( _float ) * 16;

	_byte* ibuffer = hbuffer + infoffset;

	Matrix3x4 mat = Matrix3x4::cIdentity;

	// Process vertex one by one.
	for ( _dword i = 0; i < vnumber; i ++ )
	{
		_float* srcvertex = (_float*) hbuffer;
		_float* desvertex = (_float*) vbuffer;

		Vector3 pos( srcvertex[0], srcvertex[4], srcvertex[8] );

		// Process bone influence.
		const ModelInfluenceGroup* infgroup = (ModelInfluenceGroup*) ibuffer;

		_dword boneid = infgroup->mBoneIDList[0];
		if ( boneid < bonecount )
		{
			_float weight = infgroup->mWeightList[0];
			if ( weight >= 1.0f )
			{
				mat = skinmat[ boneid ];
			}
			else
			{
				mat = skinmat[ boneid ] * weight;

				boneid = infgroup->mBoneIDList[1];
				if ( boneid < bonecount )
				{
					weight = infgroup->mWeightList[1];
					mat += skinmat[ boneid ] * weight;

					boneid = infgroup->mBoneIDList[2];
					if ( boneid < bonecount )
					{
						weight = infgroup->mWeightList[2];
						mat += skinmat[ boneid ] * weight;

						boneid = infgroup->mBoneIDList[3];
						if ( boneid < bonecount )
						{
							weight = infgroup->mWeightList[3];
							mat += skinmat[ boneid ] * weight;
						}
					}
				}
			}

			pos *= mat;

			// x, y, z.
			desvertex[0] = pos.x;
			desvertex[1] = pos.y;
			desvertex[2] = pos.z;

			// nx, ny, nz.
			if ( nbuffer )
			{
				Vector3 nor( srcvertex[12], srcvertex[16], srcvertex[20] );
				nor *= mat.GetRotationMatrix( );

				_float* norvertex = (_float*) nbuffer;

				norvertex[0] = nor.x;
				norvertex[1] = nor.y;
				norvertex[2] = nor.z;
			}

			if ( tbuffer )
			{
				Vector3 tan( srcvertex[24], srcvertex[28], srcvertex[32] );
				_float tanw = srcvertex[36];
				tan *= mat.GetRotationMatrix( );

				_float* tanvertex = (_float*) tbuffer;

				tanvertex[0] = tan.x;
				tanvertex[1] = tan.y;
				tanvertex[2] = tan.z;
				tanvertex[3] = tanw;

				tbuffer += vsize;
			}
		}
 
		// Move vertex buffer to next vertex.
		vbuffer += vsize;
		nbuffer += vsize;

		// Move helper buffer to next vertex group.
		hbuffer += sizeof( _float );
		ibuffer += sizeof( ModelInfluenceGroup );

		if ( ( i + 1 ) % 4 == 0 )
		{
			hbuffer += infoffset - sizeof( _float ) * 4 + sizeof( ModelInfluenceGroup ) * 4;
			ibuffer += infoffset;
		}
	}
}

_void Skeleton::AnimateBones( ISkeletonAnima* anima, _float time, _float weight )
{
	if ( weight <= 0.0f )
		return;

	// Skeleton affected, need to update.
	mNeedToUpdate = _true;
	mNeedToUpdateDynamicBone = _true;

	// Check if there is existing animation.
	for ( _long i = 0; i < mAffectAnimas.Length( ); i ++ )
	{
		AffectAnima& aa = mAffectAnimas[i];

		if ( aa.mAnima == anima )
		{
			aa.mTime = time;
			aa.mWeight = Math::Max( aa.mWeight, weight );
			return;
		}
	}

	GetModelFactory( ).CloneAnimation( anima );
	mAffectAnimas.Add( AffectAnima( anima, time, weight ) );
}

_void Skeleton::UpdateSkinTransform( )
{
	// Set skin transform, must be align of 16.
	if ( mSkinTransform == _null )
	{
		mSkinBuffer = new _byte[sizeof( Matrix3x4 ) * mSkinBoneCount + sizeof( _float4 )];
		mSkinTransform = (Matrix3x4*) ( mSkinBuffer + sizeof( _float4 ) - (_ptr) mSkinBuffer % sizeof( _float4 ) );
	}

	for ( _long i = 0; i < mBones.Length( ); i ++ )
	{
		Bone* bone = mBones[i];
		if ( bone->mDummy )
			continue;

		if ( bone->mScaling.Equal( Vector3::cIdentity ) == _false )
		{
			// TODO, better way than matrix transform.
			Matrix4 mat1;
			mat1.Compose( bone->mBoneSpaceTranslation, bone->mBoneSpaceRotation, Vector3::cIdentity );

			Matrix4 mat2;
			mat2.Compose( bone->mTranslation, bone->mRotation, bone->mScaling );

			mSkinTransform[i].Compose( mat1 * mat2 );
		}
		else
		{
			Vector3 bonetranslation = bone->mBoneSpaceTranslation;
			bonetranslation *= bone->mRotation;
			bonetranslation += bone->mTranslation;

			mSkinTransform[i].Compose( bonetranslation, bone->mBoneSpaceRotation * bone->mRotation, Vector3::cIdentity );
		}
	}
}

_void Skeleton::UpdateBoundBox( )
{
}

_void Skeleton::UpdateBones( _dword elapse )
{
	// Skeleton dont need update.
	if ( mNeedToUpdate == _false && elapse == 0 )
		return;

	if ( mNeedToUpdate )
	{
		for ( _long i = 0; i < mBones.Length( ); i ++ )
			mBones[i]->mScaled = _false;

		// Update affecting animas.
		for ( _long i = 0; i < mAffectAnimas.Length( ); i ++ )
		{
			AffectAnima& aa = mAffectAnimas[i];

			// Skip empty animation.
			if ( aa.mAnima->IsReady( _true ) == _false )
				continue;

			( (SkeletonAnima*) aa.mAnima )->UpdateTracks( aa.mTime, aa.mWeight, this );

			GetModelFactory( ).ReleaseSkeletonAnima( aa.mAnima );
			mAffectAnimas.RemoveAt( i -- );
		}

		// If any animation left, need to update next time.
		mNeedToUpdate = mAffectAnimas.Length( ) != 0;

		// Update each bone.
		for ( _long i = 0; i < mBones.Length( ); i ++ )
		{
			Bone* bone = mBones[i];

			_bool root = mBones.IsIndexValid( (_long) bone->mParentID ) == _false;

			Vector3		retposition = bone->mRelativeTranslation;
			Quaternion	retrotation = bone->mRelativeRotation;
			Vector3		bonescaling = Vector3::cIdentity;
			Quaternion	worldrotation = Quaternion::cIdentity;

			// Root bone.
			if ( root )
			{
				bone->mTranslation = retposition;
				bone->mRotation = retrotation;
			}
			// Child bone, make absolute transform from parent bone.
			else
			{
				Bone* parent = mBones[bone->mParentID];

				bone->mTranslation = retposition * parent->mScaling;
				bone->mTranslation *= parent->mRotation;
				bone->mTranslation += parent->mTranslation;

				bone->mRotation = retrotation * parent->mRotation;
			}

			// Set scaling.
			if ( bone->mScaled )
				bone->mScaling *= bonescaling;
			else
				bone->mScaling = bonescaling;

			if ( mSklInfUsing != _null && worldrotation != Quaternion::cIdentity )
				bone->mRotation *= worldrotation;

			if ( bone->mDummy )
				continue;
		}
	}

	UpdateSkinTransform( );
	UpdateBoundBox( );
}

IBone* Skeleton::CreateBone( StringPtr name, _dword parentid, _bool dummy )
{
	if ( parentid != -1 )
	{
		// Bad parent id.
		if ( mBones.IsIndexValid( (_long) parentid ) == _false )
			return _null;
	}

	// Create bone use memory buffer.
	Bone* bone = new ( mMemoryBuffer.BufferAlloc( sizeof( Bone ) ) ) Bone( this, name, mBones.Length( ), parentid, dummy );
	mBones.Add( bone );

	// Bone changed, need to update.
	mNeedToUpdate = _true;

	if ( dummy == _false )
		mSkinBoneCount ++;

	return bone;
}

_void Skeleton::ReleaseBone( IBone*& bone )
{
	if ( bone == _null )
		return;

	_dword boneid = bone->GetBoneID( );

	if ( GetBone( boneid ) != bone )
		return;

	// Remove child of this bone.
	for ( _long i = boneid + 1; i < mBones.Length( ); i ++ )
	{
		if ( mBones[i]->mParentID == boneid )
		{
			IBone* c = mBones[i];
			ReleaseBone( c );
		}
	}
	if ( mBones[ boneid ]->IsDummy( ) == _false )
		mSkinBoneCount --;

	// Delete use memory buffer.
	mBones[ boneid ]->Bone::~Bone( );
	mMemoryBuffer.BufferFree( mBones[ boneid ] );

	// Remove from bone array.
	mBones.RemoveAt( boneid );

	bone = _null;

	// Adjust parent ID.
	for ( _long i = boneid; i < mBones.Length( ); i ++ )
	{
		if ( mBones[i]->mParentID != -1 && mBones[i]->mParentID > boneid )
			mBones[i]->mParentID --;
	}
}

_void Skeleton::ClearBone( )
{
	for ( _long i = 0; i < mBones.Length( ); i ++ )
	{
		// Delete use memory buffer.
		mBones[i]->Bone::~Bone( );
		mMemoryBuffer.BufferFree( mBones[i] );
	}

	mBones.Clear( );
}

IBone* Skeleton::GetBone( StringPtr name ) const
{
	for ( _long i = 0; i < mBones.Length( ); i ++ )
	{
		if ( mBones[i]->GetName( ) == name )
			return mBones[i];
	}

	return _null;
}

_void Skeleton::UsingSkeleton( _dword priority )
{
	if ( mResource != _null )
	{
		mResource->UsingSkeleton( priority );
	}
	else
	{
		UsingResource( priority );

		for ( _long i = 0; i < mAffectAnimas.Length( ); i ++ )
		{
			AffectAnima& aa = mAffectAnimas[i];

			( (SkeletonAnima*) aa.mAnima )->UsingAnima( priority );
		}
	}
}

_void Skeleton::Skinning( Geometry& geo )
{
	if ( mSkinTransform == _null )
		return;

	if ( geo.mRenderFlag & Geometry::_RENDER_STATIC )
		return;

	if ( ( geo.GetVertexFormat( ) & IVertexBuffer::_FORMAT_INFLUENCE ) == 0 || geo.mVertexNumber == 0 )
		return;

	// This geometry has not being filled with data yet.
	if ( geo.mVertexBuffer == _null || ( (VertexBuffer*) geo.mVertexBuffer )->GetResObject( ) == _null )
		return;

	_dword skinmode = GetGraphicsManager( ).GetSkinningMode( );

	if ( skinmode == IGraphicsManager::_SKINNING_GPU )
	{
		// Switch to SSE mode if not support.
		if ( mSkinBoneCount > GetGraphicsManager( ).GetMaxGpuSkinningCount( ) )
			skinmode = IGraphicsManager::_SKINNING_SSE;
	}

	// Can not do GPU skinning for vertex buffer without skin count, such as binded to a tag point.
	if ( skinmode == IGraphicsManager::_SKINNING_GPU && geo.mVertexBuffer->GetSkinCount( ) == 0 )
		skinmode = IGraphicsManager::_SKINNING_SSE;

	// Process skin in GPU.
	if ( skinmode == IGraphicsManager::_SKINNING_GPU )
	{
		// Rebuild vertex buffer to put helper data into.
		if ( geo.mHelperBuffer != _null )
		{
			if ( GetGeometryFactory( ).BuildSkinBufferForGPU( geo ) == _false )
				return;
		}

		assert( mSkinBoneCount <= GetGraphicsManager( ).GetMaxGpuSkinningCount( ) )

		if ( geo.mSkeleton != this )
		{
			GetModelFactory( ).ReleaseSkeleton( geo.mSkeleton );
			geo.mSkeleton = GetModelFactory( ).CloneSkeleton( this );
		}
	}
	// Process skin in CPU.
	else
	{
		// Build helper buffer to reduce size of vertex buffer.
		if ( geo.mHelperBuffer == _null )
		{
			if ( GetGeometryFactory( ).BuildSkinBufferForCPU( geo ) == _false )
				return;
		}

		// Lock vertex buffer Mesh will be wrong display if lock flag is writeonly.
		_dword vsize = geo.mVertexBuffer->GetVertexSize( );
		_byte* vbuffer = (_byte*) geo.mVertexBuffer->Lock( geo.mStartVertex * vsize, geo.mVertexNumber * vsize, IGeometryFactory::_LOCK_WRITE );
		if ( vbuffer == _null )
			return;

		// Lock helper buffer.
		_byte* hbuffer = (_byte*) geo.mHelperBuffer->Lock( 0, geo.mHelperBuffer->GetLength( ), IGeometryFactory::_LOCK_READONLY );
		if ( hbuffer == _null )
		{
			geo.mVertexBuffer->Unlock( );
			return;
		}

		// Prepare normal buffer.
		_dword vertexformat = geo.GetVertexFormat( );
		_byte* nbuffer = ( vertexformat & IVertexBuffer::_FORMAT_NORMAL ) ? vbuffer + ModelHelper::GetVertexFieldOffset( geo.GetVertexFormat( ), IVertexBuffer::_FORMAT_NORMAL ) : _null;
		_byte* tbuffer = ( vertexformat & IVertexBuffer::_FORMAT_TANGENT ) ? vbuffer + ModelHelper::GetVertexFieldOffset( geo.GetVertexFormat( ), IVertexBuffer::_FORMAT_TANGENT ) : _null;

		// Process skin in CPU.
		AxisAlignedBoxMaker boxmaker;

		#ifndef _EXTEND_INSTRUCTIONS
		skinmode = IGraphicsManager::_SKINNING_CPU;
		#endif

		if ( skinmode == IGraphicsManager::_SKINNING_SSE )
			SSESkinning( vbuffer, nbuffer, tbuffer, hbuffer, _null, geo.mVertexNumber, vsize, mSkinTransform, mSkinBoneCount, boxmaker );
		else if ( skinmode == IGraphicsManager::_SKINNING_CPU )
			CPUSkinning( vbuffer, nbuffer, tbuffer, hbuffer, _null, geo.mVertexNumber, vsize, mSkinTransform, mSkinBoneCount, boxmaker );

		geo.mVertexBuffer->Unlock( );
		geo.mHelperBuffer->Unlock( );

		// Set bound box to vertex buffer.
		geo.mVertexBuffer->SetBoundBox( boxmaker );
	}
}
_void Skeleton::ClearAnimas( )
{
	// Unref affecting animas.
	for ( _long i = 0; i < mAffectAnimas.Length( ); i ++ )
		GetModelFactory( ).ReleaseSkeletonAnima( mAffectAnimas[i].mAnima );

	mAffectAnimas.Clear( _true );
}
