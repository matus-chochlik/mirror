/**
 * @file mire/ct/empty.hpp
 * @brief Implementation of the empty and nonempty meta-functions
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_EMPTY_1105240825_HPP
#define MIRE_CT_EMPTY_1105240825_HPP

#include <mire/ct/default.hpp>
#include <mire/ct/int_const.hpp>

namespace mire {
namespace ct {

template <typename ... P>
struct empty<range<P...>>
 : integral_constant<bool, sizeof ... (P) == 0>
{ };

template <typename ... P>
struct nonempty<range<P...>>
 : integral_constant<bool, sizeof ... (P) != 0>
{ };

template <typename Char, Char ... C>
struct empty<basic_string<Char, C...>>
 : integral_constant<bool, sizeof ... (C) == 0>
{ };

template <typename Char, Char ... C>
struct nonempty<basic_string<Char, C...>>
 : integral_constant<bool, sizeof ... (C) != 0>
{ };

} // namespace ct
} // namespace mire

#endif //include guard

