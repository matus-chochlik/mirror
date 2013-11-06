/**
 * @file mire/ct/head.hpp
 * @brief Implementation of the head meta-function
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
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
> struct head_hlp;

template <size_t N, typename Char, Char ... C>
struct head_hlp<
	integral_constant<size_t, N>,
	false_type,
	basic_string<Char, C...>,
	basic_string<Char>
>
{
	typedef basic_string<Char, C...> type;
};

template <typename Char, Char ... Hn, Char ... Tn>
struct head_hlp<
	integral_constant<size_t, 0>,
	true_type,
	basic_string<Char, Hn...>,
	basic_string<Char, Tn...>
>
{
	typedef basic_string<Char, Hn...> type;
};

template <size_t N, typename Char, Char C, Char ... Hn, Char ... Tn>
struct head_hlp<
	integral_constant<size_t, N>,
	false_type,
	basic_string<Char, Hn...>,
	basic_string<Char, C, Tn...>
> : head_hlp<
	integral_constant<size_t, N - 1>,
	integral_constant<bool, N - 1 == 0>,
	basic_string<Char, Hn..., C>,
	basic_string<Char, Tn...>
> { };

} // namespace aux

template <typename Length, typename Char, Char ... C>
struct head<
	basic_string<Char, C...>,
	Length
> : aux::head_hlp<
	integral_constant<size_t, Length::value>,
	integral_constant<bool, Length::value == 0>,
	basic_string<Char>,
	basic_string<Char, C...>
> { };

template <typename Range, size_t Length>
struct head_c
 : head<
	typename Range::type,
	integral_constant<size_t, Length>
> { };

} // namespace ct
} // namespace mire

#endif //include guard

