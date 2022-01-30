/// @example mirror/hello_enums.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include <mirror/placeholder.hpp>
#include <mirror/sequence.hpp>
#include <iostream>

enum class greeting { hello, world, of, reflection };

int main() {

    std::cout << join(
                   get_enumerators(mirror(greeting)),
                   to_string(get_name(mirror::_1)),
                   std::string(" "))
              << "!\n";

    return 0;
}
