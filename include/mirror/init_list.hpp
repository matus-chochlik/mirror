/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_INIT_LIST_HPP
#define MIRROR_INIT_LIST_HPP

#include "sequence.hpp"
#include <initializer_list>

namespace mirror {

#if defined(MIRROR_DOXYGEN)
/// @brief Applies finction to init-list of values of properties from transform.
/// @ingroup sequence_operations
/// @see make_array_of
/// @see make_value_tuple
/// @see apply_to_init_list
///
/// This function invokes the specified transform on each metaobject in a
/// sequence creates an initializer list from the obtained values and calls the
/// specified aggregate function on the init-list.
/// In this version of the function allows to explicitly specify the list
/// element type @c E.
template <typename E>
constexpr auto
apply_to_init_list_of(metaobject auto mo, auto transform, auto aggregate);
#else
template <typename E, __metaobject_id... M, typename F, typename A>
constexpr auto apply_to_init_list_of(
  unpacked_metaobject_sequence<M...>,
  F transform,
  A aggregate) {
    return aggregate(
      std::initializer_list<E>{transform(wrapped_metaobject<M>{})...});
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Applies finction to init-list of values of properties from transform.
/// @ingroup sequence_operations
/// @see make_array
/// @see make_value_tuple
/// @see apply_to_init_list_of
///
/// This function invokes the specified transform on each metaobject in a
/// sequence creates an initializer list from the obtained values and calls the
/// specified aggregate function on the init-list.
constexpr auto
apply_to_init_list_of(metaobject auto mo, auto transform, auto aggregate);
#else
template <__metaobject_id... M, typename F, typename A>
constexpr auto apply_to_init_list(
  unpacked_metaobject_sequence<M...>,
  F transform,
  A aggregate) {
    return aggregate(
      std::initializer_list<
        std::common_type_t<decltype(transform(wrapped_metaobject<M>{}))...>>{
        transform(wrapped_metaobject<M>{})...});
}

template <__metaobject_id M, typename F, typename A>
constexpr auto apply_to_init_list(
  wrapped_metaobject<M> mo,
  F transform,
  A aggregate) requires(__metaobject_is_meta_object_sequence(M)) {
    return apply_to_init_list(unpack(mo), transform, aggregate);
}
#endif

} // namespace mirror

#endif // MIRROR_MAKE_ARRAY_HPP

