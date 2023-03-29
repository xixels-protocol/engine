#pragma once

namespace Xixels
{

class IIndexBuffer
{
public:
	// Get buffer type.
	virtual _dword	GetType( ) const = 0;
	// Get length of buffer in bytes.
	virtual _dword	GetLength( ) const = 0;
	// Get index size.
	virtual _dword	GetIndexSize( ) const = 0;

	// Set user data to buffer.
	virtual _void	SetUserData( _ptr userdata ) = 0;
	// Get user data from buffer.
	virtual _ptr	GetUserData( ) const = 0;

	// Change buffer of index buffer, maybe change size of index buffer.
	virtual _void	ChangeIndexBuffer( _void* buffer, _dword length, _dword isize ) = 0;

	// Lock index buffer.
	virtual _void*	Lock( _dword offset, _dword length, _dword flag = 0 ) = 0;
	// Unlock index buffer.
	virtual _void	Unlock( ) = 0;

	// Copy data from buffer.
	virtual _bool	Copy( _dword offset, _void* buffer, _dword length ) = 0;
	// Fill data into buffer.
	virtual _bool	Fill( _dword offset, const _void* buffer, _dword length ) = 0;
};

};