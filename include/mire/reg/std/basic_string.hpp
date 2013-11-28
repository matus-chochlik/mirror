/**
 *  @file mire/mirror/reg/std/basic_string.cpp
 *  @brief Pre-registering of the std::basic_string template
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MIRROR_REG_STD_BASIC_STRING_1311042119_HPP
#define MIRROR_REG_STD_BASIC_STRING_1311042119_HPP

#include <mire/reg/std/namespace.hpp>
#include <mire/reg/std/char_traits.hpp>
#include <mire/reg/std/allocator.hpp>
#include <string>

namespace mire {
namespace reg {
namespace _std {

namespace basic_string {
struct _ : mire::reg::defaults
{
	typedef mirror::meta_class_tag category;
	typedef mirror::spec_class_tag elaborated_type;
	typedef ct::true_type is_template;
	typedef ct::true_type is_scope;
	typedef mire::reg::_std::_ scope;

	typedef mire::ct::string<'b','a','s','i','c','_','s','t','r','i','n','g'>
		base_name;

	template <typename X>
	struct named_typedef
	{
		typedef X basic_string;
	};

	template <typename X>
	struct named_mem_var
	{
		X basic_string;

		template <typename ... P>
		named_mem_var(P&& ... p)
		 : basic_string(std::forward<P>(p)...)
		{ }
	};
};
} // namespace basic_string
} // namespace _std

template <typename CharT, typename Traits, typename Alloc>
struct _type_reg<std::basic_string<CharT, Traits, Alloc>>
{
	typedef mire::reg::_std::basic_string::_ type;
};

} // namespace reg
} // namespace mire
#endif // include guard
