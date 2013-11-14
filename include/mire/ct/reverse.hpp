/**
 * @file mire/ct/reverse.hpp
 * @brief Implementation of the reverse meta-function
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_REVERSE_1105240825_HPP
#define MIRE_CT_REVERSE_1105240825_HPP

#include <mire/ct/default.hpp>
#include <mire/ct/fold.hpp>
#include <mire/ct/prepend.hpp>
#include <mire/ct/lambda.hpp>

namespace mire {
namespace ct {

template <typename ... P>
struct reverse<range<P...>>
 : fold<range<P...>, range<>, prepend<arg<0>, arg<1>>>
{ };

template <typename ... P>
struct reverse<reverse<range<P...>>>
 : range<P...>
{ };

template <typename Char, Char ... C>
struct reverse<basic_string<Char, C...>>
 : fold<basic_string<Char, C...>, basic_string<Char>, prepend<arg<0>, arg<1>>>
{ };

template <typename Char, Char ... C>
struct reverse<reverse<basic_string<Char, C...>>>
 : basic_string<Char, C...>
{ };

} // namespace ct
} // namespace mire

#endif //include guard

