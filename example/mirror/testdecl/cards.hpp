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
#include <array>

namespace example {
namespace cards {

enum class rank {
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

enum class suit { hearts, spades, diamonds, clubs };

struct card {
    const enum rank rank;
    const enum suit suit;

    constexpr card(enum rank r, enum suit s) noexcept
      : rank{r}
      , suit{s} {}

    friend auto operator==(const card l, const card r) noexcept {
        return std::make_tuple(l.rank, l.suit) ==
               std::make_tuple(r.rank, r.suit);
    }

    friend auto operator!=(const card l, const card r) noexcept {
        return std::make_tuple(l.rank, l.suit) !=
               std::make_tuple(r.rank, r.suit);
    }

    friend auto operator<(const card l, const card r) noexcept {
        return std::make_tuple(l.rank, l.suit) <
               std::make_tuple(r.rank, r.suit);
    }
};

class deck {
private:
    std::array<card, 52> _cards{
      {{rank::ace, suit::hearts},     {rank::ace, suit::spades},
       {rank::ace, suit::diamonds},   {rank::ace, suit::clubs},
       {rank::two, suit::hearts},     {rank::two, suit::spades},
       {rank::two, suit::diamonds},   {rank::two, suit::clubs},
       {rank::three, suit::hearts},   {rank::three, suit::spades},
       {rank::three, suit::diamonds}, {rank::three, suit::clubs},
       {rank::four, suit::hearts},    {rank::four, suit::spades},
       {rank::four, suit::diamonds},  {rank::four, suit::clubs},
       {rank::five, suit::hearts},    {rank::five, suit::spades},
       {rank::five, suit::diamonds},  {rank::five, suit::clubs},
       {rank::six, suit::hearts},     {rank::six, suit::spades},
       {rank::six, suit::diamonds},   {rank::six, suit::clubs},
       {rank::seven, suit::hearts},   {rank::seven, suit::spades},
       {rank::seven, suit::diamonds}, {rank::seven, suit::clubs},
       {rank::eight, suit::hearts},   {rank::eight, suit::spades},
       {rank::eight, suit::diamonds}, {rank::eight, suit::clubs},
       {rank::nine, suit::hearts},    {rank::nine, suit::spades},
       {rank::nine, suit::diamonds},  {rank::nine, suit::clubs},
       {rank::ten, suit::hearts},     {rank::ten, suit::spades},
       {rank::ten, suit::diamonds},   {rank::ten, suit::clubs},
       {rank::jack, suit::hearts},    {rank::jack, suit::spades},
       {rank::jack, suit::diamonds},  {rank::jack, suit::clubs},
       {rank::queen, suit::hearts},   {rank::queen, suit::spades},
       {rank::queen, suit::diamonds}, {rank::queen, suit::clubs},
       {rank::king, suit::hearts},    {rank::king, suit::spades},
       {rank::king, suit::diamonds},  {rank::king, suit::clubs}}};

public:
};

class player {
private:
public:
};

class dealer : player {
private:
    deck _deck;

public:
};

} // namespace cards

void register_cards(mirror::metadata_registry&);

} // namespace example

#endif
