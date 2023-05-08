#pragma once

namespace Xixels
{

class VertexBuffer : public IVertexBuffer, public ReferencedObject
{
private:
	struct ResourceData : public ReferencedObject
	{
		_void*			mResObject;
		_void*			mDeclObject;
		_byte*			mRawBuffer;
		_byte*			mAlignBuffer;
		_byte*			mStagingBuffer;
		_dword			mType;
		_dword			mLength;
		_dword			mVertexSize;
		_dword			mResVertexSize;
		_dword			mVertexFormat;
		_dword			mAlign;
		_dword			mSkinCount;
		AxisAlignedBox	mBoundBox;

		inline ResourceData( )
			: mResObject( _null ), mDeclObject( _null ), mRawBuffer( _null ), mAlignBuffer( _null ),
			mStagingBuffer( _null ), mType( 0 ), mLength( 1 ), mVertexSize( 0 ), mResVertexSize( 0 ), 
			mVertexFormat( 0 ), mAlign( 1 ), mSkinCount( 0 ), mBoundBox( AxisAlignedBox::cNullBox )
		{
		}

		inline ResourceData( _void* vb, _dword type, _dword length, _dword size, _dword format, _dword align ) 
			: mResObject( vb ), mDeclObject( _null ), mRawBuffer( _null ), mAlignBuffer( _null ), 
			mStagingBuffer( _null ), mType( type ), mLength( length ), mVertexSize( size ), mResVertexSize( size ), 
			mVertexFormat( format ), mAlign( align ), mSkinCount( 0 ), mBoundBox( AxisAlignedBox::cNullBox )
		{
		}
	};

	ResourceData*	mResourceData;
	_ptr			mUserData;
	_dword			mFrameToken;
	_dword			mLockFlag;

public:
	VertexBuffer( _void* vb, _dword type, _dword length, _dword format, _dword align, _bool needmembuffer );
	VertexBuffer( VertexBuffer* buffer );
	~VertexBuffer( );

	inline static _bool SameVertexBuffer( IVertexBuffer* buffer1, IVertexBuffer* buffer2 )
	{
		_void* obj1 = buffer1 == _null ? _null : ( (VertexBuffer*) buffer1 )->GetResObject( );
		_void* obj2 = buffer2 == _null ? _null : ( (VertexBuffer*) buffer2 )->GetResObject( );

		return obj1 == obj2;
	}

	inline _void* GetResObject( ) const
		{ return mResourceData->mResObject; }

	inline _void* GetDeclObject( ) const
		{ return mResourceData->mDeclObject; }

	inline _dword GetResVertexSize( ) const
	{
		return mResourceData->mResVertexSize; 
	}

	_void	ReleaseResourceData( );
	_void	ResetResourceData( VertexBuffer* buffer );

	_void	CreateMemoryBuffer( );
	_void	ReleaseMemoryBuffer( );
	_dword	GetMemoryBufferSize( ) const;

	_void	ChangeVertexSize( _dword number, _dword offset, _dword oldvsize, _dword newvsize );
	_void	ResetResObject( _void* vb );
	_void	ResetResObject( _void* vb, VertexBuffer* buffer );
	_void	ChangeResObject( );

public:
	virtual _dword GetType( ) const
		{ return mResourceData->mType; }
	virtual _dword GetLength( ) const
		{ return mResourceData->mLength; }
	virtual _dword GetVertexSize( ) const
		{ return mResourceData->mVertexSize; }
	virtual _dword GetVertexFormat( ) const
		{ return mResourceData->mVertexFormat; }

	virtual _void SetSkinCount( _dword skincount )
		{ mResourceData->mSkinCount = skincount; }
	virtual _dword GetSkinCount( ) const
		{ return mResourceData->mSkinCount; }

	virtual _void SetFrameToken( _dword token )
		{ mFrameToken = token; }
	virtual _dword GetFrameToken( ) const
		{ return mFrameToken; }

	virtual _void SetUserData( _ptr userdata )
		{ mUserData = userdata; }
	virtual _ptr GetUserData( ) const
		{ return mUserData; }

	virtual _void SetBoundBox( const AxisAlignedBox& boundbox )
		{ mResourceData->mBoundBox = boundbox; }
	virtual const AxisAlignedBox& GetBoundBox( ) const
		{ return mResourceData->mBoundBox; }
	
	virtual _void	ChangeVertexFormat( _dword format );
	virtual _void	ChangeVertexBuffer( _void* buffer, _dword length, _dword format );

	virtual _void*	Lock( _dword offset, _dword length, _dword flag );
	virtual _void	Unlock( );

	virtual _bool	Copy( _dword offset, _void* buffer, _dword length );
	virtual _bool	Fill( _dword offset, const _void* buffer, _dword length );
};

};
