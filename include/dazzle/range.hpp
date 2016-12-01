/**
 * @file dazzle/range.hpp
 * @brief Declaration of compile-time ranges
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef DAZZLE_RANGE_1105240825_HPP
#define DAZZLE_RANGE_1105240825_HPP

#include <mirror/range.hpp>
#include "int_const.hpp"
#include "sequence_ops.hpp"

namespace dazzle {

template <typename X>
struct wrapped;

template <typename ... P>
struct wrapped<mirror::range<P...>>
 : sequence_ops<mirror::range<P...>>
{ };

template <typename ... P>
static constexpr inline
envelope<mirror::true_> operator == (
	wrapped<mirror::range<P...>>,
	wrapped<mirror::range<P...>>
) noexcept { return {}; }

template <typename ... P, typename ... R>
static constexpr inline
envelope<mirror::false_> operator == (
	wrapped<mirror::range<P...>>,
	wrapped<mirror::range<R...>>
) noexcept { return {}; }

template <typename ... P>
static constexpr inline
envelope<mirror::false_> operator != (
	wrapped<mirror::range<P...>>,
	wrapped<mirror::range<P...>>
) noexcept { return {}; }

template <typename ... P, typename ... R>
static constexpr inline
envelope<mirror::true_> operator != (
	wrapped<mirror::range<P...>>,
	wrapped<mirror::range<R...>>
) noexcept { return {}; }

template <typename ... P>
constexpr envelope<mirror::range<P...>> range = {};

constexpr envelope<mirror::empty_range> empty_range = {};

template <typename ... P>
static constexpr inline
envelope<mirror::range<P...>> make_range(envelope<P>...)
noexcept { return {}; }

} // namespace dazzle

#endif //include guard

