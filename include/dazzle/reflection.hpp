/**
 * @file dazzle/reflection.hpp
 * @brief Declaration of the reflection operator
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef DAZZLE_REFLECTION_1105240825_HPP
#define DAZZLE_REFLECTION_1105240825_HPP

#include <mirror/reflection.hpp>

namespace dazzle {

template <typename X>
struct envelope;

#define DAZZLED(...) dazzle::envelope<MIRRORED(__VA_ARGS__)>{}

} // namespace dazzle

#endif //include guard

