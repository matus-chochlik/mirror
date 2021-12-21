/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_SEQUENCE_HPP
#define MIRROR_SEQUENCE_HPP

#include "primitives.hpp"

namespace mirror {

// transform
template <__metaobject_id... M, typename F>
constexpr auto transform(unpacked_metaobject_sequence<M...>, F function) {
    return unpacked_metaobject_sequence<unwrap(function(metaobject<M>{}))...>{};
}

template <__metaobject_id M, typename F>
constexpr auto transform(metaobject<M> mo, F function) requires(
  __metaobject_is_meta_object_sequence(M)) {
    return transform(unpack(mo), function);
}

// transform types
template <
  template <typename...>
  class Container,
  template <typename>
  class Transform,
  __metaobject_id... M>
constexpr auto store_transformed_types(unpacked_metaobject_sequence<M...>) {
    return Container<typename Transform<__unrefltype(M)>::type...>{};
}

template <
  template <typename...>
  class Container,
  template <typename>
  class Transform,
  __metaobject_id M>
constexpr auto store_transformed_types(metaobject<M> mo) requires(
  __metaobject_is_meta_object_sequence(M)) {
    return store_transformed_types(unpack(mo));
}

template <template <typename> class Transform, __metaobject_id... M>
constexpr auto transform_types(unpacked_metaobject_sequence<M...> ms) {
    return store_transformed_types<type_list, Transform>(ms);
}

template <template <typename> class Transform, __metaobject_id M>
constexpr auto transform_types(metaobject<M> mo) requires(
  __metaobject_is_meta_object_sequence(M)) {
    return store_transformed_types<type_list, Transform>(unpack(mo));
}

// extract types
template <__metaobject_id... M>
constexpr auto extract_types(unpacked_metaobject_sequence<M...> ms) {
    return transform_types<std::type_identity>(ms);
}

template <__metaobject_id M>
constexpr auto extract_types(metaobject<M> mo) requires(
  __metaobject_is_meta_object_sequence(M)) {
    return transform_types<std::type_identity>(unpack(mo));
}

// for each
template <__metaobject_id... M, typename F>
constexpr void for_each(unpacked_metaobject_sequence<M...>, F function) {
    (void)(..., function(metaobject<M>{}));
}

template <__metaobject_id M, typename F>
constexpr void for_each(metaobject<M> mo, F function) requires(
  __metaobject_is_meta_object_sequence(M)) {
    return for_each(unpack(mo), std::move(function));
}

// for each with iteration info
class for_each_iteration_info {
private:
    std::size_t _index;
    std::size_t _count;

public:
    constexpr for_each_iteration_info(
      std::size_t index,
      std::size_t count) noexcept
      : _index{index}
      , _count{count} {}

    constexpr auto is_first() const noexcept -> bool {
        return _index == 0Z;
    }

    constexpr auto is_last() const noexcept -> bool {
        return _index + 1Z >= _count;
    }

    constexpr auto index() const noexcept -> std::size_t {
        return _index;
    }

    constexpr auto count() const noexcept -> std::size_t {
        return _count;
    }
};

template <__metaobject_id M, typename F>
constexpr void for_each_info(metaobject<M> mo, F function) requires(
  __metaobject_is_meta_object_sequence(M)) {
    std::size_t index{0};
    const auto count{__metaobject_get_size(M)};
    return for_each(unpack(mo), [&](auto me) {
        function(me, for_each_iteration_info(index++, count));
    });
}

// find if
template <typename F>
constexpr auto find_if(unpacked_metaobject_sequence<>, F) {
    return no_metaobject;
}

template <__metaobject_id M1, __metaobject_id... M, typename F>
constexpr auto find_if(unpacked_metaobject_sequence<M1, M...>, F predicate) {
    if constexpr(predicate(metaobject<M1>{})) {
        return metaobject<M1>{};
    } else {
        return find_if(unpacked_metaobject_sequence<M...>{}, predicate);
    }
}

template <__metaobject_id M, typename F>
constexpr auto find_if(metaobject<M> mo, F predicate) requires(
  __metaobject_is_meta_object_sequence(M)) {
    return find_if(unpack(mo), predicate);
}

// all of
template <__metaobject_id... M, typename F>
constexpr auto all_of(unpacked_metaobject_sequence<M...>, F predicate) -> bool {
    return (... && predicate(metaobject<M>{}));
}

template <__metaobject_id M, typename F>
constexpr auto all_of(metaobject<M> mo, F predicate)
  -> bool requires(__metaobject_is_meta_object_sequence(M)) {
    return all_of(unpack(mo), predicate);
}

// any_of
template <__metaobject_id... M, typename F>
constexpr auto any_of(unpacked_metaobject_sequence<M...>, F predicate) -> bool {
    return (... || predicate(metaobject<M>{}));
}

template <__metaobject_id M, typename F>
constexpr auto any_of(metaobject<M> mo, F predicate)
  -> bool requires(__metaobject_is_meta_object_sequence(M)) {
    return any_of(unpack(mo), predicate);
}

// none_of
template <__metaobject_id... M, typename F>
constexpr auto none_of(unpacked_metaobject_sequence<M...>, F predicate)
  -> bool {
    return !(... || predicate(metaobject<M>{}));
}

template <__metaobject_id M, typename F>
constexpr auto none_of(metaobject<M> mo, F predicate)
  -> bool requires(__metaobject_is_meta_object_sequence(M)) {
    return none_of(unpack(mo), predicate);
}

// select
template <typename T, __metaobject_id... M, typename F, typename... P>
constexpr auto
select(unpacked_metaobject_sequence<M...>, F function, T fallback, P&&... param)
  -> T {
    (void)(..., function(fallback, metaobject<M>{}, std::forward<P>(param)...));
    return fallback;
}

template <typename T, __metaobject_id M, typename F, typename... P>
constexpr auto select(metaobject<M> mo, F function, T fallback, P&&... param)
  -> T requires(__metaobject_is_meta_object_sequence(M)) {
    return select(
      unpack(mo),
      std::move(function),
      std::move(fallback),
      std::forward<P>(param)...);
}

} // namespace mirror

#endif // MIRROR_SEQUENCE_HPP
