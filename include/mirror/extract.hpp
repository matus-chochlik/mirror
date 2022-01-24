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
#include <type_traits>
#include <variant>

namespace mirror {

#if defined(MIKRROR_DOXYGEN)
/// @brief Concept constraining extractable types.
/// @ingroup utilities
/// @see has_value
/// @see extract
/// This is a concept for types that can optionally store and/or provide
/// access to a value. Examples of extractable types are pointers, smart
/// pointers, optionals, etc.
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

template <typename T>
struct extracted_traits;

/// @brief Returns the value type of an extractable.
/// @ingroup utilities
/// @see extract
template <typename T>
using extracted_type_t = std::remove_cv_t<typename extracted_traits<
  std::remove_cv_t<std::remove_reference_t<T>>>::value_type>;

template <typename E, typename V>
static constexpr const auto has_value_type_v =
  std::is_convertible_v<extracted_type_t<E>, V>;

// nullptr
template <>
struct extracted_traits<nullptr_t> {
    using value_type = void;
};

constexpr auto has_value(const nullptr_t) noexcept -> bool {
    return false;
}

constexpr auto extract(const nullptr_t) noexcept -> int {
    return 0;
}

// pointer
template <typename T>
struct extracted_traits<T*> {
    using value_type = T;
};

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
struct extracted_traits<std::unique_ptr<T, D>> {
    using value_type = T;
};

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
struct extracted_traits<std::shared_ptr<T>> {
    using value_type = T;
};

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
struct extracted_traits<std::optional<T>> {
    using value_type = T;
};

template <typename T>
constexpr auto has_value(const std::optional<T>& o) noexcept -> bool {
    return o.has_value();
}

template <typename T>
constexpr auto extract(const std::optional<T>& o) noexcept -> const T& {
    return *o;
}

// variant (expected)
template <typename T, typename E>
struct extracted_traits<std::variant<T, E>> {
    using value_type = T;
};

template <typename T, typename E>
constexpr auto has_value(const std::variant<T, E>& v) noexcept -> bool {
    return std::holds_alternative<T>(v);
}

template <typename T, typename E>
constexpr auto extract(const std::variant<T, E>& v) noexcept -> const T& {
    return std::get<T>(v);
}

template <typename T, typename E>
constexpr auto extract(std::variant<T, E>& v) noexcept -> T& {
    return std::get<T>(v);
}

template <typename T, typename E>
constexpr auto get_error(const std::variant<T, E>& v) noexcept -> const E& {
    return std::get<E>(v);
}

// clang-format off
template <typename T>
concept extractable = requires(T v) {
    { has_value(v) } -> std::convertible_to<bool>;
	{ std::declval<mirror::extracted_type_t <T>>() };
	extract(v);
};
// clang-format on

/// @brief Indicates in an extractable has value type of @c V.
/// @see extract
/// @see extracted_type_t
/// @ingroup utilities
template <typename V>
consteval auto has_value_type(const extractable auto& v) noexcept -> bool {
    return has_value_type_v<decltype(v), V>;
}

} // namespace mirror

#endif
