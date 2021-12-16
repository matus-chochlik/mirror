/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_MAKE_ARRAY_HPP
#define MIRROR_MAKE_ARRAY_HPP

#include "primitives.hpp"
#include <array>

namespace mirror {

template <__metaobject_id... M, typename F>
auto make_array(unpacked_metaobject_sequence<M...>, F& transform) -> std::array<
  std::common_type_t<decltype(transform(metaobject<M>{}))...>,
  sizeof...(M)> {
    return {{transform(metaobject<M>{})...}};
}

template <__metaobject_id M, typename F>
auto make_array(metaobject<M> mo, F transform) requires(
  __metaobject_is_meta_object_sequence(M)) {
    return make_array(unpack(mo), transform);
}

} // namespace mirror

#endif // MIRROR_MAKE_ARRAY_HPP

