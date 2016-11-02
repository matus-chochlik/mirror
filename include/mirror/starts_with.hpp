/**
 * @file mirror/starts_with.hpp
 * @brief Implementation of the `starts_with` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_STARTS_WITH_1105240825_HPP
#define MIRROR_STARTS_WITH_1105240825_HPP

#include "get_head.hpp"
#include "get_size.hpp"
#include "equal.hpp"

namespace mirror {

template <typename Range, typename Prefix>
using starts_with = equal<
	get_head<Range, get_size<Prefix>>,
	to_container<Prefix>
>;

} // namespace mirror

#endif //include guard

