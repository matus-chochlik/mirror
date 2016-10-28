/**
 * @file mirror/range_ops.hpp
 * @brief Declaration of the compile-time range operations
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_RANGE_OPS_1105240825_HPP
#define MIRROR_RANGE_OPS_1105240825_HPP

#include "range.hpp"
#include "int_const.hpp"

namespace mirror {

template <typename ... L, typename ... R>
static constexpr inline
false_
operator == (range<L...>, range<R...>)
noexcept { return {}; }

template <typename ... P>
static constexpr inline
true_
operator == (range<P...>, range<P...>)
noexcept { return {}; }

template <typename ... L, typename ... R>
static constexpr inline
true_
operator != (range<L...>, range<R...>)
noexcept { return {}; }

template <typename ... P>
static constexpr inline
false_
operator != (range<P...>, range<P...>)
noexcept { return {}; }

} // namespace mirror

#endif //include guard

