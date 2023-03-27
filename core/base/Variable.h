#pragma once

namespace Xixels
{

class Variable
{
public:
	typedef _void (*OnHandleValue)( const Variable& var, _dword mode );

	enum _VALUE_TYPE
	{
		_TYPE_UNKNOWN	= 0x0000,
		_TYPE_NULL		= 0x0001,

		_TYPE_BOOL		= 0x0002,
		_TYPE_CHAR		= 0x0003,

		_TYPE_TINY		= 0x0004,
		_TYPE_SHORT		= 0x0005,
		_TYPE_LONG		= 0x0006,
		_TYPE_LARGE		= 0x0007,

		_TYPE_BYTE		= 0x0008,
		_TYPE_WORD		= 0x0009,
		_TYPE_DWORD		= 0x000A,
		_TYPE_QWORD		= 0x000B,

		_TYPE_FLOAT		= 0x000C,
		_TYPE_DOUBLE	= 0x000D,

		_TYPE_BYTES		= 0x000E,
		_TYPE_STRING	= 0x000F,
		_TYPE_OBJECT	= 0x0010,
		_TYPE_FUNCTION	= 0x0011,
		_TYPE_USERDATA	= 0x0012,

		_TYPE_STRUCT	= 0x0080,
		_TYPE_MASK		= 0x00FF,
		_TYPE_ARRAY		= 0x0100,
	};

	static Variable cInvalid;
	static Variable cNull;

private:
	String				mName;
	_dword				mType;

	union
	{
		_bool			mBool;
		_char			mChar;
		_tiny			mTiny;
		_short			mShort;
		_long			mLong;
		_large			mLarge;
		_byte			mByte;
		_word			mWord;
		_dword			mDword;
		_qword			mQword;
		_float			mFloat;
		_double			mDouble;
		_byte*			mBytes;
		_char*			mString;
		struct
		{
			_void*		mObject;
			_dword		mHelper;
		};
	};

	_double				mKey;
	_bool				mKeyEnabled;

	Variable*			mTemplate;
	Variable*			mNumber;
	Array< Variable* >	mMembers;

	OnHandleValue		mHandleFunc;

	inline _large ToLarge( ) const
	{
		if ( mType == _TYPE_FLOAT )
			return static_cast<_long>( mFloat );
		if ( mType == _TYPE_DOUBLE )
			return static_cast<_long>( mDouble );
		else if ( mType != _TYPE_STRING && mType != _TYPE_OBJECT && mType != _TYPE_STRUCT )
			return mLarge;
		else
			return 0;
	}

	inline _qword ToQword( ) const
	{
		if ( mType == _TYPE_FLOAT )
			return static_cast<_dword>( mFloat );
		if ( mType == _TYPE_DOUBLE )
			return static_cast<_dword>( mDouble );
		else if ( mType != _TYPE_STRING && mType != _TYPE_OBJECT && mType != _TYPE_STRUCT )
			return mQword;
		else
			return 0;
	}

	inline _float ToFloat( ) const
	{
		if ( mType == _TYPE_FLOAT )
			return mFloat;
		else if ( mType == _TYPE_DOUBLE )
			return static_cast<_float>( mDouble );
		else if ( mType != _TYPE_STRING && mType != _TYPE_OBJECT && mType != _TYPE_STRUCT )
			return static_cast<_float>( mLong );
		else
			return 0.0f;
	}

	inline _double ToDouble( ) const
	{
		if ( mType == _TYPE_FLOAT )
			return static_cast<_double>( mFloat );
		else if ( mType == _TYPE_DOUBLE )
			return mDouble;
		else if ( mType != _TYPE_STRING && mType != _TYPE_OBJECT && mType != _TYPE_STRUCT )
			return static_cast<_double>( mLong );
		else
			return 0.0;
	}

	_void		CopyBytes( const _byte* buffer, _dword length );
	_void		CopyString( StringPtr str );
	_void		ChangeToString( const _chara* str );
	_void		SplitNameL2R( const _char* name, _char* buffer, const _char*& prefix, const _char*& postfix ) const;
	_void		SplitNameR2L( const _char* name, _char* buffer, const _char*& prefix, const _char*& postfix ) const;

public:
	explicit Variable( StringPtr name, _dword type );

	inline explicit Variable( )
		: mType( _TYPE_UNKNOWN ), mLarge( 0 ), mKey( 0 ), mKeyEnabled( _false ), mNumber( _null ), mTemplate( _null ), mHandleFunc( _null ) { }
	inline explicit Variable( _bool value )
		: mType( _TYPE_BOOL ), mBool( value ), mKey( 0 ), mKeyEnabled( _false ), mNumber( _null ), mTemplate( _null ), mHandleFunc( _null ) { }
	inline explicit Variable( _char value )
		: mType( _TYPE_CHAR ), mChar( value ), mKey( 0 ), mKeyEnabled( _false ), mNumber( _null ), mTemplate( _null ), mHandleFunc( _null ) { }
	inline explicit Variable( _tiny value )
		: mType( _TYPE_TINY ), mTiny( value ), mKey( 0 ), mKeyEnabled( _false ), mNumber( _null ), mTemplate( _null ), mHandleFunc( _null ) { }
	inline explicit Variable( _short value )
		: mType( _TYPE_SHORT ), mShort( value ), mKey( 0 ), mKeyEnabled( _false ), mNumber( _null ), mTemplate( _null ), mHandleFunc( _null ) { }
	inline explicit Variable( _long value )
		: mType( _TYPE_LONG ), mLong( value ), mKey( 0 ), mKeyEnabled( _false ), mNumber( _null ), mTemplate( _null ), mHandleFunc( _null ) { }
	inline explicit Variable( _large value )
		: mType( _TYPE_LARGE ), mLarge( value ), mKey( 0 ), mKeyEnabled( _false ), mNumber( _null ), mTemplate( _null ), mHandleFunc( _null ) { }
	inline explicit Variable( _byte value )
		: mType( _TYPE_BYTE ), mByte( value ), mKey( 0 ), mKeyEnabled( _false ), mNumber( _null ), mTemplate( _null ), mHandleFunc( _null ) { }
	inline explicit Variable( _word value )
		: mType( _TYPE_WORD ), mWord( value ), mKey( 0 ), mKeyEnabled( _false ), mNumber( _null ), mTemplate( _null ), mHandleFunc( _null ) { }
	inline explicit Variable( _dword value )
		: mType( _TYPE_DWORD ), mDword( value ), mKey( 0 ), mKeyEnabled( _false ), mNumber( _null ), mTemplate( _null ), mHandleFunc( _null ) { }
	inline explicit Variable( _qword value )
		: mType( _TYPE_QWORD ), mQword( value ), mKey( 0 ), mKeyEnabled( _false ), mNumber( _null ), mTemplate( _null ), mHandleFunc( _null ) { }
	inline explicit Variable( _float value )
		: mType( _TYPE_FLOAT ), mFloat( value ), mKey( 0 ), mKeyEnabled( _false ), mNumber( _null ), mTemplate( _null ), mHandleFunc( _null ) { }
	inline explicit Variable( _double value )
		: mType( _TYPE_DOUBLE ), mDouble( value ), mKey( 0 ), mKeyEnabled( _false ), mNumber( _null ), mTemplate( _null ), mHandleFunc( _null ) { }
	inline explicit Variable( const _byte* buffer, _dword length )
		: mType( _TYPE_BYTES ), mLarge( 0 ), mKey( 0 ), mKeyEnabled( _false ), mNumber( _null ), mTemplate( _null ), mHandleFunc( _null ) { CopyBytes( buffer, length ); }
	inline explicit Variable( const _char* str )
		: mType( _TYPE_STRING ), mString( _null ), mKey( 0 ), mKeyEnabled( _false ), mNumber( _null ), mTemplate( _null ), mHandleFunc( _null ) { CopyString( str ); }
	inline explicit Variable( const _chara* str )
		: mType( _TYPE_STRING ), mString( _null ), mKey( 0 ), mKeyEnabled( _false ), mNumber( _null ), mTemplate( _null ), mHandleFunc( _null ) { ChangeToString( str ); }
	inline explicit Variable( _void* obj )
		: mType( _TYPE_OBJECT ), mObject( obj ), mKey( 0 ), mKeyEnabled( _false ), mNumber( _null ), mTemplate( _null ), mHandleFunc( _null ) { }
	inline Variable( const Variable& var )
		: mType( _TYPE_UNKNOWN ), mLarge( 0 ), mKey( 0 ), mKeyEnabled( _false ), mNumber( _null ), mTemplate( _null ), mHandleFunc( _null ) { Clone( var ); }
	inline Variable& operator = ( const Variable& var )
		{ Clone( var ); return *this; }

	~Variable( );

	inline _dword GetType( ) const
		{ return mType; }

	inline StringPtr GetName( ) const
		{ return mName; }
	inline _void SetName( StringPtr name )
		{ mName = name; }

	inline _double GetKey( ) const
		{ return mKey; }
	inline _void SetKey( _double key )
		{ mKey = key; }

	inline _bool IsKeyEnabled( ) const
		{ return mKeyEnabled; }
	inline _void EnableKey( _bool enable )
		{ mKeyEnabled = enable; }

	inline _bool IsUnknown( ) const
		{ return mType == _TYPE_UNKNOWN; }
	inline _bool IsNull( ) const
		{ return mType == _TYPE_NULL; }
	inline _bool IsValid( ) const
		{ return mType != _TYPE_UNKNOWN; }
	inline _bool IsBool( ) const
		{ return mType == _TYPE_BOOL; }
	inline _bool IsNumber( ) const
		{ return mType >= _TYPE_TINY && mType <= _TYPE_DOUBLE; }
	inline _bool IsString( ) const
		{ return mType == _TYPE_STRING; }
	inline _bool IsBytes( ) const
		{ return mType == _TYPE_BYTES; }
	inline _bool IsObject( ) const
		{ return mType == _TYPE_OBJECT; }
	inline _bool IsFunction( ) const
		{ return mType == _TYPE_FUNCTION; }
	inline _bool IsStruct( ) const
		{ return ( mType & _TYPE_MASK ) == _TYPE_STRUCT; }
	inline _bool IsArray( ) const
		{ return mType & _TYPE_ARRAY; }

	inline const Variable* GetTemplate( ) const
		{ return mTemplate; }
	inline _long GetMemberCount( ) const
		{ return mMembers.Length( ); }

	inline operator _bool ( ) const
		{ return mType == _TYPE_BOOL ? mBool : 0; }
	inline operator _char ( ) const
		{ return mType == _TYPE_CHAR ? mChar : 0; }
	inline operator _tiny ( ) const
		{ return (_tiny) ToLarge( ); }
	inline operator _short ( ) const
		{ return (_short) ToLarge( ); }
	inline operator _long ( ) const
		{ return (_long) ToLarge( ); }
	inline operator _large ( ) const
		{ return ToLarge( ); }
	inline operator _byte ( ) const
		{ return (_byte) ToQword( ); }
	inline operator _word ( ) const
		{ return (_word) ToQword( ); }
	inline operator _dword ( ) const
		{ return (_dword) ToQword( ); }
	inline operator _qword ( ) const
		{ return ToQword( ); }
	inline operator _float ( ) const
		{ return ToFloat( ); }
	inline operator _double ( ) const
		{ return ToDouble( ); }
	inline operator const _char* ( ) const
		{ return mType == _TYPE_STRING && mString != _null ? mString : L""; }
	inline operator StringPtr ( ) const
		{ return mType == _TYPE_STRING && mString != _null ? mString : L""; }
	inline operator String ( ) const
		{ return mType == _TYPE_STRING && mString != _null ? mString : L""; }
	inline operator _void* ( ) const
		{ return mType == _TYPE_OBJECT ? mObject : _null; }

	inline Variable& operator = ( _bool value )
		{ if ( mType == _TYPE_BOOL ) mBool = value; return *this; }
	inline Variable& operator = ( _char value )
		{ if ( mType == _TYPE_CHAR ) mChar = value; return *this; }
	inline Variable& operator = ( _tiny value )
		{ if ( mType == _TYPE_TINY || mType == _TYPE_BYTE ) mTiny = value; return *this; }
	inline Variable& operator = ( _short value )
		{ if ( mType == _TYPE_SHORT || mType == _TYPE_WORD ) mShort = value; return *this; }
	inline Variable& operator = ( _long value )
		{ if ( mType == _TYPE_LONG || mType == _TYPE_DWORD ) mLong = value; return *this; }
	inline Variable& operator = ( _large value )
		{ if ( mType == _TYPE_LARGE || mType == _TYPE_QWORD ) mLarge = value; return *this; }
	inline Variable& operator = ( _byte value )
		{ if ( mType == _TYPE_TINY || mType == _TYPE_BYTE ) mByte = value; return *this; }
	inline Variable& operator = ( _word value )
		{ if ( mType == _TYPE_SHORT || mType == _TYPE_WORD ) mWord = value; return *this; }
	inline Variable& operator = ( _dword value )
		{ if ( mType == _TYPE_LONG || mType == _TYPE_DWORD ) mDword = value; return *this; }
	inline Variable& operator = ( _qword value )
		{ if ( mType == _TYPE_LARGE || mType == _TYPE_QWORD ) mQword = value; return *this; }
	inline Variable& operator = ( _float value )
		{ if ( mType == _TYPE_FLOAT ) mFloat = value; return *this; }
	inline Variable& operator = ( _double value )
		{ if ( mType == _TYPE_DOUBLE ) mDouble = value; return *this; }
	inline Variable& operator = ( const _char* str )
		{ if ( mType == _TYPE_STRING ) CopyString( str ); return *this; }
	inline Variable& operator = ( const _chara* str )
		{ if ( mType == _TYPE_STRING ) ChangeToString( str ); return *this; }
	inline Variable& operator = ( StringPtr str )
		{ if ( mType == _TYPE_STRING ) CopyString( str ); return *this; }
	inline Variable& operator = ( const String& str )
		{ if ( mType == _TYPE_STRING ) CopyString( str ); return *this; }
	inline Variable& operator = ( _void* obj )
		{ if ( mType == _TYPE_OBJECT ) mObject = obj; return *this; }

	inline Variable& SetValue( _bool value )
		{ mType = _TYPE_BOOL; mBool = value; return *this; }
	inline Variable& SetValue( _char value )
		{ mType = _TYPE_CHAR; mChar = value; return *this; }
	inline Variable& SetValue( _tiny value )
		{ mType = _TYPE_TINY; mTiny = value; return *this; }
	inline Variable& SetValue( _short value )
		{ mType = _TYPE_SHORT; mShort = value; return *this; }
	inline Variable& SetValue( _long value )
		{ mType = _TYPE_LONG; mLong = value; return *this; }
	inline Variable& SetValue( _large value )
		{ mType = _TYPE_LARGE; mLarge = value; return *this; }
	inline Variable& SetValue( _byte value )
		{ mType = _TYPE_BYTE; mByte = value; return *this; }
	inline Variable& SetValue( _word value )
		{ mType = _TYPE_WORD; mWord = value; return *this; }
	inline Variable& SetValue( _dword value )
		{ mType = _TYPE_DWORD; mDword = value; return *this; }
	inline Variable& SetValue( _qword value )
		{ mType = _TYPE_QWORD; mQword = value; return *this; }
	inline Variable& SetValue( _float value )
		{ mType = _TYPE_FLOAT; mFloat = value; return *this; }
	inline Variable& SetValue( _double value )
		{ mType = _TYPE_DOUBLE; mDouble = value; return *this; }
	inline Variable& SetValue( StringPtr str, _bool copy = _true )
		{ return SetValue( (const _char*) str, copy ); }
	inline Variable& SetValue( const _char* str, _bool copy = _true )
		{ mType = _TYPE_STRING; if ( copy ) CopyString( str ); else mString = (_char*) str; return *this; }
	inline Variable& SetValue( _void* obj )
		{ mType = _TYPE_OBJECT; mObject = obj; return *this; }

	inline Variable& SetBytes( const _byte* buffer, _dword length )
		{ mType = _TYPE_BYTES; CopyBytes( buffer, length ); return *this; }
	inline const _byte* GetBytes( _dword& length ) const
		{ length = mHelper; return mType == _TYPE_BYTES ? mBytes : _null; }

	inline Variable& SetFunction( _long funchandle )
		{ mType = _TYPE_FUNCTION; mLong = funchandle; return *this; }
	inline _long GetFunction( ) const
		{ return mType == _TYPE_FUNCTION ? mLong : 0; }

	inline Variable& SetUserdata( _void* ptr )
		{ mType = _TYPE_USERDATA; mObject = ptr; return *this; }
	inline _void* GetUserdata( ) const
		{ return mType == _TYPE_USERDATA ? mObject : 0; }

	inline Variable& SetHelper( _dword helper )
		{ mHelper = helper; return *this; }
	inline _dword GetHelper( ) const
		{ return mHelper; }

	// Get sub variable by name.
	inline const Variable& operator [] ( StringPtr name ) const
		{ return operator [] ( (const _char*) name ); }
	inline Variable& operator [] ( StringPtr name )
		{ return operator [] ( (const _char*) name ); }

	// Get sub variable by index.
	const Variable&	operator [] ( _long index ) const;
	Variable&		operator [] ( _long index );

	// Get sub variable by name.
	const Variable& operator [] ( const _char* name ) const;
	const Variable& operator () ( const _char* name, _long i ) const;
	const Variable& operator () ( const _char* name, _long i, _long j ) const;
	const Variable& operator () ( const _char* name, _long i, _long j, _long k ) const;

	// Get sub variable by name.
	Variable& operator [] ( const _char* name );
	Variable& operator () ( const _char* name, _long i );
	Variable& operator () ( const _char* name, _long i, _long j );
	Variable& operator () ( const _char* name, _long i, _long j, _long k );

	// Set userdefined value.
	Variable&	SetUserDefinedValue( _void* obj, OnHandleValue func = _null );

	// Redefine the variable.
	_void		Redeclare( StringPtr name, _dword type );

	// Create variable member or array, use existing variable.
	Variable&	CreateMember( StringPtr name, Variable& value );

	// Create variable member or array, just like declaration.
	Variable&	DefineMember( StringPtr name, _dword type );

	// Create variable element in array.
	_void		CreateElement( _dword count );

	// Delete variable element in array.
	_void		DeleteElement( _long index );

	// Clear variable element in array.
	_void		ClearElement( );

	// Clone from another variable.
	_void		Clone( const Variable& var );

	// Clear variable itself.
	_void		Clear( );
};

};
