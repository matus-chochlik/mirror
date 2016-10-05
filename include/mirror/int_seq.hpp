/**
 * @file mirror/int_seq.hpp
 * @brief Compile-time integer sequences
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_INT_SEQ_1105240825_HPP
#define MIRROR_INT_SEQ_1105240825_HPP

#include <reflbase/int_sequence_fix.hpp>

namespace mirror {

template <typename Int, Int ... I>
using int_seq = std::integer_sequence<Int, I...>;

template <std::size_t ... I>
using index_seq = std::index_sequence<I...>;

template <typename Int, std::size_t Size>
using make_int_seq = std::make_integer_sequence<Int, Size>;

template <std::size_t Size>
using make_index_seq = std::make_index_sequence<Size>;

} // namespace mirror

#endif //include guard

