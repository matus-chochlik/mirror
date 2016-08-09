/**
 * @file puddle/type.hpp
 * @brief Implementation of the `type` wrapper
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef PUDDLE_TYPE_1105240825_HPP
#define PUDDLE_TYPE_1105240825_HPP

#include <mirror/identity.hpp>
#include <mirror/type_ops.hpp>

namespace puddle {

template <typename X>
constexpr mirror::identity<X> type = {};

} // namespace puddle

#endif //include guard

