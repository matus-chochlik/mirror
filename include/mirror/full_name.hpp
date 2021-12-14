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
std::string get_full_name(metaobject<M>);

template <
  __metaobject_id Mp,
  typename = std::enable_if_t<__metaobject_is_meta_named(Mp)>>
std::string get_qualified_name(metaobject<Mp> mo) {
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
    static std::string left(std::string s = {}) {
        return s;
    }

    static std::string base(std::string s = {}) {
        return s;
    }

    static std::string right(std::string s = {}) {
        return s;
    }

    static std::string extents(std::string s = {}) {
        return s;
    }

    static std::string params(std::string s = {}) {
        return s;
    }
};

template <typename T>
struct decorate : defaults {
    static std::string base(std::string = {}) {
        return get_qualified_name(remove_all_aliases(mirror(T)));
    }
};

template <typename T>
struct decorate_defaults {
    static std::string left(std::string s = {}) {
        return decorate<T>::left(std::move(s));
    }
    static std::string base(std::string s = {}) {
        return decorate<T>::base(std::move(s));
    }
    static std::string right(std::string s = {}) {
        return decorate<T>::right(std::move(s));
    }
    static std::string extents(std::string s = {}) {
        return decorate<T>::extents(std::move(s));
    }
    static std::string params(std::string s = {}) {
        return decorate<T>::params(std::move(s));
    }
};

template <typename T>
struct decorate<T*> : decorate_defaults<T> {
    static std::string right(std::string s = {}) {
        return decorate<T>::right(s) + "*";
    }
};

template <typename T>
struct decorate<T&> : decorate_defaults<T> {
    static std::string right(std::string s = {}) {
        return decorate<T>::right(s) + "&";
    }
};

template <typename T>
struct decorate<T&&> : decorate_defaults<T> {
    static std::string right(std::string s = {}) {
        return decorate<T>::right(s) + "&&";
    }
};

template <typename T>
struct decorate<T const> : decorate_defaults<T> {
    static std::string right(std::string s = {}) {
        return decorate<T>::right(s) + " const";
    }
};

template <typename T>
struct decorate<T volatile> : decorate_defaults<T> {
    static std::string right(std::string s = {}) {
        return decorate<T>::right(s) + " volatile";
    }
};

template <typename T>
struct decorate<T const volatile> : decorate_defaults<T> {
    static std::string right(std::string s = {}) {
        return decorate<T>::right(s) + " const volatile";
    }
};

template <typename T>
struct decorate<T[]> : decorate_defaults<T> {
    static std::string extents(std::string s = {}) {
        return decorate<T>::extents(s + "[]");
    }
};

template <typename T, std::size_t N>
struct decorate<T[N]> : decorate_defaults<T> {
    static std::string extents(std::string s = {}) {
        return decorate<T>::extents(s + "[" + std::to_string(N) + "]");
    }
};

template <typename R>
struct decorate<R()> : defaults {
    static std::string left(std::string s = {}) {
        using DR = decorate<R>;
        return s + DR::left() + DR::base() + DR::right() + DR::extents();
    }
    static std::string params(std::string s = {}) {
        using DR = decorate<R>;
        return s + "()" + DR::params();
    }
};

template <typename R>
struct decorate<R() noexcept> : defaults {
    static std::string left(std::string s = {}) {
        using DR = decorate<R>;
        return s + DR::left() + DR::base() + DR::right() + DR::extents();
    }
    static std::string params(std::string s = {}) {
        using DR = decorate<R>;
        return s + "() noexcept" + DR::params();
    }
};

template <typename R, typename P1, typename... P>
struct decorate<R(P1, P...)> : decorate<R()> {
    static std::string params(std::string s = {}) {
        using DR = decorate<R>;
        return s + "(" +
               (get_full_name(mirror(P1)) + ... +
                (", " + get_full_name(mirror(P)))) +
               ")" + DR::params();
    }
};

template <typename R, typename P1, typename... P>
struct decorate<R(P1, P...) noexcept> : decorate<R() noexcept> {
    static std::string params(std::string s = {}) {
        using DR = decorate<R>;
        return s + "(" +
               (get_full_name(mirror(P1)) + ... +
                (", " + get_full_name(mirror(P)))) +
               ") noexcept" + DR::params();
    }
};

template <typename R>
struct decorate<R (*)()> : defaults {
    static std::string left(std::string s = {}) {
        using DR = decorate<R>;
        return s + DR::left() + DR::base() + DR::right() + DR::extents() + "(";
    }
    static std::string right(std::string s = {}) {
        return "*" + s;
    }
    static std::string params(std::string s = {}) {
        using DR = decorate<R>;
        return ")" + s + "()" + DR::params();
    }
};

template <typename R>
struct decorate<R (*)() noexcept> : defaults {
    static std::string left(std::string s = {}) {
        using DR = decorate<R>;
        return s + DR::left() + DR::base() + DR::right() + DR::extents() + "(";
    }
    static std::string right(std::string s = {}) {
        return "*" + s;
    }
    static std::string params(std::string s = {}) {
        using DR = decorate<R>;
        return ")" + s + "() noexcept" + DR::params();
    }
};

template <typename R, typename P1, typename... P>
struct decorate<R (*)(P1, P...)> : decorate<R (*)()> {
    static std::string params(std::string s = {}) {
        using DR = decorate<R>;
        return ")" + s + "(" +
               (get_full_name(mirror(P1)) + ... +
                (", " + get_full_name(mirror(P)))) +
               ")" + DR::params();
    }
};

template <typename R, typename P1, typename... P>
struct decorate<R (*)(P1, P...) noexcept> : decorate<R (*)() noexcept> {
    static std::string params(std::string s = {}) {
        using DR = decorate<R>;
        return ")" + s + "(" +
               (get_full_name(mirror(P1)) + ... +
                (", " + get_full_name(mirror(P)))) +
               ") noexcept" + DR::params();
    }
};

template <template <typename...> class T, typename P1, typename... P>
struct decorate<T<P1, P...>> : defaults {
    static std::string base(std::string = {}) {
        return get_qualified_name(remove_all_aliases(mirror(T<P1, P...>)));
    }

    static std::string right(std::string s = {}) {
        return "<" +
               (get_full_name(mirror(P1)) + ... +
                (", " + get_full_name(mirror(P)))) +
               ">" + s;
    }
};

} // namespace _full_type_name

template <__metaobject_id Mp>
std::string get_full_name(metaobject<Mp> mo) {
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

