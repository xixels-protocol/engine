#pragma once

namespace Xixels
{

class IScene : public IResource
{
public:
	// Create node into scene.
	virtual ISceneNode*		CreateNode( StringPtr name = L"", const Matrix4& mat = Matrix4::cIdentity ) = 0;	
	// Remove node from scene.
	virtual _void			RemoveNode( ISceneNode*& node ) = 0;
	// Clear all node from scene.
	virtual _void			ClearNode( ) = 0;

	// Get count of node.
	virtual _dword			GetNodeCount( ) const = 0;
	// Get node by index.
	virtual ISceneNode*		GetNode( _dword index ) const = 0;

	// Get count of point lightnode.
	virtual _dword			GetPointLightNodeCount( ) const = 0;
	// Get point lightnode by index.
	virtual ILightNode*		GetPointLightNode( _dword index ) const = 0;

	// Set sky box mesh of scene.
	virtual	_void			SetSkyBox( IMesh* skybox ) = 0;
	// Get sky box mesh of scene.
	virtual IMesh*			GetSkyBox( ) const = 0;

	// Set scaling of scene, affects all nodes, and graphics data.
	virtual _void			SetScaling( _float scaling ) = 0;
	// Get scaling of scene.
	virtual _float			GetScaling( ) const = 0;

	// Pick scene by vector.
	virtual _bool			Pick( const Vector3& point, _dword pickflag = -1 ) = 0;
	// Pick scene by ray.
	virtual _bool			Pick( const Ray& ray, _float& dist, ISceneGeo*& pickgeo, _dword& faceindex, Vector3& normal, _dword pickflag = -1, _bool pickaabb = _false ) = 0;
	// Pick scene by boundbox.
	virtual _bool			Pick( const AxisAlignedBox& boundbox, _dword pickflag = -1 ) = 0;
	// Pick scene by frustum.
	virtual _bool			Pick( const Frustum& frustum, _float loddistance = Math::cMaxFloat, _dword pickflag = -1, _dword frametoken = 0 ) = 0;

	// Put point light into scene.
	virtual ILightNode*		PutPointLightIntoScene( const Light* l ) = 0;
	// Remove point light from scene.
	virtual _void			RemovePointLightFromScene( ILightNode*& lnode ) = 0;

	// Get count of picked geometry.
	virtual _dword			GetPickedGeometryCount( ) const = 0;
	// Get picked geometry by index.
	virtual const Geometry&	GetPickedGeometry( _dword geoindex ) const = 0;
	// Get picked skeleton by index.
	virtual ISkeleton*		GetPickedSkeleton( _dword geoindex ) const = 0;

	virtual _void			UsingScene( _dword priority ) = 0;

	// Get all of nodes.
	virtual const Array< ISceneNode* >& GetNodes( ) const = 0;

	// Get picked nodes.
	virtual const Array< ISceneNode* >& GetPickedNodes( ) const = 0;
	
	virtual const Array< ISceneNode* >& GetSkeletalNodes( ) const = 0;
};

};