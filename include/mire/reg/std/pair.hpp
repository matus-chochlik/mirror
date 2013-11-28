/**
 *  @file mire/mirror/reg/std/pair.cpp
 *  @brief Pre-registering of the std::pair template
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MIRROR_REG_STD_PAIR_1311042119_HPP
#define MIRROR_REG_STD_PAIR_1311042119_HPP

#include <mire/reg/std/namespace.hpp>
#include <utility>

namespace mire {
namespace reg {
namespace _std {

namespace pair {
struct _ : mire::reg::defaults
{
	typedef mirror::meta_class_tag category;
	typedef mirror::spec_struct_tag elaborated_type;
	typedef ct::true_type is_template;
	typedef mire::reg::_std::_ scope;

	typedef ct::string<'p','a','i','r'> base_name;

	template <typename X>
	struct named_typedef
	{
		typedef X pair;
	};

	template <typename X>
	struct named_mem_var
	{
		X pair;

		template <typename ... P>
		named_mem_var(P&& ... p)
		 : pair(std::forward<P>(p)...)
		{ }
	};
};

} // namespace pair
} // namespace _std

template <typename First, typename Second>
struct _type_reg<std::pair<First, Second>>
{
	typedef mire::reg::_std::pair::_ type;
};

} // namespace reg
} // namespace mire
#endif // include guard
