/**
 * @file mirror/to_string.hpp
 * @brief Implementation of the `to_string` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_TO_STRING_1105240825_HPP
#define MIRROR_TO_STRING_1105240825_HPP

#include <type_traits>
#include "identity.hpp"
#include "string.hpp"
#include "int_seq.hpp"

namespace mirror {
namespace _aux {

template <typename X>
struct op_to_string;

template <typename Char, typename SLC, typename IS>
struct basic_string_from_lit_cls;

template <typename Char, typename SLC, std::size_t ... I>
struct basic_string_from_lit_cls<Char, SLC, index_seq<I...>>
 : basic_string<Char, SLC::value[I]...>
{ };

template <typename SLC>
constexpr std::size_t str_lit_len =
	std::extent<decltype(SLC::value)>::value?
	std::extent<decltype(SLC::value)>::value-1:0;

template <typename SLC>
struct op_to_string
 : basic_string_from_lit_cls<char, SLC, make_index_seq<str_lit_len<SLC>>>
{ };

template <typename Char, Char ... C>
struct op_to_string<basic_string<Char, C...>>
 : basic_string<Char, C...>
{ };

template <typename Bool, typename Char, typename X>
struct op_to_string_if;

template <typename X, typename Char>
struct op_to_string_if<true_, Char, X>
 : op_to_string<X>
{ };

template <typename Char, typename X>
struct op_to_string_if<false_, Char, X>
 : basic_string<Char>
{ };

} // namespace _aux

template <typename X>
using to_string = eval<_aux::op_to_string<X>>;

template <typename Bool, typename Char, typename X>
using to_string_if = eval<_aux::op_to_string_if<Bool, Char, X>>;

template <bool B, typename Char, typename X>
using to_string_if_c = to_string_if<bool_<B>, Char, X>;

} // namespace mirror

#endif //include guard

