/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_UTILS_HPP
#define MIRROR_UTILS_HPP

namespace mirror {

template <typename Iterator>
consteval auto advance(Iterator it, size_t n) {
    while(n-- > 0) {
        ++it;
    }
    return it;
}

} // namespace mirror

#endif // MIRROR_UTILS_HPP
