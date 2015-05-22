/**
 *  @file mire/mirror/original_type.hpp
 *  @brief Implementation of the original_type metafunction.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2006-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_MIRROR_ORIGINAL_TYPE_1310291537_HPP
#define MIRE_MIRROR_ORIGINAL_TYPE_1310291537_HPP

#include <mire/mirror/default.hpp>
#include <mire/ct/int_const.hpp>

namespace mire {
namespace mirror {
namespace _aux {

template <typename T>
struct get_orig_type
{
	template <typename X>
	static typename X::original_type _get(X*);
	static void _get(...);

	typedef decltype(_get(static_cast<T*>(nullptr))) type;
};

} // namespace _aux

template <typename R, typename M>
struct original_type<meta<R, M>>
{
	typedef M type;
};

} // namespace mirror
} // namespace mire

#endif // include guard
