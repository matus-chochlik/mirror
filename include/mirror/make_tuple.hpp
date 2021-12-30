/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_MAKE_TUPLE_HPP
#define MIRROR_MAKE_TUPLE_HPP

#include "sequence.hpp"
#include <tuple>

namespace mirror {

template <__metaobject_id... M>
constexpr auto make_value_tuple(unpacked_metaobject_sequence<M...>) {
    return std::tuple<
      std::remove_cv_t<std::remove_reference_t<__unrefltype(M)>>...>{};
}

template <__metaobject_id M>
constexpr auto make_value_tuple(wrapped_metaobject<M> mo) requires(
  __metaobject_is_meta_object_sequence(M)) {
    return make_value_tuple(unpack(mo));
}
//
} // namespace mirror

#endif // MIRROR_MAKE_TUPLE_HPP

