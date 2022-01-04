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
    r.add(mirror(card_rank));
    r.add(mirror(card_suit));
    r.add(mirror(playing_card));
    r.add(mirror(card_deck));
}

} // namespace example

