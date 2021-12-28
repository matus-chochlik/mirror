/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_EXTRACT_HPP
#define MIRROR_EXTRACT_HPP

#include <concepts>
#include <memory>
#include <optional>
#include <system_error>
#include <variant>

namespace mirror {

#if defined(MIKRROR_DOXYGEN)
/// @brief Concept constraining extractable types.
/// @ingroup utilities
/// @see has_value
/// @see extract
/// This is a concept for types that can optionally store and/or provide access
/// to a value. Examples of extractable types are pointers, smart pointers,
/// optionals, etc.
template <typename X>
concept extractable = __unspecified;

/// @brief Indicates if an extractable has a valid value.
/// @ingroup utilities
/// @see extract
constexpr auto has_value(extractable auto p) noexcept -> bool;

/// @brief Extracts a value from an extractable if it has value.
/// @ingroup utilities
/// @see has_value
/// The extractable @p p must have a valid value, otherwise the behavior
/// is undefined.
constexpr auto extract(extractable auto p) noexcept -> const auto&;
#endif

// clang-format off
template <typename T>
concept extractable = requires(T v) {
    { has_value(v) } -> std::convertible_to<bool>;
    extract(v);
};
// clang-format on

// pointer
template <typename T>
constexpr auto has_value(const T* p) noexcept -> bool {
    return p != nullptr;
}

template <typename T>
constexpr auto extract(const T* p) noexcept -> const T& {
    return *p;
}

// unique_ptr
template <typename T, typename D>
constexpr auto has_value(const std::unique_ptr<T, D>& p) noexcept -> bool {
    return p != nullptr;
}

template <typename T, typename D>
constexpr auto extract(const std::unique_ptr<T, D>& p) noexcept -> const T& {
    return *p;
}

// shared_ptr
template <typename T>
constexpr auto has_value(const std::shared_ptr<T>& p) noexcept -> bool {
    return p != nullptr;
}

template <typename T, typename D>
constexpr auto extract(const std::shared_ptr<T>& p) noexcept -> const T& {
    return *p;
}

// optional
template <typename T>
constexpr auto has_value(const std::optional<T>& o) noexcept -> bool {
    return o.has_value();
}

template <typename T>
constexpr auto extract(const std::optional<T>& o) noexcept -> const T& {
    return *o;
}

// variant (expected)
template <typename T>
constexpr auto has_value(const std::variant<T, std::errc>& v) noexcept -> bool {
    return std::holds_alternative<T>(v);
}

template <typename T>
constexpr auto extract(const std::variant<T, std::errc>& v) noexcept
  -> const T& {
    return std::get<T>(v);
}

} // namespace mirror

#endif
