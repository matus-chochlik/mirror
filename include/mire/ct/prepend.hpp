/**
 *  @file mire/ct/prepend.hpp
 *  @brief Meta-function returning a range having the passed item
 *  prepended.
 *
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_PREPEND_1011291729_HPP
#define MIRE_CT_PREPEND_1011291729_HPP


#include <mire/ct/default.hpp>

namespace mire {
namespace ct {

#ifndef MIRROR_DOCUMENTATION_ONLY

template <typename ... P, typename ... T>
struct prepend<range<P...>, T...>
 : range<T..., P...>
{ };

template <typename Char, Char ... C, Char ... T>
struct prepend<basic_string<Char, C...>, integral_constant<Char, T>...>
 : basic_string<Char, T..., C...>
{ };

template <typename Char, Char ... C, Char ... T>
struct prepend_c<basic_string<Char, C...>, Char, T...>
 : basic_string<Char, T..., C...>
{ };

#endif // !MIRROR_DOCUMENTATION_ONLY

} // namespace ct
} // namespace mire

#endif //include guard

