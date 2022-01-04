/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_MAKE_ARRAY_HPP
#define MIRROR_MAKE_ARRAY_HPP

#include "sequence.hpp"
#include <array>

namespace mirror {

template <__metaobject_id... M, typename F>
constexpr auto
make_array(unpacked_metaobject_sequence<M...>, F transform) noexcept
  -> std::array<
    std::common_type_t<decltype(transform(wrapped_metaobject<M>{}))...>,
    sizeof...(M)> {
    return {{transform(wrapped_metaobject<M>{})...}};
}

template <__metaobject_id M, typename F>
auto make_array(wrapped_metaobject<M> mo, F transform) noexcept
  requires(__metaobject_is_meta_object_sequence(M)) {
    return make_array(unpack(mo), transform);
}

} // namespace mirror

#endif // MIRROR_MAKE_ARRAY_HPP

