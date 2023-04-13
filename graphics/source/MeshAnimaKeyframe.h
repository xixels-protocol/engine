#pragma once

namespace Xixels
{

class MeshAnimaKeyframe : public IMeshAnimaKeyframe
{
public:
	_float	mTime;
	_dword	mVertexFormat;
	_dword	mVertexSize;
	_dword	mVertexCount;

	_bool	mBufferOwner;
	_dword	mKeyframeLength;
	_byte*	mKeyframeBuffer;

public:
	MeshAnimaKeyframe( _float time, _dword format, _dword count );
	MeshAnimaKeyframe( MeshAnimaKeyframe* frame );

	inline ~MeshAnimaKeyframe( )
		{ if ( mBufferOwner ) delete[] mKeyframeBuffer; }

	inline operator _float ( ) const
		{ return mTime; }

	_void			ChangeResObject( );

	_byte*			GetVertexBufferToWrite( _dword index, _dword field );
	const _byte*	GetVertexBufferToRead( _dword index, _dword field ) const;

public:
	virtual _float GetTime( ) const
		{ return mTime; }
	virtual _dword GetVertexFormat( ) const
		{ return mVertexFormat; }
	virtual _dword GetVertexCount( ) const
		{ return mVertexCount; }

	virtual _dword GetKeyframeLength( ) const
		{ return mKeyframeLength; }
	virtual const _byte* GetKeyframeBuffer( ) const
		{ return mKeyframeBuffer; }

	virtual _void			SetVertexPosition( _dword index, const Vector3& pos );
	virtual const Vector3&	GetVertexPosition( _dword index ) const;

	virtual _void			SetVertexNormal( _dword index, const Vector3& nor );
	virtual const Vector3&	GetVertexNormal( _dword index ) const;

	virtual _void			SetVertexDiffuse( _dword index, _dword col );
	virtual _dword			GetVertexDiffuse( _dword index ) const;

	virtual _void			SetVertexTexcoord( _dword index, _dword tex, const Vector2& texc );
	virtual const Vector2&	GetVertexTexcoord( _dword index, _dword tex ) const;

	virtual _byte*			LockKeyframeBuffer( );
};

};