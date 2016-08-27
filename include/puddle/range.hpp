/**
 * @file puddle/range.hpp
 * @brief Declaration of range
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef PUDDLE_RANGE_1105240825_HPP
#define PUDDLE_RANGE_1105240825_HPP

#include <mirror/range.hpp>

namespace puddle {

template <typename ... P>
constexpr mirror::range<P...> range = {};

constexpr mirror::empty_range empty_range = {};

} // namespace puddle

#endif //include guard

