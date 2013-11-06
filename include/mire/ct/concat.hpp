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

template <
	typename String1,
	typename String2,
	typename String3,
	typename ... Strings
> struct concat<
	String1,
	String2,
	String3,
	Strings...
>
{
	typedef typename concat<
		typename concat<String1, String2>::type,
		String3,
		Strings...
	>::type type;
};

template <typename ... Strings>
struct concat<range<Strings...>>
 : concat<Strings...>
{ };

} // namespace ct
} // namespace mire

#endif //include guard

