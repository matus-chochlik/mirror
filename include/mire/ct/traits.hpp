/**
 * @file mire/ct/traits.hpp
 * @brief Traits for the compile-time utilities
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_TRAITS_1105240825_HPP
#define MIRE_CT_TRAITS_1105240825_HPP

#include <mire/ct/evaluate.hpp>

namespace mire {
namespace ct {

#ifdef MIRROR_DOCUMENTATION_ONLY
/// This trait meta-function can be used to check if the passed type is a range
template <typename T>
struct is_range : BooleanConstant
{ };
#else

namespace aux {
template <typename T>
struct is_range
 : false_type
{ };

template <typename ... P>
struct is_range<range<P...>>
 : true_type
{ };
} // namespace aux

template <typename T>
struct is_range
 : aux::is_range<typename evaluate<T>::type>
{ };
#endif

#ifdef MIRROR_DOCUMENTATION_ONLY
/// This trait meta-function can be used to check if the passed type is a string
template <typename T>
struct is_string : BooleanConstant
{ };
#else

namespace aux {
template <typename T>
struct is_string
 : false_type
{ };

template <typename Char, Char ... C>
struct is_string<basic_string<Char, C...>>
 : true_type
{ };
} // namespace aux

template <typename T>
struct is_string
 : aux::is_string<typename evaluate<T>::type>
{ };
#endif

} // namespace ct
} // namespace mire

#endif //include guard

