/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_HASH_HPP
#define MIRROR_HASH_HPP

#include "full_name.hpp"
#include "sequence.hpp"
#include <functional>

namespace mirror {

template <__metaobject_id M>
constexpr auto get_hash(wrapped_metaobject<M> mo) -> size_t
  requires(!__metaobject_is_meta_object_sequence(M)) {
    return std::hash<std::string>{}(get_full_name(mo));
}

constexpr auto _do_get_hash(unpacked_metaobject_sequence<>, size_t s)
  -> size_t {
    return s;
}

template <__metaobject_id M, __metaobject_id... Ms>
constexpr auto _do_get_hash(unpacked_metaobject_sequence<M, Ms...>, size_t s)
  -> size_t {
    return s ^
           std::hash<std::string>{}(get_full_name(wrapped_metaobject<M>{})) ^
           _do_get_hash(unpacked_metaobject_sequence<Ms...>{}, s + 1);
}

template <__metaobject_id... M>
constexpr auto get_hash(unpacked_metaobject_sequence<M...> ms) {
    return _do_get_hash(ms, 0Z);
}

template <__metaobject_id M>
constexpr auto get_hash(wrapped_metaobject<M> mo) -> size_t
  requires(__metaobject_is_meta_object_sequence(M)) {
    return get_hash(unpack(mo));
}

} // namespace mirror

#endif

