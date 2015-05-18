/**
 *  @file mire/mirror/reg/std/string.cpp
 *  @brief Pre-registering of the std::string typedef
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MIRROR_REG_STD_STRING_1311042119_HPP
#define MIRROR_REG_STD_STRING_1311042119_HPP

#include <mire/reg/std/namespace.hpp>
#include <mire/reg/std/basic_string.hpp>
#include <string>

namespace mire {
namespace reg {
namespace _std {

namespace string {
struct _ : mire::reg::defaults
{
	typedef mirror::typedef_tag category;
	typedef mire::reg::_std::_ scope;
	typedef ct::true_type has_template;
	typedef mire::reg::_std::basic_string::_ template_;
	typedef mire::reg::_std::basic_string::_ typedef_type;

	typedef mire::ct::string<'s','t','r','i','n','g'>
		base_name;

	template <typename X>
	struct _named_typedef
	{
		typedef X string;
	};

	template <typename X>
	struct _named_mem_var
	{
		X string;

		template <typename ... P>
		_named_mem_var(P&& ... p)
		 : string(std::forward<P>(p)...)
		{ }
	};
};
} // namespace string
} // namespace _std

template <>
struct _type_reg<std::string>
{
	typedef mire::reg::_std::string::_ type;
};

} // namespace reg
} // namespace mire
#endif // include guard
