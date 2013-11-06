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
> struct tail_hlp;

template <size_t N, typename Char, Char ... C>
struct tail_hlp<
	integral_constant<size_t, N>,
	false_type,
	basic_string<Char, C...>,
	basic_string<Char>
>
{
	typedef basic_string<Char> type;
};

template <size_t N, typename Char, Char ... Hn, Char ... Tn>
struct tail_hlp<
	integral_constant<size_t, N>,
	true_type,
	basic_string<Char, Hn...>,
	basic_string<Char, Tn...>
>
{
	typedef basic_string<Char, Tn...> type;
};

template <size_t N, typename Char, Char C, Char ... Hn, Char ... Tn>
struct tail_hlp<
	integral_constant<size_t, N>,
	false_type,
	basic_string<Char, Hn...>,
	basic_string<Char, C, Tn...>
> : tail_hlp<
	integral_constant<size_t, N - 1>,
	integral_constant<bool, N - 1 == 0>,
	basic_string<Char, Hn..., C>,
	basic_string<Char, Tn...>
> { };

} // namespace aux

template <typename Size, typename Char, Char ... C>
struct tail<
	basic_string<Char, C...>,
	Size
> : aux::tail_hlp<
	integral_constant<
		size_t,
		size<basic_string<Char, C...> >::value -
		Size::value
	>,
	integral_constant<
		bool,
		size<basic_string<Char, C...> >::value <=
		Size::value
	>,
	basic_string<Char>,
	basic_string<Char, C...>
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

