/**
 * @file dazzle/none.hpp
 * @brief Declaration of none type
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef DAZZLE_NONE_1105240825_HPP
#define DAZZLE_NONE_1105240825_HPP

#include <mirror/none.hpp>
#include "sequence_ops.hpp"

namespace dazzle {

template <typename X>
struct wrapped;

template <>
struct wrapped<mirror::none>
 : sequence_ops<mirror::none>
{ };

constexpr wrapped<mirror::none> none = {};

} // namespace dazzle

#endif //include guard

