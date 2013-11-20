/**
 *  @file mire/reg/global_scope.cpp
 *  @brief Pre-registering of the global scope
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MIRE_REG_GLOBAL_SCOPE_1311042119_HPP
#define MIRE_REG_GLOBAL_SCOPE_1311042119_HPP

#include <mire/tags.hpp>

namespace mire {
namespace reg {

using namespace ::mire::tags;

template <typename T>
struct _type_reg;

struct _
{
	typedef meta_global_scope_tag category;
	typedef mire::reg::_ scope;
	struct base_name
	{
		static constexpr const char* c_str = "";
		static constexpr std::size_t size = 0;
	};
	struct full_name
	{
		static constexpr const char* c_str = "";
		static constexpr std::size_t size = 0;
	};

	template <typename X>
	struct named_typedef
	{
		typedef X _;
	};

	template <typename X>
	struct named_mem_var
	{
		X _;

		named_mem_var(void) = default;

		template <typename ... P>
		named_mem_var(P&& ... p)
		 : _(std::forward<P>(p)...)
		{ }
	};
};

struct anon_t
{
	typedef meta_type_tag category;
	typedef mire::reg::_ scope;
	struct base_name
	{
		static constexpr const char* c_str = "";
		static constexpr std::size_t size = 0;
	};
	struct full_name
	{
		static constexpr const char* c_str = "<anon>";
		static constexpr std::size_t size = 6;
	};

	template <typename X>
	struct named_typedef
	{
		typedef X _;
	};

	template <typename X>
	struct named_mem_var
	{
		X _;

		named_mem_var(void) = default;

		template <typename ... P>
		named_mem_var(P&& ... p)
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
