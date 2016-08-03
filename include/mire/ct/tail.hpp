/**
 * @file mire/ct/tail.hpp
 * @brief Implementation of the tail meta-function
 *
 *  Copyright 2008-2015 Matus Chochlik. Distributed under the Boost
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
	size_constant<N>,
	false_type,
	basic_string<Char, C...>,
	basic_string<Char>
>: basic_string<Char>
{ };

template <size_t N, typename Char, Char ... Hn, Char ... Tn>
struct tail<
	size_constant<N>,
	true_type,
	basic_string<Char, Hn...>,
	basic_string<Char, Tn...>
>: basic_string<Char, Tn...>
{ };

template <size_t N, typename Char, Char C, Char ... Hn, Char ... Tn>
struct tail<
	size_constant<N>,
	false_type,
	basic_string<Char, Hn...>,
	basic_string<Char, C, Tn...>
> : tail<
	size_constant<N - 1>,
	boolean_constant<N - 1 == 0>,
	basic_string<Char, Hn..., C>,
	basic_string<Char, Tn...>
> { };

template <size_t N, typename ... P>
struct tail<
	size_constant<N>,
	false_type,
	range<P...>,
	range<>
>: range<>
{ };

template <size_t N, typename ... H, typename ... T>
struct tail<
	size_constant<N>,
	true_type,
	range<H...>,
	range<T...>
>: range<T...>
{ };

template <size_t N, typename C, typename ... H, typename ... T>
struct tail<
	size_constant<N>,
	false_type,
	range<H...>,
	range<C, T...>
> : tail<
	size_constant<N - 1>,
	boolean_constant<N - 1 == 0>,
	range<H..., C>,
	range<T...>
> { };

} // namespace aux

template <typename Size, typename Char, Char ... C>
struct tail<
	basic_string<Char, C...>,
	Size
> : aux::tail<
	size_constant<sizeof...(C) -  Size::value>,
	boolean_constant<sizeof...(C) <= Size::value>,
	basic_string<Char>,
	basic_string<Char, C...>
> { };

template <typename Size, typename ... P>
struct tail<
	range<P...>,
	Size
> : aux::tail<
	size_constant<sizeof...(P) -  Size::value>,
	boolean_constant<sizeof...(P) <= Size::value>,
	range<>,
	range<P...>
> { };

template <typename Range, size_t Size>
struct tail_c
 : tail<
	typename Range::type,
	size_constant<Size>
> { };

} // namespace ct
} // namespace mire

#endif //include guard

