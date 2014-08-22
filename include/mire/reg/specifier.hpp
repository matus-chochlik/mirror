/**
 *  @file mire/mirror/reg/specifier.cpp
 *  @brief Pre-registering of the C++ specifiers
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MIRROR_REG_SPECIFIER_1311042119_HPP
#define MIRROR_REG_SPECIFIER_1311042119_HPP

#include <mire/ct/int_const.hpp>
#include <mire/mirror/tags.hpp>

namespace mire {
namespace reg {

struct _extern
{
	typedef _extern _;
	typedef ct::true_type is_specifier;
	typedef mire::mirror::spec_extern_tag spec_tag;
};

struct _static
{
	typedef _static _;
	typedef ct::true_type is_specifier;
	typedef mire::mirror::spec_static_tag spec_tag;
};

struct _mutable
{
	typedef _mutable _;
	typedef ct::true_type is_specifier;
	typedef mire::mirror::spec_mutable_tag spec_tag;
};

struct _register
{
	typedef _register _;
	typedef ct::true_type is_specifier;
	typedef mire::mirror::spec_register_tag spec_tag;
};

struct _thread_local
{
	typedef _thread_local _;
	typedef ct::true_type is_specifier;
	typedef mire::mirror::spec_thread_local_tag spec_tag;
};

struct _constexpr
{
	typedef _constexpr _;
	typedef ct::true_type is_specifier;
	typedef mire::mirror::spec_constexpr_tag spec_tag;
};

struct _const
{
	typedef _const _;
	typedef ct::true_type is_specifier;
	typedef mire::mirror::spec_const_tag spec_tag;
};

struct _volatile
{
	typedef _volatile _;
	typedef ct::true_type is_specifier;
	typedef mire::mirror::spec_volatile_tag spec_tag;
};

struct _virtual
{
	typedef _virtual _;
	typedef ct::true_type is_specifier;
	typedef mire::mirror::spec_virtual_tag spec_tag;
};

struct _private
{
	typedef _private _;
	typedef ct::true_type is_specifier;
	typedef mire::mirror::spec_private_tag spec_tag;
};

struct _protected
{
	typedef _protected _;
	typedef ct::true_type is_specifier;
	typedef mire::mirror::spec_protected_tag spec_tag;
};

struct _public
{
	typedef _public _;
	typedef ct::true_type is_specifier;
	typedef mire::mirror::spec_public_tag spec_tag;
};

struct _class
{
	typedef _class _;
	typedef ct::true_type is_specifier;
	typedef mire::mirror::spec_class_tag spec_tag;
};

struct _struct
{
	typedef _struct _;
	typedef ct::true_type is_specifier;
	typedef mire::mirror::spec_struct_tag spec_tag;
};

struct _union
{
	typedef _union _;
	typedef ct::true_type is_specifier;
	typedef mire::mirror::spec_union_tag spec_tag;
};

struct _enum
{
	typedef _enum _;
	typedef ct::true_type is_specifier;
	typedef mire::mirror::spec_enum_tag spec_tag;
};

struct _enum_class
{
	typedef _enum_class _;
	typedef ct::true_type is_specifier;
	typedef mire::mirror::spec_enum_class_tag spec_tag;
};

struct _typedef
{
	typedef _typedef _;
	typedef ct::true_type is_specifier;
	typedef mire::mirror::spec_typedef_tag spec_tag;
};

} // namespace reg
} // namespace mire

#endif // include guard
