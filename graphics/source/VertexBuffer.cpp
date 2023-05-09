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

_void VertexBuffer::ChangeVertexSize( _dword number, _dword offset, _dword oldvsize, _dword newvsize )
{
	FG_ASSERT( GetModelFactory( ).IsForceRefreshResObjectEnabled( ) || mResourceData->GetRefCount( ) == 1 )

	_dword minsize = Math::Min( newvsize, oldvsize );
	_dword newlength = newvsize * number;

	offset = Math::Min( minsize, offset );
	
	// Process buffer in memory.
	if ( mResourceData->mAlignBuffer != _null )
	{
		_byte* rbuffer = mResourceData->mRawBuffer;
		_byte* abuffer = mResourceData->mAlignBuffer;

		_dword oldsize = GetMemoryBufferSize( );
		mResourceData->mLength = newlength;
		CreateMemoryBuffer( );

		_byte* newbuffer = mResourceData->mAlignBuffer;

		// Copy vertex data.
		for ( _dword i = 0; i < number; i ++ )
		{
			if ( offset == minsize )
			{
				Memory::MemCpy( newbuffer + newvsize * i, abuffer + oldvsize * i, minsize );
			}
			else
			{
				Memory::MemCpy( newbuffer + newvsize * i, abuffer + oldvsize * i, offset );

				if ( newvsize > oldvsize )
					Memory::MemCpy( newbuffer + newvsize * i + offset + newvsize - oldvsize, abuffer + oldvsize * i + offset, minsize - offset );
				else
					Memory::MemCpy( newbuffer + newvsize * i + offset, abuffer + oldvsize * i + offset + oldvsize - newvsize, minsize - offset );
			}
		}

		delete[] rbuffer;

		( (GeometryFactory&) GetGeometryFactory( ) ).DecreaseVertexBufferSize( IGeometryFactory::_BUFFER_SYSTEM, oldsize );
	}

	// Process buffer in render api.
	if ( mResourceData->mResObject != _null )
	{	
		_void* vb = GetRenderer( ).CreateVertexBuffer( mResourceData->mType, newlength );
		if ( vb == _null )
			return;

		( (GeometryFactory&) GetGeometryFactory( ) ).IncreaseVertexBufferSize( IGeometryFactory::_BUFFER_RENDER, newlength );

		_byte* oldbuffer = (_byte*) GetRenderer( ).LockVertexBuffer( mResourceData->mResObject, 0, mResourceData->mLength, IGeometryFactory::_LOCK_READONLY );
		_byte* newbuffer = (_byte*) GetRenderer( ).LockVertexBuffer( vb, 0, newlength, IGeometryFactory::_LOCK_SUBWRITE );

		if ( oldbuffer != _null && newbuffer != _null )
		{
			// Copy vertex data.
			for ( _dword i = 0; i < number; i ++ )
			{
				if ( offset == minsize )
				{
					Memory::MemCpy( newbuffer + newvsize * i, oldbuffer + oldvsize * i, minsize );
				}
				else
				{
					Memory::MemCpy( newbuffer + newvsize * i, oldbuffer + oldvsize * i, offset );

					if ( newvsize > oldvsize )
						Memory::MemCpy( newbuffer + newvsize * i + offset + newvsize - oldvsize, oldbuffer + oldvsize * i + offset, minsize - offset );
					else
						Memory::MemCpy( newbuffer + newvsize * i + offset, oldbuffer + oldvsize * i + offset + oldvsize - newvsize, minsize - offset );
				}
			}
		}

		GetRenderer( ).UnlockVertexBuffer( mResourceData->mResObject, _null, 0 );
		if ( mResourceData->mAlignBuffer != _null )
			GetRenderer( ).UnlockVertexBuffer( vb, newbuffer, newlength );
		else
			GetRenderer( ).UnlockVertexBuffer( vb, _null, 0 );

		GetRenderer( ).ReleaseVertexBuffer( mResourceData->mResObject );
		( (GeometryFactory&) GetGeometryFactory( ) ).DecreaseVertexBufferSize( IGeometryFactory::_BUFFER_RENDER, mResourceData->mLength );

		mResourceData->mResObject = vb;
		mResourceData->mLength = newlength;
	}

	mResourceData->mVertexSize = newvsize;
}

_void VertexBuffer::ResetResObject( _void* vb )
{
	if ( mResourceData->mResObject == vb )
		return;

	if ( vb != _null )
		( (GeometryFactory&) GetGeometryFactory( ) ).IncreaseVertexBufferSize( IGeometryFactory::_BUFFER_RENDER, mResourceData->mLength );

	// Reset resource object.
	GetRenderer( ).ReleaseVertexBuffer( mResourceData->mResObject );
	if ( mResourceData->mResObject != _null )
		( (GeometryFactory&) GetGeometryFactory( ) ).DecreaseVertexBufferSize( IGeometryFactory::_BUFFER_RENDER, mResourceData->mLength );

	mResourceData->mResObject = vb;
}

_void VertexBuffer::ResetResObject( _void* vb, VertexBuffer* buffer )
{
	ResetResObject( vb );
	if ( buffer != _null )
	{
		ReleaseMemoryBuffer( );

		mResourceData->mType			= buffer->mResourceData->mType;
		mResourceData->mLength			= buffer->mResourceData->mLength;
		mResourceData->mVertexSize		= buffer->mResourceData->mVertexSize;
		mResourceData->mResVertexSize	= buffer->mResourceData->mResVertexSize;
		mResourceData->mVertexFormat	= buffer->mResourceData->mVertexFormat;
		mResourceData->mAlign			= buffer->mResourceData->mAlign;
		mResourceData->mSkinCount		= buffer->mResourceData->mSkinCount;
		mResourceData->mBoundBox		= buffer->mResourceData->mBoundBox;

		mResourceData->mDeclObject		= GeometryFactory::GetVertexDecl( mResourceData->mVertexFormat );;

		if ( buffer->mResourceData->mAlignBuffer != _null )
		{
			CreateMemoryBuffer( );
			Memory::MemCpy( mResourceData->mAlignBuffer, buffer->mResourceData->mAlignBuffer, mResourceData->mLength );
			if ( mResourceData->mResObject != _null )
				GetRenderer( ).UnlockVertexBuffer( mResourceData->mResObject, mResourceData->mAlignBuffer, mResourceData->mLength );
		}
	}
}

_void VertexBuffer::ChangeResObject( )
{
	if ( GetModelFactory( ).IsForceRefreshResObjectEnabled( ) )
		return;

	// Already owned resource, dont need to change.
	if ( mResourceData->GetRefCount( ) == 1 )
		return;

	_byte* abuffer = mResourceData->mAlignBuffer;

	// Create resource data.
	ResourceData* data = new ResourceData( GetRenderer( ).CloneVertexBuffer( mResourceData->mResObject ),
		mResourceData->mType, mResourceData->mLength, mResourceData->mVertexSize, mResourceData->mVertexFormat, mResourceData->mAlign );
	data->mSkinCount = mResourceData->mSkinCount;
	data->mBoundBox = mResourceData->mBoundBox;
	mResourceData->DecRefCount( );
	mResourceData = data;
	if ( mResourceData->mResObject != _null )
		( (GeometryFactory&) GetGeometryFactory( ) ).IncreaseVertexBufferSize( IGeometryFactory::_BUFFER_RENDER, mResourceData->mLength );

	// Create vertex decl.
	mResourceData->mDeclObject = GeometryFactory::GetVertexDecl( mResourceData->mVertexFormat );

	// Copy memory buffer back if needed.
	if ( abuffer != _null )
	{
		CreateMemoryBuffer( );
		Memory::MemCpy( mResourceData->mAlignBuffer, abuffer, mResourceData->mLength );
	}

	// Write back memory buffer into vertex buffer.
	if ( mResourceData->mResObject != _null && mResourceData->mAlignBuffer != _null )
		GetRenderer( ).UnlockVertexBuffer( mResourceData->mResObject, mResourceData->mAlignBuffer, mResourceData->mLength );
}

_void VertexBuffer::ChangeVertexFormat( _dword format )
{
	// Only lower 15bits are useful.
	format &= IVertexBuffer::_FORMAT_VERTEXDECL_MASK;

	if ( mResourceData->mVertexFormat == format )
		return;

	// Change vertex buffer size.
	if ( mResourceData->mResObject != _null || mResourceData->mAlignBuffer != _null )
	{
		ChangeResObject( );

		_dword vnumber = mResourceData->mLength / mResourceData->mVertexSize;
		_dword sameformat = 0, diffformat = 0;
		_dword voffset = ModelHelper::GetVertexDiffOffset( mResourceData->mVertexFormat, format, sameformat, diffformat );
		_dword newsize = ModelHelper::GetVertexSize( format );

		ChangeVertexSize( vnumber, voffset, mResourceData->mVertexSize, newsize );
	}

	mResourceData->mVertexFormat = format;
	mResourceData->mResVertexSize = mResourceData->mVertexSize;

	// Create vertex decl.
	mResourceData->mDeclObject = GeometryFactory::GetVertexDecl( format );
}

_void VertexBuffer::ChangeVertexBuffer( _void* buffer, _dword length, _dword format )
{
	if ( buffer == _null )
		return;

	ChangeResObject( );

	// Only lower 15bits is used for vertex format.
	format &= IVertexBuffer::_FORMAT_VERTEXDECL_MASK;
	mResourceData->mVertexFormat = format;

	_dword oldlength = mResourceData->mLength;
	mResourceData->mLength = length;
	mResourceData->mVertexSize = ModelHelper::GetVertexSize( format );
	mResourceData->mResVertexSize = mResourceData->mVertexSize;

	// Process buffer in memory.
	if ( mResourceData->mAlignBuffer != _null )
	{
		_dword oldsize = GetMemoryBufferSize( );
		_byte* rbuffer = mResourceData->mRawBuffer;
		CreateMemoryBuffer( );
		Memory::MemCpy( mResourceData->mAlignBuffer, buffer, length );
		FG_ASSERT( rbuffer != buffer )
		delete[] rbuffer;
		( (GeometryFactory&) GetGeometryFactory( ) ).DecreaseVertexBufferSize( IGeometryFactory::_BUFFER_SYSTEM, oldsize );
	}

	// Process buffer in render api.
	if ( mResourceData->mResObject != _null )
	{
		_dword newlength = ModelHelper::GetSize( format, length );
		_void* vb = GetRenderer( ).CreateVertexBuffer( mResourceData->mType, newlength );
		if ( vb == _null )
			return;

		( (GeometryFactory&) GetGeometryFactory( ) ).IncreaseVertexBufferSize( IGeometryFactory::_BUFFER_RENDER, length );

		_byte* newbuffer = (_byte*) GetRenderer( ).LockVertexBuffer( vb, 0, newlength, IGeometryFactory::_LOCK_INITFILL );

		if ( newbuffer != _null ) 
		{
			Memory::MemCpy( newbuffer, buffer, newlength );
		}

		if ( mResourceData->mAlignBuffer != _null )
			GetRenderer( ).UnlockVertexBuffer( vb, mResourceData->mAlignBuffer, newlength );
		else
			GetRenderer( ).UnlockVertexBuffer( vb, _null, 0 );

		GetRenderer( ).ReleaseVertexBuffer( mResourceData->mResObject );
		( (GeometryFactory&) GetGeometryFactory( ) ).DecreaseVertexBufferSize( IGeometryFactory::_BUFFER_RENDER, oldlength );

		mResourceData->mResObject = vb;
	}

	mResourceData->mDeclObject = GeometryFactory::GetVertexDecl( format );
}

_void* VertexBuffer::Lock( _dword offset, _dword length, _dword flag )
{
	if ( mResourceData->mResObject == _null && mResourceData->mAlignBuffer == _null )
		return _null;

	if ( offset + length > mResourceData->mLength )
		return _null;

	mLockFlag = flag;

	// Change vertex buffer resource when lock to write.
	if ( ( flag & IGeometryFactory::_LOCK_READONLY ) == 0 && ( flag & IGeometryFactory::_LOCK_INITFILL ) == 0 )
		ChangeResObject( );

	// We use both resource object and memory buffer in OpenglES 2.0 in which case only the memory buffer is accessable.
	if ( mResourceData->mAlignBuffer != _null )
		return mResourceData->mAlignBuffer + offset;

	if ( length == 0 )
		length = mResourceData->mLength;

	// Lock vertex buffer.
	_byte* buffer = _null;
	if ( mResourceData->mResObject != _null )
		buffer = (_byte*) GetRenderer( ).LockVertexBuffer( mResourceData->mResObject, offset, length, flag );

	return buffer;
}

_void VertexBuffer::Unlock( )
{
	if ( mResourceData->mResObject == _null && mResourceData->mAlignBuffer == _null )
		return;

	// Write back memory buffer into vertex buffer when mLockFlag is not readonly.
	if ( mResourceData->mAlignBuffer != _null )
	{
		if ( GeometryFactory::IsVertexBufferUnlockDisabled( ) == _false )
		{
			GetRenderer( ).UnlockVertexBuffer( mResourceData->mResObject, mResourceData->mAlignBuffer, mResourceData->mLength );
			mLockFlag = 0;
		}
	}
	else
	{
		GetRenderer( ).UnlockVertexBuffer( mResourceData->mResObject, _null, mResourceData->mLength );
		mLockFlag = 0;
	}
}

_bool VertexBuffer::Copy( _dword offset, _void* buffer, _dword length )
{
	if ( offset + length > mResourceData->mLength )
		return _false;

	// Lock vertex buffer to read.
	_void* tempbuffer = Lock( offset, length, IGeometryFactory::_LOCK_READONLY );
	if ( tempbuffer == _null )
		return _false;

	Memory::MemCpy( buffer, tempbuffer, length );

	Unlock( );

	return _true;
}

_bool VertexBuffer::Fill( _dword offset, const _void* buffer, _dword length )
{
	if ( buffer == _null )
		return _false;

	if ( offset + length > mResourceData->mLength )
		return _false;

	// Lock vertex buffer to write.
	_void* tempbuffer = Lock( offset, length, IGeometryFactory::_LOCK_WRITEONLY );
	if ( tempbuffer == _null )
		return _false;

	Memory::MemCpy( tempbuffer, buffer, length );

	Unlock( );

	return _true;
}