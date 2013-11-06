/**
 * @file mire/ct/string.hpp
 * @brief Declaration of the compile-time basic_string and string
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_STRING_1105240825_HPP
#define MIRE_CT_STRING_1105240825_HPP

namespace mire {
namespace ct {

/// A compile-time basic-string template for various characted types
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
	static constexpr char c_str[] = { C..., '\0' };
	static constexpr size_t size = sizeof...(C);
};
template <typename Char, Char ... C>
constexpr char basic_string<Char, C...>::c_str[];

#ifdef MIRROR_DOCUMENTATION_ONLY
/// This trait meta-function can be used to check if the passed type is a string
template <typename T>
struct is_string  : BooleanConstant
{ };
#else
template <typename T>
struct is_string
 : false_type
{ };

template <typename Char, Char ... C>
struct is_string<basic_string<Char, C...>>
 : true_type
{ };
#endif

/// A specialization of the basic compile-time string using @c char type
/**
 *  @see basic_string
 *
 *  @ingroup ct_utils
 */
template <char ... C>
struct string
 : basic_string<char, C...>
{ };

} // namespace ct
} // namespace mire

#endif //include guard

