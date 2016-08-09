/**
 * @file mirror/string.hpp
 * @brief Declaration of compile-time basic_string and string
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_STRING_1105240825_HPP
#define MIRROR_STRING_1105240825_HPP

#include "int_const.hpp"

namespace mirror {

/// A compile-time basic-string template for various character types
/**
 *  @see string
 *
 *  @ingroup utils
 */
template <typename Char, Char ... C>
struct basic_string
{
	typedef basic_string<Char, C...> type;
};

/// A specialization of the basic compile-time string using @c char type
/**
 *  @see basic_string
 *  @see empty_string
 *
 *  @ingroup utils
 */
template <char ... C>
using string = basic_string<char, C...>;

/// An empty compile-time string
/**
 *  @see basic_string
 *  @see string
 *
 *  @ingroup utils
 */
using empty_string = string<>;

} // namespace mirror

#endif //include guard

