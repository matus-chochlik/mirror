/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include <iostream>
#include <mirror/meta.hpp>
#include <mirror/testdecl.hpp>
#include <mirror/utils.hpp>
#include <utility>

namespace mirror {

template <std::experimental::meta::info MO>
consteval auto constructors_of() {
    return std::experimental::meta::members_of(
      ^test::point, std::experimental::meta::is_constructor);
}

template <std::experimental::meta::info... MO>
struct unpacked_range {
    constexpr static auto count = sizeof...(MO);
};

template <std::experimental::meta::info MO, std::size_t... I>
consteval auto do_unpack_range(std::index_sequence<I...>) {
    return unpacked_range<*advance(constructors_of<MO>().begin(), I)...>{};
}

template <std::experimental::meta::info MO>
consteval auto unpack_range() {
    return do_unpack_range<MO>(
      std::make_index_sequence<size(constructors_of<MO>())>{});
}

} // namespace mirror

int main() {
    std::cout << mirror::unpack_range<^test::point>().count << std::endl;
    return 0;
}
