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
#include "placeholder.hpp"
#include "sequence.hpp"
#include <functional>

namespace mirror {

// TODO: make the hashes platform-independent

using hash_t = std::uint64_t;

template <__metaobject_id M>
constexpr auto get_hash(wrapped_metaobject<M>) -> hash_t
  requires(__metaobject_is_meta_global_scope(M)) {
    return 95ULL;
}

template <__metaobject_id M>
constexpr auto get_hash(wrapped_metaobject<M> mo) -> hash_t requires(
  !__metaobject_is_meta_object_sequence(M) &&
  !__metaobject_is_meta_global_scope(M) && !__metaobject_is_meta_callable(M) &&
  !__metaobject_is_meta_function_call_expression(M) &&
  !__metaobject_is_meta_parenthesized_expression(M)) {
    return std::hash<std::string>{}(get_full_name(mo));
}

constexpr auto _do_get_hash(unpacked_metaobject_sequence<>, hash_t s)
  -> hash_t {
    return s;
}

template <__metaobject_id M, __metaobject_id... Ms>
constexpr auto _do_get_hash(unpacked_metaobject_sequence<M, Ms...>, hash_t s)
  -> hash_t {
    return s ^
           std::hash<std::string>{}(get_full_name(wrapped_metaobject<M>{})) ^
           _do_get_hash(unpacked_metaobject_sequence<Ms...>{}, s + 1);
}

template <__metaobject_id... M>
constexpr auto get_hash(unpacked_metaobject_sequence<M...> ms) {
    return _do_get_hash(ms, 0Z);
}

template <__metaobject_id M>
constexpr auto get_hash(wrapped_metaobject<M> mo) -> hash_t
  requires(__metaobject_is_meta_object_sequence(M)) {
    return get_hash(unpack(mo));
}

template <__metaobject_id M>
constexpr auto get_hash(wrapped_metaobject<M> mo) -> hash_t
  requires(__metaobject_is_meta_callable(M)) {
    return std::hash<std::string>{}(get_full_name(mo)) ^
           get_hash(transform(get_parameters(mo), get_type(_1)));
}

template <__metaobject_id M>
constexpr auto get_hash(wrapped_metaobject<M> mo) -> hash_t
  requires(__metaobject_is_meta_function_call_expression(M)) {
    return get_hash(get_callable(mo));
}

template <__metaobject_id M>
constexpr auto get_hash(wrapped_metaobject<M> mo) -> hash_t
  requires(__metaobject_is_meta_parenthesized_expression(M)) {
    return get_hash(get_subexpression(mo));
}

} // namespace mirror

#endif

