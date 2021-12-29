/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_SERIALIZE_READ_BACKEND_HPP
#define MIRROR_SERIALIZE_READ_BACKEND_HPP

#include "../extract.hpp"
#include "result.hpp"
#include <concepts>

namespace mirror::serialize {
struct read_driver;

template <typename T>
concept read_backend = requires(T v) {
    { v.enum_as_string(std::declval<typename T::context&>()) }
    ->std::convertible_to<bool>;

    { v.begin(std::declval<typename T::context&>()) }
    ->extractable;

    {
        v.read(
          std::declval<read_driver>(),
          std::declval<typename T::context&>(),
          std::declval<int&>())
    }
    ->std::same_as<deserialization_errors>;

    {
        v.begin_list(
          std::declval<typename T::context&>(), std::declval<size_t>())
    }
    ->extractable;

    {
        v.begin_element(
          std::declval<typename T::context&>(), std::declval<size_t&>())
    }
    ->extractable;

    { v.separate_element(std::declval<typename T::context&>()) }
    ->std::same_as<deserialization_errors>;

    {
        v.finish_element(
          std::declval<typename T::context&>(), std::declval<size_t>())
    }
    ->std::same_as<deserialization_errors>;

    { v.finish_list(std::declval<typename T::context&>()) }
    ->std::same_as<deserialization_errors>;

    {
        v.begin_record(
          std::declval<typename T::context&>(), std::declval<size_t&>())
    }
    ->extractable;

    {
        v.begin_attribute(
          std::declval<typename T::context&>(),
          std::declval<std::string_view>())
    }
    ->extractable;

    { v.separate_attribute(std::declval<typename T::context&>()) }
    ->std::same_as<deserialization_errors>;

    {
        v.finish_attribute(
          std::declval<typename T::context&>(),
          std::declval<std::string_view>())
    }
    ->std::same_as<deserialization_errors>;

    { v.finish_record(std::declval<typename T::context&>()) }
    ->std::same_as<deserialization_errors>;

    { v.finish(std::declval<typename T::context&>()) }
    ->std::same_as<deserialization_errors>;
};

}; // namespace mirror::serialize

#endif
