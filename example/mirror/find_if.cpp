/// @example find_if
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include <iostream>
#include <mirror/primitives.hpp>

struct mystruct {
    std::string s{"str"};
    float f{1.2F};
    int i{345};
    bool b{false};
};

int main() {
    mystruct x;

    const auto found = find_if(get_data_members(mirror(mystruct)), [](auto me) {
        return has_name(me, "f");
    });
    if(reflects_variable(found)) {
        std::cout << get_value(found, x) << std::endl;
    }
    return 0;
}
