/**
 * @file mirror/integers.hpp
 * @brief Compile-time integers
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_INTEGERS_1105240825_HPP
#define MIRROR_INTEGERS_1105240825_HPP

#include <type_traits>
#include "identity.hpp"

namespace mirror {

template <typename Int, Int I>
using int_const = std::integral_constant<Int, I>;

template <bool B>
using bool_ = int_const<bool, B>;

using true_ = bool_<true>;
using false_ = bool_<false>;

template <char C>
using char_ = int_const<char, C>;

template <int I>
using int_ = int_const<int, I>;

template <unsigned U>
using unsigned_ = int_const<unsigned, U>;

template <typename Int>
constexpr auto value = Int::value;

} // namespace mirror

#endif //include guard

