/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_APPLY_HPP
#define MIRROR_APPLY_HPP

#include "primitives.hpp"
#include <tuple>

namespace mirror {

template <typename T>
constexpr auto get_tuple_indices(const T&) noexcept {
    return std::make_index_sequence<std::tuple_size_v<T>>{};
}

template <__metaobject_id M, typename C, typename A, size_t... I>
constexpr auto do_apply_on(
  wrapped_metaobject<M> mo,
  C& obj,
  A&& args,
  std::index_sequence<I...>) requires(__metaobject_is_meta_member_function(M)) {
    if constexpr(is_static(mo)) {
        return (*_get_pointer<M>::value)(std::get<I>(std::forward<A>(args))...);
    } else {
        return (obj.*_get_pointer<M>::value)(
          std::get<I>(std::forward<A>(args))...);
    }
}

#if defined(MIRROR_DOXYGEN)
/// @brief Applies the reflected member function on @p obj with specified @p args.
/// @ingroup operations
/// @see reflects_member_function
/// @see get_pointer
/// @see invoke_on
/// @see apply
constexpr auto apply_on(metaobject auto mo, auto& obj, auto&& args) requires(
  reflects_member_function(mo));
#else
template <__metaobject_id M, typename C, typename A>
constexpr auto apply_on(wrapped_metaobject<M> mo, C& obj, A&& args) requires(
  __metaobject_is_meta_member_function(M)) {
    return do_apply_on(mo, obj, std::forward<A>(args), get_tuple_indices(args));
}
#endif

template <__metaobject_id M, typename A, size_t... I>
constexpr auto do_apply(
  wrapped_metaobject<M>,
  A&& args,
  std::index_sequence<I...>) requires(__metaobject_is_meta_function(M)) {
    return (*_get_pointer<M>::value)(std::get<I>(std::forward<A>(args))...);
}

#if defined(MIRROR_DOXYGEN)
/// @brief Applies the reflected function on the specified @p args tuple.
/// @ingroup operations
/// @see reflects_function
/// @see reflects_member_function
/// @see is_static
/// @see get_pointer
/// @see invoke
/// @see apply_on
constexpr auto
apply(metaobject auto mo, auto&& args) requires(reflects_function(mo));
#else
template <__metaobject_id M, typename A>
constexpr auto apply(wrapped_metaobject<M> mo, A&& args) requires(
  __metaobject_is_meta_function(M)) {
    return do_apply(mo, std::forward<A>(args), get_tuple_indices(args));
}
#endif

template <__metaobject_id M, typename A, size_t... I>
constexpr auto do_apply(
  wrapped_metaobject<M>,
  A&& args,
  std::index_sequence<I...>) requires(__metaobject_is_meta_constructor(M)) {
    return __unrefltype(__metaobject_get_scope(M))(
      std::get<I>(std::forward<A>(args))...);
}

#if defined(MIRROR_DOXYGEN)
/// @brief Applies the reflected constructor on the specified @p args tuple.
/// @ingroup operations
/// @see reflects_function
/// @see reflects_member_function
/// @see is_static
/// @see get_pointer
/// @see invoke
/// @see apply_on
constexpr auto
apply(metaobject auto mo, auto&& args) requires(reflects_constructor(mo));
#else
template <__metaobject_id M, typename A>
constexpr auto apply(wrapped_metaobject<M> mo, A&& args) requires(
  __metaobject_is_meta_constructor(M)) {
    return do_apply(mo, std::forward<A>(args), get_tuple_indices(args));
}
#endif

} // namespace mirror

#endif
