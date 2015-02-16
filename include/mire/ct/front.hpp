/**
 * @file mire/ct/front.hpp
 * @brief Implementation of the front meta-function
 *
 *  Copyright 2008-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_FRONT_1105240825_HPP
#define MIRE_CT_FRONT_1105240825_HPP

#include <mire/ct/default.hpp>
#include <mire/ct/int_const.hpp>
#include <mire/ct/identity.hpp>

namespace mire {
namespace ct {

template <>
struct front<range<>>
 : nil_t
{ };

template <typename F, typename ... P>
struct front<range<F, P...>>
 : identity<F>
{ };

template <typename Char>
struct front<basic_string<Char> >
 : integral_constant<Char, Char(0)>
{ };

template <typename Char, Char C, Char ... Cn>
struct front<basic_string<Char, C, Cn...> >
 : integral_constant<Char, C>
{ };

} // namespace ct
} // namespace mire

#endif //include guard

