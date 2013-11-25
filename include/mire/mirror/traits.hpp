/**
 *  @file mire/mirror/traits.hpp
 *  @brief Metaobject traits
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2006-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_MIRROR_TRAITS_1310291537_HPP
#define MIRE_MIRROR_TRAITS_1310291537_HPP

#include <mire/ct/int_const.hpp>
#include <mire/mirror/evaluate.hpp>

namespace mire {
namespace mirror {

// *is_metaobject*
namespace _aux {

template <typename X>
struct is_metaobject
 : ct::false_type
{ };

template <typename R, typename M>
struct is_metaobject<meta<R, M>>
 : ct::true_type
{ };

} // namespace _aux

template <typename X>
struct is_metaobject
 : _aux::is_metaobject<typename evaluate<X>::type>
{ };

// *is_specifier*
namespace _aux {

template <typename X>
struct is_specifier
 : ct::false_type
{ };

template <typename T>
struct is_specifier<spec<T>>
 : ct::true_type
{ };

} // namespace _aux

template <typename X>
struct is_specifier
 : _aux::is_specifier<typename evaluate<X>::type>
{ };


// *has_name*
namespace _aux {

template <typename X>
struct has_name
 : ct::false_type
{ };

template <typename R, typename M>
struct has_name<meta<R, M>>
 : R::has_name
{ };

} // namespace _aux

template <typename X>
struct has_name
 : _aux::has_name<typename evaluate<X>::type>
{ };

// *has_scope*
namespace _aux {

template <typename X>
struct has_scope
 : ct::false_type
{ };

template <typename R, typename M>
struct has_scope<meta<R, M>>
 : R::has_scope
{ };

} // namespace _aux

template <typename X>
struct has_scope
 : _aux::has_scope<typename evaluate<X>::type>
{ };

// *is_scope*
namespace _aux {

template <typename X>
struct is_scope
 : ct::false_type
{ };

template <typename R, typename M>
struct is_scope<meta<R, M>>
 : R::is_scope
{ };

} // namespace _aux

template <typename X>
struct is_scope
 : _aux::is_scope<typename evaluate<X>::type>
{ };

// *is_class_member*
namespace _aux {

template <typename X>
struct is_class_member
 : ct::false_type
{ };

template <typename R, typename M>
struct is_class_member<meta<R, M>>
 : R::is_class_member
{ };

} // namespace _aux

template <typename X>
struct is_class_member
 : _aux::is_class_member<typename evaluate<X>::type>
{ };

// *has_template*
namespace _aux {

template <typename X>
struct has_template
 : ct::false_type
{ };

template <typename R, template <typename...> class T, typename ... P>
struct has_template<meta<R, T<P...>>>
 : R::is_template
{ };

template <typename R, typename M>
struct has_template<meta<R, M>>
 : R::has_template
{ };

} // namespace _aux

template <typename X>
struct has_template
 : _aux::has_template<typename evaluate<X>::type>
{ };

// *is_template*
namespace _aux {

template <typename X>
struct is_template
 : ct::false_type
{ };

template <typename R>
struct is_template<meta<R, void>>
 : R::is_template
{ };

template <typename R, typename M>
struct is_template<meta<R, M>>
 : ct::false_type
{ };

} // namespace _aux

template <typename X>
struct is_template
 : _aux::is_template<typename evaluate<X>::type>
{ };

} // namespace mirror
} // namespace mire

#endif // include guard
