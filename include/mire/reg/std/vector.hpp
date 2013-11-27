/**
 *  @file mire/mirror/reg/std/vector.cpp
 *  @brief Pre-registering of the std::vector template
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MIRROR_REG_STD_VECTOR_1311042119_HPP
#define MIRROR_REG_STD_VECTOR_1311042119_HPP

#include <mire/reg/std/namespace.hpp>
#include <mire/reg/std/allocator.hpp>
#include <vector>

namespace mire {
namespace reg {
namespace _std {

namespace vector {
struct _ : mire::reg::defaults
{
	typedef meta_class_tag category;
	typedef ct::true_type is_template;
	typedef ct::true_type is_scope;
	typedef mire::reg::_std::_ scope;

	typedef mire::ct::string<'v','e','c','t','o','r'> base_name;

	template <typename X>
	struct named_typedef
	{
		typedef X vector;
	};

	template <typename X>
	struct named_mem_var
	{
		X vector;

		template <typename ... P>
		named_mem_var(P&& ... p)
		 : vector(std::forward<P>(p)...)
		{ }
	};
};
} // namespace vector
} // namespace _std

template <typename First, typename Second>
struct _type_reg<std::vector<First, Second>>
{
	typedef mire::reg::_std::vector::_ type;
};

} // namespace reg
} // namespace mire
#endif // include guard
