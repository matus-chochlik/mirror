/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[puddle_range_1
template <typename ... P>
constexpr __mirror_range<P...> range;

constexpr __mirror_empty_range empty_range;
//]

