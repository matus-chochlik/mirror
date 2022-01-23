/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_FROM_STRING_HPP
#define MIRROR_FROM_STRING_HPP

#include "enum_utils.hpp"
#include "extract.hpp"
#include "is_within_limits.hpp"
#include "tribool.hpp"
#include <algorithm>
#include <array>
#include <charconv>
#include <chrono>
#include <cstdlib>
#include <string>
#include <string_view>

namespace mirror {
//------------------------------------------------------------------------------
static inline auto
from_string(const std::string_view src, const std::type_identity<bool>) noexcept
  -> std::variant<bool, std::errc> {

    const std::array<const std::string_view, 5> true_strs{
      {{"true"}, {"True"}, {"1"}, {"t"}, {"T"}}};
    if(std::find(true_strs.begin(), true_strs.end(), src) != true_strs.end()) {
        return {true};
    }

    const std::array<const std::string_view, 5> false_strs{
      {{"false"}, {"False"}, {"0"}, {"f"}, {"F"}}};
    if(std::find(false_strs.begin(), false_strs.end(), src) != false_strs.end()) {
        return {false};
    }

    return {std::errc::invalid_argument};
}

static inline auto from_string(
  const std::string_view src,
  const std::type_identity<tribool>) noexcept
  -> std::variant<tribool, std::errc> {
    if(const auto val{from_string(src, std::type_identity<bool>{})};
       has_value(val)) {
        return {tribool{extract(val)}};
    }

    const std::array<const std::string_view, 4> unknown_strs{
      {{"indeterminate"}, {"Indeterminate"}, {"unknown"}, {"-"}}};
    if(
      std::find(unknown_strs.begin(), unknown_strs.end(), src) !=
      unknown_strs.end()) {
        return {indeterminate};
    }

    return {std::errc::invalid_argument};
}

static inline auto
from_string(const std::string_view src, const std::type_identity<char>) noexcept
  -> std::variant<char, std::errc> {
    if(src.size() == 1) {
        return {src.front()};
    }
    return {std::errc::invalid_argument};
}

template <typename T>
static inline auto
from_string(const std::string_view src, const std::type_identity<T>) noexcept
  -> std::variant<T, std::errc> requires(std::is_integral_v<T>) {
    T value{};
    const auto res{
      std::from_chars<T>(src.data(), src.data() + src.size(), value, 10)};
    if(res.ec == std::errc{}) {
        if(std::string_view{res.ptr}.empty()) {
            return {value};
        }
        return {std::errc::invalid_argument};
    }
    return {res.ec};
}

template <typename T>
static inline auto
from_string(const std::string_view src, const std::type_identity<T>) noexcept
  -> std::variant<T, std::errc> requires(std::is_enum_v<T>) {
    if(const auto converted{string_to_enum<T>(src)}) {
        return {extract(converted)};
    }
    return {std::errc::invalid_argument};
}

static inline auto from_string(
  const std::string_view src,
  const std::type_identity<std::string_view>) noexcept
  -> std::variant<std::string_view, std::errc> {
    return {src};
}

static inline auto from_string(
  const std::string_view src,
  const std::type_identity<std::string>) noexcept
  -> std::variant<std::string, std::errc> {
    return {std::string{src}};
}

template <typename Rep, typename Period>
static inline auto convert_from_string(
  const std::string_view src,
  const std::string_view suffix,
  const std::type_identity<std::chrono::duration<Rep, Period>>) noexcept
  -> std::optional<std::chrono::duration<Rep, Period>> {
    using D = std::chrono::duration<Rep, Period>;

    Rep value{};
    const auto res{
      std::from_chars<Rep>(src.data(), src.data() + src.size(), value, 10)};
    if(std::string_view{res.ptr} == suffix) {
        if(res.ec == std::errc{}) {
            return {D{value}};
        }
    }
    return {};
}

template <typename Rep, typename Period>
static inline auto from_string(
  const std::string_view src,
  const std::type_identity<std::chrono::duration<Rep, Period>>) noexcept
  -> std::variant<std::chrono::duration<Rep, Period>, std::errc> {

    using D = std::chrono::duration<Rep, Period>;

    if(const auto d{convert_from_string(
         src,
         "s",
         std::type_identity<std::chrono::duration<Rep, std::ratio<1>>>())}) {
        return {std::chrono::duration_cast<D>(*d)};
    }

    if(const auto d{convert_from_string(
         src,
         "min",
         std::type_identity<std::chrono::duration<Rep, std::ratio<60>>>())}) {
        return {std::chrono::duration_cast<D>(*d)};
    }

    if(const auto d{convert_from_string(
         src,
         "hr",
         std::type_identity<std::chrono::duration<Rep, std::ratio<3600>>>())}) {
        return {std::chrono::duration_cast<D>(*d)};
    }

    if(const auto d{convert_from_string(
         src,
         "day",
         std::type_identity<
           std::chrono::duration<Rep, std::ratio<86400LL>>>())}) {
        return {std::chrono::duration_cast<D>(*d)};
    }

    if(const auto d{convert_from_string(
         src,
         "ms",
         std::type_identity<std::chrono::duration<Rep, std::milli>>())}) {
        return {std::chrono::duration_cast<D>(*d)};
    }

    if(const auto d{convert_from_string(
         src,
         "μs",
         std::type_identity<std::chrono::duration<Rep, std::micro>>())}) {
        return {std::chrono::duration_cast<D>(*d)};
    }

    return {std::errc::invalid_argument};
}
//------------------------------------------------------------------------------
#if defined(MIRROR_DOXYGEN)
/// @brief Converts the string representation in @p src to a value of type @p T.
/// @ingroup utilities
/// @see is_within_limits
template <typename T>
auto from_string(const std::string_view src) noexcept -> extractable;
#endif

template <typename T>
auto from_string(const std::string_view src) noexcept {
    return from_string(src, std::type_identity<T>{});
}

template <typename T>
auto from_extractable_string(
  const extractable auto src,
  std::type_identity<T> tid = {}) noexcept -> std::optional<T> {
    if(has_value_of<std::string_view>(src) && has_value(src)) {
        if(auto converted{from_string(extract(src), tid)};
           has_value(converted)) {
            return {std::move(extract(converted))};
        }
    }
    return {};
}
//------------------------------------------------------------------------------
} // namespace mirror

#endif // MIRROR_FROM_STRING_HPP
