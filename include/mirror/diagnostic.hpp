/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_DIAGNOSTIC_HPP
#define MIRROR_DIAGNOSTIC_HPP

#include "preprocessor.hpp"

#if defined(__clang__)
#define MIRROR_DIAG_PRAGMA(EXPR) MIRROR_PRAGMA(clang diagnostic EXPR)
#elif defined(__GNUC__)
#define MIRROR_DIAG_PRAGMA(EXPR) MIRROR_PRAGMA(GCC diagnostic EXPR)
#endif

#if defined(__clang__) || defined(__GNUC__)

#define MIRROR_DIAG_OFF(EXPR) \
    MIRROR_DIAG_PRAGMA(ignored MIRROR_STRINGIFY(MIRROR_JOIN(-W, EXPR)))

#define MIRROR_DIAG_PUSH() MIRROR_DIAG_PRAGMA(push)
#define MIRROR_DIAG_POP() MIRROR_DIAG_PRAGMA(pop)

#endif

#endif // MIRROR_DIAGNOSTIC_HPP
