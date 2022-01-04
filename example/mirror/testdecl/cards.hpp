/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_TESTDECL_CARDS_HPP
#define MIRROR_TESTDECL_CARDS_HPP

#include <mirror/registry_fwd.hpp>
#include <set>
#include <tuple>

namespace example {

enum class card_rank {
    ace = 1,
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine,
    ten,
    jack,
    queen,
    king
};

enum class card_suit { hearts, spades, diamonds, clubs };

struct playing_card {
    const card_rank rank;
    const card_suit suit;

    constexpr playing_card(card_rank r, card_suit s) noexcept
      : rank{r}
      , suit{s} {}

    friend auto operator==(const playing_card l, const playing_card r) noexcept {
        return std::make_tuple(l.rank, l.suit) ==
               std::make_tuple(r.rank, r.suit);
    }

    friend auto operator!=(const playing_card l, const playing_card r) noexcept {
        return std::make_tuple(l.rank, l.suit) !=
               std::make_tuple(r.rank, r.suit);
    }

    friend auto operator<(const playing_card l, const playing_card r) noexcept {
        return std::make_tuple(l.rank, l.suit) <
               std::make_tuple(r.rank, r.suit);
    }
};

class card_deck {
private:
    std::set<playing_card> _cards{{card_rank::ace, card_suit::hearts},
                                  {card_rank::ace, card_suit::spades},
                                  {card_rank::ace, card_suit::diamonds},
                                  {card_rank::ace, card_suit::clubs},
                                  {card_rank::two, card_suit::hearts},
                                  {card_rank::two, card_suit::spades},
                                  {card_rank::two, card_suit::diamonds},
                                  {card_rank::two, card_suit::clubs},
                                  {card_rank::three, card_suit::hearts},
                                  {card_rank::three, card_suit::spades},
                                  {card_rank::three, card_suit::diamonds},
                                  {card_rank::three, card_suit::clubs},
                                  {card_rank::four, card_suit::hearts},
                                  {card_rank::four, card_suit::spades},
                                  {card_rank::four, card_suit::diamonds},
                                  {card_rank::four, card_suit::clubs},
                                  {card_rank::five, card_suit::hearts},
                                  {card_rank::five, card_suit::spades},
                                  {card_rank::five, card_suit::diamonds},
                                  {card_rank::five, card_suit::clubs},
                                  {card_rank::six, card_suit::hearts},
                                  {card_rank::six, card_suit::spades},
                                  {card_rank::six, card_suit::diamonds},
                                  {card_rank::six, card_suit::clubs},
                                  {card_rank::seven, card_suit::hearts},
                                  {card_rank::seven, card_suit::spades},
                                  {card_rank::seven, card_suit::diamonds},
                                  {card_rank::seven, card_suit::clubs},
                                  {card_rank::eight, card_suit::hearts},
                                  {card_rank::eight, card_suit::spades},
                                  {card_rank::eight, card_suit::diamonds},
                                  {card_rank::eight, card_suit::clubs},
                                  {card_rank::nine, card_suit::hearts},
                                  {card_rank::nine, card_suit::spades},
                                  {card_rank::nine, card_suit::diamonds},
                                  {card_rank::nine, card_suit::clubs},
                                  {card_rank::ten, card_suit::hearts},
                                  {card_rank::ten, card_suit::spades},
                                  {card_rank::ten, card_suit::diamonds},
                                  {card_rank::ten, card_suit::clubs},
                                  {card_rank::jack, card_suit::hearts},
                                  {card_rank::jack, card_suit::spades},
                                  {card_rank::jack, card_suit::diamonds},
                                  {card_rank::jack, card_suit::clubs},
                                  {card_rank::queen, card_suit::hearts},
                                  {card_rank::queen, card_suit::spades},
                                  {card_rank::queen, card_suit::diamonds},
                                  {card_rank::queen, card_suit::clubs},
                                  {card_rank::king, card_suit::hearts},
                                  {card_rank::king, card_suit::spades},
                                  {card_rank::king, card_suit::diamonds},
                                  {card_rank::king, card_suit::clubs}};

public:
};

void register_cards(mirror::metadata_registry&);

} // namespace example

#endif
