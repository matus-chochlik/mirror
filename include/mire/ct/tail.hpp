/**
 * @file mire/ct/tail.hpp
 * @brief Implementation of the tail meta-function
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_TAIL_1105240825_HPP
#define MIRE_CT_TAIL_1105240825_HPP

#include <mire/ct/default.hpp>

namespace mire {
namespace ct {
namespace aux {

template <
	typename Count,
	typename Done,
	typename Head,
	typename Tail
> struct tail;

template <size_t N, typename Char, Char ... C>
struct tail<
	integral_constant<size_t, N>,
	false_type,
	basic_string<Char, C...>,
	basic_string<Char>
>: basic_string<Char>
{ };

template <size_t N, typename Char, Char ... Hn, Char ... Tn>
struct tail<
	integral_constant<size_t, N>,
	true_type,
	basic_string<Char, Hn...>,
	basic_string<Char, Tn...>
>: basic_string<Char, Tn...>
{ };

template <size_t N, typename Char, Char C, Char ... Hn, Char ... Tn>
struct tail<
	integral_constant<size_t, N>,
	false_type,
	basic_string<Char, Hn...>,
	basic_string<Char, C, Tn...>
> : tail<
	integral_constant<size_t, N - 1>,
	integral_constant<bool, N - 1 == 0>,
	basic_string<Char, Hn..., C>,
	basic_string<Char, Tn...>
> { };

template <size_t N, typename ... P>
struct tail<
	integral_constant<size_t, N>,
	false_type,
	range<P...>,
	range<>
>: range<>
{ };

template <size_t N, typename ... H, typename ... T>
struct tail<
	integral_constant<size_t, N>,
	true_type,
	range<H...>,
	range<T...>
>: range<T...>
{ };

template <size_t N, typename C, typename ... H, typename ... T>
struct tail<
	integral_constant<size_t, N>,
	false_type,
	range<H...>,
	range<C, T...>
> : tail<
	integral_constant<size_t, N - 1>,
	integral_constant<bool, N - 1 == 0>,
	range<H..., C>,
	range<T...>
> { };

} // namespace aux

template <typename Size, typename Char, Char ... C>
struct tail<
	basic_string<Char, C...>,
	Size
> : aux::tail<
	integral_constant<size_t, sizeof...(C) -  Size::value>,
	integral_constant<bool,   sizeof...(C) <= Size::value>,
	basic_string<Char>,
	basic_string<Char, C...>
> { };

template <typename Size, typename ... P>
struct tail<
	range<P...>,
	Size
> : aux::tail<
	integral_constant<size_t, sizeof...(P) -  Size::value>,
	integral_constant<bool,   sizeof...(P) <= Size::value>,
	range<>,
	range<P...>
> { };

template <typename Range, size_t Size>
struct tail_c
 : tail<
	typename Range::type,
	integral_constant<size_t, Size>
> { };

} // namespace ct
} // namespace mire

#endif //include guard

