/**
 * @file mire/ct/zip.hpp
 * @brief Implementation of the zip meta-function
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_ZIP_1105240825_HPP
#define MIRE_CT_ZIP_1105240825_HPP

#include <mire/ct/default.hpp>
#include <mire/ct/or.hpp>
#include <mire/ct/empty.hpp>
#include <mire/ct/front.hpp>
#include <mire/ct/pop_front.hpp>

namespace mire {
namespace ct {
namespace _aux {

template <typename Range, typename Empty, typename ... Ranges>
struct zip;

// range
template <typename ... P, typename ... PT>
struct zip<range<P...>, false_type, range<PT>...>
 : range<P..., PT...>
{ };

template <typename ... P, typename ... Ranges>
struct zip<range<P...>, false_type, Ranges...>
 : zip<
	range<P..., typename front<Ranges>::type...>,
	false_type,
	typename pop_front<Ranges>::type...
>
{ };

template <typename ... Ranges>
struct zip<range<>, true_type, Ranges...>
 : empty_range
{ };

// string
template <typename Char, Char ... P, Char ... PT>
struct zip<basic_string<Char, P...>, false_type, basic_string<Char, PT>...>
 : basic_string<Char, P..., PT...>
{ };

template <typename Char, Char ... P, typename ... Strings>
struct zip<basic_string<Char, P...>, false_type, Strings...>
 : zip<
	basic_string<Char, P..., front<Strings>::value...>,
	false_type,
	typename pop_front<Strings>::type...
>
{ };

template <typename Char, typename ... Strings>
struct zip<basic_string<Char>, true_type, Strings...>
 : basic_string<Char>
{ };

} // namespace _aux

// range
template <typename ...P, typename ... Ranges>
struct zip<range<P...>, Ranges...>
 : _aux::zip<
	range<>,
	typename evaluate<or_<empty<range<P...>>, empty<Ranges>...>>::type,
	range<P...>,
	Ranges...
>
{ };

// string
template <typename Char, Char ...P, typename ... Strings>
struct zip<basic_string<Char, P...>, Strings...>
 : _aux::zip<
	basic_string<Char>,
	typename evaluate<or_<
		empty<basic_string<Char, P...>>,
		empty<Strings>...
	>>::type,
	basic_string<Char, P...>,
	Strings...
>
{ };

} // namespace ct
} // namespace mire

#endif //include guard

