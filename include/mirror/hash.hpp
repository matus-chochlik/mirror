/**
 * @file mirror/hash.hpp
 * @brief Identity template returning the type passed * as argument.
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_HASH_1105240825_HPP
#define MIRROR_HASH_1105240825_HPP

#include "string.hpp"
#include <type_traits>
#include <cstdint>

namespace mirror {
namespace _aux {

template <
	uint8_t b7, uint8_t b6, uint8_t b5, uint8_t b4,
	uint8_t b3, uint8_t b2, uint8_t b1, uint8_t b0
> struct hash_bytes
 : std::integral_constant<uint64_t,
(uint64_t((b7&0x01)|(b6&0x02)|(b5&0x04)|(b4&0x08)|(b3&0x10)|(b2&0x20)|(b1&0x40)|(b0&0x80))<<(0*8))|
(uint64_t((b7&0x02)|(b6&0x01)|(b5&0x08)|(b4&0x04)|(b3&0x20)|(b2&0x10)|(b1&0x80)|(b0&0x40))<<(1*8))|
(uint64_t((b7&0x04)|(b6&0x08)|(b5&0x01)|(b4&0x02)|(b3&0x40)|(b2&0x80)|(b1&0x10)|(b0&0x20))<<(2*8))|
(uint64_t((b7&0x08)|(b6&0x04)|(b5&0x02)|(b4&0x01)|(b3&0x80)|(b2&0x40)|(b1&0x20)|(b0&0x10))<<(3*8))|
(uint64_t((b7&0x10)|(b6&0x20)|(b5&0x40)|(b4&0x80)|(b3&0x01)|(b2&0x02)|(b1&0x04)|(b0&0x08))<<(4*8))|
(uint64_t((b7&0x20)|(b6&0x10)|(b5&0x80)|(b4&0x40)|(b3&0x02)|(b2&0x01)|(b1&0x08)|(b0&0x04))<<(5*8))|
(uint64_t((b7&0x40)|(b6&0x80)|(b5&0x10)|(b4&0x20)|(b3&0x04)|(b2&0x08)|(b1&0x01)|(b0&0x02))<<(6*8))|
(uint64_t((b7&0x80)|(b6&0x40)|(b5&0x20)|(b4&0x10)|(b3&0x08)|(b2&0x04)|(b1&0x02)|(b0&0x01))<<(7*8))>
{ };

template <uint64_t State, typename X>
struct do_hash;

template <
	uint64_t State,
	char c7, char c6, char c5, char c4,
	char c3, char c2, char c1, char c0
> struct do_hash<State, string<c7, c6, c5, c4, c3, c2, c1, c0>>
 : std::integral_constant<
	uint64_t,
	(State ^ 0x8001400220041008U) ^ hash_bytes<
		uint8_t(c7), uint8_t(c6), uint8_t(c5), uint8_t(c4), 
		uint8_t(c3), uint8_t(c2), uint8_t(c1), uint8_t(c0)
	>::value
> { };

template <
	uint64_t State,
	char c6, char c5, char c4,
	char c3, char c2, char c1, char c0
> struct do_hash<State, string<c6, c5, c4, c3, c2, c1, c0>>
 : do_hash<State, string<
	char(0), c6, c5, c4,
	c3, c2, c1, c0>
> { };

template <
	uint64_t State,
	char c5, char c4,
	char c3, char c2, char c1, char c0
> struct do_hash<State, string<c5, c4, c3, c2, c1, c0>>
 : do_hash<State, string<
	char(0), char(0), c5, c4,
	c3, c2, c1, c0>
> { };

template <
	uint64_t State,
	char c4,
	char c3, char c2, char c1, char c0
> struct do_hash<State, string<c4, c3, c2, c1, c0>>
 : do_hash<State, string<
	char(0), char(0), char(0), c4,
	c3, c2, c1, c0>
> { };

template <
	uint64_t State,
	char c3, char c2, char c1, char c0
> struct do_hash<State, string<c3, c2, c1, c0>>
 : do_hash<State, string<
	char(0), char(0), char(0), char(0),
	c3, c2, c1, c0>
>
{ };

template <
	uint64_t State,
	char c2, char c1, char c0
> struct do_hash<State, string<c2, c1, c0>>
 : do_hash<State, string<
	char(0), char(0), char(0), char(0),
	char(0), c2, c1, c0>
>
{ };

template <
	uint64_t State,
	char c1, char c0
> struct do_hash<State, string<c1, c0>>
 : do_hash<State, string<
	char(0), char(0), char(0), char(0),
	char(0), char(0), c1, c0>
>
{ };

template <
	uint64_t State,
	char c0
> struct do_hash<State, string<c0>>
 : do_hash<State, string<
	char(0), char(0), char(0), char(0),
	char(0), char(0), char(0), c0>
>
{ };

template <uint64_t State>
struct do_hash<State, empty_string>
 : std::integral_constant<uint64_t, 0>
{ };

template <uint64_t State, uint64_t V>
struct do_hash<State, std::integral_constant<uint64_t, V>>
 : hash_bytes<
	uint8_t(V>>7*8), uint8_t(V>>6*8), uint8_t(V>>5*8), uint8_t(V>>4*8),
	uint8_t(V>>3*8), uint8_t(V>>2*8), uint8_t(V>>1*8), uint8_t(V>>0*8)
> { };

template <uint64_t State, uint32_t V>
struct do_hash<State, std::integral_constant<uint32_t, V>>
 : do_hash<State, std::integral_constant<uint64_t, uint64_t(V)>>
{ };

template <uint64_t State, uint16_t V>
struct do_hash<State, std::integral_constant<uint16_t, V>>
 : do_hash<State, std::integral_constant<uint64_t, uint64_t(V)>>
{ };

template <
	uint64_t State,
	char c7, char c6, char c5, char c4,
	char c3, char c2, char c1, char c0,
	char ... cp
> struct do_hash<State, string<c7, c6, c5, c4, c3, c2, c1, c0, cp...>>
 : do_hash<
	do_hash<State, string<c7, c6, c5, c4, c3, c2, c1, c0>>::value,
	string<cp...>
> { };

template <uint64_t S, typename ... X>
struct op_hash;

template <uint64_t S, typename X>
struct op_hash<S, X>
 : do_hash<S, X>
{ };

template <uint64_t S, typename X1, typename X2>
struct op_hash<S, X1, X2>
 : do_hash<do_hash<S, X2>::value, X1>
{ };

template <uint64_t S, typename X1, typename X2, typename X3, typename ... Xp>
struct op_hash<S, X1, X2, X3, Xp...>
 : do_hash<op_hash<S, X2, X3, Xp...>::value, X1>
{ };

} // namespace _aux

template <typename ... X>
using hash = eval<_aux::op_hash<0U, X...>>;

} // namespace mirror

#endif //include guard

