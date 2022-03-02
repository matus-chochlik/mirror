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

#if defined(MIRROR_DOXYGEN)
/// @brief Makes an array of values of metaobject properties extracted by transform.
/// @ingroup sequence_operations
/// @see make_array
/// @see make_value_tuple
/// @see apply_to_init_list_of
///
/// This function applies the specified transform on each metaobject in a sequence
/// and returns the results as an array with explicitly specified element type
/// @c E.
template <typename E>
constexpr auto
make_array_of(metaobject_sequence auto mo, auto transform) noexcept
  -> std::array<E, __unspecified>;
#else
template <typename E, __metaobject_id... M, typename F>
constexpr auto
make_array_of(unpacked_metaobject_sequence<M...>, F transform) noexcept
  -> std::array<E, sizeof...(M)> {
    return {{transform(wrapped_metaobject<M>{})...}};
}

template <typename E, __metaobject_id M, typename F>
auto make_array_of(wrapped_metaobject<M> mo, F transform) noexcept
  requires(__metaobject_is_meta_object_sequence(M)) {
    return make_array_of<E>(unpack(mo), transform);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Makes an array of values of metaobject properties extracted by transform.
/// @ingroup sequence_operations
/// @see make_array_of
/// @see make_value_tuple
/// @see apply_to_init_list
///
/// This function applies the specified transform on each metaobject in a sequence
/// and returns the results as an array with element type auto-detected from
/// the return type of transform.
/// @c E.
template <typename E>
constexpr auto make_array(metaobject_sequence auto mo, auto transform) noexcept
  -> std::array<E, __unspecified>;
#else
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
#endif

} // namespace mirror

#endif // MIRROR_MAKE_ARRAY_HPP

