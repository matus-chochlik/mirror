/**
 * @file dazzle/int_const.hpp
 * @brief Declaration of integral constants
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef DAZZLE_INT_CONST_1105240825_HPP
#define DAZZLE_INT_CONST_1105240825_HPP

#include <mirror/int_const.hpp>
#include <mirror/value.hpp>
#include "envelope.hpp"

namespace dazzle {

template <typename Int, Int I>
struct wrapped<mirror::int_const<Int, I>>
{
	using impl = mirror::int_const<Int, I>;

	static constexpr auto value(void) {
		return mirror::value<impl>;
	}

	constexpr operator Int (void) const {
		return I;
	}
};

template <typename Int1, Int1 I1, typename Int2, Int2 I2>
static constexpr inline
wrapped<mirror::int_const<decltype(I1 == I2), (I1 == I2)>> operator == (
	wrapped<mirror::int_const<Int1, I1>>,
	wrapped<mirror::int_const<Int2, I2>>
) noexcept { return {}; }

template <typename Int1, Int1 I1, typename Int2, Int2 I2>
static constexpr inline
wrapped<mirror::int_const<decltype(I1 != I2), (I1 != I2)>> operator != (
	wrapped<mirror::int_const<Int1, I1>>,
	wrapped<mirror::int_const<Int2, I2>>
) noexcept { return {}; }

template <typename Int1, Int1 I1, typename Int2, Int2 I2>
static constexpr inline
wrapped<mirror::int_const<decltype(I1 <  I2), (I1 <  I2)>> operator <  (
	wrapped<mirror::int_const<Int1, I1>>,
	wrapped<mirror::int_const<Int2, I2>>
) noexcept { return {}; }

template <typename Int1, Int1 I1, typename Int2, Int2 I2>
static constexpr inline
wrapped<mirror::int_const<decltype(I1 <= I2), (I1 <= I2)>> operator <= (
	wrapped<mirror::int_const<Int1, I1>>,
	wrapped<mirror::int_const<Int2, I2>>
) noexcept { return {}; }

template <typename Int1, Int1 I1, typename Int2, Int2 I2>
static constexpr inline
wrapped<mirror::int_const<decltype(I1 >  I2), (I1 >  I2)>> operator >  (
	wrapped<mirror::int_const<Int1, I1>>,
	wrapped<mirror::int_const<Int2, I2>>
) noexcept { return {}; }

template <typename Int1, Int1 I1, typename Int2, Int2 I2>
static constexpr inline
wrapped<mirror::int_const<decltype(I1 >= I2), (I1 >= I2)>> operator >= (
	wrapped<mirror::int_const<Int1, I1>>,
	wrapped<mirror::int_const<Int2, I2>>
) noexcept { return {}; }


template <bool B>
constexpr envelope<mirror::bool_<B>> bool_ = {};

template <char C>
constexpr envelope<mirror::char_<C>> char_ = {};

template <int I>
constexpr envelope<mirror::int_<I>> int_ = {};

template <unsigned U>
constexpr envelope<mirror::unsigned_<U>> unsigned_ = {};

template <std::size_t S>
constexpr envelope<mirror::size_t_<S>> size_t_ = {};

} // namespace dazzle

#endif //include guard

