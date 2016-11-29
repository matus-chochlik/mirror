/**
 * @file dazzle/sequence_ops.hpp
 * @brief Declaration of sequence operation wrappers
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef DAZZLE_SEQUENCE_OPS_1105240825_HPP
#define DAZZLE_SEQUENCE_OPS_1105240825_HPP

#include <mirror/is_empty.hpp>
#include <mirror/get_size.hpp>
#include <mirror/get_element.hpp>
#include <mirror/get_front.hpp>
#include <mirror/get_head.hpp>
#include <mirror/get_tail.hpp>
#include <mirror/skip.hpp>
#include <mirror/slice_before.hpp>
#include <mirror/slice_after.hpp>
#include <mirror/starts_with.hpp>
#include <mirror/ends_with.hpp>
#include <mirror/contains.hpp>

#include <mirror/join.hpp>
#include <mirror/transform.hpp>

#include <mirror/for_each.hpp>
#include <mirror/apply_on.hpp>
#include "envelope.hpp"

namespace dazzle {

template <typename X>
struct sequence_ops
{
	using impl = X;

	DAZZLE_MEMFN_ENVELOP_MIRROR_OP(is_empty)
	DAZZLE_MEMFN_ENVELOP_MIRROR_OP(empty)
	DAZZLE_MEMFN_ENVELOP_MIRROR_OP(get_size)
	DAZZLE_MEMFN_ENVELOP_MIRROR_OP(size)

	template <typename W>
	static constexpr
	auto get_element(envelope<W>)
	noexcept {
		return envelope<mirror::wrap_if_not_special<
			mirror::get_element<impl, W>
		>>{};
	}

	static constexpr
	auto get_front(void)
	noexcept {
		return envelope<mirror::wrap_if_not_special<
			mirror::get_front<impl>
		>>{};
	}

	DAZZLE_MEMFN_ENVELOP_MIRROR_OP_1(get_head)
	DAZZLE_MEMFN_ENVELOP_MIRROR_OP_1(get_tail)
	DAZZLE_MEMFN_ENVELOP_MIRROR_OP_1(skip)
	DAZZLE_MEMFN_ENVELOP_MIRROR_OP_1(slice_before)
	DAZZLE_MEMFN_ENVELOP_MIRROR_OP_1(slice_after)
	DAZZLE_MEMFN_ENVELOP_MIRROR_OP_1(starts_with)
	DAZZLE_MEMFN_ENVELOP_MIRROR_OP_1(ends_with)
	DAZZLE_MEMFN_ENVELOP_MIRROR_OP_1(contains)

	template <typename ... P>
	static constexpr
	auto join(envelope<P>...)
	noexcept {
		return envelope<mirror::join<impl, P...>>{};
	}

	template <template <class> class Transf>
	static constexpr
	auto transform(void)
	noexcept {
		return envelope<mirror::transform<Transf, impl>>{};
	}

	template <typename Func>
	static constexpr
	auto for_each(Func func) {
		return mirror::for_each<impl>::apply(wrap_args_of(func));
	}

	template <typename Func, typename Sep>
	static constexpr
	auto for_each(Func func, Sep sep) {
		return mirror::for_each<impl>::apply(wrap_args_of(func), sep);
	}

	template <typename Func>
	static constexpr
	auto apply(Func func) {
		return mirror::apply_on<impl>::apply(wrap_args_of(func));
	}
};

} // namespace dazzle

#endif //include guard

