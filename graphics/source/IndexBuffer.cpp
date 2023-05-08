#include "IndexBuffer.h"

IndexBuffer::IndexBuffer( _void* ib, _dword type, _dword length, _dword isize, _dword align, _dword needmembuffer ) : mUserData( 0 ), mLockFlag( 0 )
{
	// Create resource data.
	mResourceData = new ResourceData( ib, type, length, isize, Math::Clamp( align, (_dword) 1, (_dword) 16 ) );
	if ( ib != _null )
		( (GeometryFactory&) GetGeometryFactory( ) ).IncreaseIndexBufferSize( IGeometryFactory::_BUFFER_RENDER, length );

	if ( needmembuffer )
		CreateMemoryBuffer( );
}

IndexBuffer::IndexBuffer( IndexBuffer* buffer ) : mUserData( 0 ), mLockFlag( 0 )
{
	// Reference resource object.
	mResourceData = buffer->mResourceData;
	mResourceData->IncRefCount( );
}

IndexBuffer::~IndexBuffer( )
{
	ReleaseResourceData( );
}

_void IndexBuffer::ReleaseResourceData( )
{
	// Release owned resource.
	if ( mResourceData->DecRefCount( ) == 0 )
	{
		if ( mResourceData->mResObject != _null )
		{
			GetRenderer( ).ReleaseIndexBuffer( mResourceData->mResObject );
			( (GeometryFactory&) GetGeometryFactory( ) ).DecreaseIndexBufferSize( IGeometryFactory::_BUFFER_RENDER, mResourceData->mLength );
		}
		if ( mResourceData->mRawBuffer != _null )
		{
			delete[] mResourceData->mRawBuffer;
			( (GeometryFactory&) GetGeometryFactory( ) ).DecreaseIndexBufferSize( IGeometryFactory::_BUFFER_SYSTEM, mResourceData->mLength );
		}

		delete mResourceData;
	}
}

_void IndexBuffer::ResetResourceData( IndexBuffer* buffer )
{
	if ( mResourceData == buffer->mResourceData )
		return;

	ReleaseResourceData( );

	mResourceData = buffer->mResourceData;
	mResourceData->IncRefCount( );
}

_void IndexBuffer::CreateMemoryBuffer( )
{
	_byte* rbuffer = _null;
	_byte* abuffer = _null;

	// Align is 1, so just create buffer in any address.
	if ( mResourceData->mAlign == 1 )
	{
		rbuffer = new _byte[ mResourceData->mLength ];
		abuffer = rbuffer;
		( (GeometryFactory&) GetGeometryFactory( ) ).IncreaseIndexBufferSize( IGeometryFactory::_BUFFER_SYSTEM, mResourceData->mLength );
	}
	// Align is not 1, create buffer a litte larger, and adjust align buffer.
	else
	{
		rbuffer = new _byte[ mResourceData->mLength + mResourceData->mAlign ];
		abuffer = (_byte*) ( ( (_ptr) rbuffer + mResourceData->mAlign - 1 ) / mResourceData->mAlign * mResourceData->mAlign );
		( (GeometryFactory&) GetGeometryFactory( ) ).IncreaseIndexBufferSize( IGeometryFactory::_BUFFER_SYSTEM, mResourceData->mLength + mResourceData->mAlign );
	}

	mResourceData->mRawBuffer = rbuffer;
	mResourceData->mAlignBuffer = abuffer;
}

_void IndexBuffer::ReleaseMemoryBuffer( )
{
	if ( mResourceData->mRawBuffer == _null )
		return;

	_dword size = GetMemoryBufferSize( );

	delete[] mResourceData->mRawBuffer;
	mResourceData->mRawBuffer = _null;
	mResourceData->mAlignBuffer = _null;

	( (GeometryFactory&) GetGeometryFactory( ) ).DecreaseIndexBufferSize( IGeometryFactory::_BUFFER_SYSTEM, size );
}

_dword IndexBuffer::GetMemoryBufferSize( ) const
{
	if ( mResourceData->mRawBuffer == _null )
		return 0;
	else if ( mResourceData->mAlign == 1 )
		return mResourceData->mLength;
	else
		return mResourceData->mLength + mResourceData->mAlign;
}

_void IndexBuffer::ResetResObject( _void* ib )
{
	if ( mResourceData->mResObject == ib )
		return;

	if ( ib != _null )
		( (GeometryFactory&) GetGeometryFactory( ) ).IncreaseIndexBufferSize( IGeometryFactory::_BUFFER_RENDER, mResourceData->mLength );

	GetRenderer( ).ReleaseIndexBuffer( mResourceData->mResObject );
	( (GeometryFactory&) GetGeometryFactory( ) ).DecreaseIndexBufferSize( IGeometryFactory::_BUFFER_RENDER, mResourceData->mLength );
	mResourceData->mResObject = ib;
}

_void IndexBuffer::ResetResObject( _void* ib, IndexBuffer* buffer )
{
	ResetResObject( ib );
	if ( buffer != _null )
	{
		ReleaseMemoryBuffer( );

		mResourceData->mType			= buffer->mResourceData->mType;
		mResourceData->mLength			= buffer->mResourceData->mLength;
		mResourceData->mIndexSize		= buffer->mResourceData->mIndexSize;
		mResourceData->mAlign			= buffer->mResourceData->mAlign;

		if ( buffer->mResourceData->mAlignBuffer != _null )
		{
			CreateMemoryBuffer( );
			Memory::MemCpy( mResourceData->mAlignBuffer, buffer->mResourceData->mAlignBuffer, mResourceData->mLength );
			if ( mResourceData->mResObject != _null )
				GetRenderer( ).UnlockIndexBuffer( mResourceData->mResObject, mResourceData->mAlignBuffer, mResourceData->mLength );
		}
	}
}

_void IndexBuffer::ChangeResObject( )
{
	if ( GetModelFactory( ).IsForceRefreshResObjectEnabled( ) )
		return;

	// Already owned resource, dont need to change.
	if ( mResourceData->GetRefCount( ) == 1 )
		return;

	_byte* abuffer = mResourceData->mAlignBuffer;

	// Create resource data.
	ResourceData* data = new ResourceData( GetRenderer( ).CloneIndexBuffer( mResourceData->mResObject ),
		mResourceData->mType, mResourceData->mLength, mResourceData->mIndexSize, mResourceData->mAlign );
	mResourceData->DecRefCount( );
	mResourceData = data;
	if ( mResourceData->mResObject != _null )
		( (GeometryFactory&) GetGeometryFactory( ) ).IncreaseIndexBufferSize( IGeometryFactory::_BUFFER_RENDER, mResourceData->mLength );

	// Copy memory buffer back if needed.
	if ( abuffer != _null )
	{
		CreateMemoryBuffer( );
		Memory::MemCpy( mResourceData->mAlignBuffer, abuffer, mResourceData->mLength );
	}
	
	// Write back memory buffer into index buffer.
	if ( mResourceData->mResObject != _null && mResourceData->mAlignBuffer != _null )
		GetRenderer( ).UnlockIndexBuffer( mResourceData->mResObject, mResourceData->mAlignBuffer, mResourceData->mLength );
}