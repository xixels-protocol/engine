#pragma once

namespace Xixels
{

class IMesh : public IResource
{
public:
	// Create an empty sub mesh.
	virtual ISubMesh*	CreateSubMesh( StringPtr name ) = 0;
	// Create a sub mesh with geometry & material.
	virtual ISubMesh*	CreateSubMesh( StringPtr name, const Geometry& geo, const Material& mtl = Material::cNull ) = 0;
	// Create a sub mesh with geometry & material.
	virtual ISubMesh*	CreateSubMesh( StringPtr name, const Geometry& geo, IMeshMaterial* mtl = _null ) = 0;
	// Create a sub mesh by clone existing sub mesh.
	virtual ISubMesh*	CreateSubMesh( ISubMesh* submesh ) = 0;
	// Release a sub mesh.
	virtual _void		ReleaseSubMesh( ISubMesh*& submesh ) = 0;
	// Clear all sub mesh.
	virtual _void		ClearSubMesh( ) = 0;

	// Get count of sub mesh.
	virtual _dword		GetSubMeshCount( ) const = 0;
	// Get sub mesh by index.
	virtual ISubMesh*	GetSubMesh( _dword index ) const = 0;
	// Get sub mesh by name.
	virtual ISubMesh*	GetSubMesh( StringPtr name ) const = 0;

	virtual _void		UsingMesh( _dword priority ) = 0;
	// Update mesh according to skeleton ( skinning ).
	virtual _void		Update( ISkeleton* skeleton, _dword elapse ) = 0;

};