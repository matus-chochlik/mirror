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
#include <mirror/get_front.hpp>
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

	static constexpr auto get_front(void) {
		return envelope<
			mirror::wrap_if_not_special<mirror::get_front<impl>>
		>{};
	}

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

} // namespace dazzle

#endif //include guard

