/**
 * @file mire/ct/concat.hpp
 * @brief Implementation of the concat meta-function
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_CONCAT_1105240825_HPP
#define MIRE_CT_CONCAT_1105240825_HPP

#include <mire/ct/default.hpp>

namespace mire {
namespace ct {

template <typename Char, Char ... C>
struct concat<basic_string<Char, C...>>
{
	typedef basic_string<Char, C...> type;
};

template <typename Char, Char ... C1, Char ... C2>
struct concat<basic_string<Char, C1...>, basic_string<Char, C2...> >
{
	typedef basic_string<Char, C1..., C2...> type;
};

template <typename ... P>
struct concat<range<P...>>
{
	typedef range<P...> type;
};

template <typename ... P1, typename ... P2>
struct concat<range<P1...>, range<P2...>>
{
	typedef range<P1..., P2...> type;
};

template <
	typename Range1,
	typename Range2,
	typename Range3,
	typename ... Ranges
> struct concat<
	Range1,
	Range2,
	Range3,
	Ranges...
>
{
	typedef typename concat<
		typename concat<Range1, Range2>::type,
		Range3,
		Ranges...
	>::type type;
};

} // namespace ct
} // namespace mire

#endif //include guard

