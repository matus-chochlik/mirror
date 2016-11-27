/**
 * @file mirror/get_head.hpp
 * @brief Implementation of the `get_head` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_GET_HEAD_1105240825_HPP
#define MIRROR_GET_HEAD_1105240825_HPP

#include "or.hpp"
#include "equal.hpp"
#include "minus.hpp"
#include "is_empty.hpp"
#include "get_empty.hpp"
#include "get_front.hpp"
#include "pop_front.hpp"
#include "push_back.hpp"

namespace mirror {
namespace _aux {

template <
	typename Count,
	typename Done,
	typename Head,
	typename Tail
> struct op_get_head;

template <typename Count, typename Head, typename Tail>
struct op_get_head<Count, true_, Head, Tail>
 : Head
{ };

template <typename Count, typename Head, typename Tail>
struct op_get_head<Count, false_, Head, Tail>
 : op_get_head<
	minus<Count, size_t_<1>>, 
	or_<is_empty<Tail>, equal<Count, size_t_<1>>>,
	push_back<Head, get_front<Tail>>,
	pop_front<Tail>
> { };

} // namespace _aux

template <typename X, typename Length>
using get_head = eval<_aux::op_get_head<
	Length,
	or_<is_empty<X>, equal<Length, size_t_<0>>>,
	get_empty<X>, X
>>; 
} // namespace mirror

#endif //include guard

