/**
 * @file mire/ct/size.hpp
 * @brief Implementation of the size and length meta-functions
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_SIZE_1105240825_HPP
#define MIRE_CT_SIZE_1105240825_HPP

#include <mire/ct/default.hpp>
#include <mire/ct/int_const.hpp>

namespace mire {
namespace ct {

template <typename ... P>
struct size<range<P...>>
 : integral_constant<size_t, sizeof ... (P)>
{ };

template <typename Char, Char ... C>
struct size<basic_string<Char, C...> >
 : integral_constant<size_t, sizeof ... (C)>
{ };

template <typename Char, Char ... C>
struct length<basic_string<Char, C...> >
 : integral_constant<size_t, sizeof ... (C)>
{ };

} // namespace ct
} // namespace mire

#endif //include guard

