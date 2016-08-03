/**
 * @file mire/ct/find_if.hpp
 * @brief Implementation of the find_if meta-function
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_FIND_IF_1105240825_HPP
#define MIRE_CT_FIND_IF_1105240825_HPP

#include <mire/ct/default.hpp>
#include <mire/ct/lambda.hpp>
#include <mire/ct/eval_if.hpp>

namespace mire {
namespace ct {

template <typename Predicate>
struct find_if<range<>, Predicate>
 : range<>
{ };

template <typename H, typename ... P, typename Predicate>
struct find_if<range<H, P...>, Predicate>
 : eval_if<
	apply<Predicate, H>,
	range<H, P...>,
	find_if<range<P...>, Predicate>
>
{ };

template <typename Char, typename Predicate>
struct find_if<basic_string<Char>, Predicate>
 : basic_string<Char>
{ };

template <typename Char, Char H, Char ... P, typename Predicate>
struct find_if<basic_string<Char, H, P...>, Predicate>
 : eval_if<
	apply_c<Predicate, Char, H>,
	basic_string<Char, H, P...>,
	find_if<basic_string<Char, P...>, Predicate>
>
{ };

} // namespace ct
} // namespace mire

#endif //include guard

