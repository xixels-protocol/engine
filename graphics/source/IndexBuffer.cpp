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

_void IndexBuffer::ChangeIndexBuffer( _void* buffer, _dword length, _dword isize )
{
	ChangeResObject( );

	_dword oldlength = mResourceData->mLength;
	mResourceData->mLength = length;
	mResourceData->mIndexSize = isize;

	// Process buffer in memory.
	if ( mResourceData->mAlignBuffer != _null )
	{
		_byte* rbuffer = mResourceData->mRawBuffer;
		CreateMemoryBuffer( );
		Memory::MemCpy( mResourceData->mAlignBuffer, buffer, length );
		assert( rbuffer != buffer )
		delete[] rbuffer;
		( (GeometryFactory&) GetGeometryFactory( ) ).DecreaseIndexBufferSize( IGeometryFactory::_BUFFER_SYSTEM, oldlength );
	}

	// Process buffer in render api.
	if ( mResourceData->mResObject != _null )
	{
		_void* ib = GetRenderer( ).CreateIndexBuffer( mResourceData->mType, length, isize );
		if ( ib == _null )
			return;

		( (GeometryFactory&) GetGeometryFactory( ) ).IncreaseIndexBufferSize( IGeometryFactory::_BUFFER_RENDER, length );

		_byte* newbuffer = (_byte*) GetRenderer( ).LockIndexBuffer( ib, 0, length, 0 );

		Memory::MemCpy( newbuffer, buffer, length );

		if ( mResourceData->mAlignBuffer != _null)
			GetRenderer( ).UnlockIndexBuffer( ib, newbuffer, length );
		else
			GetRenderer( ).UnlockIndexBuffer( ib, _null, 0 );

		GetRenderer( ).ReleaseIndexBuffer( mResourceData->mResObject );
		( (GeometryFactory&) GetGeometryFactory( ) ).DecreaseIndexBufferSize( IGeometryFactory::_BUFFER_RENDER, oldlength );

		mResourceData->mResObject = ib;
	}
}

_void* IndexBuffer::Lock( _dword offset, _dword length, _dword flag )
{
	if ( mResourceData->mResObject == _null && mResourceData->mAlignBuffer == _null )
		return _null;

	if ( offset + length > mResourceData->mLength )
		return _null;

	mLockFlag = flag;

	// Change index buffer resource when lock to write.
	if ( ( flag & IGeometryFactory::_LOCK_READONLY ) == 0 && ( flag & IGeometryFactory::_LOCK_INITFILL ) == 0 )
		ChangeResObject( );
	
	// We use both resource object and memory buffer in OpenglES 2.0 in which case only the memory buffer is accessable.
	if ( mResourceData->mAlignBuffer != _null )
		return mResourceData->mAlignBuffer + offset;

	if ( length == 0 )
		length = mResourceData->mLength;

	// Lock index buffer.
	_byte* buffer = _null;
	if ( mResourceData->mResObject != _null )
		buffer = (_byte*) GetRenderer( ).LockIndexBuffer( mResourceData->mResObject, offset, length, flag );

	return buffer;
}

_void IndexBuffer::Unlock( )
{
	if ( mResourceData->mResObject == _null && mResourceData->mAlignBuffer == _null )
		return;

	// Write back memory buffer into index buffer when mLockFlag is not readonly.
	if ( mResourceData->mAlignBuffer != _null )
	{
		if ( mLockFlag != IGeometryFactory::_LOCK_READONLY && GeometryFactory::IsIndexBufferUnlockDisabled( ) == _false )
			GetRenderer( ).UnlockIndexBuffer( mResourceData->mResObject, mResourceData->mAlignBuffer, mResourceData->mLength );
	}
	else
	{
		GetRenderer( ).UnlockIndexBuffer( mResourceData->mResObject, _null, mResourceData->mLength );
	}

	mLockFlag = 0;
}

_bool IndexBuffer::Copy( _dword offset, _void* buffer, _dword length )
{
	if ( offset + length > mResourceData->mLength )
		return _false;

	// Lock index buffer to read.
	_void* tempbuffer = Lock( offset, length, IGeometryFactory::_LOCK_READONLY );
	if ( tempbuffer == _null )
		return _false;

	Memory::MemCpy( buffer, tempbuffer, length );

	Unlock( );

	return _true;
}

_bool IndexBuffer::Fill( _dword offset, const _void* buffer, _dword length )
{
	if ( buffer == _null )
		return _false;

	if ( offset + length > mResourceData->mLength )
		return _false;

	// Lock index buffer to write.
	_void* tempbuffer = Lock( offset, length, IGeometryFactory::_LOCK_WRITEONLY );
	if ( tempbuffer == _null )
		return _false;

	Memory::MemCpy( tempbuffer, buffer, length );

	Unlock( );

	return _true;
}