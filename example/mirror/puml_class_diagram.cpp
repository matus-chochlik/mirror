/// @example mirror/puml_class_diagram.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#include "testdecl/cards.hpp"
#include <mirror/puml.hpp>
#include <mirror/registry.hpp>
#include <iostream>

int main() {
    mirror::metadata_registry r;
    example::register_cards(r);
    const auto& md_cards = r.find(mirror(example::cards));

    mirror::puml_class_diagram puml;
    puml.generate(std::cout, r.filtered([&](const auto& md) {
        return md.scope() == md_cards;
    }));

    return 0;
}
