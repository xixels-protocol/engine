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

_void MeshAnimaKeyframe::SetVertexPosition( _dword index, const Vector3& pos )
{
	_byte* buffer = GetVertexBufferToWrite( index, IVertexBuffer::_FORMAT_POSITION );
	if ( buffer != _null )
		*( (Vector3*) buffer ) = pos;
}

const Vector3& MeshAnimaKeyframe::GetVertexPosition( _dword index ) const
{
	const _byte* buffer = GetVertexBufferToRead( index, IVertexBuffer::_FORMAT_POSITION );
	return buffer != _null ? *( (const Vector3*) buffer ) : Vector3::cOrigin;
}

_void MeshAnimaKeyframe::SetVertexNormal( _dword index, const Vector3& nor )
{
	_byte* buffer = GetVertexBufferToWrite( index, IVertexBuffer::_FORMAT_NORMAL );
	if ( buffer != _null )
		*( (Vector3*) buffer ) = nor;
}

const Vector3& MeshAnimaKeyframe::GetVertexNormal( _dword index ) const
{
	const _byte* buffer = GetVertexBufferToRead( index, IVertexBuffer::_FORMAT_NORMAL );
	return buffer != _null ? *( (const Vector3*) buffer ) : Vector3::cOrigin;
}

_void MeshAnimaKeyframe::SetVertexDiffuse( _dword index, _dword col )
{
	_byte* buffer = GetVertexBufferToWrite( index, IVertexBuffer::_FORMAT_DIFFUSE );
	if ( buffer != _null )
		*( (_dword*) buffer ) = col;
}

_dword MeshAnimaKeyframe::GetVertexDiffuse( _dword index ) const
{
	const _byte* buffer = GetVertexBufferToRead( index, IVertexBuffer::_FORMAT_DIFFUSE );
	return buffer != _null ? *( (const _dword*) buffer ) : 0;
}

_void MeshAnimaKeyframe::SetVertexTexcoord( _dword index, _dword tex, const Vector2& texc )
{
	_dword field = 0;
	if ( tex == 1 )
		field = IVertexBuffer::_FORMAT_TEXCOORD1;
	else if ( tex == 2 )
		field = IVertexBuffer::_FORMAT_TEXCOORD2;
	else if ( tex == 3 )
		field = IVertexBuffer::_FORMAT_TEXCOORD3;
	else if ( tex == 4 )
		field = IVertexBuffer::_FORMAT_TEXCOORD4;

	_byte* buffer = GetVertexBufferToWrite( index, field );
	if ( buffer != _null )
		*( (Vector2*) buffer ) = texc;
}

const Vector2& MeshAnimaKeyframe::GetVertexTexcoord( _dword index, _dword tex ) const
{
	_dword field = 0;
	if ( tex == 1 )
		field = IVertexBuffer::_FORMAT_TEXCOORD1;
	else if ( tex == 2 )
		field = IVertexBuffer::_FORMAT_TEXCOORD2;
	else if ( tex == 3 )
		field = IVertexBuffer::_FORMAT_TEXCOORD3;
	else if ( tex == 4 )
		field = IVertexBuffer::_FORMAT_TEXCOORD4;

	const _byte* buffer = GetVertexBufferToRead( index, field );
	return buffer != _null ? *( (const Vector2*) buffer ) : Vector2::cOrigin;
}

_byte* MeshAnimaKeyframe::LockKeyframeBuffer( )
{
	ChangeResObject( );

	return mKeyframeBuffer;
}