#pragma once

namespace Xixels
{

class TagPoint : public ITagPoint, public ReferencedObject
{
private:
	_dword					mIgnoreFlag;
	ITagPoint*				mParent;

	Matrix4					mTransform;

	ISkeleton*				mBindSkeleton;
	_dword					mBindBoneID;

	Array< IVertexBuffer* >	mBindVertexBuffers;
	_dword					mBindVertexCount;

public:
	TagPoint( );
	TagPoint( TagPoint* tp );
	TagPoint( const Matrix4& mat );
	~TagPoint( );

public:
	virtual _void SetIgnoreFlag( _dword flag )
		{ mIgnoreFlag = flag; }
	virtual _dword GetIgnoreFlag( ) const
		{ return mIgnoreFlag; }

	virtual _void SetParent( ITagPoint* tp )
		{ GetPhysicsFactory( ).ReleaseTagPoint( mParent ); mParent = GetPhysicsFactory( ).CloneTagPoint( tp ); }
	virtual ITagPoint* GetParent( ) const
		{ return mParent; }

	virtual _void SetTransform( const Matrix4& mat )
		{ mTransform = mat; }

	virtual ISkeleton* GetBindSkeleton( ) const
		{ return mBindSkeleton; }
	virtual IBone* GetBindBone( ) const
		{ return mBindSkeleton != _null ? mBindSkeleton->GetBone( mBindBoneID ) : _null; }

	virtual _dword GetBindGeometryCount( ) const
		{ return mBindVertexBuffers.Length( ); }

	virtual Matrix4&	GetTransform( _bool bind );

	virtual Matrix4		BuildTransform( );
	virtual Matrix4		BuildTransform( const Matrix4& wmat );
	virtual Matrix4		BuildTransform( const Matrix4& wmat, const Matrix4& pmat );

	virtual _bool		IsIgnoreWorld( ) const;
	virtual _void		IgnoreTransform( Matrix4& mat );

	virtual _void		BindSkeleton( ISkeleton* skeleton, _dword boneid );
	virtual _void		UnbindSkeleton( );

	virtual _void		BindGeometry( const Geometry& geo );
	virtual _void		UnbindGeometry( );
};

};