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
#include <string>

namespace mirror {

template <__metaobject_id... M>
struct unpacked_metaobject_sequence {};

template <__metaobject_id M>
consteval auto is_object_sequence(wrapped_metaobject<M>) noexcept -> bool {
    return __metaobject_is_meta_object_sequence(M);
}

template <__metaobject_id... M>
consteval auto is_object_sequence(unpacked_metaobject_sequence<M...>) noexcept
  -> bool {
    return true;
}

/// @brief Indicates if the argument is a sequence of metaobjects.
/// @ingroup classification
/// @see reflects_object_sequence
/// @see is_empty
/// @see get_size
template <typename X>
consteval auto is_object_sequence(const X&) noexcept -> bool {
    return false;
}

/// @brief Concept for metaobject sequence types.
/// @ingroup classification
/// @see reflects_object_sequence
/// @see is_object_sequence
template <typename X>
concept metaobject_sequence = is_object_sequence(X{});

template <__metaobject_id... M>
consteval auto is_empty(unpacked_metaobject_sequence<M...>) noexcept -> bool {
    return sizeof...(M) == 0Z;
}

template <__metaobject_id... M>
consteval auto get_size(unpacked_metaobject_sequence<M...>) noexcept -> size_t {
    return sizeof...(M);
}

/// @brief Unpacks a sequence metaobject into sequence of separate metaobject ids.
/// @ingroup sequence_operations
/// @see reflects_object_sequence
template <__metaobject_id M>
constexpr auto unpack(wrapped_metaobject<M>) noexcept
  -> __unpack_metaobject_seq<unpacked_metaobject_sequence, M> requires(
    __metaobject_is_meta_object_sequence(M)) {
    return {};
}

template <__metaobject_id... M>
constexpr auto unpack(unpacked_metaobject_sequence<M...> ms) noexcept {
    return ms;
}

#if defined(MIRROR_DOXYGEN)
/// @brief Makes an unpacked_metaobject_sequence from individual metaobjects.
/// @ingroup sequence_operations
/// @see is_object_sequence
constexpr auto make_sequence(metaobject auto...) noexcept;
#else
template <__metaobject_id... M>
constexpr auto make_sequence(wrapped_metaobject<M>...) noexcept
  -> unpacked_metaobject_sequence<M...> {
    return {};
}
#endif

// count if
template <__metaobject_id... M, typename F>
constexpr auto
count_if(unpacked_metaobject_sequence<M...>, F predicate) noexcept -> size_t {
    return (0Z + ... + (predicate(wrapped_metaobject<M>{}) ? 1Z : 0Z));
}

template <__metaobject_id M, typename F>
constexpr auto count_if(wrapped_metaobject<M> mo, F predicate) noexcept
  -> size_t requires(__metaobject_is_meta_object_sequence(M)) {
    return count_if(unpack(mo), predicate);
}

// transform
template <__metaobject_id... M, typename F>
constexpr auto
transform(unpacked_metaobject_sequence<M...>, F function) noexcept {
    return unpacked_metaobject_sequence<unwrap(
      function(wrapped_metaobject<M>{}))...>{};
}

template <__metaobject_id M, typename F>
constexpr auto transform(wrapped_metaobject<M> mo, F function) noexcept
  requires(__metaobject_is_meta_object_sequence(M)) {
    return transform(unpack(mo), function);
}

// transform types
template <
  template <typename...>
  class Container,
  template <typename>
  class Transform,
  __metaobject_id... M>
constexpr auto
store_transformed_types(unpacked_metaobject_sequence<M...>) noexcept {
    return Container<typename Transform<__unrefltype(M)>::type...>{};
}

template <
  template <typename...>
  class Container,
  template <typename>
  class Transform,
  __metaobject_id M>
constexpr auto store_transformed_types(wrapped_metaobject<M> mo) noexcept
  requires(__metaobject_is_meta_object_sequence(M)) {
    return store_transformed_types(unpack(mo));
}

template <template <typename> class Transform, __metaobject_id... M>
constexpr auto transform_types(unpacked_metaobject_sequence<M...> ms) noexcept {
    return store_transformed_types<type_list, Transform>(ms);
}

template <template <typename> class Transform, __metaobject_id M>
constexpr auto transform_types(wrapped_metaobject<M> mo) noexcept
  requires(__metaobject_is_meta_object_sequence(M)) {
    return store_transformed_types<type_list, Transform>(unpack(mo));
}

// extract types
template <__metaobject_id... M>
constexpr auto extract_types(unpacked_metaobject_sequence<M...> ms) noexcept {
    return transform_types<std::type_identity>(ms);
}

template <__metaobject_id M>
constexpr auto extract_types(wrapped_metaobject<M> mo) noexcept
  requires(__metaobject_is_meta_object_sequence(M)) {
    return transform_types<std::type_identity>(unpack(mo));
}

// fold
template <__metaobject_id... M, typename F, typename A>
constexpr auto
fold(unpacked_metaobject_sequence<M...>, F transform, A aggregate) {
    return aggregate(transform(wrapped_metaobject<M>{})...);
}

template <__metaobject_id M, typename F, typename A>
constexpr auto fold(
  wrapped_metaobject<M> mo,
  F transform,
  A aggregate) requires(__metaobject_is_meta_object_sequence(M)) {
    return fold(unpack(mo), transform, aggregate);
}

// join
template <typename F, typename S, typename A>
constexpr auto join(unpacked_metaobject_sequence<>, F, S, A) {
    return S{};
}

template <
  __metaobject_id M,
  __metaobject_id... Ms,
  typename F,
  typename S,
  typename A>
constexpr auto join(
  unpacked_metaobject_sequence<M, Ms...>,
  F transform,
  S separator,
  A aggregate) {
    return aggregate(
      transform(wrapped_metaobject<M>{}),
      aggregate(separator, transform(wrapped_metaobject<Ms>{}))...);
}

template <__metaobject_id... M, typename F, typename S>
constexpr auto
join(unpacked_metaobject_sequence<M...> ms, F transform, S separator) {
    return join(ms, std::move(transform), std::move(separator), [](auto... v) {
        return (... + v);
    });
}

template <__metaobject_id M, typename F, typename S>
constexpr auto join(
  wrapped_metaobject<M> mo,
  F transform,
  S separator) requires(__metaobject_is_meta_object_sequence(M)) {
    return join(unpack(mo), std::move(transform), std::move(separator));
}

// join to string
template <typename F, typename S>
auto join_to_string(unpacked_metaobject_sequence<>, const F&, std::string_view)
  -> std::string {
    return {};
}

template <__metaobject_id M, __metaobject_id... Ms, typename F>
auto join_to_string(
  unpacked_metaobject_sequence<M, Ms...>,
  F transform,
  std::string_view separator) -> std::string {
    std::string result;
    result.reserve(
      ((sizeof...(Ms) * separator.size()) + ... +
       transform(wrapped_metaobject<Ms>{}).size()));
    result.append(transform(wrapped_metaobject<M>{}));
    for_each(unpacked_metaobject_sequence<Ms...>{}, [&](auto mo) {
        result.append(separator);
        result.append(transform(mo));
    });

    return result;
}

template <__metaobject_id M, typename F>
auto join_to_string(
  wrapped_metaobject<M> mo,
  F transform,
  std::string_view separator) -> std::string
  requires(__metaobject_is_meta_object_sequence(M)) {
    return join_to_string(unpack(mo), std::move(transform), separator);
}

// for each
template <__metaobject_id... M, typename F>
constexpr void
for_each(unpacked_metaobject_sequence<M...>, F function) noexcept {
    (void)(..., function(wrapped_metaobject<M>{}));
}

template <__metaobject_id M, typename F>
constexpr void for_each(wrapped_metaobject<M> mo, F function) noexcept
  requires(__metaobject_is_meta_object_sequence(M)) {
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
constexpr void for_each_info(wrapped_metaobject<M> mo, F function) noexcept
  requires(__metaobject_is_meta_object_sequence(M)) {
    std::size_t index{0};
    const auto count{__metaobject_get_size(M)};
    return for_each(unpack(mo), [&](auto me) {
        function(me, for_each_iteration_info(index++, count));
    });
}

// find if
template <typename F>
constexpr auto find_if(unpacked_metaobject_sequence<>, F) noexcept {
    return no_metaobject;
}

template <__metaobject_id M, __metaobject_id... Mt, typename F>
constexpr auto
find_if(unpacked_metaobject_sequence<M, Mt...>, F predicate) noexcept {
    if constexpr(predicate(wrapped_metaobject<M>{})) {
        return wrapped_metaobject<M>{};
    } else {
        return find_if(unpacked_metaobject_sequence<Mt...>{}, predicate);
    }
}

template <__metaobject_id M, typename F>
constexpr auto find_if(wrapped_metaobject<M> mo, F predicate) noexcept
  requires(__metaobject_is_meta_object_sequence(M)) {
    return find_if(unpack(mo), predicate);
}

// find if not
template <typename F>
constexpr auto find_if_not(unpacked_metaobject_sequence<>, F) noexcept {
    return no_metaobject;
}

template <__metaobject_id M, __metaobject_id... Mt, typename F>
constexpr auto
find_if_not(unpacked_metaobject_sequence<M, Mt...>, F predicate) noexcept {
    if constexpr(!predicate(wrapped_metaobject<M>{})) {
        return wrapped_metaobject<M>{};
    } else {
        return find_if_not(unpacked_metaobject_sequence<Mt...>{}, predicate);
    }
}

template <__metaobject_id M, typename F>
constexpr auto find_if_not(wrapped_metaobject<M> mo, F predicate) noexcept
  requires(__metaobject_is_meta_object_sequence(M)) {
    return find_if_not(unpack(mo), predicate);
}

// find ranking
template <__metaobject_id M, typename F, typename C>
constexpr auto find_ranking(unpacked_metaobject_sequence<M>, F, C) {
    return wrapped_metaobject<M>{};
}

template <__metaobject_id M0, __metaobject_id M1, typename F, typename C>
constexpr auto
find_ranking(unpacked_metaobject_sequence<M0, M1>, F transform, C compare) {
    const auto l{wrapped_metaobject<M0>{}};
    const auto r{wrapped_metaobject<M1>{}};
    if constexpr(compare(transform(l), transform(r))) {
        return r;
    } else {
        return l;
    }
}

template <
  __metaobject_id M0,
  __metaobject_id M1,
  __metaobject_id M2,
  __metaobject_id... Ms,
  typename F,
  typename C>
constexpr auto find_ranking(
  unpacked_metaobject_sequence<M0, M1, M2, Ms...>,
  F transform,
  C compare) {
    const auto l{wrapped_metaobject<M0>{}};
    const auto r{wrapped_metaobject<M1>{}};
    if constexpr(compare(transform(l), transform(r))) {
        return find_ranking(
          unpacked_metaobject_sequence<M1, M2, Ms...>{}, transform, compare);
    } else {
        return find_ranking(
          unpacked_metaobject_sequence<M0, M2, Ms...>{}, transform, compare);
    }
}

template <__metaobject_id M, typename F, typename C>
constexpr auto find_ranking(
  wrapped_metaobject<M> mo,
  F transform,
  C compare) requires(__metaobject_is_meta_object_sequence(M)) {
    return find_ranking(unpack(mo), transform, compare);
}

template <typename S, typename F>
constexpr auto
find_ranking(S seq, F transform) requires(is_object_sequence(seq)) {
    return find_ranking(seq, transform, [](auto l, auto r) { return l < r; });
}

// get top value
template <__metaobject_id... M, typename F, typename C>
constexpr auto
get_top_value(unpacked_metaobject_sequence<M...> seq, F transform, C compare) {
    return transform(find_ranking(seq, transform, compare));
}

template <__metaobject_id M, typename F, typename C>
constexpr auto get_top_value(
  wrapped_metaobject<M> mo,
  F transform,
  C compare) requires(__metaobject_is_meta_object_sequence(M)) {
    return get_top_value(unpack(mo), transform, compare);
}

template <typename S, typename F>
constexpr auto
get_top_value(S seq, F transform) requires(is_object_sequence(seq)) {
    return get_top_value(seq, transform, [](auto l, auto r) { return l < r; });
}

// filter
template <__metaobject_id... M, typename F>
constexpr auto do_filter(
  unpacked_metaobject_sequence<M...>,
  unpacked_metaobject_sequence<>,
  F) noexcept -> unpacked_metaobject_sequence<M...> {
    return {};
}

template <
  __metaobject_id... Mh,
  __metaobject_id M,
  __metaobject_id... Mt,
  typename F>
constexpr auto do_filter(
  unpacked_metaobject_sequence<Mh...>,
  unpacked_metaobject_sequence<M, Mt...>,
  F predicate) noexcept {
    if constexpr(predicate(wrapped_metaobject<M>{})) {
        return do_filter(
          unpacked_metaobject_sequence<Mh..., M>{},
          unpacked_metaobject_sequence<Mt...>{},
          predicate);
    } else {
        return do_filter(
          unpacked_metaobject_sequence<Mh...>{},
          unpacked_metaobject_sequence<Mt...>{},
          predicate);
    }
}

template <__metaobject_id... M, typename F>
constexpr auto
filter(unpacked_metaobject_sequence<M...> seq, F predicate) noexcept {
    return do_filter(unpacked_metaobject_sequence<>{}, seq, predicate);
}

template <__metaobject_id M, typename F>
constexpr auto filter(wrapped_metaobject<M> mo, F predicate) noexcept
  requires(__metaobject_is_meta_object_sequence(M)) {
    return filter(unpack(mo), predicate);
}

// remove if
template <__metaobject_id... M, typename F>
constexpr auto
remove_if(unpacked_metaobject_sequence<M...> seq, F predicate) noexcept {
    return filter(seq, [predicate](auto mo) { return !predicate(mo); });
}

template <__metaobject_id M, typename F>
constexpr auto remove_if(wrapped_metaobject<M> mo, F predicate) noexcept
  requires(__metaobject_is_meta_object_sequence(M)) {
    return remove_if(unpack(mo), predicate);
}

// is sorted
template <typename F>
constexpr auto is_sorted(unpacked_metaobject_sequence<>, F) {
    return true;
}

template <__metaobject_id M, typename F>
constexpr auto is_sorted(unpacked_metaobject_sequence<M>, F) {
    return true;
}

template <__metaobject_id M0, __metaobject_id M1, typename F>
constexpr auto is_sorted(unpacked_metaobject_sequence<M0, M1>, F compare) {
    return compare(wrapped_metaobject<M0>{}, wrapped_metaobject<M1>{});
}

template <
  __metaobject_id M0,
  __metaobject_id M1,
  __metaobject_id M2,
  __metaobject_id... Ms,
  typename F>
constexpr auto
is_sorted(unpacked_metaobject_sequence<M0, M1, M2, Ms...>, F compare) {
    return compare(wrapped_metaobject<M0>{}, wrapped_metaobject<M1>{}) &&
           is_sorted(unpacked_metaobject_sequence<M1, M2, Ms...>{}, compare);
}

template <__metaobject_id M, typename F>
constexpr auto is_sorted(wrapped_metaobject<M> mo, F compare) requires(
  __metaobject_is_meta_object_sequence(M)) {
    return is_sorted(unpack(mo), compare);
}

// all of
template <__metaobject_id... M, typename F>
constexpr auto all_of(unpacked_metaobject_sequence<M...>, F predicate) noexcept
  -> bool {
    return (... && predicate(wrapped_metaobject<M>{}));
}

template <__metaobject_id M, typename F>
constexpr auto all_of(wrapped_metaobject<M> mo, F predicate) noexcept
  -> bool requires(__metaobject_is_meta_object_sequence(M)) {
    return all_of(unpack(mo), predicate);
}

// any_of
template <__metaobject_id... M, typename F>
constexpr auto any_of(unpacked_metaobject_sequence<M...>, F predicate) noexcept
  -> bool {
    return (... || predicate(wrapped_metaobject<M>{}));
}

template <__metaobject_id M, typename F>
constexpr auto any_of(wrapped_metaobject<M> mo, F predicate) noexcept
  -> bool requires(__metaobject_is_meta_object_sequence(M)) {
    return any_of(unpack(mo), predicate);
}

// none_of
template <__metaobject_id... M, typename F>
constexpr auto none_of(unpacked_metaobject_sequence<M...>, F predicate) noexcept
  -> bool {
    return !(... || predicate(wrapped_metaobject<M>{}));
}

template <__metaobject_id M, typename F>
constexpr auto none_of(wrapped_metaobject<M> mo, F predicate) noexcept
  -> bool requires(__metaobject_is_meta_object_sequence(M)) {
    return none_of(unpack(mo), predicate);
}

// select
template <typename T, __metaobject_id... M, typename F, typename... P>
constexpr auto select(
  unpacked_metaobject_sequence<M...>,
  F function,
  T fallback,
  P&&... param) noexcept -> T {
    (void)(..., function(fallback, wrapped_metaobject<M>{}, std::forward<P>(param)...));
    return fallback;
}

template <typename T, __metaobject_id M, typename F, typename... P>
constexpr auto
select(wrapped_metaobject<M> mo, F function, T fallback, P&&... param) noexcept
  -> T requires(__metaobject_is_meta_object_sequence(M)) {
    return select(
      unpack(mo),
      std::move(function),
      std::move(fallback),
      std::forward<P>(param)...);
}

// concat
template <__metaobject_id... L, __metaobject_id... R>
constexpr auto concat(
  unpacked_metaobject_sequence<L...>,
  unpacked_metaobject_sequence<R...>) noexcept
  -> unpacked_metaobject_sequence<L..., R...> {
    return {};
}

template <metaobject_sequence M>
constexpr auto concat(M ms) noexcept {
    return ms;
}

template <metaobject_sequence M, metaobject_sequence... Ms>
constexpr auto concat(M h, Ms... t) noexcept {
    return concat(unpack(h), concat(unpack(t)...));
}

// flatten
template <__metaobject_id... M>
constexpr auto flatten(unpacked_metaobject_sequence<M...>) requires(
  ...&& is_object_sequence(wrapped_metaobject<M>{})) {
    return concat(wrapped_metaobject<M>{}...);
}

} // namespace mirror

#endif // MIRROR_SEQUENCE_HPP
