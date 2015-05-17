/**
 *  @file mire/mirror/reg/std/char_traits.cpp
 *  @brief Pre-registering of the std::char_traits template
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MIRROR_REG_STD_CHAR_TRAITS_1311042119_HPP
#define MIRROR_REG_STD_CHAR_TRAITS_1311042119_HPP

#include <mire/reg/specifier.hpp>
#include <mire/reg/std/namespace.hpp>
#include <string>

namespace mire {
namespace reg {
namespace _std {

namespace char_traits {
struct _ : mire::reg::defaults
{
	typedef mirror::meta_class_tag category;
	typedef mire::reg::_struct elaborated_type;
	typedef ct::true_type is_template;
	typedef mire::reg::_std::_ scope;

	typedef mire::ct::string<'c','h','a','r','_','t','r','a','i','t','s'>
		base_name;

	template <typename X>
	struct _named_typedef
	{
		typedef X char_traits;
	};

	template <typename X>
	struct _named_mem_var
	{
		X char_traits;

		template <typename ... P>
		_named_mem_var(P&& ... p)
		 : char_traits(std::forward<P>(p)...)
		{ }
	};
};
} // namespace char_traits
} // namespace _std

template <typename T>
struct _type_reg<std::char_traits<T>>
{
	typedef mire::reg::_std::char_traits::_ type;
};

} // namespace reg
} // namespace mire
#endif // include guard
