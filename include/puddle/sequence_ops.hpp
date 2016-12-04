/**
 * @file puddle/sequence_ops.hpp
 * @brief Implementation of sequence, range, string operations
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef PUDDLE_SEQUENCE_OPS_1105240825_HPP
#define PUDDLE_SEQUENCE_OPS_1105240825_HPP

#include <mirror/unpack.hpp>
#include <mirror/is_empty.hpp>
#include <mirror/get_empty.hpp>
#include <mirror/get_size.hpp>
#include <mirror/get_front.hpp>
#include <mirror/get_head.hpp>
#include <mirror/get_tail.hpp>
#include <mirror/skip.hpp>
#include <mirror/slice.hpp>
#include <mirror/slice_before.hpp>
#include <mirror/slice_after.hpp>
#include <mirror/starts_with.hpp>
#include <mirror/ends_with.hpp>
#include <mirror/push_back.hpp>
#include <mirror/push_front.hpp>
#include <mirror/pop_front.hpp>
#include <mirror/concat.hpp>
#include <mirror/join.hpp>
#include <mirror/contains.hpp>
#include <mirror/get_element.hpp>
#include <mirror/for_each.hpp>
#include <mirror/apply_on.hpp>
#include <mirror/wrap.hpp>
#include <mirror/unwrap.hpp>
#include <mirror/foldl.hpp>
#include <mirror/transform.hpp>
#include <puddle/enable_if.hpp>

namespace puddle {

template <typename X, typename = enable_if_any_opt_sequence<X>>
static constexpr inline
auto is_empty(X)
noexcept {
	return mirror::is_empty<X>{};
}

template <typename X, typename = enable_if_opt_eager_sequence<X>>
static constexpr inline
auto get_empty(X)
noexcept {
	return mirror::get_empty<X>{};
}

template <typename X, typename = enable_if_any_opt_sequence<X>>
static constexpr inline
auto get_size(X)
noexcept {
	return mirror::get_size<X>{};
}

template <typename X, typename = enable_if_any_opt_sequence<X>>
static constexpr inline
auto size(X)
noexcept {
	return mirror::size<X>{};
}

template <typename X, typename = enable_if_any_opt_sequence<X>>
static constexpr inline
auto get_front(X)
noexcept {
	return mirror::wrap_if_not_special<mirror::get_front<X>>{};
}

template <
	typename X,
	typename I,
	typename = enable_if_any_opt_sequence<X>,
	typename = enable_if_int_const<I>
> static constexpr inline
auto get_head(X, I)
noexcept {
	return mirror::get_head<X, I>{};
}

template <
	typename X,
	typename I,
	typename = enable_if_any_opt_sequence<X>,
	typename = enable_if_int_const<I>
> static constexpr inline
auto get_tail(X, I)
noexcept {
	return mirror::get_tail<X, I>{};
}

template <
	typename X,
	typename I,
	typename = enable_if_any_opt_sequence<X>,
	typename = enable_if_int_const<I>
> static constexpr inline
auto skip(X, I)
noexcept {
	return mirror::skip<X, I>{};
}

template <
	typename X,
	typename I,
	typename L,
	typename = enable_if_any_opt_sequence<X>,
	typename = enable_if_int_const<I>,
	typename = enable_if_int_const<L>
> static constexpr inline
auto slice(X, I, L)
noexcept {
	return mirror::slice<X, I, L>{};
}

template <
	typename X,
	typename S,
	typename = enable_if_any_opt_sequence<X>
> static constexpr inline
auto slice_before(X, S)
noexcept {
	return mirror::slice_before<X, S>{};
}

template <
	typename X,
	typename S,
	typename = enable_if_any_opt_sequence<X>
> static constexpr inline
auto slice_after(X, S)
noexcept {
	return mirror::slice_after<X, S>{};
}

template <
	typename X,
	typename Y,
	typename = enable_if_any_opt_sequence<X>,
	typename = enable_if_any_opt_sequence<Y>
> static constexpr inline
auto starts_with(X, Y)
noexcept {
	return mirror::starts_with<X, Y>{};
}

template <
	typename X,
	typename Y,
	typename = enable_if_any_opt_sequence<X>,
	typename = enable_if_any_opt_sequence<Y>
> static constexpr inline
auto ends_with(X, Y)
noexcept {
	return mirror::ends_with<X, Y>{};
}

template <
	typename X,
	typename E,
	typename = enable_if_opt_eager_sequence<X>
> static constexpr inline
auto push_back(X, E)
noexcept {
	return mirror::push_back<X, mirror::unwrap_identity<E>>{};
}

template <
	typename X,
	typename E,
	typename = enable_if_opt_eager_sequence<X>
> static constexpr inline
auto push_front(X, E)
noexcept {
	return mirror::push_front<X, mirror::unwrap_identity<E>>{};
}

template <
	typename X,
	typename = enable_if_opt_eager_sequence<X>
> static constexpr inline
auto pop_front(X)
noexcept {
	return mirror::pop_front<X>{};
}

template <typename ... X>
static constexpr inline
auto concat(X...)
noexcept {
	return mirror::concat<X...>{};
}

template <typename S, typename ... X>
static constexpr inline
auto join(S, X...)
noexcept {
	return mirror::join<S, X...>{};
}

template <
	typename X,
	typename S,
	typename = enable_if_any_opt_sequence<X>
> static constexpr inline
auto contains(X, S)
noexcept {
	return mirror::contains<X, S>{};
}

template <
	template <class, class> class T, typename X, typename I,
	typename = enable_if_any_opt_sequence<X>
> static constexpr inline
auto foldl(X, I)
noexcept {
	return mirror::foldl<T, X, I>{};
}

template <
	template <class> class T, typename X,
	typename = enable_if_any_opt_sequence<X>
> static constexpr inline
auto transform(X)
noexcept {
	return mirror::transform<T, X>{};
}

template <
	typename X, typename I,
	typename = enable_if_any_opt_sequence<X>,
	typename = enable_if_int_const<I>
> static constexpr inline
auto get_element(X, I)
noexcept {
	return mirror::wrap_if_not_special<mirror::get_element<X, I>>{};
}

template <typename X, typename = enable_if_opt_metaobject_sequence<X>>
static constexpr inline
auto unpack(X)
noexcept {
	return mirror::unpack<X>{};
}

template <typename Rng, typename Func>
static constexpr inline
Func for_each(Rng, Func func) {
	return mirror::for_each<Rng>::apply(func);
}

template <typename Rng, typename Func, typename SepFunc>
static constexpr inline
Func for_each(Rng, Func func, SepFunc sep_func) {
	return mirror::for_each<Rng>::apply(func, sep_func);
}

template <typename Rng, typename Func>
static constexpr inline
auto apply_on(Rng, Func func) {
	return mirror::apply_on<Rng>::apply(func);
}

} // namespace puddle

#endif //include guard

