/// @example mirror/print_struct.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include <iostream>
#include <mirror/primitives.hpp>

template <typename S>
void print_struct(const S& x) {
    std::cout << get_name(get_aliased(mirror(S)));
    std::cout << '(';
    for_each_info(
      get_data_members(get_aliased(mirror(S))), [&](auto mo, auto info) {
          if(!info.is_first()) {
              std::cout << ", ";
          }
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
