/**
 *  @file mire/mirror/scope.hpp
 *  @brief Implementation of the scope metafunction.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2006-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_MIRROR_SCOPE_1310291537_HPP
#define MIRE_MIRROR_SCOPE_1310291537_HPP

#include <mire/mirror/default.hpp>
#include <mire/mirror/original_type.hpp>

namespace mire {
namespace mirror {

template <typename R, typename M>
struct scope<meta<R, M>>
 : meta<
	typename R::scope,
	typename _aux::get_orig_type<typename R::scope>::type
>
{ };

} // namespace mirror
} // namespace mire

#endif // include guard
