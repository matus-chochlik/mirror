/**
 * @file mirror/none_ops.hpp
 * @brief Compile-time operations on none
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_NONE_OPS_1105240825_HPP
#define MIRROR_NONE_OPS_1105240825_HPP

#include "int_const.hpp"
#include <iosfwd>

namespace mirror {

static constexpr inline
true_ operator == (none, none)
noexcept { return {}; }

template <typename T>
static constexpr inline
false_ operator == (none, T)
noexcept { return {}; }

template <typename T>
static constexpr inline
false_ operator == (T, none)
noexcept { return {}; }

static constexpr inline
false_ operator != (none, none)
noexcept { return {}; }

template <typename T>
static constexpr inline
true_ operator != (none, T)
noexcept { return {}; }

template <typename T>
static constexpr inline
true_ operator != (T, none)
noexcept { return {}; }

static inline
std::ostream& operator << (std::ostream& out, none)
{
	return out;
}

} // namespace mirror

#endif //include guard

