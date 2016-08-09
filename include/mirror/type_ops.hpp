/**
 * @file mirror/type_ops.hpp
 * @brief Implementation of constexpr operations on type-lists
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_TYPE_OPS_1105240825_HPP
#define MIRROR_TYPE_OPS_1105240825_HPP

#include "range.hpp"
#include "identity.hpp"
#include "int_const.hpp"
#include <iosfwd>
#include <string>

namespace mirror {

template <typename L, typename R>
static constexpr inline
false_ operator == (identity<L>, identity<R>)
noexcept { return {}; }

template <typename T>
static constexpr inline
true_ operator == (identity<T>, identity<T>)
noexcept { return {}; }

template <typename L, typename R>
static constexpr inline
true_ operator != (identity<L>, identity<R>)
noexcept { return {}; }

template <typename T>
static constexpr inline
false_ operator != (identity<T>, identity<T>)
noexcept { return {}; }

} // namespace mirror

#endif //include guard

