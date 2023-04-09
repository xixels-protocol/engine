#pragma once

namespace Xixels
{

class IMeshMaterial : public IResource
{
public:
	enum _MTL_TEXTURE_FLAG
	{
		_DIFFUSE			= 0,
		_NORMAL				= 1,
		_EMISSIVE			= 2,
		_METALLIC			= 3,
		_ROUGHNESS			= 4,
		_SPECULAR			= 5,
		_AO					= 6,
		_CUSTOM				= 7,
		_MAX_TEXTURE_COUNT	= 8,
	};

public:
	virtual _void				SetMaterial( const Material& mtl ) = 0;
	virtual Material&			GetMaterial( ) = 0;

	virtual _void				SetRenderFlag( _dword flag ) = 0;
	virtual _dword				GetRenderFlag( ) const = 0;

	virtual _void				SetTexture( _dword index, StringPtr tex ) = 0;
	virtual _void				SetTexture( _dword index, ITexture* tex ) = 0;
	virtual ITexture*			GetTexture( _dword index ) const = 0;

	virtual Matrix3				GetUVTransform( ) const = 0;
	virtual _void				SetUVTransform( const Matrix3& transform ) = 0;

	virtual _void				SetParamFlag( _dword flag ) = 0;
	virtual _dword				GetParamFlag( ) const = 0;

	virtual _void				SetDiffuseSeqMapRow( _dword row ) = 0;
	virtual _dword				GetDiffuseSeqMapRow( ) const = 0;

	virtual _void				UsingMaterial( _dword priority ) = 0;
	virtual _void				Update( _dword elapse ) = 0;
	virtual _void				Reset( ) = 0;

	virtual _void				UseMaterial( Geometry& geo, Vector4 fresnelmask = Vector4::cOrigin, Vector3 boundboxpos = Vector3::cOrigin, _float uvscale = 1.0f ) = 0;
	virtual _void				UseMaterial( Vector2& lt, Vector2& rt, Vector2& rb, Vector2& lb ) = 0;
	
	virtual _dword				IsEqual( IMeshMaterial* material ) const = 0;
};

};