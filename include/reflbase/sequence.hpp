/**
 * @file reflbase/sequence.hpp
 * @brief compile-time sequence
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef REFLBASE_SEQUENCE_1105240825_HPP
#define REFLBASE_SEQUENCE_1105240825_HPP

namespace reflbase {

template <typename ... T>
struct sequence { };

using empty_sequence = sequence<>;

} // namespace reflbase

#endif //include guard

