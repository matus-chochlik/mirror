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

template <bool B>
using bool_ = std::integral_constant<bool, B>;

using true_ = bool_<true>;
using false_ = bool_<false>;

template <int I>
using int_ = std::integral_constant<int, I>;

template <unsigned U>
using unsigned_ = std::integral_constant<unsigned, U>;

} // namespace mirror

#endif //include guard

