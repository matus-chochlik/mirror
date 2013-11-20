/**
 * @file mire/ct/int_to_str.hpp
 * @brief Metafunctions turning integral constants to strings of digits.
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_EXP10_1105240825_HPP
#define MIRE_CT_EXP10_1105240825_HPP

#include <mire/ct/int_const.hpp>
#include <mire/ct/string.hpp>
#include <mire/ct/at.hpp>

namespace mire {
namespace ct {
namespace aux {

template <typename Str, typename Int, Int Base, Int Value, bool Done>
struct int_to_istr;

template <typename Int, Int Base, Int Value>
struct int_to_istr<basic_string<Int>, Int, Base, Value, true>
 : basic_string<Int, Int(0)>
{ };

template <typename Int, Int Base, Int Value, Int D, Int ... I>
struct int_to_istr<basic_string<Int, D, I...>, Int, Base, Value, true>
 : basic_string<Int, D, I...>
{ };

template <typename Int, Int Base, Int Value, Int ... I>
struct int_to_istr<basic_string<Int, I...>, Int, Base, Value, false>
 : int_to_istr<
	basic_string<Int, Value % Base, I...>,
	Int,
	Base,
	Value / Base,
	Value / Base == 0
>
{ };

template <typename Int, Int Base, Int Value>
struct conv_int_to_istr
 : int_to_istr<basic_string<Int>, Int, Base, Value, Value == 0>
{ };

template <typename Char, typename Digits, typename IStr>
struct istr_to_str;

template <typename Char, typename Int, Char ... D, Int ... I>
struct istr_to_str<Char, basic_string<Char, D...>, basic_string<Int, I...>>
 : basic_string<Char, at_c<basic_string<Char, D...>, I>::value...>
{ };

} // namespace aux

/// Converts an IntegralConstant to a string of its binary digits
/**
 *  @ingroup ct_utils
 */
template <typename IntegralConstant, typename Char = char>
struct int_to_str2
#ifndef MIRROR_DOCUMENTATION_ONLY
 : aux::istr_to_str<
	Char,
	basic_string<Char, Char('0'),Char('1')>,
	typename aux::conv_int_to_istr<
		typename std::remove_cv<decltype(IntegralConstant::value)>::type,
		2,
		IntegralConstant::value
	>::type
>
#else
 : String
#endif
{ };

template <typename Int, Int I, typename Char = char>
struct int_to_str2_c
 : int_to_str2<integral_constant<Int, I>, Char>
{ };

/// Converts an IntegralConstant to a string of its decadic digits
/**
 *  @ingroup ct_utils
 */
template <typename IntegralConstant, typename Char = char>
struct int_to_str10
#ifndef MIRROR_DOCUMENTATION_ONLY
 : aux::istr_to_str<
	Char,
	basic_string<
		Char,
		Char('0'),Char('1'),Char('2'),Char('3'),Char('4'),
		Char('5'),Char('6'),Char('7'),Char('8'),Char('9')
	>,
	typename aux::conv_int_to_istr<
		typename std::remove_cv<decltype(IntegralConstant::value)>::type,
		10,
		IntegralConstant::value
	>::type
>
#else
 : String
#endif
{ };

template <typename Int, Int I, typename Char = char>
struct int_to_str10_c
 : int_to_str10<integral_constant<Int, I>, Char>
{ };

/// Converts an IntegralConstant to a string of its hexadecimal digits
/**
 *  @ingroup ct_utils
 */
template <typename IntegralConstant, typename Char = char>
struct int_to_str16
#ifndef MIRROR_DOCUMENTATION_ONLY
 : aux::istr_to_str<
	Char,
	basic_string<
		Char,
		Char('0'),Char('1'),Char('2'),Char('3'),
		Char('4'),Char('5'),Char('6'),Char('7'),
		Char('8'),Char('9'),Char('A'),Char('B'),
		Char('C'),Char('D'),Char('E'),Char('F')
	>,
	typename aux::conv_int_to_istr<
		typename std::remove_cv<decltype(IntegralConstant::value)>::type,
		16,
		IntegralConstant::value
	>::type
>
#else
 : String
#endif
{ };

template <typename Int, Int I, typename Char = char>
struct int_to_str16_c
 : int_to_str16<integral_constant<Int, I>, Char>
{ };

} // namespace ct
} // namespace mire

#endif //include guard

