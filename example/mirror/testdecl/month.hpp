/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_TESTDECL_MONTH_HPP
#define MIRROR_TESTDECL_MONTH_HPP

#include <mirror/registry_fwd.hpp>

namespace example {

enum class month : int {
    january = 1,
    february,
    march,
    april,
    may,
    june,
    july,
    august,
    september,
    october,
    november,
    december
};

void register_month(mirror::metadata_registry&);

} // namespace example

#endif
