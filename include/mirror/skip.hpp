/**
 * @file mirror/skip.hpp
 * @brief Implementation of the `skip` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_SKIP_1105240825_HPP
#define MIRROR_SKIP_1105240825_HPP

#include "get_tail.hpp"
#include "get_size.hpp"
#include "minus.hpp"
#include "conditional.hpp"

namespace mirror {

template <typename Range, typename Count>
using skip = get_tail<
	Range,
	lazy_conditional<
		less<Count, get_size<Range>>,
		minus<get_size<Range>, Count>,
		size_t_<0>
	>
>;

} // namespace mirror

#endif //include guard

