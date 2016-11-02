/**
 * @file mirror/split.hpp
 * @brief Implementation of the `split` operations
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_SPLIT_1105240825_HPP
#define MIRROR_SPLIT_1105240825_HPP

#include "push_back.hpp"
#include "pop_front.hpp"
#include "get_front.hpp"
#include "starts_with.hpp"
#include "to_container.hpp"
#include "get_empty.hpp"
#include "is_empty.hpp"
#include "or.hpp"

namespace mirror {
namespace _aux {

template <typename H, typename T, typename Srch, typename Done>
struct op_split;

template <typename H, typename T, typename Srch>
struct op_split<H, T, Srch, true_>
{
	using head = H;
	using tail = T;
};

template <typename H, typename T, typename Srch>
struct op_split<H, T, Srch, false_>
 : op_split<
	push_back<H, get_front<T>>,
	pop_front<T>,
	Srch,
	or_<is_empty<T>, starts_with<pop_front<T>, Srch>>
> { };

} // namespace _aux

template <typename X, typename SX>
using get_split_head = typename _aux::op_split<
	get_empty<X>, X, to_container<SX>,
	or_<is_empty<X>, starts_with<X, SX>>
>::head; 

template <typename X, typename SX>
using get_split_tail = typename _aux::op_split<
	get_empty<X>, X, to_container<SX>,
	or_<is_empty<X>, starts_with<X, SX>>
>::tail; 

} // namespace mirror

#endif //include guard

