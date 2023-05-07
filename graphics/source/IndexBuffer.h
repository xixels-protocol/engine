#pragma once

namespace Xixels
{

class IndexBuffer : public IIndexBuffer, public ReferencedObject
{
private:
	struct ResourceData : public ReferencedObject
	{
		_void*		mResObject;
		_byte*		mRawBuffer;
		_byte*		mAlignBuffer;
		_dword		mType;
		_dword		mLength;
		_dword		mIndexSize;
		_dword		mAlign;

		inline ResourceData( ) : mResObject( _null ), mRawBuffer( _null ), mAlignBuffer( _null ),
			mType( 0 ), mLength( 1 ), mIndexSize( 0 ), mAlign( 1 )
		{
		}

		inline ResourceData( _void* ib, _dword type, _dword length, _dword isize, _dword align ) : mResObject( ib ), mRawBuffer( _null ),
			mAlignBuffer( _null ), mType( type ), mLength( length ), mIndexSize( isize ), mAlign( align )
		{
		}
	};

	ResourceData*	mResourceData;
	_ptr			mUserData;
	_dword			mLockFlag;

public:
	IndexBuffer( _void* ib, _dword type, _dword length, _dword isize, _dword align, _dword needmembuffer );
	IndexBuffer( IndexBuffer* buffer );
	~IndexBuffer( );

	inline static _bool SameIndexBuffer( IIndexBuffer* buffer1, IIndexBuffer* buffer2 )
	{
		_void* obj1 = buffer1 == _null ? _null : ( (IndexBuffer*) buffer1 )->GetResObject( );
		_void* obj2 = buffer2 == _null ? _null : ( (IndexBuffer*) buffer2 )->GetResObject( );

		return obj1 == obj2;
	}

	inline _void* GetResObject( ) const
		{ return mResourceData->mResObject; }

	_void	ReleaseResourceData( );
	_void	ResetResourceData( IndexBuffer* buffer );

	_void	CreateMemoryBuffer( );
	_void	ReleaseMemoryBuffer( );
	_dword	GetMemoryBufferSize( ) const;

	_void	ResetResObject( _void* ib );
	_void	ResetResObject( _void* ib, IndexBuffer* buffer );
	_void	ChangeResObject( );

public:
	virtual _dword GetType( ) const
		{ return mResourceData->mType; }
	virtual _dword GetLength( ) const
		{ return mResourceData->mLength; }
	virtual _dword GetIndexSize( ) const
		{ return mResourceData->mIndexSize; }

	virtual _void SetUserData( _ptr userdata )
		{ mUserData = userdata; }
	virtual _ptr	GetUserData( ) const
		{ return mUserData; }

	virtual _void	ChangeIndexBuffer( _void* buffer, _dword length, _dword isize );

	virtual _void*	Lock( _dword offset, _dword length, _dword flag );
	virtual _void	Unlock( );

	virtual _bool	Copy( _dword offset, _void* buffer, _dword length );
	virtual _bool	Fill( _dword offset, const _void* buffer, _dword length );
};

};
