/**
 * @file puddle/int_const.hpp
 * @brief Declaration of integral constants
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef PUDDLE_INT_CONST_1105240825_HPP
#define PUDDLE_INT_CONST_1105240825_HPP

#include <mirror/int_const.hpp>
#include <mirror/int_ops.hpp>

namespace puddle {

template <typename Int, Int I>
constexpr mirror::int_const<Int, I> int_const = {};

template <bool B>
constexpr mirror::bool_<B> bool_ = {};

constexpr mirror::true_ true_ = {};
constexpr mirror::false_ false_ = {};

template <char C>
constexpr mirror::char_<C> char_ = {};

template <int I>
constexpr mirror::int_<I> int_ = {};

template <unsigned U>
constexpr mirror::unsigned_<U> unsigned_ = {};

using namespace mirror::cexpr;

} // namespace puddle

#endif //include guard

