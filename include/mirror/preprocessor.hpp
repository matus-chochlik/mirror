/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_PREPROCESSOR_HPP
#define MIRROR_PREPROCESSOR_HPP

#define MIRROR_STRINGIFY(EXPR) MIRROR_DO_STRINGIFY(EXPR)
#define MIRROR_DO_STRINGIFY(EXPR) #EXPR

#define MIRROR_JOIN(L, R) MIRROR_DO_JOIN(L, R)
#define MIRROR_DO_JOIN(L, R) MIRROR_DO_JOIN2(L, R)
#define MIRROR_DO_JOIN2(L, R) L##R

#if defined(__clang__) || defined(__GNUC__)

#define MIRROR_PRAGMA(x) _Pragma(MIRROR_STRINGIFY(x))

#elif defined(_MSC_VER)

#define MIRROR_PRAGMA(x) __pragma(x)

#endif

#endif // MIRROR_PREPROCESSOR_HPP
