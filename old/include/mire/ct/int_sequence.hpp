/**
 * @file mire/ct/int_sequence.hpp
 * @brief Integral sequences
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_INT_SEQUENCE_1105240825_HPP
#define MIRE_CT_INT_SEQUENCE_1105240825_HPP

#include <mire/ct/int_const.hpp>

namespace mire {
namespace ct {

/* TODO
using ::std::integer_sequence;
using ::std::index_sequence;
using ::std::make_integer_sequence;
using ::std::make_index_sequence;
*/

template <typename Int, Int ... I>
struct integer_sequence
{
	typedef integer_sequence type;
};

template <size_t ... I>
using index_sequence = integer_sequence<size_t, I ...>;

template <typename IS, typename I>
struct push_back_t;

template <typename Int, Int ... I, Int N>
struct push_back_t<integer_sequence<Int, I...>, integral_constant<Int, N>>
 : integer_sequence<Int, I..., N>
{ };

template <typename N>
struct make_integer_sequence_t;

template <typename Int>
struct make_integer_sequence_t<integral_constant<Int, Int(0)>>
 : integer_sequence<Int>
{ };

template <typename Int, Int N>
struct make_integer_sequence_t<integral_constant<Int, N>>
 : push_back_t<
	typename make_integer_sequence_t<integral_constant<Int, N-1>>::type,
	integral_constant<Int, N-1>
>
{ };

template <typename Int, Int N>
struct make_integer_sequence
 : make_integer_sequence_t<integral_constant<Int, N>>
{ };

template <size_t N>
using make_index_sequence = make_integer_sequence<size_t, N>;

} // namespace ct
} // namespace mire

#endif //include guard

