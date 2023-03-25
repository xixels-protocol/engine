#pragma once

namespace Xixels
{

template < >
struct TypeConverter< const _char* >
{
	TypeConverter( ) { }
	TypeConverter( const _char* ) { }
};

template < >
struct TypeConverter< _char* >
{
	TypeConverter( ) { }
	TypeConverter( _char* ) { }
};

template < >
struct TypeConverter< const _void* >
{
	TypeConverter( ) { }
	TypeConverter( const _void* ) { }
};

template < >
struct TypeConverter< _void* >
{
	TypeConverter( ) { }
	TypeConverter( _void* ) { }
};

template < >
struct TypeConverter< _bool >
{
	TypeConverter( ) { }
	TypeConverter( _bool ) { }
};

template < >
struct TypeConverter< _char >
{
	TypeConverter( ) { }
	TypeConverter( _char ) { }
};

template < >
struct TypeConverter< _tiny >
{
	TypeConverter( ) { }
	TypeConverter( _tiny ) { }
};

template < >
struct TypeConverter< _short >
{
	TypeConverter( ) { }
	TypeConverter( _short ) { }
};

template < >
struct TypeConverter< _long >
{
	TypeConverter( ) { }
	TypeConverter( _long ) { }
};

template < >
struct TypeConverter< _large >
{
	TypeConverter( ) { }
	TypeConverter( _large ) { }
};

template < >
struct TypeConverter< _byte >
{
	TypeConverter( ) { }
	TypeConverter( _byte ) { }
};

template < >
struct TypeConverter< _word >
{
	TypeConverter( ) { }
	TypeConverter( _word ) { }
};

template < >
struct TypeConverter< _dword >
{
	TypeConverter( ) { }
	TypeConverter( _dword ) { }
};

template < >
struct TypeConverter< _qword >
{
	TypeConverter( ) { }
	TypeConverter( _qword ) { }
};

template < >
struct TypeConverter< _float >
{
	TypeConverter( ) { }
	TypeConverter( _float ) { }
};

template < >
struct TypeConverter< _double >
{
	TypeConverter( ) { }
	TypeConverter( _double ) { }
};

template < >
struct TypeConverter< Buffer >
{
	TypeConverter( ) { }
	TypeConverter( Buffer ) { }
};

template < >
struct TypeConverter< StringPtr >
{
	TypeConverter( ) { }
	TypeConverter( StringPtr ) { }
};

template < >
struct TypeConverter< String >
{
	TypeConverter( ) { }
	TypeConverter( String ) { }
};

template < >
struct TypeConverter< Point >
{
	TypeConverter( ) { }
	TypeConverter( Point ) { }
};

template < >
struct TypeConverter< Rect >
{
	TypeConverter( ) { }
	TypeConverter( Rect ) { }
};

template < >
struct TypeConverter< Vector2 >
{
	TypeConverter( ) { }
	TypeConverter( Vector2 ) { }
};

template < >
struct TypeConverter< Vector3 >
{
	TypeConverter( ) { }
	TypeConverter( Vector3 ) { }
};

template < >
struct TypeConverter< Vector4 >
{
	TypeConverter( ) { }
	TypeConverter( Vector4 ) { }
};

template < >
struct TypeConverter< Quaternion >
{
	TypeConverter( ) { }
	TypeConverter( Quaternion ) { }
};

template < >
struct TypeConverter< EulerAngles >
{
	TypeConverter( ) { }
	TypeConverter( EulerAngles ) { }
};

template < >
struct TypeConverter< AxisAlignedBox >
{
	TypeConverter( ) { }
	TypeConverter( AxisAlignedBox ) { }
};

class ScriptObject;
template < >
struct TypeConverter< ScriptObject* >
{
	TypeConverter( ) { }
	TypeConverter( ScriptObject* ) { }
};

template < >
struct TypeConverter< Variable >
{
	TypeConverter( ) { }
	TypeConverter( Variable ) { }
};

};