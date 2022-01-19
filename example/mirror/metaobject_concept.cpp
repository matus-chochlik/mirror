/// @example mirror/metaobject_concept.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include <mirror/primitives.hpp>
#include <iostream>

int main() {
    const auto meta_int = mirror(int);
    static_assert(mirror::metaobject<decltype(meta_int)>);

    return 0;
}
