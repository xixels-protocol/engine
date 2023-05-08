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
}