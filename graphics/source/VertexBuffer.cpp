#include "VertexBuffer.h"

VertexBuffer::VertexBuffer( _void* vb, _dword type, _dword length, _dword format, _dword align, _bool needmembuffer ) : mFrameToken( 0 ), mUserData( 0 ), mLockFlag( 0 )
{
	// Only lower 15bits is used for vertex format.
	format &= IVertexBuffer::_FORMAT_VERTEXDECL_MASK;

	// Create resource data.
	mResourceData = new ResourceData( vb, type, length, ModelHelper::GetVertexSize( format ),
		format, Math::Clamp( align, (_dword) 1, (_dword) 16 ) );
	if ( vb != _null )
		( (GeometryFactory&) GetGeometryFactory( ) ).IncreaseVertexBufferSize( IGeometryFactory::_BUFFER_RENDER, length );

	// Create vertex decl.
	mResourceData->mDeclObject = GeometryFactory::GetVertexDecl( mResourceData->mVertexFormat );

	if ( needmembuffer )
		CreateMemoryBuffer( );
}

VertexBuffer::VertexBuffer( VertexBuffer* buffer ) : mFrameToken( 0 ), mUserData( 0 ), mLockFlag( 0 )
{
	// Reference resource object.
	mResourceData = buffer->mResourceData;
	mResourceData->IncRefCount( );
}

VertexBuffer::~VertexBuffer( )
{
}