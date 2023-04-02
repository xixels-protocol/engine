#pragma once

namespace Xixels
{

class ISubMesh : public IResource
{
public:
	// Get geometry of sub mesh.
	virtual Geometry&		GetGeometry( ) = 0;

	// Set material of sub mesh.
	virtual _void			SetMaterial( IMeshMaterial* mtl ) = 0;
	// Get material of sub mesh.
	virtual IMeshMaterial*	GetMaterial( ) = 0;

	// Update mesh according to skeleton ( skinning ).
	virtual _void			Update( ISkeleton* skeleton, _dword elpase ) = 0;

	virtual _void			UsingSubMesh( _dword priority ) = 0;

	// Get the bound box of sub mesh.
	virtual const AxisAlignedBox& GetBoundBox( _dword sameboneid = -1 ) const = 0;
};

};