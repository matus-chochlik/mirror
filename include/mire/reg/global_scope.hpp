/**
 *  @file mire/reg/global_scope.cpp
 *  @brief Pre-registering of the global scope
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MIRE_REG_GLOBAL_SCOPE_1311042119_HPP
#define MIRE_REG_GLOBAL_SCOPE_1311042119_HPP

#include <mire/ct/int_const.hpp>
#include <mire/ct/string.hpp>
#include <mire/mirror/tags.hpp>
#include <utility>

namespace mire {
namespace reg {

template <typename T>
struct _type_reg;

struct defaults
{
	typedef ct::false_type is_specifier;
	typedef ct::true_type has_name;
	typedef ct::true_type has_scope;
	typedef ct::false_type is_scope;
	typedef ct::false_type has_position;
	typedef ct::false_type is_class_member;
	typedef ct::false_type has_template;
	typedef ct::false_type is_template;

	typedef ct::empty_string source_file;
	typedef ct::integral_constant<unsigned, 0u> source_line;
};

struct _ : mire::reg::defaults
{
	typedef ct::true_type is_scope;
	typedef mirror::meta_global_scope_tag category;
	typedef mire::reg::_ scope;

	typedef ct::empty_string base_name;

	template <typename X>
	struct _named_typedef
	{
		typedef X _;
	};

	template <typename X>
	struct _named_mem_var
	{
		X _;

		template <typename ... P>
		_named_mem_var(P&& ... p)
		 : _(std::forward<P>(p)...)
		{ }
	};
};

struct anon_t : mire::reg::defaults
{
	typedef mirror::meta_type_tag category;
	typedef mire::reg::_ scope;
	struct base_name
	{
		static constexpr const char* c_str = "";
		static constexpr std::size_t size = 0;
	};

	template <typename X>
	struct _named_typedef
	{
		typedef X _;
	};

	template <typename X>
	struct _named_mem_var
	{
		X _;

		template <typename ... P>
		_named_mem_var(P&& ... p)
		 : _(std::forward<P>(p)...)
		{ }
	};
};

template <>
struct _type_reg<anon_t>
{
	typedef anon_t type;
};

template <typename T>
struct _type_reg<T const>
 : _type_reg<T>
{ };

template <typename T>
struct _type_reg<T volatile>
 : _type_reg<T>
{ };

template <typename T>
struct _type_reg<T const volatile>
 : _type_reg<T>
{ };

template <typename T>
struct _type_reg<T*>
 : _type_reg<T>
{ };

template <typename T>
struct _type_reg<T&>
 : _type_reg<T>
{ };

template <typename T>
struct _type_reg<T&&>
 : _type_reg<T>
{ };

template <typename T>
struct _type_reg<T[]>
 : _type_reg<T>
{ };

template <typename T>
struct _type_reg<T const[]>
 : _type_reg<T>
{ };

template <typename T>
struct _type_reg<T volatile[]>
 : _type_reg<T>
{ };

template <typename T>
struct _type_reg<T const volatile[]>
 : _type_reg<T>
{ };

template <typename T, size_t N>
struct _type_reg<T[N]>
 : _type_reg<T>
{ };

template <typename T, size_t N>
struct _type_reg<T const [N]>
 : _type_reg<T>
{ };

template <typename T, size_t N>
struct _type_reg<T volatile [N]>
 : _type_reg<T>
{ };

template <typename T, size_t N>
struct _type_reg<T const volatile [N]>
 : _type_reg<T>
{ };

template <typename RV, typename ... P>
struct _type_reg<RV(P...)>
 : _type_reg<anon_t>
{ };

} // namespace reg
} // namespace mire
#endif // include guard
