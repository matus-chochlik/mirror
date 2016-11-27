/**
 * @file mirror/get_tail.hpp
 * @brief Implementation of the `get_tail` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_GET_TAIL_1105240825_HPP
#define MIRROR_GET_TAIL_1105240825_HPP

#include "or.hpp"
#include "less.hpp"
#include "equal.hpp"
#include "minus.hpp"
#include "get_size.hpp"
#include "is_empty.hpp"
#include "get_front.hpp"
#include "pop_front.hpp"
#include "push_back.hpp"

namespace mirror {
namespace _aux {

template <
	typename Count,
	typename Done,
	typename Tail
> struct op_get_tail;

template <typename Count, typename Tail>
struct op_get_tail<Count, true_, Tail>
 : Tail
{ };

template <typename Count, typename Tail>
struct op_get_tail<Count, false_, Tail>
 : op_get_tail<
	minus<Count, size_t_<1>>, 
	or_<is_empty<Tail>, equal<Count, size_t_<1>>>,
	pop_front<Tail>
> { };

} // namespace _aux

template <typename X, typename Length>
using get_tail = eval<_aux::op_get_tail<
	minus<get_size<X>, Length>,
	less_equal<get_size<X>, Length>,
	X
>>; 
} // namespace mirror

#endif //include guard

