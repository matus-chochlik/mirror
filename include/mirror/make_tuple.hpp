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

#if defined(MIRROR_DOXYGEN)
/// @brief Makes a default-initialized tuple from metaobjects reflecting types.
/// @ingroup sequence_operations
/// @see get_reflected_type_t
/// @see make_array
/// @see make_array_of
///
/// This function un-reflects the types reflected by metaobjects in a sequence
/// and returns a default-initialized instantiation of std::tuple.
constexpr auto make_value_tuple(metaobject_sequence mo);
#else
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
#endif
} // namespace mirror

#endif // MIRROR_MAKE_TUPLE_HPP

