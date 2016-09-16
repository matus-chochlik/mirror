/**
 * @file mirror/reflection.hpp
 * @brief Reflection operators
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_REFLECTION_1105240825_HPP
#define MIRROR_REFLECTION_1105240825_HPP

#include "metaobject.hpp"

#define MIRRORED(...) ::mirror::metaobject<reflexpr(__VA_ARGS__)>

#endif //include guard

