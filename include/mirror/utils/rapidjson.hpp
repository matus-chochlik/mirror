/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_UTILS_RAPIDJSON_HPP
#define MIRROR_UTILS_RAPIDJSON_HPP

#include <string_view>

MIRROR_DIAG_PUSH()
#if defined(__clang__)
MIRROR_DIAG_OFF(zero-as-null-pointer-constant)
#endif

#include <rapidjson/document.h>

#if defined(__clang__)
MIRROR_DIAG_POP()
#endif

namespace mirror {

static inline auto to_rapidjson(std::string_view v) noexcept {
    return rapidjson::GenericStringRef<char>(
      v.data(), rapidjson::SizeType(v.size()));
}

static inline auto from_rapidjson(rapidjson::GenericStringRef<char> v) noexcept {
    return std::string_view(v.s, static_cast<size_t>(v.length));
}

} // namespace mirror

#endif

