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
#include "int_const.hpp"
#include "envelope.hpp"

namespace dazzle {

template <>
struct wrapped<mirror::none>
 : sequence_ops<mirror::none>
{ };

constexpr envelope<mirror::none> none = {};

static constexpr inline
envelope<mirror::true_> operator == (
	envelope<mirror::none>,
	envelope<mirror::none>
) noexcept { return {}; }

template <typename X>
static constexpr inline
envelope<mirror::false_> operator == (envelope<mirror::none>, envelope<X>)
noexcept { return {}; }

template <typename X>
static constexpr inline
envelope<mirror::false_> operator == (envelope<X>, envelope<mirror::none>)
noexcept { return {}; }

static constexpr inline
envelope<mirror::false_> operator != (
	envelope<mirror::none>,
	envelope<mirror::none>
) noexcept { return {}; }

template <typename X>
static constexpr inline
envelope<mirror::true_> operator != (envelope<mirror::none>, envelope<X>)
noexcept { return {}; }

template <typename X>
static constexpr inline
envelope<mirror::true_> operator != (envelope<X>, envelope<mirror::none>)
noexcept { return {}; }

} // namespace dazzle

#endif //include guard

