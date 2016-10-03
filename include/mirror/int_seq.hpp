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

#include <cstdint>

namespace mirror {

// TODO
template <typename Int, Int ... I>
struct int_seq;

template <std::size_t ... I>
using index_seq = int_seq<std::size_t, I...>;

template <typename Int, std::size_t Size>
using make_int_seq = __make_integer_seq<int_seq, Int, Size>;

template <std::size_t Size>
using make_index_seq = make_int_seq<std::size_t, Size>;

} // namespace mirror

#endif //include guard

