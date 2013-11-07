/**
 * @file mire/ct/compare.hpp
 * @brief Implementation of compile-time string comparison meta-functions
 *
 *  Copyright 2008-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_COMPARE_1105240825_HPP
#define MIRE_CT_COMPARE_1105240825_HPP

#include <mire/ct/default.hpp>
#include <mire/ct/int_const.hpp>

namespace mire {
namespace ct {

// basic_string
template <typename Char, Char ... C>
struct equal<basic_string<Char, C...>, basic_string<Char, C...>>
 : true_type
{ };

template <typename Char, Char ... C1, Char ... C2>
struct equal<basic_string<Char, C1...>, basic_string<Char, C2...>>
 : false_type
{ };

template <typename Char, Char ... C>
struct nonequal<basic_string<Char, C...>, basic_string<Char, C...>>
 : false_type
{ };

template <typename Char, Char ... C1, Char ... C2>
struct nonequal<basic_string<Char, C1...>, basic_string<Char, C2...>>
 : true_type
{ };

// range
template <typename ... P>
struct equal<range<P...>, range<P...>>
 : true_type
{ };

template <typename ... P1, typename ... P2>
struct equal<range<P1...>, range<P2...>>
 : false_type
{ };

template <typename ... P>
struct nonequal<range<P...>, range<P...>>
 : false_type
{ };

template <typename ... P1, typename ... P2>
struct nonequal<range<P1...>, range<P2...>>
 : true_type
{ };

// optional
template <typename T>
struct equal<optional<T>, optional<T>>
 : true_type
{ };

template <typename T1, typename T2>
struct equal<optional<T1>, optional<T2>>
 : false_type
{ };

template <typename T>
struct nonequal<optional<T>, optional<T>>
 : false_type
{ };

template <typename T1, typename T2>
struct nonequal<optional<T1>, optional<T2>>
 : true_type
{ };

} // namespace ct
} // namespace mire

#endif //include guard

