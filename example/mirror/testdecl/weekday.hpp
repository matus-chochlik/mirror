/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_TESTDECL_WEEKDAY_HPP
#define MIRROR_TESTDECL_WEEKDAY_HPP

#include <cstdint>

namespace example {

enum class weekday : int {
    monday = 1,
    tuesday,
    wednesday,
    thursday,
    friday,
    saturday,
    sunday
};

enum class weekday_bit : std::uint8_t {
    monday = 0x1,
    tuesday = 0x2,
    wednesday = 0x4,
    thursday = 0x8,
    friday = 0x10,
    saturday = 0x20,
    sunday = 0x40
};

} // namespace example

#endif
