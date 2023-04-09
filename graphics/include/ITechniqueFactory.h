namespace Xixels
{

struct ShaderConstMap;
struct AsyncTextureData;
class Shader;

struct RenderPipeState
{
	_bool	rgbblend;
	_dword	rgbFunc;
	_dword	rgbSrcFactor;
	_dword	rgbDstFactor;
	_bool	rgbwrite;

	_bool	alphablend;
	_dword	alphaFunc;
	_dword	alphaSrcFactor;
	_dword	alphaDstFactor;
	_bool	alphawrite;

	_dword	colorPixelFormat[ IRenderSet::_MRT_COUNT ];
	_dword	depthPixelFormat;
	_dword	stencilPixelFormat;
	_dword	sampleCount;
	_dword	attachCount;

	_void*	vertexFunc;
	_void*	pixelFunc;
	_void*	vertexDecl;

	_void*	vertexMethod;
	_void*	pixelMethod;

	_void*	pipeState;
	_void*	state;

	_dword	status;

	inline RenderPipeState( )
		: rgbblend( _false ), rgbFunc( 0 ), rgbSrcFactor( 0 ), rgbDstFactor( 0 ), alphablend( _false ), alphaFunc( 0 ),
			alphaSrcFactor( 0 ),alphaDstFactor( 0 ), rgbwrite( _true ), alphawrite( _true ), depthPixelFormat( 0 ), stencilPixelFormat( 0 ),
			vertexFunc( _null ), pixelFunc( _null ), vertexDecl( _null ), vertexMethod( _null ), pixelMethod( _null ), sampleCount( 1 ), attachCount( 1 ), pipeState( _null ), state( _null ), status( 0 )
	{
		for ( _dword i = 0 ; i < IRenderSet::_MRT_COUNT; i ++ )
			colorPixelFormat[i] = 0;
	}

	inline _bool SameAs( const RenderPipeState* state ) const
		{
			return rgbblend == state->rgbblend &&
				alphablend == state->alphablend &&
				rgbFunc == state->rgbFunc &&
				rgbSrcFactor == state->rgbSrcFactor &&
				rgbDstFactor == state->rgbDstFactor &&
				alphaFunc == state->alphaFunc &&
				alphaSrcFactor == state->alphaSrcFactor &&
				alphaDstFactor == state->alphaDstFactor &&
				rgbwrite == state->rgbwrite &&
				alphawrite == state->alphawrite &&
				colorPixelFormat[0] == state->colorPixelFormat[0] &&
				colorPixelFormat[1] == state->colorPixelFormat[1] &&
				colorPixelFormat[2] == state->colorPixelFormat[2] &&
				colorPixelFormat[3] == state->colorPixelFormat[3] &&
				depthPixelFormat == state->depthPixelFormat &&
				stencilPixelFormat == state->stencilPixelFormat &&
				vertexFunc == state->vertexFunc &&
				pixelFunc == state->pixelFunc &&
				vertexDecl == state->vertexDecl &&
				vertexMethod == state->vertexMethod &&
				pixelMethod == state->pixelMethod &&
				sampleCount == state->sampleCount &&
				attachCount == state->attachCount;
		}
};

class ITechniqueFactory
{
public:
	enum _SHADER_RESULT
	{
		_RESULT_OK			= 0,
		_RESULT_FAILED		= 1,
		_RESULT_PROCESSING	= 2,
	};

	typedef Shader* (*CreateShader)( const ShaderParam& param, _dword format, const PrimaryKey& key, _bool async );

public:
	virtual ITechniqueBuilder&		GetTechniqueBuilder( ) const = 0;

	virtual _dword					GetShaderCompilerStat( ) const = 0;

	virtual IRenderSet*				CreateRenderSet( ) = 0;
	virtual IRenderSet*				CreateRenderSet( ITexture* rendertarget, ITexture* depthstencil ) = 0;
	virtual IRenderSet*				CreateRenderSet( ITexture* rt1, ITexture* rt2, ITexture* rt3, ITexture* rt4, ITexture* depthstencil ) = 0;
	virtual IRenderSet*				CloneRenderSet( IRenderSet* rs, _bool ref = _true ) = 0;
	virtual _void					ReleaseRenderSet( IRenderSet*& rs ) = 0;
	virtual _void					ClearRenderSetResource( ITexture* tex ) = 0;

	virtual IShaderConst*			CreateShaderConst( ) = 0;
	virtual IShaderConst*			CloneShaderConst( IShaderConst* sc, _bool ref = _true ) = 0;
	virtual _void					ReleaseShaderConst( IShaderConst*& sc ) = 0;

	virtual _void					ReleaseShaderReflection( IShaderReflection*& isr ) = 0;

	virtual	IPostProcess*			CreatePostProcess( _dword mode = 0 ) = 0;
	virtual	_void					ReleasePostProcess( IPostProcess*& pp ) = 0;

	virtual IRenderMethod*			CreateRenderMethod( ) = 0;
	virtual IRenderMethod*			GetRenderMethod_Common( ) = 0;
	virtual IRenderMethod*			GetRenderMethod_Wireframe( _bool nocull = _false ) = 0;
	virtual IRenderMethod*			GetRenderMethod_Overlay( ) = 0;
	virtual IRenderMethod*			GetRenderMethod_BackFace( ) = 0;
	virtual IRenderMethod*			GetRenderMethod_NoCull( ) = 0;
	virtual IRenderMethod*			GetRenderMethod_NoDepth( ) = 0;
	virtual IRenderMethod*			CloneRenderMethod( IRenderMethod* method, _bool ref = _true ) = 0;
	virtual _void					ReleaseRenderMethod( IRenderMethod*& method ) = 0;

	virtual IStencilMethod*			CreateStencilMethod( ) = 0;
	virtual IStencilMethod*			GetStencilMethod_IncPass( ) = 0;
	virtual IStencilMethod*			GetStencilMethod_IncFail( ) = 0;
	virtual IStencilMethod*			GetStencilMethod_DecPass( ) = 0;
	virtual IStencilMethod*			GetStencilMethod_DecFail( ) = 0;
	virtual IStencilMethod*			GetStencilMethod_ClearPass( ) = 0;
	virtual IStencilMethod*			GetStencilMethod_ClearFail( ) = 0;
	virtual IStencilMethod*			GetStencilMethod_MaskPass( ) = 0;
	virtual IStencilMethod*			GetStencilMethod_MaskNoPass( ) = 0;
	virtual IStencilMethod*			GetStencilMethod_IncMaskPass( ) = 0;
	virtual IStencilMethod*			GetStencilMethod_IncMaskNoPass( )= 0;
	virtual IStencilMethod*			GetStencilMethod_ReplacePass( ) = 0;
	virtual IStencilMethod*			CloneStencilMethod( IStencilMethod* method, _bool ref = _true ) = 0;
	virtual _void					ReleaseStencilMethod( IStencilMethod*& method ) = 0;

	virtual IBlendMethod*			CreateBlendMethod( ) = 0;
	virtual IBlendMethod*			GetBlendMethod_None( ) = 0;
	virtual IBlendMethod*			GetBlendMethod_Copy( ) = 0;
	virtual IBlendMethod*			GetBlendMethod_Decal( ) = 0;
	virtual IBlendMethod*			GetBlendMethod_Alpha( ) = 0;
	virtual IBlendMethod*			GetBlendMethod_Additive( _bool noalpha = _false ) = 0;
	virtual IBlendMethod*			CloneBlendMethod( IBlendMethod* method, _bool ref = _true ) = 0;
	virtual _void					ReleaseBlendMethod( IBlendMethod*& method ) = 0;

	virtual ISamplerMethod*			CreateSamplerMethod( ) = 0;
	virtual ISamplerMethod*			GetSamplerMethod_Point( ) = 0;
	virtual ISamplerMethod*			GetSamplerMethod_Clamp( ) = 0;
	virtual ISamplerMethod*			GetSamplerMethod_NoMip( ) = 0;
	virtual ISamplerMethod*			GetSamplerMethod_AlphaLayer( ) = 0;
	virtual ISamplerMethod*			CloneSamplerMethod( ISamplerMethod* method, _bool ref = _true ) = 0;
	virtual _void					ReleaseSamplerMethod( ISamplerMethod*& method ) = 0;

	virtual IVertexMethod*			CreateVertexMethod( _bool isdef = _true ) = 0;
	virtual IVertexMethod*			CreateVertexMethod( const _chara* code, const ShaderCodeConfig& cfg ) = 0;
	virtual IVertexMethod*			CloneVertexMethod( IVertexMethod* method, _bool ref = _true ) = 0;
	virtual _void					ReleaseVertexMethod( IVertexMethod*& method ) = 0;

	virtual IPixelMethod*			CreatePixelMethod( _bool isdef = _true ) = 0;
	virtual IPixelMethod*			CreatePixelMethod( const _chara* code, const ShaderCodeConfig& cfg ) = 0;
	virtual IPixelMethod*			ClonePixelMethod( IPixelMethod* method, _bool ref = _true ) = 0;
	virtual _void					ReleasePixelMethod( IPixelMethod*& method ) = 0;

	virtual _void					EnableAsyncCompile( _bool enable ) = 0;
	virtual _bool					IsAsyncCompileEnabled( ) const = 0;

	virtual _bool					BuildVertexShader( IVertexMethod* method, StringPtr n, const PrimaryKey& key, const _chara* code, const ShaderContext* sc = _null ) = 0;
	virtual _bool					BuildPixelShader( IPixelMethod* method, StringPtr n, const PrimaryKey& key, const _chara* code, const ShaderContext* sc = _null ) = 0;

	virtual _dword					LinkShader( IVertexMethod* vm, IPixelMethod* pm, _bool instancing, _bool async ) = 0;
};

};
