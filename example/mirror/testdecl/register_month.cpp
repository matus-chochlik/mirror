/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#include "month.hpp"
#include <mirror/registry.hpp>

namespace example {

void register_month(mirror::metadata_registry& r) {
    r.add(mirror(month));
}

} // namespace example

