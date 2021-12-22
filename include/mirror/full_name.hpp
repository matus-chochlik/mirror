/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_FULL_NAME_HPP
#define MIRROR_FULL_NAME_HPP

#include "primitives.hpp"

namespace mirror {

template <__metaobject_id M>
auto get_full_name(wrapped_metaobject<M>) -> std::string;

template <__metaobject_id Mp>
auto get_qualified_name(wrapped_metaobject<Mp> mo) -> std::string
  requires(__metaobject_is_meta_named(Mp)) {
    if constexpr(reflects_global_scope_member(mo) || !reflects_scope_member(mo)) {
        return std::string{get_name(mo)};
    } else {
        const auto ms = get_scope(mo);
        if constexpr(reflects_inline_namespace(ms) || is_unnamed(ms)) {
            return get_full_name(get_scope(ms)) +
                   "::" + std::string(get_name(mo));
        } else {
            return get_full_name(ms) + "::" + std::string(get_name(mo));
        }
    }
}

namespace _full_type_name {

struct defaults {
    static auto left(std::string s = {}) {
        return s;
    }

    static auto base(std::string s = {}) {
        return s;
    }

    static auto right(std::string s = {}) {
        return s;
    }

    static auto extents(std::string s = {}) {
        return s;
    }

    static auto params(std::string s = {}) {
        return s;
    }
};

template <typename T>
struct decorate : defaults {
    static auto base(std::string = {}) {
        return get_qualified_name(remove_all_aliases(mirror(T)));
    }
};

template <typename T>
struct decorate_defaults {
    static auto left(std::string s = {}) {
        return decorate<T>::left(std::move(s));
    }
    static auto base(std::string s = {}) {
        return decorate<T>::base(std::move(s));
    }
    static auto right(std::string s = {}) {
        return decorate<T>::right(std::move(s));
    }
    static auto extents(std::string s = {}) {
        return decorate<T>::extents(std::move(s));
    }
    static auto params(std::string s = {}) {
        return decorate<T>::params(std::move(s));
    }
};

template <typename T>
struct decorate<T*> : decorate_defaults<T> {
    static auto right(std::string s = {}) {
        return decorate<T>::right(s) + "*";
    }
};

template <typename T>
struct decorate<T&> : decorate_defaults<T> {
    static auto right(std::string s = {}) {
        return decorate<T>::right(s) + "&";
    }
};

template <typename T>
struct decorate<T&&> : decorate_defaults<T> {
    static auto right(std::string s = {}) {
        return decorate<T>::right(s) + "&&";
    }
};

template <typename T>
struct decorate<T const> : decorate_defaults<T> {
    static auto right(std::string s = {}) {
        return decorate<T>::right(s) + " const";
    }
};

template <typename T>
struct decorate<T volatile> : decorate_defaults<T> {
    static auto right(std::string s = {}) {
        return decorate<T>::right(s) + " volatile";
    }
};

template <typename T>
struct decorate<T const volatile> : decorate_defaults<T> {
    static auto right(std::string s = {}) {
        return decorate<T>::right(s) + " const volatile";
    }
};

template <typename T>
struct decorate<T[]> : decorate_defaults<T> {
    static auto extents(std::string s = {}) {
        return decorate<T>::extents(s + "[]");
    }
};

template <typename T, std::size_t N>
struct decorate<T[N]> : decorate_defaults<T> {
    static auto extents(std::string s = {}) {
        return decorate<T>::extents(s + "[" + std::to_string(N) + "]");
    }
};

static inline auto make_list(type_list<>) -> std::string {
    return {};
}

template <typename P1, typename... P>
auto make_list(type_list<P1, P...>) -> std::string {
    return (
      get_full_name(mirror(P1)) + ... + (", " + get_full_name(mirror(P))));
}

template <typename R, typename... P>
struct decorate<R(P...)> : defaults {
    static auto left(std::string s = {}) {
        using DR = decorate<R>;
        return s + DR::left() + DR::base() + DR::right() + DR::extents();
    }
    static auto params(std::string s = {}) {
        using DR = decorate<R>;
        return s + "(" + make_list(type_list<P...>{}) + ")" + DR::params();
    }
};

template <typename R, typename... P>
struct decorate<R(P...) noexcept> : defaults {
    static auto left(std::string s = {}) {
        using DR = decorate<R>;
        return s + DR::left() + DR::base() + DR::right() + DR::extents();
    }
    static auto params(std::string s = {}) {
        using DR = decorate<R>;
        return s + "(" + make_list(type_list<P...>{}) + ") noexcept" +
               DR::params();
    }
};

template <typename R, typename... P>
struct decorate<R (*)(P...)> : defaults {
    static auto left(std::string s = {}) {
        using DR = decorate<R>;
        return s + DR::left() + DR::base() + DR::right() + DR::extents() + "(";
    }
    static auto right(std::string s = {}) {
        return "*" + s;
    }
    static auto params(std::string s = {}) {
        using DR = decorate<R>;
        return ")" + s + "(" + make_list(type_list<P...>{}) + ")" +
               DR::params();
    }
};

template <typename R, typename... P>
struct decorate<R (*)(P...) noexcept> : defaults {
    static auto left(std::string s = {}) {
        using DR = decorate<R>;
        return s + DR::left() + DR::base() + DR::right() + DR::extents() + "(";
    }
    static auto right(std::string s = {}) {
        return "*" + s;
    }
    static auto params(std::string s = {}) {
        using DR = decorate<R>;
        return ")" + s + "(" + make_list(type_list<P...>{}) + ") noexcept" +
               DR::params();
    }
};

template <typename R, typename C, typename... P>
struct decorate<R (C::*)(P...)> : defaults {
    static auto left(std::string s = {}) {
        using DR = decorate<R>;
        return s + DR::left() + DR::base() + DR::right() + DR::extents() + "(";
    }
    static auto base(std::string s = {}) {
        return get_full_name(mirror(C)) + "::" + s;
    }
    static auto right(std::string s = {}) {
        return "*" + s;
    }
    static auto params(std::string s = {}) {
        using DR = decorate<R>;
        return ")" + s + "(" + make_list(type_list<P...>{}) + ")" +
               DR::params();
    }
};

template <typename R, typename C, typename... P>
struct decorate<R (C::*)(P...) const> : defaults {
    static auto left(std::string s = {}) {
        using DR = decorate<R>;
        return s + DR::left() + DR::base() + DR::right() + DR::extents() + "(";
    }
    static auto base(std::string s = {}) {
        return get_full_name(mirror(C)) + "::" + s;
    }
    static auto right(std::string s = {}) {
        return "*" + s;
    }
    static auto params(std::string s = {}) {
        using DR = decorate<R>;
        return ")" + s + "(" + make_list(type_list<P...>{}) + ") const" +
               DR::params();
    }
};

template <typename R, typename C, typename... P>
struct decorate<R (C::*)(P...) noexcept> : defaults {
    static auto left(std::string s = {}) {
        using DR = decorate<R>;
        return s + DR::left() + DR::base() + DR::right() + DR::extents() + "(";
    }
    static auto base(std::string s = {}) {
        return get_full_name(mirror(C)) + "::" + s;
    }
    static auto right(std::string s = {}) {
        return "*" + s;
    }
    static auto params(std::string s = {}) {
        using DR = decorate<R>;
        return ")" + s + "(" + make_list(type_list<P...>{}) + ") noexcept" +
               DR::params();
    }
};

template <typename R, typename C, typename... P>
struct decorate<R (C::*)(P...) const noexcept> : defaults {
    static auto left(std::string s = {}) {
        using DR = decorate<R>;
        return s + DR::left() + DR::base() + DR::right() + DR::extents() + "(";
    }
    static auto base(std::string s = {}) {
        return get_full_name(mirror(C)) + "::" + s;
    }
    static auto right(std::string s = {}) {
        return "*" + s;
    }
    static auto params(std::string s = {}) {
        using DR = decorate<R>;
        return ")" + s + "(" + make_list(type_list<P...>{}) +
               ") const noexcept" + DR::params();
    }
};

template <typename T, typename C>
struct decorate<T C::*> : defaults {
    static auto left(std::string s = {}) {
        using DT = decorate<T>;
        return s + DT::left() + DT::base() + DT::right() + DT::extents();
    }
    static auto base(std::string s = {}) {
        return " " + get_full_name(mirror(C)) + "::" + s;
    }
    static auto right(std::string s = {}) {
        return "*" + s;
    }
};

template <template <typename...> class T, typename... P>
struct decorate<T<P...>> : defaults {
    static auto base(std::string = {}) {
        return get_qualified_name(remove_all_aliases(mirror(T<P...>)));
    }

    static auto right(std::string s = {}) {
        return "<" + make_list(type_list<P...>{}) + ">" + s;
    }
};

} // namespace _full_type_name

template <__metaobject_id Mp>
auto get_full_name(wrapped_metaobject<Mp> mo) -> std::string {
    if constexpr(reflects_type(mo)) {
        using D = _full_type_name::decorate<__unrefltype(Mp)>;
        return D::left() + D::base() + D::right() + D::extents() + D::params();
    } else if constexpr(reflects_named(mo)) {
        return get_qualified_name(mo);
    } else {
        return {};
    }
}

} // namespace mirror

#endif // MIRROR_FULL_NAME_HPP

