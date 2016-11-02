/**
 * @file mirror/slice_before.hpp
 * @brief Implementation of the `slice_before` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_SLICE_BEFORE_1105240825_HPP
#define MIRROR_SLICE_BEFORE_1105240825_HPP

#include "split.hpp"

namespace mirror {

template <typename Range, typename SubR>
using slice_before = get_split_head<Range, SubR>;

} // namespace mirror

#endif //include guard

