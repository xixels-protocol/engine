#pragma once

namespace Xixels
{

#ifdef _TYPECHECKER_ENABLE

template < typename T >
struct TypeChecker;

template < typename T >
struct TypeChecker
{
	static constexpr bool Value = false;
};

template < >
struct TypeChecker< const _char* >
{
	static constexpr bool Value = true;
};

template < >
struct TypeChecker< _char* >
{
	static constexpr bool Value = true;
};

template < >
struct TypeChecker< const _void* >
{
	static constexpr bool Value = true;
};

template < >
struct TypeChecker< _void* >
{
	static constexpr bool Value = true;
};

template < >
struct TypeChecker< _bool >
{
	static constexpr bool Value = true;
};

template < >
struct TypeChecker< _chara >
{
	static constexpr bool Value = true;
};

template < >
struct TypeChecker< _char >
{
	static constexpr bool Value = true;
};

template < >
struct TypeChecker< _tiny >
{
	static constexpr bool Value = true;
};

template < >
struct TypeChecker< _short >
{
	static constexpr bool Value = true;
};

template < >
struct TypeChecker< _long >
{
	static constexpr bool Value = true;
};

template < >
struct TypeChecker< _byte >
{
	static constexpr bool Value = true;
};

template < >
struct TypeChecker< _word >
{
	static constexpr bool Value = true;
};

template < >
struct TypeChecker< _dword >
{
	static constexpr bool Value = true;
};

template < >
struct TypeChecker< _float >
{
	static constexpr bool Value = true;
};

template < >
struct TypeChecker< _ptr >
{
	static constexpr bool Value = true;
};

#endif

};