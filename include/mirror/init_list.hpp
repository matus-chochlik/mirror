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

template <typename T, __metaobject_id... M, typename F, typename A>
constexpr auto
fold_init_list_of(unpacked_metaobject_sequence<M...>, F transform, A aggregate) {
    return aggregate(
      std::initializer_list<T>{transform(wrapped_metaobject<M>{})...});
}

template <__metaobject_id... M, typename F, typename A>
constexpr auto
fold_init_list(unpacked_metaobject_sequence<M...>, F transform, A aggregate) {
    return aggregate(
      std::initializer_list<
        std::common_type_t<decltype(transform(wrapped_metaobject<M>{}))...>>{
        transform(wrapped_metaobject<M>{})...});
}

template <__metaobject_id M, typename F, typename A>
constexpr auto fold_init_list(
  wrapped_metaobject<M> mo,
  F transform,
  A aggregate) requires(__metaobject_is_meta_object_sequence(M)) {
    return fold_init_list(unpack(mo), transform, aggregate);
}

} // namespace mirror

#endif // MIRROR_MAKE_ARRAY_HPP

