#pragma once

namespace Xixels
{

public:

	enum _FORMAT_FLAG
	{
		_FORMAT_START			= 0x00000001,
		_FORMAT_POSITION		= 0x00000001,
		_FORMAT_NORMAL			= 0x00000002,
		_FORMAT_TANGENT			= 0x00000004,
		_FORMAT_DIFFUSE			= 0x00000008,
		_FORMAT_TEXCOORD1		= 0x00000010,
		_FORMAT_TEXCOORD2		= 0x00000020,
		_FORMAT_TEXCOORD3		= 0x00000040,
		_FORMAT_TEXCOORD4		= 0x00000080,
		_FORMAT_INFLUENCE		= 0x00000100,
		_FORMAT_BONEBLEND		= 0x00000200,
		_FORMAT_END				= 0x00000200,
	};

public:
	// Get buffer type.
	virtual _dword	GetType( ) const = 0;
	// Get length of buffer in bytes.
	virtual _dword	GetLength( ) const = 0;
	// Get vertex size of vertex buffer.
	virtual _dword	GetVertexSize( ) const = 0;
	// Get vertex format of vertex buffer.
	virtual _dword	GetVertexFormat( ) const = 0;

	// Set skin count of vertex buffer ( used for gpu skinning ).
	virtual _void	SetSkinCount( _dword skincount ) = 0;
	// Get skin count of vertex buffer.
	virtual _dword	GetSkinCount( ) const = 0;

	// Set frame token of vertex buffer ( used for clipping ).
	virtual _void	SetFrameToken( _dword token ) = 0;
	// Get frame token of vertex buffer.
	virtual _dword	GetFrameToken( ) const = 0;

	// Set user data to buffer.
	virtual _void	SetUserData( _ptr userdata ) = 0;
	// Get user data from buffer.
	virtual _ptr	GetUserData( ) const = 0;

	// Change vertex format of vertex buffer, maybe change size of vertex buffer.
	virtual _void	ChangeVertexFormat( _dword format ) = 0;
	// Change buffer of vertex buffer, maybe change size of vertex buffer.
	virtual	_void	ChangeVertexBuffer( _void* buffer, _dword length, _dword format ) = 0;

	// Lock vertex buffer.
	virtual _void*	Lock( _dword offset, _dword length, _dword flag ) = 0;
	// Unlock vertex buffer.
	virtual _void	Unlock( ) = 0;

	// Copy data from buffer.
	virtual _bool	Copy( _dword offset, _void* buffer, _dword length ) = 0;
	// Fill data into buffer.
	virtual _bool	Fill( _dword offset, const _void* buffer, _dword length ) = 0;

	// Set bound box to vertex buffer.
	virtual _void	SetBoundBox( const AxisAlignedBox& boundbox ) = 0;
	// Get bound box from vertex buffer.
	virtual const AxisAlignedBox&	GetBoundBox( ) const = 0;

};

};