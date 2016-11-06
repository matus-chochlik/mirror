/**
 * @file mirror/slice_after.hpp
 * @brief Implementation of the `slice_after` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_SLICE_AFTER_1105240825_HPP
#define MIRROR_SLICE_AFTER_1105240825_HPP

#include "split.hpp"
#include "skip.hpp"
#include "get_size.hpp"

namespace mirror {

template <typename Range, typename SubR>
using slice_after = skip<get_split_tail<Range, SubR>, get_size<SubR>>;

} // namespace mirror

#endif //include guard

