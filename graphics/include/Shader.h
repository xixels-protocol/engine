#pragma once

namespace Xixels
{

class FShaderType
{
public:
	typedef _dword (*onFormatMask) ( _dword format );

	enum _SHADER_TYPE
	{
		_VERTEX	= 0,
		_PIXEL	= 1,
	};

private:
	String			mName;
	_SHADER_TYPE	mType;
	onFormatMask	mOnFormatMask;

public:
	FShaderType( StringPtr name, _SHADER_TYPE type, onFormatMask mask = _null )
		: mName( name ), mType( type ), mOnFormatMask( mask ) { }

	StringPtr GetName( ) const
		{ return mName; }

	_SHADER_TYPE GetType( ) const
		{ return mType; }

	onFormatMask GetFormatMaskFunc( ) const
		{ return mOnFormatMask; }

	virtual _bool IsGlobalShader( ) const
		{ return _false; }
};

class MaterialShaderType : public FShaderType
{
public:
	MaterialShaderType( StringPtr name, _SHADER_TYPE type, onFormatMask mask = _null )
		: FShaderType( name, type, mask ) { }
};

class GlobalShaderType : public FShaderType
{
public:
	GlobalShaderType( StringPtr name, _SHADER_TYPE type, onFormatMask mask = _null )
		: FShaderType( name, type, mask ) { }

	virtual _bool IsGlobalShader( ) const
		{ return _true; }
};

class Shader
{
private:
	_void*			mResObject;
	FShaderType*	mShaderType;

public:
	Shader( IVertexMethod* vm, FShaderType* type )
		: mResObject( vm ), mShaderType( type ) { }
	Shader( IPixelMethod* pm, FShaderType* type )
		: mResObject( pm ), mShaderType( type ) { }

	IVertexMethod* GetVertexMethod( ) const
		{ assert( mShaderType->GetType( ) == FShaderType::_VERTEX ); return (IVertexMethod*) mResObject; }
	IPixelMethod* GetPixelMethod( ) const
		{ assert( mShaderType->GetType( ) == FShaderType::_PIXEL ); return (IPixelMethod*) mResObject; }
	inline const FShaderType* GetShaderType( ) const 
		{ return mShaderType; }

	~Shader( );
};

struct ShaderConstMap
{
	_dword			mIndex;
	const _chara*	mName;

	ShaderConstMap( )
		: mIndex( 0 ), mName( _null ) { }
	ShaderConstMap( _dword index, const _chara* str )
		: mIndex( index ), mName( str ) { }
};

struct PrimaryKey
{
	FShaderType*	mType;
	ParameterKey	mParamKey;

	PrimaryKey( )
		: mType( _null ) { }
	PrimaryKey( FShaderType* type, const ParameterKey& key )
		: mType( type ), mParamKey( key ) { }

	_bool operator < ( const PrimaryKey& rhs ) const
	{
		if ( (_void*) mType == (_void*) rhs.mType )
			return mParamKey < rhs.mParamKey;

		return (_void*) mType < (_void*) rhs.mType;
	}

	_bool operator > ( const PrimaryKey& rhs ) const
		{ return rhs < (*this); }

	_bool operator <= ( const PrimaryKey& rhs ) const
		{ return !( (*this) > rhs ); }

	_bool operator >= ( const PrimaryKey& rhs ) const
		{ return !( (*this) < rhs ); }

	_bool operator == ( const PrimaryKey& rhs ) const
		{ return mType == rhs.mType && mParamKey == rhs.mParamKey; }

	_bool operator != ( const PrimaryKey& rhs ) const
		{ return !( (*this) == rhs ); }
};

class ShaderMap
{
private:
	typedef Pair< ParameterKey, Shader* >	ShaderMapElement;

public:
	~ShaderMap( );

	template< typename ShaderType >
	Shader* GetShader( _dword format = 0, _bool async = _false )
	{
		const ShaderParam& param = GetTechniqueFactory( ).GetTechniqueBuilder( ).GetShaderParam( );

		return GetShader< ShaderType >( param, format, async );
	}

	template< typename ShaderType >
	Shader* GetShader( const ShaderParam& param, _dword format = 0, _bool async = _false )
	{
		format |= param.formatex;

		typename ShaderType::ParamType mparam;
		ParameterKey paramkey = mparam.GetParamKey( param, format );

		_dword index = -1;
		if ( ShaderType::sShaderToken != -1 )
			index = mShaders[ ShaderType::sShaderToken ].IndexOf( paramkey );
		else
			ShaderType::sShaderToken = mShaders.Add( SortArray< ShaderMapElement, ParameterKey >( ) );

		if ( index == -1 )
		{
			PrimaryKey key( &ShaderType::StaticType, paramkey );
			Shader* shader = ShaderType::CreateShader( param, format, key, async );

			_bool vs = ShaderType::StaticType.GetType( ) == FShaderType::_VERTEX;

			if ( vs )
				shader->GetVertexMethod( )->SetPrimaryKey( key );
			else
				shader->GetPixelMethod( )->SetPrimaryKey( key );

			mShaders[ ShaderType::sShaderToken ].Add( ShaderMapElement( paramkey, shader ) );

			return shader;
		}

		return mShaders[ ShaderType::sShaderToken ][ index ].obj2;
	}

private:
	Array< SortArray< ShaderMapElement, ParameterKey > >	mShaders;
};

#define _DECLARE_GLOBAL_SHADER( Parameter ) \
public: \
	typedef GlobalShaderType ShaderMetaType; \
	static ShaderMetaType StaticType; \
	typedef Parameter ParamType; \
	static _dword sShaderToken; \
	\
	static _void ParseParamKey( const ParameterKey& paramkey, ShaderParam& param, _dword& format ) \
		{ Parameter::ParseParamKey( paramkey, param, format ); }

#define _DECLARE_MATERIAL_SHADER( Parameter ) \
public: \
	typedef MaterialShaderType ShaderMetaType; \
	static ShaderMetaType StaticType; \
	typedef Parameter ParamType; \
	static _dword sShaderToken; \
	\
	static _void ParseParamKey( const ParameterKey& paramkey, ShaderParam& param, _dword& format ) \
		{ Parameter::ParseParamKey( paramkey, param, format ); }

#define _IMPLEMENT_SHADER( ShaderClass, Name, Type, ... ) \
ShaderClass::ShaderMetaType ShaderClass::StaticType( Name, Type, ##__VA_ARGS__ ); \
_dword ShaderClass::sShaderToken = -1

#define _IMPLEMENT_SHADER_T( ShaderClass, Name, Type, ... ) \
template< > \
ShaderClass::ShaderMetaType ShaderClass::StaticType( Name, Type, ##__VA_ARGS__ ); \
template< > \
_dword ShaderClass::sShaderToken = -1

#define _DECLARE_CREATESHADER( ) \
	static Shader* CreateShader( const ShaderParam& param, _dword format, const PrimaryKey& key, _bool async )
}