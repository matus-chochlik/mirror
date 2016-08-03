/**
 * @file mire/ct/remove.hpp
 * @brief Implementation of the remove meta-function
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_REMOVE_1105240825_HPP
#define MIRE_CT_REMOVE_1105240825_HPP

#include <mire/ct/default.hpp>

namespace mire {
namespace ct {
namespace _aux {

template <typename Result, typename Temp, typename Elem>
struct remove;

// range
template <typename ... P, typename Elem>
struct remove<range<P...>, range<>, Elem>
 : range<P...>
{ };

template <typename ... P, typename ... R, typename Elem>
struct remove<range<P...>, range<Elem, R...>, Elem>
 : remove<range<P...>, range<R...>, Elem>
{ };

template <typename ... P, typename ... R, typename H, typename Elem>
struct remove<range<P...>, range<H, R...>, Elem>
 : remove<range<P..., H>, range<R...>, Elem>
{ };

// string
template <typename Char, Char ... P, typename Elem>
struct remove<basic_string<Char, P...>, basic_string<Char>, Elem>
 : basic_string<Char, P...>
{ };

template <typename Char, Char ... P, Char ... R, typename Elem>
struct remove<
	basic_string<Char, P...>,
	basic_string<Char, Elem::value, R...>,
	Elem
>: remove<basic_string<Char, P...>, basic_string<Char, R...>, Elem>
{ };

template <typename Char, Char ... P, Char ... R, Char H, typename Elem>
struct remove<
	basic_string<Char, P...>,
	basic_string<Char, H, R...>,
	Elem
>: remove<basic_string<Char, P..., H>, basic_string<Char, R...>, Elem>
{ };

} // namespace _aux

// range
template <typename ... P, typename Elem>
struct remove<range<P...>, Elem>
 : _aux::remove<range<>, range<P...>, Elem>
{ };

// string
template <typename Char, Char ... P, typename Elem>
struct remove<basic_string<Char, P...>, Elem>
 : _aux::remove<basic_string<Char>, basic_string<Char, P...>, Elem>
{ };

template <typename Char, Char ... P, Char C>
struct remove_c<basic_string<Char, P...>, Char, C>
 : _aux::remove<
	basic_string<Char>,
	basic_string<Char, P...>,
	integral_constant<Char, C>
>
{ };


} // namespace ct
} // namespace mire

#endif //include guard

