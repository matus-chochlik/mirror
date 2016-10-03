/**
 * @file mire/ct/only_if.hpp
 * @brief Implementation of the only_if meta-function
 *
 *  Copyright 2008-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_ONLY_IF_1105240825_HPP
#define MIRE_CT_ONLY_IF_1105240825_HPP

#include <mire/ct/default.hpp>
#include <mire/ct/prepend.hpp>
#include <mire/ct/lambda.hpp>
#include <mire/ct/conditional.hpp>

namespace mire {
namespace ct {

#ifndef MIRROR_DOCUMENTATION_ONLY

template <typename Char, typename Predicate>
struct only_if<basic_string<Char>, Predicate>
 : basic_string<Char>
{ };

template <typename Char, Char C, Char ... P, class Predicate>
struct only_if<basic_string<Char, C, P...>, Predicate>
 : conditional<
	apply_c<Predicate, Char, C>,
	prepend_c<only_if<basic_string<Char, P...>, Predicate>, Char, C>,
	only_if<basic_string<Char, P...>, Predicate>
>
{ };

template <typename Predicate>
struct only_if<range<>, Predicate>
 : range<>
{ };

template <typename T, typename ... P, class Predicate>
struct only_if<range<T, P...>, Predicate>
 : conditional<
	apply<Predicate, T>,
	prepend<only_if<range<P...>, Predicate>, T>,
	only_if<range<P...>, Predicate>
>
{ };

#endif // !MIRROR_DOCUMENTATION_ONLY

} // namespace ct
} // namespace mire

#endif //include guard

