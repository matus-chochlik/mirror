/// @example print_struct
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include <iostream>
#include <mirror/enum_utils.hpp>

template <typename S>
void print_struct(const S& x) {
    std::cout << get_name(get_aliased(mirror(S)));
    std::cout << '(';
    bool first = true;
    for_each(get_data_members(get_aliased(mirror(S))), [&](auto mo) {
        if(first)
            first = false;
        else
            std::cout << ", ";
        std::cout << get_name(mo) << ": " << get_value(mo, x);
    });
    std::cout << ')' << std::endl;
}

struct mystruct {
    std::string s{"str"};
    float f{1.2F};
    int i{345};
    bool b{false};
};

int main() {
    mystruct x;
    print_struct(x);
    return 0;
}
