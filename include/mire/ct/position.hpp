/**
 * @file mire/ct/position.hpp
 * @brief Implementation of the position meta-function
 *
 *  Copyright 2008-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_POSITION_1105240825_HPP
#define MIRE_CT_POSITION_1105240825_HPP

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
	typename Position,
	typename Found,
	typename Failed
> struct position;
// basic_string

template <typename Char, size_t P>
struct position<
	basic_string<Char>,
	basic_string<Char>,
	integral_constant<size_t, P>,
	true_type,
	true_type
>: nil_t
{ };

template <
	typename Char,
	Char ... CTn,
	Char ... CSn,
	size_t P
> struct position<
	basic_string<Char, CTn...>,
	basic_string<Char, CSn...>,
	integral_constant<size_t, P>,
	true_type,
	false_type
>: integral_constant<size_t, P>
{ };

template <
	typename Char,
	Char ... CTn,
	Char ... CSn,
	size_t P
> struct position<
	basic_string<Char, CTn...>,
	basic_string<Char, CSn...>,
	integral_constant<size_t, P>,
	false_type,
	true_type
>: nil_t
{ };

template <
	typename Char,
	Char CT,
	Char ... CTn,
	Char ... CSn,
	size_t P
> struct position<
	basic_string<Char, CT, CTn...>,
	basic_string<Char, CSn...>,
	integral_constant<size_t, P>,
	false_type,
	false_type
> : position<
	basic_string<Char, CTn...>,
	basic_string<Char, CSn...>,
	integral_constant<size_t, P+1>,
	typename starts_with<
		basic_string<Char, CTn...>,
		basic_string<Char, CSn...>
	>::type,
	typename empty<basic_string<Char, CTn...>>::type
>
{ };

// range
template <size_t P>
struct position<
	range<>,
	range<>,
	integral_constant<size_t, P>,
	true_type,
	true_type
>: nil_t
{ };

template <
	typename ... CT,
	typename ... CS,
	size_t P
> struct position<
	range<CT...>,
	range<CS...>,
	integral_constant<size_t, P>,
	true_type,
	false_type
>: integral_constant<size_t, P>
{ };

template <
	typename ... CT,
	typename ... CS,
	size_t P
> struct position<
	range<CT...>,
	range<CS...>,
	integral_constant<size_t, P>,
	false_type,
	true_type
>: nil_t
{ };

template <
	typename C,
	typename ... CT,
	typename ... CS,
	size_t P
> struct position<
	range<C, CT...>,
	range<CS...>,
	integral_constant<size_t, P>,
	false_type,
	false_type
> : position<
	range<CT...>,
	range<CS...>,
	integral_constant<size_t, P+1>,
	typename starts_with<
		range<CT...>,
		range<CS...>
	>::type,
	typename empty<range<CT...>>::type
>
{ };

} // namespace aux

template <typename Char, Char ... C1n, Char ... C2n>
struct position<
	basic_string<Char, C1n...>,
	basic_string<Char, C2n...>
> : aux::position<
	basic_string<Char, C1n...>,
	basic_string<Char, C2n...>,
	integral_constant<size_t, 0>,
	typename starts_with<
		basic_string<Char, C1n...>,
		basic_string<Char, C2n...>
	>::type,
	typename empty<basic_string<Char, C1n...>>::type
> { };

template <typename ... P1, typename ... P2>
struct position<
	range<P1...>,
	range<P2...>
> : aux::position<
	range<P1...>,
	range<P2...>,
	integral_constant<size_t, 0>,
	typename starts_with<
		range<P1...>,
		range<P2...>
	>::type,
	typename empty<range<P1...>>::type
> { };

} // namespace ct
} // namespace mire

#endif //include guard

