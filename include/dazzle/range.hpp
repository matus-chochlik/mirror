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
#include <mirror/is_empty.hpp>
#include <mirror/get_size.hpp>
#include <mirror/for_each.hpp>
#include <mirror/apply_on.hpp>
#include "int_const.hpp"
#include "envelope.hpp"
#include "wrap.hpp"

namespace dazzle {

template <typename X>
struct wrapped;

template <typename ... P>
struct wrapped<mirror::range<P...>>
{
	using impl = mirror::range<P...>;

	DAZZLE_MEMFN_ENVELOP_MIRROR_OP(is_empty)
	DAZZLE_MEMFN_ENVELOP_MIRROR_OP(empty)
	DAZZLE_MEMFN_ENVELOP_MIRROR_OP(get_size)
	DAZZLE_MEMFN_ENVELOP_MIRROR_OP(size)

	template <typename Func>
	static constexpr auto for_each(Func func) {
		return mirror::for_each<impl>::apply(wrap_args_of(func));
	}

	template <typename Func, typename Sep>
	static constexpr auto for_each(Func func, Sep sep) {
		return mirror::for_each<impl>::apply(wrap_args_of(func), sep);
	}

	template <typename Func>
	static constexpr auto apply(Func func) {
		return mirror::apply_on<impl>::apply(wrap_args_of(func));
	}
};

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

} // namespace dazzle

#endif //include guard

