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

template <typename... E>
consteval auto is_object_sequence(type_list<E...>) noexcept -> bool {
    return (... && (is_object(E{}) || is_object_sequence(E{})));
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
consteval auto has_one_element(unpacked_metaobject_sequence<M...>) noexcept
  -> bool {
    return sizeof...(M) == 1Z;
}

template <__metaobject_id... M>
consteval auto
has_multiple_elements(unpacked_metaobject_sequence<M...>) noexcept -> bool {
    return sizeof...(M) > 1Z;
}

template <__metaobject_id... M>
consteval auto get_size(unpacked_metaobject_sequence<M...>) noexcept -> size_t {
    return sizeof...(M);
}

template <typename... E>
consteval auto get_size(type_list<E...> tl) noexcept -> size_t
  requires(is_object_sequence(tl)) {
    return sizeof...(E);
}

#if defined(MIRROR_DOXYGEN)
/// @brief Unpacks a sequence metaobject into sequence of separate metaobject ids.
/// @ingroup sequence_operations
/// @see reflects_object_sequence
constexpr auto unpack(metaobject_sequence auto mo) noexcept;
#else
template <__metaobject_id M>
constexpr auto unpack(wrapped_metaobject<M>) noexcept
  -> __unpack_metaobject_seq<unpacked_metaobject_sequence, M> requires(
    __metaobject_is_meta_object_sequence(M)) {
    return {};
}
#endif

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
#if defined(MIRROR_DOXYGEN)
/// @brief Counts elements in a metaobject sequence satisfying a predicate.
/// @ingroup sequence_operations
/// @see find_if
/// @see find_if_not
constexpr auto count_if(metaobject_sequence auto mo, auto predicate) noexcept
  -> size_t;
#else
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
#endif

// transform
#if defined(MIRROR_DOXYGEN)
/// @brief Transforms each element in a sequence by applying the given function
/// @ingroup sequence_operations
/// @see transform_types
/// @see for_each
/// @see fold
constexpr auto transform(metaobject_sequence auto mo, auto function) noexcept;
#else
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

template <typename... E, typename F>
constexpr auto transform(type_list<E...> tl, F function) noexcept
  requires(is_object_sequence(tl)) {
    return type_list<decltype(function(E{}))...>{};
}
#endif

// transform types
#if defined(MIRROR_DOXYGEN)
/// @brief Unreflects and transforms by Transform and instantiates Container
/// @ingroup sequence_operations
/// @see transform
/// @see transform_types
/// @see for_each
/// @see fold
///
/// This function takes a sequence of metaobjects reflecting types, un-reflects
/// them, applies the Transform template on each one and then instantiates
/// the Container template with the resulting types.
template <
  template <typename...>
  class Container,
  template <typename>
  class Transform>
constexpr auto store_transformed_types(metaobject_sequence auto mo) noexcept
  -> Container<Transform<__unspecified>...>;
#else
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
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Unreflects metaobject in a sequence and transforms by Transform
/// @ingroup sequence_operations
/// @see transform
/// @see store_transformed_types
/// @see extract_types
/// @see for_each
/// @see fold
///
/// This function takes a sequence of metaobjects reflecting types, un-reflects
/// them, applies the Transform template on each one and then instantiates
/// the type_list template with the resulting types.
template <template <typename> class Transform>
constexpr auto transform_types(metaobject_sequence auto mo) noexcept
  -> type_list<Transform<__unspecified>...>;
#else
template <template <typename> class Transform, __metaobject_id... M>
constexpr auto transform_types(unpacked_metaobject_sequence<M...> ms) noexcept {
    return store_transformed_types<type_list, Transform>(ms);
}

template <template <typename> class Transform, __metaobject_id M>
constexpr auto transform_types(wrapped_metaobject<M> mo) noexcept
  requires(__metaobject_is_meta_object_sequence(M)) {
    return store_transformed_types<type_list, Transform>(unpack(mo));
}
#endif

// extract types
#if defined(MIRROR_DOXYGEN)
/// @brief Unreflects metaobject in a sequence and stores them in type_list
/// @ingroup sequence_operations
/// @see transform
/// @see store_transformed_types
/// @see transform_types
/// @see for_each
/// @see fold
///
/// This function takes a sequence of metaobjects reflecting types, un-reflects
/// them, applies the Transform template on each one and then instantiates
/// the type_list template with the resulting types.
constexpr auto extract_types(metaobject_sequence auto mo) noexcept
  -> type_list<__unspecified...>;
#else
template <__metaobject_id... M>
constexpr auto extract_types(unpacked_metaobject_sequence<M...> ms) noexcept {
    return transform_types<std::type_identity>(ms);
}

template <__metaobject_id M>
constexpr auto extract_types(wrapped_metaobject<M> mo) noexcept
  requires(__metaobject_is_meta_object_sequence(M)) {
    return transform_types<std::type_identity>(unpack(mo));
}
#endif

// fold
#if defined(MIRROR_DOXYGEN)
/// @brief Transforms each metaobject in sequence and then aggregates the result.
/// @ingroup sequence_operations
/// @see transform
/// @see transform_types
/// @see for_each
/// @see join
///
/// This function takes a sequence of metaobjects applies the specified transform
/// function on each one of them and then makes a single call to the (variadic)
/// aggregate function with the transformed metaobjects as arguments and returns
/// the aggregated result.
constexpr auto fold(metaobject_sequence auto mo, auto transform, auto aggregate);
#else
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
#endif

// join
#if defined(MIRROR_DOXYGEN)
/// @brief Transforms each metaobject in sequence and aggregates them.
/// @ingroup sequence_operations
/// @see transform
/// @see transform_types
/// @see for_each
/// @see fold
constexpr auto join(
  metaobject_sequence auto mo,
  auto transform,
  auto separator,
  auto aggregate);
#else
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
#endif

// join to string
#if defined(MIRROR_DOXYGEN)
/// @brief Transforms each metaobject and joins the results separated by separator
/// @ingroup sequence_operations
/// @see transform
/// @see for_each
/// @see join
constexpr auto join_to_string(
  metaobject_sequence auto mo,
  auto transform,
  std::string_view separator) -> std::string;
#else
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
#endif

// for each
#if defined(MIRROR_DOXYGEN)
/// @brief Calls the specified function for each metaobject in a sequence.
/// @ingroup sequence_operations
/// @see transform
/// @see fold
/// @see join
constexpr void for_each(metaobject_sequence auto mo, auto function) noexcept;
#else
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

template <typename... E, typename F>
constexpr void for_each(type_list<E...>, F function) noexcept {
    (void)(..., function(E{}));
}
#endif

// for each with iteration info
/// @brief Class used to provide information about sequence element iteration.
/// @ingroup utilities
/// @see for_each
/// @see for_each_info
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

    /// @brief Indicates that this is the first iteation.
    /// @see is_last
    constexpr auto is_first() const noexcept -> bool {
        return _index == 0Z;
    }

    /// @brief Indicates that this is the last iteation.
    /// @see is_first
    constexpr auto is_last() const noexcept -> bool {
        return _index + 1Z >= _count;
    }

    /// @brief Returns the iteration index.
    /// @see count
    constexpr auto index() const noexcept -> std::size_t {
        return _index;
    }

    /// @brief Returns the total number of iterations.
    /// @see index
    constexpr auto count() const noexcept -> std::size_t {
        return _count;
    }
};

#if defined(MIRROR_DOXYGEN)
/// @brief Calls the specified function for each metaobject in a sequence.
/// @ingroup sequence_operations
/// @see for_each
/// @see for_each_iteration_info
/// @see transform
/// @see fold
/// @see join
///
/// This function call the provided function for each metaobject in a sequence
/// where the first argument is the metaobject and the second is an instance
/// of for_each_iteration_info providing information about each cycle.
constexpr void
for_each_info(metaobject_sequence auto mo, auto function) noexcept;
#else
template <__metaobject_id M, typename F>
constexpr void for_each_info(wrapped_metaobject<M> mo, F function) noexcept
  requires(__metaobject_is_meta_object_sequence(M)) {
    std::size_t index{0};
    const auto count{__metaobject_get_size(M)};
    return for_each(unpack(mo), [&](auto me) {
        function(me, for_each_iteration_info(index++, count));
    });
}
#endif

// find if
#if defined(MIRROR_DOXYGEN)
/// @brief Finds first metaobject in sequence satisfying a predicate
/// @ingroup sequence_operations
/// @see find_if_not
/// @see find_ranking
/// @see for_each
/// @see count_if
constexpr auto find_if(metaobject_sequence auto mo, auto predicate) noexcept;
#else
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
#endif

// find if not
#if defined(MIRROR_DOXYGEN)
/// @brief Finds first metaobject in sequence not satisfying a predicate
/// @ingroup sequence_operations
/// @see find_if
/// @see find_ranking
/// @see for_each
/// @see count_if
constexpr auto find_if_not(metaobject_sequence auto mo, auto predicate) noexcept;
#else
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
#endif

// find ranking
#if defined(MIRROR_DOXYGEN)
/// @brief Finds metaobject with ranking value of some property.
/// @ingroup sequence_operations
/// @see find_if
/// @see find_if_not
/// @see for_each
/// @see get_top_value
///
/// This function extracts the value of a property for each metaobjects
/// is a sequence and returns the metaobject for which the value is highest
/// according to a binary compare function.
constexpr auto
find_ranking(metaobject_sequence auto mo, auto transform, auto compare);
#else
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
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Finds metaobject with highest value of some property.
/// @ingroup sequence_operations
/// @see find_if
/// @see find_if_not
/// @see for_each
/// @see get_top_value
///
/// This function extracts the value of a property for each metaobjects
/// is a sequence and returns the metaobject for which the value is highest
/// according to a less than operator.
constexpr auto find_ranking(metaobject_sequence auto mo, auto transform);
#else
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
#endif

// get top value
#if defined(MIRROR_DOXYGEN)
/// @brief Finds the highest value of a property of metaobjects in a sequence
/// @ingroup sequence_operations
/// @see find_ranking
/// @see is_sorted
/// @see for_each
///
/// This function extracts the value of a property for each metaobjects
/// is a sequence and returns that value which is highest according to a binary
/// compare function.
constexpr auto get_top_value(metaobject_sequence auto mo, auto transform);
#else
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
#endif

// filter
#if defined(MIRROR_DOXYGEN)
/// @brief Removes metaobjects not satisfying a predicate from a sequence.
/// @ingroup sequence_operations
/// @see remove_if
/// @see for_each
/// @see select
constexpr auto filter(metaobject_sequence auto mo, auto predicate) noexcept;
#else
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
#endif

// remove if
#if defined(MIRROR_DOXYGEN)
/// @brief Removes metaobjects satisfying a predicate from a sequence.
/// @ingroup sequence_operations
/// @see filter
/// @see for_each
/// @see select
constexpr auto filter(metaobject_sequence auto mo, auto predicate) noexcept;
#else
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
#endif

// is sorted
#if defined(MIRROR_DOXYGEN)
/// @brief Tests if metaobjects in a sequence are sorted according to compare function
/// @ingroup sequence_operations
/// @see find_ranking
/// @see get_top_value
constexpr auto is_sorted(unpacked_metaobject_sequence<>, auto compare) -> bool;
#else
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
#endif

// all of
#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if all metaobjects in a sequence satisfy a predicate
/// @ingroup sequence_operations
/// @see filter
/// @see any_of
/// @see none_of
constexpr auto all_of(metaobject_sequence auto mo, auto predicate) noexcept
  -> bool;
#else
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

template <typename... E, typename F>
constexpr auto all_of(type_list<E...> tl, F predicate) noexcept
  -> bool requires(is_object_sequence(tl)) {
    return (... && predicate(E{}));
}
#endif

// any_of
#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if some metaobjects in a sequence satisfy a predicate
/// @ingroup sequence_operations
/// @see filter
/// @see all_of
/// @see none_of
constexpr auto any_of(metaobject_sequence auto mo, auto predicate) noexcept
  -> bool;
#else
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

template <typename... E, typename F>
constexpr auto any_of(type_list<E...> tl, F predicate) noexcept
  -> bool requires(is_object_sequence(tl)) {
    return (... || predicate(E{}));
}
#endif

// none_of
#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if no metaobjects in a sequence satisfy a predicate
/// @ingroup sequence_operations
/// @see filter
/// @see all_of
/// @see none_of
constexpr auto none_of(metaobject_sequence auto mo, auto predicate) noexcept
  -> bool;
#else
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

template <typename... E, typename F>
constexpr auto none_of(type_list<E...> tl, F predicate) noexcept
  -> bool requires(is_object_sequence(tl)) {
    return !(... && predicate(E{}));
}
#endif

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

template <typename T, typename... E, typename F, typename... P>
constexpr auto
select(type_list<E...> tl, F function, T fallback, P&&... param) noexcept -> T
  requires(is_object_sequence(tl)) {
    (void)(..., function(fallback, E{}, std::forward<P>(param)...));
    return fallback;
}

// concat
#if defined(MIRROR_DOXYGEN)
/// @brief Concatenates multiple metaobject sequences
/// @ingroup sequence_operations
/// @see for_each
/// @see make_sequence
/// @see flatten
constexpr auto concat(auto... mo) noexcept requires(...&& is_object(mo));
#else
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
#endif

// sort by
#if defined(MIRROR_DOXYGEN)
/// @brief Sorts metaobjects by the value returned by transform according to compare.
/// @ingroup sequence_operations
/// @see is_sorted
/// @see group_by
/// @see group_and_sort_by
/// @see filter
///
/// This function applies the transform function on each metaobject in a sequence
/// and then returns a new sequence of those metaobjects sorted by the result
/// of the transform according to the specified compare function.
constexpr auto
sort_by(auto mo, auto transform, auto compare) requires(is_object_sequence(mo));
#else
template <typename E, typename... L, typename F, typename C>
constexpr auto do_insert_by(type_list<L...>, type_list<>, F, C) {
    return type_list<L..., E>{};
}

template <
  typename E,
  typename... L,
  typename M,
  typename... R,
  typename F,
  typename C>
constexpr auto
do_insert_by(type_list<L...>, type_list<M, R...>, F transform, C compare) {
    if constexpr(compare(transform(E{}), transform(M{}))) {
        return type_list<L..., E, M, R...>{};
    } else {
        return do_insert_by<E>(
          type_list<L..., M>{}, type_list<R...>{}, transform, compare);
    }
}

template <typename... E, typename F, typename C>
constexpr auto do_sort_by(type_list<E...> result, type_list<>, F, C) {
    return result;
}

template <typename... L, typename E, typename... R, typename F, typename C>
constexpr auto
do_sort_by(type_list<L...>, type_list<E, R...>, F transform, C compare) {
    return do_sort_by(
      do_insert_by<E>(type_list<>{}, type_list<L...>{}, transform, compare),
      type_list<R...>{},
      transform,
      compare);
}

template <typename... E, typename F, typename C>
constexpr auto sort_by(type_list<E...> s, F transform, C compare) requires(
  is_object_sequence(s)) {
    return do_sort_by(type_list<>{}, s, transform, compare);
}

template <__metaobject_id... M, typename F, typename C>
constexpr auto
sort_by(unpacked_metaobject_sequence<M...>, F transform, C compare) {
    return sort_by(type_list<wrapped_metaobject<M>...>{}, transform, compare);
}

template <__metaobject_id M, typename F, typename C>
constexpr auto sort_by(
  wrapped_metaobject<M> mo,
  F transform,
  C compare) requires(__metaobject_is_meta_object_sequence(M)) {
    return sort_by(unpack(mo), transform, compare);
}

template <typename S, typename F>
constexpr auto sort_by(S s, F transform) requires(is_object_sequence(s)) {
    return sort_by(s, transform, [](auto l, auto r) { return l < r; });
}

template <typename S, typename F>
constexpr auto
reverse_sort_by(S s, F transform) requires(is_object_sequence(s)) {
    return sort_by(s, transform, [](auto l, auto r) { return l > r; });
}
#endif

// group by
#if defined(MIRROR_DOXYGEN)
/// @brief Groups metaobjects into sub-sequences by the value returned by transform
/// @ingroup sequence_operations
/// @see is_sorted
/// @see sort_by
/// @see group_and_sort_by
/// @see flatten
///
/// This function applies the transform function on each metaobject in a sequence
/// and then returns a new sequence of metaobject sequences where the metaobjects
/// in each sequence the result of transform is the same.
constexpr auto
group_by(auto mo, auto transform) requires(is_object_sequence(mo));
#else
template <typename... E, typename F>
constexpr auto
do_group_by(unpacked_metaobject_sequence<>, type_list<E...> result, F) {
    return result;
}

template <__metaobject_id M, __metaobject_id... Mt, typename... T, typename F>
constexpr auto do_group_by(
  unpacked_metaobject_sequence<M, Mt...> src,
  type_list<T...>,
  F transform) {
    const auto compare = [=](auto mo) {
        return transform(mo) == transform(wrapped_metaobject<M>{});
    };
    return do_group_by(
      remove_if(src, compare),
      type_list<T..., decltype(filter(src, compare))>{},
      transform);
}

template <__metaobject_id... M, typename F>
constexpr auto group_by(unpacked_metaobject_sequence<M...> s, F transform) {
    return do_group_by(s, type_list<>{}, transform);
}

template <__metaobject_id M, typename F>
constexpr auto group_by(wrapped_metaobject<M> mo, F transform) requires(
  __metaobject_is_meta_object_sequence(M)) {
    return group_by(unpack(mo), transform);
}
#endif

// group and sort by
#if defined(MIRROR_DOXYGEN)
/// @brief Groups and sorts metaobjects by the value returned by transform
/// @ingroup sequence_operations
/// @see is_sorted
/// @see sort_by
/// @see group_by
/// @see flatten
///
/// This function applies the transform function on each metaobject in a
/// sequence and then returns a new sequence of metaobject sequences where the
/// metaobjects in each sequence the result of transform is the same and then
/// sorts the sub-sequences according to the result of the compare function.
constexpr auto group_and_sort_by(
  auto mo,
  auto transform,
  auto compare) requires(is_object_sequence(mo));
#else
template <typename S, typename F, typename C>
constexpr auto
group_and_sort_by(S s, F transform, C compare) requires(is_object_sequence(s)) {
    return sort_by(
      group_by(s, transform),
      [transform](auto e) { return transform(get_front(e)); },
      compare);
}

template <typename S, typename F>
constexpr auto
group_and_sort_by(S s, F transform) requires(is_object_sequence(s)) {
    return group_and_sort_by(
      s, transform, [](auto l, auto r) { return l < r; });
}

template <typename S, typename F>
constexpr auto
reverse_group_and_sort_by(S s, F transform) requires(is_object_sequence(s)) {
    return group_and_sort_by(
      s, transform, [](auto l, auto r) { return l > r; });
}
#endif

// flatten
#if defined(MIRROR_DOXYGEN)
/// @brief Flattens a sequence of sub-sequences into one sequence of elements
/// @ingroup sequence_operations
/// @see group_by
/// @see sort_and_group_by
/// @see concat
constexpr auto flatten(auto mo) requires(is_object_sequence(mo));
#else
template <__metaobject_id... M>
constexpr auto flatten(unpacked_metaobject_sequence<M...>) requires(
  ...&& is_object_sequence(wrapped_metaobject<M>{})) {
    return concat(wrapped_metaobject<M>{}...);
}

template <typename... E>
constexpr auto flatten(type_list<E...> tl) requires(is_object_sequence(tl)) {
    return concat(E{}...);
}
#endif

template <size_t I, __metaobject_id M, __metaobject_id... Mt>
consteval auto get(mirror::unpacked_metaobject_sequence<M, Mt...>) noexcept {
    if constexpr(I == 0Z) {
        return mirror::wrapped_metaobject<M>{};
    } else {
        return get<I - 1Z>(mirror::unpacked_metaobject_sequence<Mt...>{});
    }
}

template <size_t I, __metaobject_id... M>
constexpr auto get_element(unpacked_metaobject_sequence<M...> mos) noexcept {
    return get<I>(mos);
}

template <__metaobject_id... M>
constexpr auto get_front(unpacked_metaobject_sequence<M...> mos) noexcept {
    return get<0Z>(mos);
}

template <size_t I, typename E, typename... Et>
consteval auto get(mirror::type_list<E, Et...>) noexcept {
    if constexpr(I == 0Z) {
        return E{};
    } else {
        return get<I - 1Z>(mirror::type_list<Et...>{});
    }
}

template <size_t I, typename... E>
constexpr auto get_element(type_list<E...> tl) noexcept
  requires(is_object_sequence(tl)) {
    return get<I>(tl);
}

template <typename... E>
constexpr auto get_front(type_list<E...> tl) noexcept
  requires(is_object_sequence(tl) && sizeof...(E) != 0Z) {
    return get<0Z>(tl);
}

} // namespace mirror

namespace std {

template <__metaobject_id... M>
struct tuple_size<mirror::unpacked_metaobject_sequence<M...>>
  : integral_constant<size_t, sizeof...(M)> {};

template <typename... E>
struct tuple_size<mirror::type_list<E...>>
  : integral_constant<size_t, sizeof...(E)> {};

template <__metaobject_id M, __metaobject_id... Mt>
struct tuple_element<0Z, mirror::unpacked_metaobject_sequence<M, Mt...>>
  : type_identity<mirror::wrapped_metaobject<M>> {};

template <size_t I, __metaobject_id M, __metaobject_id... Mt>
struct tuple_element<I, mirror::unpacked_metaobject_sequence<M, Mt...>>
  : tuple_element<I - 1Z, mirror::unpacked_metaobject_sequence<Mt...>> {};

template <typename E, typename... Et>
struct tuple_element<0Z, mirror::type_list<E, Et...>> : type_identity<E> {};

template <size_t I, typename E, typename... Et>
struct tuple_element<I, mirror::type_list<E, Et...>>
  : tuple_element<I - 1Z, mirror::type_list<Et...>> {};

} // namespace std

#endif // MIRROR_SEQUENCE_HPP
