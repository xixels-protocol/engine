#pragma once

namespace Xixels
{
	class ShaderContext
	{
	public:
		ShaderCodeConfig	mCfg;
		_dword				mFormat;
		_bool				mAsyncCompile;
		IShaderReflection*	mReflection;

		ShaderContext( );
		ShaderContext( IShaderReflection* reflection );
		~ShaderContext( );

		template < class T >
		T* GetReflectionInstance( )
		{
			if ( mReflection == _null )
				return _null;

			T* newReflection = (T*) ( GetShaderReflectionFactory( ).Pop( mReflection->mId ) );

			if ( newReflection == _null )
				newReflection = new T( );
			else
				newReflection->IncRefCount( );

			newReflection->SetCfg( mCfg );
			newReflection->mConst = ( (T*) mReflection )->mConst;
			newReflection->mSampler = ( (T*) mReflection )->mSampler;
			newReflection->mInput = ( (T*) mReflection )->mInput;
			newReflection->mOutput = ( (T*) mReflection )->mOutput;
			newReflection->SortConsts( );

			return newReflection;
		}

		_void AddProperties( Variable values );
		SF_Reflection* GetConstByName( StringPtr name );
		SF_Reflection* GetSamplerByName( StringPtr name );

		virtual _dword CheckGlobalIndexExist( _dword index );

	private:
		_dword NameToType( StringPtr type );
		_void AddProperties( Array< SF_Reflection* >& arr, Variable value );
		SF_Reflection* GetReflection( Array< SF_Reflection* >& arr, StringPtr name );
	};

};