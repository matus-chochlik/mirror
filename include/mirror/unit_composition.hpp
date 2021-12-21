/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_UNIT_COMPOSITION_HPP
#define MIRROR_UNIT_COMPOSITION_HPP

#include "sequence.hpp"
#include <array>

namespace mirror {

template <template <typename> class Unit, typename Sequence>
struct unit_composition;

template <template <typename> class Unit, __metaobject_id... M>
struct unit_composition<Unit, unpacked_metaobject_sequence<M...>>
  : Unit<metaobject<M>>... {

    template <typename... A>
    constexpr unit_composition(A&... args)
      : Unit<metaobject<M>>{args...}... {}
};

template <template <typename> class Unit, __metaobject_id M>
struct unit_composition<Unit, metaobject<M>>
  : unit_composition<Unit, decltype(unpack(metaobject<M>{}))> {
    using unit_composition<Unit, decltype(unpack(metaobject<M>{}))>::
      unit_composition;
};

// apply
template <template <typename> class Unit, __metaobject_id... M, typename F>
constexpr auto apply(
  unit_composition<Unit, unpacked_metaobject_sequence<M...>>& cmp,
  F function) {
    return function(static_cast<Unit<metaobject<M>>&>(cmp)...);
}

template <template <typename> class Unit, __metaobject_id... M, typename F>
constexpr auto apply(
  const unit_composition<Unit, unpacked_metaobject_sequence<M...>>& cmp,
  F function) {
    return function(static_cast<const Unit<metaobject<M>>&>(cmp)...);
}

// for each
template <template <typename> class Unit, __metaobject_id... M, typename F>
constexpr void for_each(
  unit_composition<Unit, unpacked_metaobject_sequence<M...>>& cmp,
  F function) {
    (void)(..., function(static_cast<Unit<metaobject<M>>&>(cmp)));
}

template <template <typename> class Unit, __metaobject_id... M, typename F>
constexpr void for_each(
  const unit_composition<Unit, unpacked_metaobject_sequence<M...>>& cmp,
  F function) {
    (void)(..., function(static_cast<const Unit<metaobject<M>>&>(cmp)));
}

// for each info
template <template <typename> class Unit, __metaobject_id... M, typename F>
constexpr void for_each_info(
  const unit_composition<Unit, unpacked_metaobject_sequence<M...>>& cmp,
  F function) {
    std::size_t index{0};
    const auto count{sizeof...(M)};
    return for_each(cmp, [&](auto& unit) {
        function(unit, for_each_iteration_info(index++, count));
    });
}

// make  array
template <template <typename> class Unit, __metaobject_id... M, typename F>
constexpr auto make_array(
  const unit_composition<Unit, unpacked_metaobject_sequence<M...>>& cmp,
  F transform)
  -> std::array<
    std::common_type_t<
      decltype(transform(static_cast<const Unit<metaobject<M>>&>(cmp)))...>,
    sizeof...(M)> {
    return {{transform(static_cast<const Unit<metaobject<M>>&>(cmp))...}};
}

template <typename R, template <typename> class Unit, __metaobject_id... M>
constexpr auto make_array_of(
  unit_composition<Unit, unpacked_metaobject_sequence<M...>>& cmp) noexcept
  -> std::array<R, sizeof...(M)> {
    return {{R(static_cast<Unit<metaobject<M>>&>(cmp))...}};
}

template <typename R, template <typename> class Unit, __metaobject_id... M>
constexpr auto make_array_of(
  const unit_composition<Unit, unpacked_metaobject_sequence<M...>>& cmp) noexcept
  -> std::array<std::add_const_t<R>, sizeof...(M)> {
    return {
      {std::add_const_t<R>(static_cast<const Unit<metaobject<M>>&>(cmp))...}};
}

// get element
template <typename R, template <typename> class Unit, __metaobject_id... M>
constexpr auto get_element(
  unit_composition<Unit, unpacked_metaobject_sequence<M...>>& cmp,
  size_t index) noexcept -> R& {
    return make_array_of<std::reference_wrapper<R>>(cmp)[index].get();
}

template <typename R, template <typename> class Unit, __metaobject_id... M>
constexpr auto get_element(
  const unit_composition<Unit, unpacked_metaobject_sequence<M...>>& cmp,
  size_t index) noexcept -> std::add_const_t<R>& {
    return make_array_of<std::reference_wrapper<std::add_const_t<R>>>(
             cmp)[index]
      .get();
}

} // namespace mirror

#endif // MIRROR_UNIT_COMPOSITION_HPP

