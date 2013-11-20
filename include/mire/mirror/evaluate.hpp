/**
 *  @file mire/mirror/evaluate.hpp
 *  @brief Implementation of the evaluate meta-function
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2006-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRROR_EVALUATE_1310291537_HPP
#define MIRROR_EVALUATE_1310291537_HPP

#include <mire/mirror/fwd.hpp>
#include <mire/mirror/stddef.hpp>

namespace mire {
namespace mirror {

template <typename X>
struct evaluate
 : evaluate<typename X::type>
{ };

template <typename R, typename M>
struct evaluate<meta<R, M>>
 : meta<R, M>
{ };

} // namespace mirror
} // namespace mire

#endif // include guard
