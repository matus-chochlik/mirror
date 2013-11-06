/**
 *  @file mire/mirror/reg/global_scope.cpp
 *  @brief Pre-registering of the global scope
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MIRROR_REG_GLOBAL_SCOPE_1311042119_HPP
#define MIRROR_REG_GLOBAL_SCOPE_1311042119_HPP

#include <mirror/tags.hpp>

namespace mirror {
namespace _reg {

struct _
{
	typedef meta_global_scope_tag category;
	typedef _ scope;
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

} // namespace _reg
} // namespace mirror
#endif // include guard
