/**
 *  @file mire/mirror/reg/specifier.cpp
 *  @brief Pre-registering of the C++ specifiers
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MIRROR_REG_SPECIFIER_1311042119_HPP
#define MIRROR_REG_SPECIFIER_1311042119_HPP

#include <mire/ct/int_const.hpp>
#include <mire/ct/string.hpp>
#include <mire/mirror/tags.hpp>

namespace mire {
namespace reg {

struct _none
{
	typedef _none _;
	typedef ct::true_type is_specifier;
	typedef mirror::none_tag spec_tag;
	typedef ct::empty_string keyword;
};

struct _extern
{
	typedef _extern _;
	typedef ct::true_type is_specifier;
	typedef mirror::extern_tag spec_tag;
	typedef ct::string<'e','x','t','e','r','n'> keyword;
};

struct _static
{
	typedef _static _;
	typedef ct::true_type is_specifier;
	typedef mirror::static_tag spec_tag;
	typedef ct::string<'s','t','a','t','i','c'> keyword;
};

struct _mutable
{
	typedef _mutable _;
	typedef ct::true_type is_specifier;
	typedef mirror::mutable_tag spec_tag;
	typedef ct::string<'m','u','t','a','b','l','e'> keyword;
};

struct _register
{
	typedef _register _;
	typedef ct::true_type is_specifier;
	typedef mirror::register_tag spec_tag;
	typedef ct::string<'r','e','g','i','s','t','e','r'> keyword;
};

struct _thread_local
{
	typedef _thread_local _;
	typedef ct::true_type is_specifier;
	typedef mirror::thread_local_tag spec_tag;
	typedef ct::string<'t','h','r','e','a','d','_','l','o','c','a','l'>
		keyword;
};

struct _constexpr
{
	typedef _constexpr _;
	typedef ct::true_type is_specifier;
	typedef mirror::constexpr_tag spec_tag;
	typedef ct::string<'c','o','n','s','t','e','x','p','r'> keyword;
};

struct _const
{
	typedef _const _;
	typedef ct::true_type is_specifier;
	typedef mirror::const_tag spec_tag;
	typedef ct::string<'c','o','n','s','t'> keyword;
};

struct _volatile
{
	typedef _volatile _;
	typedef ct::true_type is_specifier;
	typedef mirror::volatile_tag spec_tag;
	typedef ct::string<'v','o','l','a','t','i','l','e'> keyword;
};

struct _virtual
{
	typedef _virtual _;
	typedef ct::true_type is_specifier;
	typedef mirror::virtual_tag spec_tag;
	typedef ct::string<'v','i','r','t','u','a','l'> keyword;
};

struct _override
{
	typedef _override _;
	typedef ct::true_type is_specifier;
	typedef mirror::override_tag spec_tag;
	typedef ct::string<'o','v','e','r','r','i','d','e'> keyword;
};

struct _private
{
	typedef _private _;
	typedef ct::true_type is_specifier;
	typedef mirror::private_tag spec_tag;
	typedef ct::string<'p','r','i','v','a','t','e'> keyword;
};

struct _protected
{
	typedef _protected _;
	typedef ct::true_type is_specifier;
	typedef mirror::protected_tag spec_tag;
	typedef ct::string<'p','r','o','t','e','c','t','e','d'> keyword;
};

struct _public
{
	typedef _public _;
	typedef ct::true_type is_specifier;
	typedef mirror::public_tag spec_tag;
	typedef ct::string<'p','u','b','l','i','c'> keyword;
};

struct _class
{
	typedef _class _;
	typedef ct::true_type is_specifier;
	typedef mirror::class_tag spec_tag;
	typedef ct::string<'c','l','a','s','s'> keyword;
};

struct _struct
{
	typedef _struct _;
	typedef ct::true_type is_specifier;
	typedef mirror::struct_tag spec_tag;
	typedef ct::string<'s','t','r','u','c','t'> keyword;
};

struct _union
{
	typedef _union _;
	typedef ct::true_type is_specifier;
	typedef mirror::union_tag spec_tag;
	typedef ct::string<'u','n','i','o','n'> keyword;
};

struct _enum
{
	typedef _enum _;
	typedef ct::true_type is_specifier;
	typedef mirror::enum_tag spec_tag;
	typedef ct::string<'e','n','u','m'> keyword;
};

struct _enum_class
{
	typedef _enum_class _;
	typedef ct::true_type is_specifier;
	typedef mirror::enum_class_tag spec_tag;
	typedef ct::string<'e','n','u','m',' ','c','l','a','s','s'> keyword;
};

struct _typedef
{
	typedef _typedef _;
	typedef ct::true_type is_specifier;
	typedef mirror::typedef_tag spec_tag;
	typedef ct::string<'t','y','p','e','d','e','f'> keyword;
};

struct _noexcept
{
	typedef _noexcept _;
	typedef ct::true_type is_specifier;
	typedef mirror::noexcept_tag spec_tag;
	typedef ct::string<'n','o','e','x','c','e','p','t'> keyword;
};

} // namespace reg
} // namespace mire

#endif // include guard
