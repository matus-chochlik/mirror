/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_CTRE_MATCH_HPP
#define MIRROR_CTRE_MATCH_HPP

#include "diagnostic.hpp"
#include "placeholder.hpp"

MIRROR_DIAG_PUSH()
#if defined(__clang__)
MIRROR_DIAG_OFF(class-varargs)
MIRROR_DIAG_OFF(ctad-maybe-unsupported)
MIRROR_DIAG_OFF(newline-eof)
MIRROR_DIAG_OFF(reserved-macro-identifier)
#endif
#include <ctre.hpp>
MIRROR_DIAG_POP()

namespace mirror {

template <CTRE_REGEX_INPUT_TYPE Input>
constexpr auto ctre_match(std::string_view s) noexcept {
    return ctre::match<Input>(s);
}

template <CTRE_REGEX_INPUT_TYPE Input, typename X>
constexpr auto ctre_match(placeholder_expr<X> e) noexcept {
    return placeholder_expr{[e](auto mo) {
        return ctre::match<Input>(e(mo));
    }};
}

} // namespace mirror

#endif
