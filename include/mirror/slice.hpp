/**
 * @file mirror/slice.hpp
 * @brief Implementation of the `slice` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_SLICE_1105240825_HPP
#define MIRROR_SLICE_1105240825_HPP

#include "get_head.hpp"
#include "get_size.hpp"
#include "skip.hpp"

namespace mirror {

template <typename Range, typename Start, typename Length>
using slice = get_head<skip<Range, Start>, Length>;

} // namespace mirror

#endif //include guard

