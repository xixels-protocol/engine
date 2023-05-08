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