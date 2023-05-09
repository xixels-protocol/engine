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

_void VertexBuffer::ReleaseResourceData( )
{
	if ( mResourceData->DecRefCount( ) == 0 )
	{
		if ( mResourceData->mResObject != _null )
		{
			GetRenderer( ).ReleaseVertexBuffer( mResourceData->mResObject );
			( (GeometryFactory&) GetGeometryFactory( ) ).DecreaseVertexBufferSize( IGeometryFactory::_BUFFER_RENDER, mResourceData->mLength );
		}

		ReleaseMemoryBuffer( );

		delete mResourceData;
	}
}

_void VertexBuffer::ResetResourceData( VertexBuffer* buffer )
{
	if ( mResourceData == buffer->mResourceData )
		return;

	ReleaseResourceData( );

	mResourceData = buffer->mResourceData;
	mResourceData->IncRefCount( );
}

_void VertexBuffer::CreateMemoryBuffer( )
{
	_byte* rbuffer = _null;
	_byte* abuffer = _null;

	// Align is 1, so just create buffer in any address.
	if ( mResourceData->mAlign == 1 )
	{
		rbuffer = new _byte[ mResourceData->mLength ];
		abuffer = rbuffer;
		( (GeometryFactory&) GetGeometryFactory( ) ).IncreaseVertexBufferSize( IGeometryFactory::_BUFFER_SYSTEM, mResourceData->mLength );
	}
	// Align is not 1, create buffer a litte larger, and adjust align buffer.
	else
	{
		rbuffer = new _byte[ mResourceData->mLength + mResourceData->mAlign ];
		abuffer = (_byte*) ( ( (_ptr) rbuffer + mResourceData->mAlign - 1 ) / mResourceData->mAlign * mResourceData->mAlign );
		( (GeometryFactory&) GetGeometryFactory( ) ).IncreaseVertexBufferSize( IGeometryFactory::_BUFFER_SYSTEM, mResourceData->mLength + mResourceData->mAlign );
	}

	mResourceData->mRawBuffer = rbuffer;
	mResourceData->mAlignBuffer = abuffer;
}

_void VertexBuffer::ReleaseMemoryBuffer( )
{
	if ( mResourceData->mRawBuffer == _null )
		return;

	_dword size = GetMemoryBufferSize( );

	delete[] mResourceData->mRawBuffer;
	mResourceData->mRawBuffer = _null;
	mResourceData->mAlignBuffer = _null;

	( (GeometryFactory&) GetGeometryFactory( ) ).DecreaseVertexBufferSize( IGeometryFactory::_BUFFER_SYSTEM, size );
}

_dword VertexBuffer::GetMemoryBufferSize( ) const
{
	if ( mResourceData->mRawBuffer == _null )
		return 0;
	else if ( mResourceData->mAlign == 1 )
		return mResourceData->mLength;
	else
		return mResourceData->mLength + mResourceData->mAlign;
}