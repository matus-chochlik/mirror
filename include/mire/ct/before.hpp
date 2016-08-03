/**
 * @file mire/ct/before.hpp
 * @brief Implementation of the before meta-function
 *
 *  Copyright 2008-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_BEFORE_1105240825_HPP
#define MIRE_CT_BEFORE_1105240825_HPP

#include <mire/ct/default.hpp>
#include <mire/ct/starts_with.hpp>
#include <mire/ct/empty.hpp>
#include <mire/ct/int_const.hpp>

namespace mire {
namespace ct {
namespace aux {

// basic_string
template <
	typename Result,
	typename Temp,
	typename Searched,
	typename Found,
	typename Failed
> struct before;

template <
	typename Char,
	Char ... CFn,
	Char ... CTn,
	Char ... CSn
> struct before<
	basic_string<Char, CFn...>,
	basic_string<Char, CTn...>,
	basic_string<Char, CSn...>,
	true_type,
	true_type
>: basic_string<Char>
{ };

template <
	typename Char,
	Char ... CFn,
	Char ... CTn,
	Char ... CSn
> struct before<
	basic_string<Char, CFn...>,
	basic_string<Char, CTn...>,
	basic_string<Char, CSn...>,
	false_type,
	true_type
>: basic_string<Char>
{ };

template <
	typename Char,
	Char ... CFn,
	Char ... CTn,
	Char ... CSn
> struct before<
	basic_string<Char, CFn...>,
	basic_string<Char, CTn...>,
	basic_string<Char, CSn...>,
	true_type,
	false_type
>: basic_string<Char, CFn...>
{ };

template <
	typename Char,
	Char CT,
	Char ... CFn,
	Char ... CTn,
	Char ... CSn
> struct before<
	basic_string<Char, CFn...>,
	basic_string<Char, CT, CTn...>,
	basic_string<Char, CSn...>,
	false_type,
	false_type
>: before<
	basic_string<Char, CFn..., CT>,
	basic_string<Char, CTn...>,
	basic_string<Char, CSn...>,
	typename starts_with<
		basic_string<Char, CTn...>,
		basic_string<Char, CSn...>
	>::type,
	typename empty<basic_string<Char, CTn...>>::type
>
{ };

// range
template <
	typename ... CF,
	typename ... CT,
	typename ... CS
> struct before<
	range<CF...>,
	range<CT...>,
	range<CS...>,
	true_type,
	true_type
>: range<>
{ };

template <
	typename ... CF,
	typename ... CT,
	typename ... CS
> struct before<
	range<CF...>,
	range<CT...>,
	range<CS...>,
	false_type,
	true_type
>: range<>
{ };

template <
	typename ... CF,
	typename ... CT,
	typename ... CS
> struct before<
	range<CF...>,
	range<CT...>,
	range<CS...>,
	true_type,
	false_type
>: range<CF...>
{ };

template <
	typename C,
	typename ... CF,
	typename ... CT,
	typename ... CS
> struct before<
	range<CF...>,
	range<C, CT...>,
	range<CS...>,
	false_type,
	false_type
>: before<
	range<CF..., C>,
	range<CT...>,
	range<CS...>,
	typename starts_with<
		range<CT...>,
		range<CS...>
	>::type,
	typename empty<range<CT...>>::type
>
{ };

} // namespace aux

template <typename Char, Char ... C1n, Char ... C2n>
struct before<
	basic_string<Char, C1n...>,
	basic_string<Char, C2n...>
>: aux::before<
	basic_string<Char>,
	basic_string<Char, C1n...>,
	basic_string<Char, C2n...>,
	typename starts_with<
		basic_string<Char, C1n...>,
		basic_string<Char, C2n...>
	>::type,
	typename empty<basic_string<Char, C1n...>>::type
> { };

template <typename Char, Char ... C2n>
struct before<
	basic_string<Char>,
	basic_string<Char, C2n...>
>: basic_string<Char>
{ };

template <typename ... P1, typename ... P2>
struct before<
	range<P1...>,
	range<P2...>
>: aux::before<
	range<>,
	range<P1...>,
	range<P2...>,
	typename starts_with<
		range<P1...>,
		range<P2...>
	>::type,
	typename empty<range<P1...>>::type
> { };

template <typename ... P2>
struct before<
	range<>,
	range<P2...>
>: range<>
{ };

} // namespace ct
} // namespace mire

#endif //include guard

