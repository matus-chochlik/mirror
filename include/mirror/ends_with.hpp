/**
 * @file mirror/ends_with.hpp
 * @brief Implementation of the `ends_with` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_ENDS_WITH_1105240825_HPP
#define MIRROR_ENDS_WITH_1105240825_HPP

#include "get_tail.hpp"
#include "get_size.hpp"
#include "equal.hpp"

namespace mirror {

template <typename Range, typename Suffix>
using ends_with = equal<get_tail<Range, get_size<Suffix>>, Suffix>;

} // namespace mirror

#endif //include guard

