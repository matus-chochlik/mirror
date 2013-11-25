/**
 *  @file mire/mirror/reg/std/namespace.cpp
 *  @brief Pre-registering of the std namespace
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MIRROR_REG_STD_NAMESPACE_1311042119_HPP
#define MIRROR_REG_STD_NAMESPACE_1311042119_HPP

#include <mire/reg/global_scope.hpp>

namespace mire {
namespace reg {

namespace _std {
struct _ : mire::reg::defaults
{
	typedef meta_namespace_tag category;
	typedef mire::reg::_ scope;

	typedef ct::string<'s','t','d'> base_name;

	template <typename X>
	struct named_typedef
	{
		typedef X std;
	};

	template <typename X>
	struct named_mem_var
	{
		X std;

		template <typename ... P>
		named_mem_var(P&& ... p)
		 : std(std::forward<P>(p)...)
		{ }
	};
};
} // namespace _std

} // namespace reg
} // namespace mire
#endif // include guard
