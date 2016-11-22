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

namespace dazzle {

template <typename X>
struct wrapped;

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

} // namespace dazzle

#endif //include guard

