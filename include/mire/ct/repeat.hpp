/**
 * @file mire/ct/repeat.hpp
 * @brief Implementation of the repeat meta-function
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_REPEAT_1105240825_HPP
#define MIRE_CT_REPEAT_1105240825_HPP

#include <mire/ct/default.hpp>

namespace mire {
namespace ct {
namespace _aux {

template <typename Range, typename Type, size_t Remaining>
struct repeat_type;

template <typename ... P, typename Type, size_t Remaining>
struct repeat_type<range<P...>, Type, Remaining>
 : repeat_type<range<P..., Type>, Type, Remaining-1>
{ };

template <typename ... P, typename Type>
struct repeat_type<range<P...>, Type, 0>
 : range<P...>
{ };

template <typename String, typename Char, Char C, size_t Remaining>
struct repeat_char;

template <typename Char, Char ... P, Char C, size_t Remaining>
struct repeat_char<basic_string<Char, P...>, Char, C, Remaining>
 : repeat_char<basic_string<Char, P..., C>, Char, C, Remaining-1>
{ };

template <typename Char, Char ... P, Char C>
struct repeat_char<basic_string<Char, P...>, Char, C, 0>
 : basic_string<Char, P...>
{ };

} // namespace _aux

template <size_t Count, typename Type>
struct repeat_type_c
 : _aux::repeat_type<empty_range, Type, Count>
{ };

template <typename Count, typename Type>
struct repeat_type
 : repeat_type_c<Count::value, Type>
{ };

template <size_t Count, typename Char, Char C>
struct repeat_char_c
 : _aux::repeat_char<basic_string<Char>, Char, C, Count>
{ };

template <typename Count, typename Char, Char C>
struct repeat_char
 : repeat_char_c<Count::value, Char, C>
{ };

} // namespace ct
} // namespace mire

#endif //include guard

