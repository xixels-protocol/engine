#include "TagPoint.h"

TagPoint::TagPoint( ) : mIgnoreFlag( 0 ), mParent( _null ),
	mTransform( Matrix4::cIdentity ), mBindSkeleton( _null ), mBindBoneID( -1 ), mBindVertexCount( 0 )
{
}

TagPoint::TagPoint( const Matrix4& mat ) : mIgnoreFlag( 0 ), mParent( _null ),
	mTransform( mat ), mBindSkeleton( _null ), mBindBoneID( -1 ), mBindVertexCount( 0 )
{
}

TagPoint::TagPoint( TagPoint* tp ) : mParent( _null ), mBindSkeleton( _null )
{
	mIgnoreFlag			= tp->mIgnoreFlag;
	mTransform			= tp->mTransform;
	mBindBoneID			= tp->mBindBoneID;
	mBindVertexCount	= tp->mBindVertexCount;

	if ( tp->mParent != _null )
		mParent = GetPhysicsFactory( ).CloneTagPoint( tp->mParent );

	if ( tp->mBindSkeleton != _null )
		mBindSkeleton = GetModelFactory( ).CloneSkeleton( tp->mBindSkeleton );

	for ( _long i = 0; i < tp->mBindVertexBuffers.Length( ); i ++ )
		mBindVertexBuffers.Add( GetGeometryFactory( ).CloneVertexBuffer( tp->mBindVertexBuffers[i] ) );
}

TagPoint::~TagPoint( )
{
	GetPhysicsFactory( ).ReleaseTagPoint( mParent );
	GetModelFactory( ).ReleaseSkeleton( mBindSkeleton );

	for ( _long i = 0; i < mBindVertexBuffers.Length( ); i ++ )
		GetGeometryFactory( ).ReleaseVertexBuffer( mBindVertexBuffers[i] );
}

Matrix4& TagPoint::GetTransform( _bool bind )
{
	if ( bind == _false )
		return mTransform;

	if ( mBindSkeleton == _null && mBindVertexCount == 0 )
		return mTransform;

	// Build transform from bone.
	if ( mBindSkeleton != _null )
	{
		IBone* bone = mBindSkeleton->GetBone( mBindBoneID );
		if ( bone != _null )
			mTransform.Compose( bone->GetTranslation( ), bone->GetRotation( ), bone->GetScaling( ) );
	}
	// Build transform from geometry.
	else if ( mBindVertexCount != 0 )
	{
		_dword vidx = Math::Random( mBindVertexCount );

		for ( _long i = 0; i < mBindVertexBuffers.Length( ); i ++ )
		{
			IVertexBuffer* vb = mBindVertexBuffers[i];

			_dword vnum = vb->GetLength( ) / vb->GetVertexSize( );
			if ( vidx >= vnum )
			{
				vidx -= vnum;
				continue;
			}

			Vector3* vertex = (Vector3*) vb->Lock( vidx * vb->GetVertexSize( ), vb->GetVertexSize( ), IGeometryFactory::_LOCK_READONLY );
			if ( vertex != _null )
			{
				Vector3 pos = *vertex;
				vb->Unlock( );

				mTransform.Translation( pos );
			}

			break;
		}
	}

	// Ignore translation / rotation / scaling.
	IgnoreTransform( mTransform );

	return mTransform;
}

Matrix4	TagPoint::BuildTransform( )
{
	Matrix4 mat = GetTransform( _true );

	// Not ignore parent, apply parent transform.
	if ( ( mIgnoreFlag & _IGNORE_PARENT ) == 0 && mParent != _null )
	{
		Matrix4 pmat = mParent->BuildTransform( );

		// Ignore translation / rotation / scaling.
		IgnoreTransform( pmat );

		mat *= pmat;
	}

	return mat;
}

Matrix4 TagPoint::BuildTransform( const Matrix4& wmat )
{
	Matrix4 mat = BuildTransform( );

	// Not ignore world, apply world transform.
	if ( IsIgnoreWorld( ) == _false )
		mat *= wmat;

	return mat;
}

Matrix4 TagPoint::BuildTransform( const Matrix4& wmat, const Matrix4& pmat )
{
	Matrix4 mat = BuildTransform( );

	// Not ignore parent, apply parent transform.
	if ( ( mIgnoreFlag & _IGNORE_PARENT ) == 0 )
	{
		Matrix4 tpmat = pmat;

		// Ignore translation / rotation / scaling.
		IgnoreTransform( tpmat );

		mat *= tpmat;
	}

	// Not ignore world, apply world transform.
	if ( IsIgnoreWorld( ) == _false )
		mat *= wmat;

	return mat;
}

_bool TagPoint::IsIgnoreWorld( ) const
{
	if ( mIgnoreFlag & _IGNORE_WORLD )
		return _true;

	if ( mParent != _null )
		return ( (TagPoint*) mParent )->IsIgnoreWorld( );

	return _false;
}

_void TagPoint::IgnoreTransform( Matrix4& mat )
{
	// Ignore translation / rotation / scaling.
	if ( ( mIgnoreFlag & ( _IGNORE_TRANSLATION | _IGNORE_ROTATION | _IGNORE_SCALING ) ) == 0 )
		return;

	Vector3 t, s; Matrix3 r;
	mat.Decompose( t, r, s );

	if ( mIgnoreFlag & _IGNORE_TRANSLATION )
		t = Vector3::cOrigin;
	if ( mIgnoreFlag & _IGNORE_SCALING )
		s = Vector3::cIdentity;
	if ( mIgnoreFlag & _IGNORE_ROTATION )
		r = Matrix3::cIdentity;

	mat.Compose( t, r, s );
}

_void TagPoint::BindSkeleton( ISkeleton* skeleton, _dword boneid )
{
	GetModelFactory( ).ReleaseSkeleton( mBindSkeleton );
	mBindSkeleton = GetModelFactory( ).CloneSkeleton( skeleton );
	mBindBoneID = boneid;
}

_void TagPoint::UnbindSkeleton( )
{
	GetModelFactory( ).ReleaseSkeleton( mBindSkeleton );
	mBindBoneID = 0;
}

_void TagPoint::BindGeometry( const Geometry& geo )
{
	IVertexBuffer* vb = geo.mVertexBuffer;
	if ( vb == _null || vb->GetLength( ) == 0 || vb->GetVertexSize( ) == 0 )
		return;

	// Turn off GPU skinning for tag point geometry, skin count 5 means disable.
	if ( geo.GetVertexFormat( ) & IVertexBuffer::_FORMAT_BONEBLEND )
		vb->SetSkinCount( 5 );

	mBindVertexBuffers.Add( GetGeometryFactory( ).CloneVertexBuffer( vb ) );
	mBindVertexCount += vb->GetLength( ) / vb->GetVertexSize( );
}

_void TagPoint::UnbindGeometry( )
{
	for ( _long i = 0; i < mBindVertexBuffers.Length( ); i ++ )
		GetGeometryFactory( ).ReleaseVertexBuffer( mBindVertexBuffers[i] );

	mBindVertexBuffers.Clear( );
	mBindVertexCount = 0;
}