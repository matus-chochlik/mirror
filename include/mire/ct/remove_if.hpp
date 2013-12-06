/**
 * @file mire/ct/remove_if.hpp
 * @brief Implementation of the remove_if meta-function
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_FIND_IF_1105240825_HPP
#define MIRE_CT_FIND_IF_1105240825_HPP

#include <mire/ct/default.hpp>
#include <mire/ct/lambda.hpp>
#include <mire/ct/if.hpp>

namespace mire {
namespace ct {
namespace _aux {

template <typename Result, typename Temp, typename Predicate>
struct remove_if;

// range
template <typename ... P, typename Predicate>
struct remove_if<range<P...>, range<>, Predicate>
 : range<P...>
{ };

template <typename ... P, typename ... R, typename H, typename Predicate>
struct remove_if<range<P...>, range<H, R...>, Predicate>
 : remove_if<
	typename if_<
		apply<Predicate, H>,
		range<P...>,
		range<P..., H>
	>::type,
	range<R...>,
	Predicate
>
{ };

// string
template <typename Char, Char ... P, typename Predicate>
struct remove_if<basic_string<Char, P...>, basic_string<Char>, Predicate>
 : basic_string<Char, P...>
{ };

template <typename Char, Char ... P, Char ... R, Char H, typename Predicate>
struct remove_if<
	basic_string<Char, P...>,
	basic_string<Char, H, R...>,
	Predicate
>: remove_if<
	typename if_<
		apply_c<Predicate, Char, H>,
		basic_string<Char, P...>,
		basic_string<Char, P..., H>
	>::type,
	basic_string<Char, R...>,
	Predicate
>
{ };

} // namespace _aux

template <typename ... P, typename Predicate>
struct remove_if<range<P...>, Predicate>
 : _aux::remove_if<range<>, range<P...>, Predicate>
{ };

template <typename Char, Char ... P, typename Predicate>
struct remove_if<basic_string<Char, P...>, Predicate>
 : _aux::remove_if<basic_string<Char>, basic_string<Char, P...>, Predicate>
{ };

} // namespace ct
} // namespace mire

#endif //include guard

