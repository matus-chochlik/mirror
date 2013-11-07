/**
 * @file mire/ct/find.hpp
 * @brief Implementation of the find meta-function
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_FIND_1105240825_HPP
#define MIRE_CT_FIND_1105240825_HPP

#include <mire/ct/default.hpp>
#include <mire/ct/starts_with.hpp>
#include <mire/ct/empty.hpp>
#include <mire/ct/int_const.hpp>

namespace mire {
namespace ct {
namespace aux {

template <
	typename Temp,
	typename Searched,
	typename Found,
	typename Failed
> struct find;

template <typename Char>
struct find<
	basic_string<Char>,
	basic_string<Char>,
	true_type,
	true_type
>: basic_string<Char>
{ };

template <
	typename Char,
	Char ... CTn,
	Char ... CSn
> struct find<
	basic_string<Char, CTn...>,
	basic_string<Char, CSn...>,
	true_type,
	false_type
>: basic_string<Char, CTn...>
{ };

template <
	typename Char,
	Char ... CTn,
	Char ... CSn
> struct find<
	basic_string<Char, CTn...>,
	basic_string<Char, CSn...>,
	false_type,
	true_type
>: basic_string<Char>
{ };

template <
	typename Char,
	Char CT,
	Char ... CTn,
	Char ... CSn
> struct find<
	basic_string<Char, CT, CTn...>,
	basic_string<Char, CSn...>,
	false_type,
	false_type
> : find<
	basic_string<Char, CTn...>,
	basic_string<Char, CSn...>,
	typename starts_with<
		basic_string<Char, CTn...>,
		basic_string<Char, CSn...>
	>::type,
	typename empty<basic_string<Char, CTn...> >::type
>
{ };

} // namespace aux

template <typename Char, Char ... C1n, Char ... C2n>
struct find<
	basic_string<Char, C1n...>,
	basic_string<Char, C2n...>
> : aux::find<
	basic_string<Char, C1n...>,
	basic_string<Char, C2n...>,
	typename starts_with<
		basic_string<Char, C1n...>,
		basic_string<Char, C2n...>
	>::type,
	typename empty<basic_string<Char, C1n...> >::type
> { };

} // namespace ct
} // namespace mire

#endif //include guard

