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

/// This trait meta-function can be used to check if the passed type is a range
/**
 *  @ingroup ct_utils
 */
template <typename T>
struct is_range
#ifndef MIRROR_DOCUMENTATION_ONLY
 : aux::is_range<typename evaluate<T>::type>
#else
 : BooleanConstant
#endif
{ };

namespace aux {

template <typename T>
struct is_string
 : false_type
{ };

template <typename Char, Char ... C>
struct is_string<basic_string<Char, C...>>
 : true_type
{ };

template <char ... C>
struct is_string<string<C...>>
 : true_type
{ };

} // namespace aux

/// This trait meta-function can be used to check if the passed type is a string
/**
 *  @ingroup ct_utils
 */
template <typename T>
struct is_string
#ifndef MIRROR_DOCUMENTATION_ONLY
 : aux::is_string<typename evaluate<T>::type>
#else
 : BooleanConstant
#endif
{ };


namespace aux {

template <typename T>
struct is_optional
 : false_type
{ };

template <typename T>
struct is_optional<optional<T>>
 : true_type
{ };

} // namespace aux

/// This trait meta-function can be used to check if the passed type is optional
/**
 *  @ingroup ct_utils
 */
template <typename T>
struct is_optional
#ifndef MIRROR_DOCUMENTATION_ONLY
 : aux::is_optional<typename evaluate<T>::type>
#else
 : BooleanConstant
#endif
{ };

namespace aux {

template <typename T>
struct is_nil_t
 : false_type
{ };

template <>
struct is_nil_t<nil_t>
 : true_type
{ };

} // namespace aux

/// This trait meta-function can be used to check if the passed type is a nil_t
/**
 *  @ingroup ct_utils
 */
template <typename T>
struct is_nil_t
#ifndef MIRROR_DOCUMENTATION_ONLY
 : aux::is_nil_t<typename evaluate<T>::type>
#else
 : BooleanConstant
#endif
{ };

} // namespace ct
} // namespace mire

#endif //include guard

