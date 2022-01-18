/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_OVERLOAD_HPP
#define MIRROR_OVERLOAD_HPP

#include <utility>

namespace mirror {

template <typename... Func>
struct overload;

template <typename Func>
struct overload<Func> : Func {
    overload(const Func& func)
      : Func{func} {}

    overload(Func&& func)
      : Func{std::move(func)} {}

    using Func::operator();
};

template <typename Func, typename... Funcs>
struct overload<Func, Funcs...>
  : Func
  , overload<Funcs...> {
    template <typename... F>
    overload(const Func& func, F&&... funcs)
      : Func{func}
      , overload<Funcs...>{std::forward<Funcs>(funcs)...} {}

    template <typename... F>
    overload(Func&& func, F&&... funcs)
      : Func{std::move(func)}
      , overload<Funcs...>{std::forward<Funcs>(funcs)...} {}

    using Func::operator();
    using overload<Funcs...>::operator();
};

template <typename... F>
overload(const F&...) -> overload<F...>;

} // namespace mirror

#endif // MIRROR_OVERLOAD_HPP
