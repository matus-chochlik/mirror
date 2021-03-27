/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_FACTORY_UTILITY_HPP
#define MIRROR_FACTORY_UTILITY_HPP

#include "../meta.hpp"
#include "../utils.hpp"
#include <string_view>
#include <utility>

namespace mirror {
//------------------------------------------------------------------------------
template <typename T>
struct factory_utils {
    consteval static auto constructors() {
        return std::experimental::meta::members_of(
          ^T, std::experimental::meta::is_constructor);
    }

    consteval static auto constructor_count() {
        return size(constructors());
    }

    using constructor_indices = std::make_index_sequence<constructor_count()>;

    consteval static auto constructor(size_t i)
      -> std::experimental::meta::info {
        return *advance(constructors().begin(), i);
    }

    consteval static auto is_default_constructor(size_t i) {
        return std::experimental::meta::is_default_constructor(constructor(i));
    }

    consteval static auto is_move_constructor(size_t i) {
        return std::experimental::meta::is_move_constructor(constructor(i));
    }

    consteval static auto is_copy_constructor(size_t i) {
        return std::experimental::meta::is_copy_constructor(constructor(i));
    }

    consteval static auto constructor_parameters(size_t i) {
        return std::experimental::meta::parameters_of(constructor(i));
    }

    consteval static auto constructor_parameter_count(size_t i) {
        return size(constructor_parameters(i));
    }

    template <size_t I>
    using constructor_parameter_indices =
      std::make_index_sequence<constructor_parameter_count(I)>;

    consteval static auto constructor_parameter(size_t i, size_t j)
      -> std::experimental::meta::info {
        return *advance(constructor_parameters(i).begin(), j);
    }

    consteval static auto constructor_parameter_name(size_t i, size_t j) {
        return std::experimental::meta::name_of(constructor_parameter(i, j));
    }

    template <size_t I, size_t J>
    using constructor_parameter_type =
      // clang-format off
    typename [: std::experimental::meta::type_of(constructor_parameter(I, J)) :];
    // clang-format on
};
//------------------------------------------------------------------------------
} // namespace mirror

#endif // MIRROR_FACTORY_UTILITY_HPP
