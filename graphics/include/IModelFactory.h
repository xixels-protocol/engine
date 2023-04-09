#pragma once

namespace Xixels
{

class IModelFactory
{
public:
	virtual IMesh*				CreateMesh( ) = 0;
	virtual IMesh*				CreateMesh( StringPtr resname ) = 0;
	virtual IMesh*				CreateMesh( StringPtr mshname, const Geometry& geo, const Material& mtl = Material::cNull, IMesh* mesh = _null ) = 0;
	virtual IMesh*				CloneMesh( IMesh* mesh, _bool ref = _true ) = 0;
	virtual _void				ReleaseMesh( IMesh*& mesh ) = 0;
	virtual _bool				SaveMesh( IMesh* mesh, BinFile& datafile ) = 0;

	virtual ISubMesh*			CreateSubMesh( ISubMesh* submesh ) = 0;
	virtual _void				ReleaseSubMesh( ISubMesh*& submesh ) = 0;

	virtual IMeshMaterial*		CreateMeshMaterial( ) = 0;
	virtual IMeshMaterial*		CreateMeshMaterial( StringPtr resname ) = 0;
	virtual IMeshMaterial*		CloneMeshMaterial( IMeshMaterial* mtl, _bool ref = _true ) = 0;
	virtual _void				ReleaseMeshMaterial( IMeshMaterial*& mtl ) = 0;
	virtual _void				SaveMeshMaterial( IMeshMaterial* mtl, BinFile& datafile ) = 0;

	virtual IMeshAnima*			CreateMeshAnima( ) = 0;
	virtual IMeshAnima*			CreateMeshAnima( StringPtr resname ) = 0;
	virtual IMeshAnima*			CloneMeshAnima( IMeshAnima* anima, _bool ref = _true ) = 0;
	virtual _void				ReleaseMeshAnima( IMeshAnima*& anima ) = 0;
	virtual _void				SaveMeshAnima( IMeshAnima* anima, BinFile& datafile ) = 0;

	virtual ISkeleton*			CreateSkeleton( ) = 0;
	virtual ISkeleton*			CreateSkeleton( StringPtr resname ) = 0;
	virtual ISkeleton*			CloneSkeleton( ISkeleton* skeleton, _bool ref = _true ) = 0;
	virtual _void				ReleaseSkeleton( ISkeleton*& skeleton ) = 0;
	virtual _void				SaveSkeleton( ISkeleton* skeleton, BinFile& datafile ) = 0;

	virtual ISkeletonAnima*		CreateSkeletonAnima( ) = 0;
	virtual ISkeletonAnima*		CreateSkeletonAnima( StringPtr resname ) = 0;
	virtual ISkeletonAnima*		CloneSkeletonAnima( ISkeletonAnima* anima, _bool ref = _true ) = 0;
	virtual _void				ReleaseSkeletonAnima( ISkeletonAnima*& anima ) = 0;
	virtual _void				SaveSkeletonAnima( ISkeletonAnima* anima, BinFile& datafile ) = 0;

	virtual IAnimation*			CloneAnimation( IAnimation* anima, _bool ref = _true ) = 0;
	virtual _void				ReleaseAnimation( IAnimation*& anima ) = 0;

	virtual IScene*				CreateScene( const Region& region, _dword depth ) = 0;
	virtual IScene*				CreateScene( _dword tx, _dword ty, _float scale ) = 0;
	virtual IScene*				CreateScene( StringPtr resname, IScene::OnCreateNode funcptr1 = _null, _ptr userdata = 0 ) = 0;
	virtual IScene*				CloneScene( IScene* scene, _bool ref = _true ) = 0;
	virtual _void				ReleaseScene( IScene*& scene ) = 0;
	virtual _void				SaveScene( IScene* scene, BinFile& datafile ) = 0;
};

};