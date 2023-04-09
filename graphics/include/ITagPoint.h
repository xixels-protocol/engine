#pragma once

namespace Xixels
{

class ISkeleton;
class IBone;

class ITagPoint
{
public:
	enum _IGNORE_FLAG
	{
		_IGNORE_TRANSLATION	= 0x01,
		_IGNORE_ROTATION	= 0x02,
		_IGNORE_SCALING		= 0x04,
		_IGNORE_PARENT		= 0x08,
		_IGNORE_WORLD		= 0x10,
	};

public:
	virtual _void		SetIgnoreFlag( _dword flag ) = 0;
	virtual _dword		GetIgnoreFlag( ) const = 0;

	virtual _void		SetParent( ITagPoint* tp ) = 0;
	virtual ITagPoint*	GetParent( ) const = 0;

	virtual _void		SetTransform( const Matrix4& mat ) = 0;
	virtual Matrix4&	GetTransform( _bool bind = _true ) = 0;

	virtual Matrix4		BuildTransform( ) = 0;
	virtual Matrix4		BuildTransform( const Matrix4& wmat ) = 0;
	virtual Matrix4		BuildTransform( const Matrix4& wmat, const Matrix4& pmat ) = 0;

	virtual _bool		IsIgnoreWorld( ) const = 0;
	virtual _void		IgnoreTransform( Matrix4& mat ) = 0;

	virtual _void		BindSkeleton( ISkeleton* skeleton, _dword boneid ) = 0;
	virtual _void		UnbindSkeleton( ) = 0;
	virtual ISkeleton*	GetBindSkeleton( ) const = 0;
	virtual IBone*		GetBindBone( ) const = 0;

	virtual _void		BindGeometry( const Geometry& geo ) = 0;
	virtual _void		UnbindGeometry( ) = 0;
};

};