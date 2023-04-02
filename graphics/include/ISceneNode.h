#pragma once

namespace Xixels
{

class ISceneNode : public IResource
{
public:
	virtual _void			SetTransform( const Matrix4& mat ) = 0;
	virtual const Matrix4&	GetTransform( ) const = 0;

	// Append mesh into node, includes all geometry in mesh.
	virtual Array< ISceneGeo* > AddMesh( IMesh* mesh, const Matrix4& mat = Matrix4::cIdentity ) = 0;
	// Append sub mesh into node.
	virtual ISceneGeo*		AddSubMesh( ISubMesh* submesh, ISkeleton* skl = _null, const Matrix4& mat = Matrix4::cIdentity ) = 0;
	// Append skeleton into node.
	virtual _void			AddSkeleton( ISkeleton* skl, const Matrix4& mat = Matrix4::cIdentity ) = 0;
	// Append geometry into node.
	virtual ISceneGeo*		AddGeometry( const Geometry& geo, ISkeleton* skl = _null, StringPtr name = L"", const Matrix4& mat = Matrix4::cIdentity ) = 0;
	// Remove geometry from node.
	virtual _void			DelGeometry( _dword geoindex ) = 0;
	// Clear all geometry from node.
	virtual _void			ClearGeometry( ) = 0;

	// Set skeleton resource of node.
	virtual	_void			SetSkeleton( StringPtr resname ) = 0;
	// Get skeleton resource of node.
	virtual	StringPtr		GetSkeleton( ) const = 0;

	// Set animation resource of node.
	virtual	_void			SetAnimation( StringPtr resname ) = 0;
	// Get animation resource of node.
	virtual	StringPtr		GetAnimation( ) const = 0;

	// Set visible flag of node.
	virtual	_void			SetVisible( _bool visible ) = 0;
	// Get visible flag of node.
	virtual	_bool			GetVisible( ) const = 0;

	// Set pick flag of node.
	virtual	_void			SetPickFlag( _dword pickflag ) = 0;
	// Get pick flag of node.
	virtual	_dword			GetPickFlag( ) const = 0;

	// Set render flag of node.
	virtual _void			SetRenderFlag( _dword flag ) = 0;
	// Get render flag of node.
	virtual _dword			GetRenderFlag( ) const = 0;

	virtual _void			SetLoadLevel( _dword level ) = 0;
	virtual _dword			GetLoadLevel( ) const = 0;

	// Put node into scene, then it can be picked and clipped.
	virtual _void			PutIntoScene( ) = 0;
	// Remove node from scene.
	virtual _void			RemoveFromScene( ) = 0;

	// Get boundbox of node.
	virtual const AxisAlignedBox& GetBoundBox( ) const = 0;
};

};