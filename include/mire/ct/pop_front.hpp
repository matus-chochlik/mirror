/**
 * @file mire/ct/pop_front.hpp
 * @brief Implementation of the pop_front meta-function
 *
 *  Copyright 2008-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_POP_FRONT_1105240825_HPP
#define MIRE_CT_POP_FRONT_1105240825_HPP

#include <mire/ct/default.hpp>

namespace mire {
namespace ct {

template <>
struct pop_front<range<>>
 : range<>
{ };

template <typename F, typename ... P>
struct pop_front<range<F, P...>>
 : range<P...>
{ };

template <typename Char>
struct pop_front<basic_string<Char>>
 : basic_string<Char>
{ };

template <typename Char, Char C, Char ... Cn>
struct pop_front<basic_string<Char, C, Cn...>>
 : basic_string<Char, Cn...>
{ };

} // namespace ct
} // namespace mire

#endif //include guard

