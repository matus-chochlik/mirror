/**
 *  @file mire/mirror/reg/std/allocator.cpp
 *  @brief Pre-registering of the std::allocator template
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MIRROR_REG_STD_ALLOCATOR_1311042119_HPP
#define MIRROR_REG_STD_ALLOCATOR_1311042119_HPP

#include <mire/reg/std/namespace.hpp>
#include <memory>

namespace mire {
namespace reg {
namespace _std {

namespace allocator {
struct _ : mire::reg::defaults
{
	typedef mirror::meta_class_tag category;
	typedef mirror::spec_class_tag elaborated_type;
	typedef ct::true_type is_template;
	typedef mire::reg::_std::_ scope;

	typedef mire::ct::string<'a','l','l','o','c','a','t','o','r'>
		base_name;

	template <typename X>
	struct named_typedef
	{
		typedef X allocator;
	};

	template <typename X>
	struct named_mem_var
	{
		X allocator;

		template <typename ... P>
		named_mem_var(P&& ... p)
		 : allocator(std::forward<P>(p)...)
		{ }
	};
};
} // namespace allocator
} // namespace _std

template <typename T>
struct _type_reg<std::allocator<T>>
{
	typedef mire::reg::_std::allocator::_ type;
};

} // namespace reg
} // namespace mire
#endif // include guard
