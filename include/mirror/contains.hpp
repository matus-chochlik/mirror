/**
 * @file mirror/contains.hpp
 * @brief Implementation of the `contains` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_CONTAINS_1105240825_HPP
#define MIRROR_CONTAINS_1105240825_HPP

#include "split.hpp"
#include "is_empty.hpp"
#include "not.hpp"
#include "or.hpp"

namespace mirror {

template <typename Range, typename SubR>
using contains = or_<
	is_empty<SubR>,
	not_<is_empty<get_split_tail<Range, SubR>>>
>;

} // namespace mirror

#endif //include guard

