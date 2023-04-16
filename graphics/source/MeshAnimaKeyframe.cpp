#include "MeshAnimaKeyframe.h"

MeshAnimaKeyframe::MeshAnimaKeyframe( _float time, _dword format, _dword count )
	: mTime( time ), mVertexFormat( format ), mVertexCount( count ), mBufferOwner( _true ), mKeyframeBuffer( _null )
{
	mVertexSize = ModelHelper::GetVertexSize( format );

	if ( ( format & IVertexBuffer::_FORMAT_POSITION ) == 0 )
	{
		assert( mVertexSize >= sizeof( Vector3 ) );
		mVertexSize -= sizeof( Vector3 );
	}

	mKeyframeLength = mVertexSize * mVertexCount;

	if ( mKeyframeLength > 0 )
		mKeyframeBuffer = new _byte[ mKeyframeLength ];
}

MeshAnimaKeyframe::MeshAnimaKeyframe( MeshAnimaKeyframe* frame ) : mTime( frame->mTime ),
	mVertexFormat( frame->mVertexFormat ), mVertexSize( frame->mVertexSize ), mVertexCount( frame->mVertexCount ),
	mBufferOwner( _false ), mKeyframeBuffer( frame->mKeyframeBuffer ), mKeyframeLength( frame->mKeyframeLength )
{
}

_void MeshAnimaKeyframe::ChangeResObject( )
{
	if ( mBufferOwner )
		return;

	if ( mKeyframeLength > 0 )
	{
		_byte* buffer = mKeyframeBuffer;
		mKeyframeBuffer = new _byte[ mKeyframeLength ];
		Memory::MemCpy( mKeyframeBuffer, buffer, mKeyframeLength );
	}

	mBufferOwner = _true;
}

_byte* MeshAnimaKeyframe::GetVertexBufferToWrite( _dword index, _dword field )
{
	if ( index >= mVertexCount )
		return _null;

	if ( ( mVertexFormat & field ) == 0 )
		return _null;

	ChangeResObject( );

	return mKeyframeBuffer + index * mVertexSize + ModelHelper::GetVertexFieldOffset( mVertexFormat, field );
}

const _byte* MeshAnimaKeyframe::GetVertexBufferToRead( _dword index, _dword field ) const
{
	if ( index >= mVertexCount )
		return _null;

	if ( ( mVertexFormat & field ) == 0 )
		return _null;

	return mKeyframeBuffer + index * mVertexSize + ModelHelper::GetVertexFieldOffset( mVertexFormat, field );
}