/**
 * @file mire/ct/string.hpp
 * @brief Declaration of the compile-time basic_string and string
 *
 *  Copyright 2008-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_STRING_1105240825_HPP
#define MIRE_CT_STRING_1105240825_HPP

#include <mire/ct/stddef.hpp>

namespace mire {
namespace ct {

/// A compile-time basic-string template for various character types
/**
 *  @see string
 *  @see empty
 *  @see size
 *  @see concat
 *  @see front
 *  @see at
 *  @see head
 *  @see tail
 *  @see slice
 *  @see starts_with
 *  @see ends_with
 *  @see contains
 *  @see find
 *  @see equal
 *  @see evaluate
 *
 *  @ingroup ct_utils
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
 *  @ingroup ct_utils
 */
template <char ... C>
using string = basic_string<char, C...>;

/// An empty string
/**
 *  @see basic_string
 *  @see string
 *
 *  @ingroup ct_utils
 */
typedef string<> empty_string;

} // namespace ct
} // namespace mire

#endif //include guard

