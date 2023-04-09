namespace Xixels
{

class ITechniqueBuilder
{
public:
	typedef Pair< const _char*, _dword > ConstMap;

public:
	virtual IShaderConst*		PrepareVertexShaderConst( ) = 0;
	virtual IShaderConst*		PreparePixelShaderConst( ) = 0;

	virtual _void				SetPixelShaderConst( IShaderConst* sc ) = 0;

	virtual const ShaderParam&	GetShaderParam( ) const = 0;
	virtual _void				SetShaderParam( const ShaderParam& param ) = 0;

	virtual IShaderConst*		GetVertexShaderConst( ) const = 0;
	virtual IShaderConst*		GetPixelShaderConst( ) const = 0;

	virtual SortArray< ConstMap, _qword >	GetUniformReflections( ) const = 0;

	virtual _void				Reset( ) = 0;
};

};