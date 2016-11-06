/**
 * @file mirror/int_ops.hpp
 * @brief Compile-time integer operations
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_INT_OPS_1105240825_HPP
#define MIRROR_INT_OPS_1105240825_HPP

#include "int_const.hpp"
#include <iosfwd>

namespace mirror {
namespace cexpr {

template <bool BL, bool BR>
static constexpr inline
bool_<BL && BR> operator && (bool_<BL>, bool_<BR>)
noexcept { return {}; }

template <bool BL, bool BR>
static constexpr inline
bool_<BL || BR> operator || (bool_<BL>, bool_<BR>)
noexcept { return {}; }

template <typename Int, Int L, Int R>
static constexpr inline
int_const<Int, (L == R)> operator == (int_const<Int, L>, int_const<Int, R>)
noexcept { return {}; }

template <typename Int, Int L, Int R>
static constexpr inline
int_const<Int, (L != R)> operator != (int_const<Int, L>, int_const<Int, R>)
noexcept { return {}; }

template <typename Int, Int L, Int R>
static constexpr inline
int_const<Int, (L <= R)> operator <= (int_const<Int, L>, int_const<Int, R>)
noexcept { return {}; }

template <typename Int, Int L, Int R>
static constexpr inline
int_const<Int, (L <  R)> operator <  (int_const<Int, L>, int_const<Int, R>)
noexcept { return {}; }

template <typename Int, Int L, Int R>
static constexpr inline
int_const<Int, (L >= R)> operator >= (int_const<Int, L>, int_const<Int, R>)
noexcept { return {}; }

template <typename Int, Int L, Int R>
static constexpr inline
int_const<Int, (L >  R)> operator >  (int_const<Int, L>, int_const<Int, R>)
noexcept { return {}; }

template <typename Int, Int L, Int R>
static constexpr inline
int_const<Int, (L + R)> operator + (int_const<Int, L>, int_const<Int, R>)
noexcept { return {}; }

template <typename Int, Int L, Int R>
static constexpr inline
int_const<Int, (L - R)> operator - (int_const<Int, L>, int_const<Int, R>)
noexcept { return {}; }

template <typename Int, Int L, Int R>
static constexpr inline
int_const<Int, (L * R)> operator * (int_const<Int, L>, int_const<Int, R>)
noexcept { return {}; }

template <typename Int, Int L, Int R>
static constexpr inline
int_const<Int, (L / R)> operator / (int_const<Int, L>, int_const<Int, R>)
noexcept { return {}; }

template <typename Int, Int I>
static inline
std::ostream& operator << (std::ostream& out, int_const<Int, I>)
{
	return out << I;
}

} // namespace cexpr
} // namespace mirror

#endif //include guard

