/**
 * @file puddle/hash.hpp
 * @brief Implementation of the `hash` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef PUDDLE_HASH_1105240825_HPP
#define PUDDLE_HASH_1105240825_HPP

#include <mirror/hash.hpp>

namespace puddle {

template <typename ... X>
static constexpr inline
auto hash(X...)
noexcept
{
	return mirror::hash<X...>{};
}

} // namespace puddle

#endif //include guard

