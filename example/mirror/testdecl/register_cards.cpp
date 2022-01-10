/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#include "cards.hpp"
#include <mirror/registry.hpp>

namespace example {

void register_cards(mirror::metadata_registry& r) {
    r.add(mirror(cards));
    r.add(mirror(cards::rank));
    r.add(mirror(cards::suit));
    r.add(mirror(cards::card));
    r.add(mirror(cards::deck));
    r.add(mirror(cards::player));
    r.add(mirror(cards::dealer));
    r.add(mirror(cards::game));
}

} // namespace example

