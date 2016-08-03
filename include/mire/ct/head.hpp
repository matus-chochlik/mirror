/**
 * @file mire/ct/head.hpp
 * @brief Implementation of the head meta-function
 *
 *  Copyright 2008-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_HEAD_1105240825_HPP
#define MIRE_CT_HEAD_1105240825_HPP

#include <mire/ct/default.hpp>
#include <mire/ct/int_const.hpp>

namespace mire {
namespace ct {
namespace aux {

template <
	typename Count,
	typename Done,
	typename Head,
	typename Tail
> struct head;

// basic_string
template <size_t N, typename Char, Char ... C>
struct head<
	size_constant<N>,
	false_type,
	basic_string<Char, C...>,
	basic_string<Char>
>: basic_string<Char, C...>
{ };

template <typename Char, Char ... Hn, Char ... Tn>
struct head<
	size_constant<0>,
	true_type,
	basic_string<Char, Hn...>,
	basic_string<Char, Tn...>
>: basic_string<Char, Hn...>
{ };

template <size_t N, typename Char, Char C, Char ... Hn, Char ... Tn>
struct head<
	size_constant<N>,
	false_type,
	basic_string<Char, Hn...>,
	basic_string<Char, C, Tn...>
> : head<
	size_constant<N - 1>,
	boolean_constant<N - 1 == 0>,
	basic_string<Char, Hn..., C>,
	basic_string<Char, Tn...>
> { };

// range
template <size_t N, typename ... P>
struct head<
	size_constant<N>,
	false_type,
	range<P...>,
	range<>
>: range<P...>
{ };

template <typename ... H, typename ... T>
struct head<
	size_constant<0>,
	true_type,
	range<H...>,
	range<T...>
>: range<H...>
{ };

template <size_t N, typename C, typename ... H, typename ... T>
struct head<
	size_constant<N>,
	false_type,
	range<H...>,
	range<C, T...>
> : head<
	size_constant<N - 1>,
	boolean_constant<N - 1 == 0>,
	range<H..., C>,
	range<T...>
> { };

} // namespace aux

template <typename Length, typename Char, Char ... C>
struct head<
	basic_string<Char, C...>,
	Length
> : aux::head<
	size_constant<Length::value>,
	boolean_constant<Length::value == 0>,
	basic_string<Char>,
	basic_string<Char, C...>
> { };

template <typename Length, typename ... P>
struct head<
	range<P...>,
	Length
> : aux::head<
	size_constant<Length::value>,
	boolean_constant<Length::value == 0>,
	range<>,
	range<P...>
> { };

template <typename Range, size_t Length>
struct head_c
 : head<
	typename Range::type,
	size_constant<Length>
> { };

} // namespace ct
} // namespace mire

#endif //include guard

