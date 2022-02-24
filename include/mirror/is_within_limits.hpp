/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#ifndef MIRROR_IS_WITHIN_LIMITS_HPP
#define MIRROR_IS_WITHIN_LIMITS_HPP

#include "diagnostic.hpp"
#include <cstdint>
#include <limits>
#include <optional>
#include <type_traits>
#include <utility>

MIRROR_DIAG_PUSH()
#if defined(__clang__)
MIRROR_DIAG_OFF(shorten-64-to-32)
#elif defined(__GNUC__)
MIRROR_DIAG_OFF(sign-compare)
#endif

namespace mirror {
//------------------------------------------------------------------------------
template <typename Dst, typename Src>
struct implicitly_within_limits
  : std::integral_constant<
      bool,
      (((std::is_integral_v<Dst> && std::is_integral_v<Src>) ||
        (std::is_floating_point_v<Dst> && std::is_floating_point_v<Src>)) &&
       (std::is_signed_v<Dst> ==
        std::is_signed_v<Src>)&&(sizeof(Dst) >= sizeof(Src)))> {};

template <typename Dst>
struct implicitly_within_limits<Dst, bool> : std::is_integral<Dst> {};

template <>
struct implicitly_within_limits<float, std::int16_t> : std::true_type {};

template <>
struct implicitly_within_limits<float, std::int32_t> : std::true_type {};

template <>
struct implicitly_within_limits<double, std::int16_t> : std::true_type {};

template <>
struct implicitly_within_limits<double, std::int32_t> : std::true_type {};

template <>
struct implicitly_within_limits<double, std::int64_t> : std::true_type {};
//------------------------------------------------------------------------------
template <
  typename Dst,
  typename Src,
  bool DIsInt,
  bool SIsInt,
  bool DIsSig,
  bool SIsSig>
struct within_limits_num {
    static constexpr auto check(const Src) noexcept {
        return implicitly_within_limits<Dst, Src>::value;
    }
};
//------------------------------------------------------------------------------
template <typename Dst, typename Src, bool IsInt, bool IsSig>
struct within_limits_num<Dst, Src, IsInt, IsInt, IsSig, IsSig> {
    static constexpr auto check(const Src value) noexcept {
        using dnl = std::numeric_limits<Dst>;

        return (dnl::min() <= value) && (value <= dnl::max());
    }
};
//------------------------------------------------------------------------------
template <typename Dst, typename Src, bool IsInt>
struct within_limits_num<Dst, Src, IsInt, IsInt, false, true> {
    static constexpr auto check(const Src value) noexcept {
        using Dnl = std::numeric_limits<Dst>;
        using Tmp = std::make_unsigned_t<Src>;

        return (value < Src(0)) ? false : (Tmp(value) < Dnl::max());
    }
};
//------------------------------------------------------------------------------
template <typename Dst, typename Src, bool IsInt>
struct within_limits_num<Dst, Src, IsInt, IsInt, true, false> {
    static constexpr auto check(const Src value) noexcept {
        using dnl = std::numeric_limits<Dst>;

        return (value < dnl::max());
    }
};
//------------------------------------------------------------------------------
template <typename Dst, typename Src>
struct within_limits
  : within_limits_num<
      Dst,
      Src,
      std::is_integral_v<Dst>,
      std::is_integral_v<Src>,
      std::is_signed_v<Dst>,
      std::is_signed_v<Src>> {};
//------------------------------------------------------------------------------
template <typename T>
struct within_limits<T, T> {
    static constexpr auto check(const T&) noexcept {
        return true;
    }
};
//------------------------------------------------------------------------------
/// @brief Indicates if @p value fits into the specified Dst type.
/// @ingroup utilities
/// @see limit_cast
/// @see convert_if_fits
///
/// This function tests if the specified argument would fit into another type.
/// For example if a value stored in 64-bit integer can be converted into
/// a 16-bit integer without overflow.
template <typename Dst, typename Src>
static constexpr auto is_within_limits(const Src value) noexcept {
    return implicitly_within_limits<Dst, Src>::value ||
           within_limits<Dst, Src>::check(value);
}
//------------------------------------------------------------------------------
/// @brief Casts @p value to Dst type if the value fits in that type.
/// @ingroup utilities
/// @see is_within_limits
/// @see convert_if_fits
/// @see signedness_cast
/// @pre is_within_limits<Dst>(value)
template <typename Dst, typename Src>
static constexpr auto limit_cast(Src value) noexcept
  -> std::enable_if_t<std::is_convertible_v<Src, Dst>, Dst> {
    is_within_limits<Dst>(value), Dst(std::move(value));
}
//------------------------------------------------------------------------------
/// @brief Casts @p value to a type with the opposite signedness.
/// @ingroup utilities
/// @see is_within_limits
/// @see convert_if_fits
/// @see limit_cast
template <typename Src>
static constexpr auto signedness_cast(Src value) noexcept {
    return limit_cast<std::conditional_t<
      std::is_signed_v<Src>,
      std::make_unsigned_t<Src>,
      std::make_signed_t<Src>>>(value);
}
//------------------------------------------------------------------------------
/// @brief Optionally converts @p value to Dst type if the value fits in that type.
/// @ingroup utilities
/// @see is_within_limits
/// @see limit_cast
/// @see from_string
template <typename Dst, typename Src>
static constexpr auto convert_if_fits(Src value) noexcept
  -> std::enable_if_t<std::is_convertible_v<Src, Dst>, std::optional<Dst>> {

    if(is_within_limits<Dst>(value)) {
        return {Dst(std::move(value))};
    }
    return {};
}
//------------------------------------------------------------------------------
} // namespace mirror

MIRROR_DIAG_POP()

#endif // MIRROR_IS_WITHIN_LIMITS_HPP
