/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_CHAISCRIPT_HPP
#define MIRROR_CHAISCRIPT_HPP

#include "diagnostic.hpp"
#include "placeholder.hpp"
#include "sequence.hpp"

MIRROR_DIAG_PUSH()
#if defined(__clang__)
MIRROR_DIAG_OFF(documentation)
MIRROR_DIAG_OFF(double-promotion)
MIRROR_DIAG_OFF(exit-time-destructors)
MIRROR_DIAG_OFF(reserved-identifier)
MIRROR_DIAG_OFF(switch-enum)
#endif
#include <chaiscript/chaiscript.hpp>
MIRROR_DIAG_POP()

namespace mirror {

template <typename T>
void _add_type(
  chaiscript::ChaiScript& chai,
  std::type_identity<T>,
  const std::string& name) {
    chai.add(chaiscript::user_type<T>(), name);
}

template <typename T, typename... P>
void _add_constructor(
  chaiscript::ChaiScript& chai,
  std::type_identity<T>,
  type_list<P...>,
  const std::string& name) {
    chai.add(chaiscript::constructor<T(P...)>(), name);
}

template <typename Base, typename Derived>
void _add_base_class(
  chaiscript::ChaiScript& chai,
  std::type_identity<Base>,
  std::type_identity<Derived>) {
    chai.add(chaiscript::base_class<Base, Derived>());
}

template <typename From, typename To>
void _add_conversion(
  chaiscript::ChaiScript& chai,
  std::type_identity<From>,
  std::type_identity<To>) {
    chai.add(chaiscript::type_conversion<From, To>());
}

void _do_add_to(
  chaiscript::ChaiScript& chai,
  metaobject auto mo,
  metaobject auto ms) {
    if constexpr(reflects_object_sequence(mo)) {
        for_each(mo, [&](auto me) { _do_add_to(chai, me, ms); });
    } else if constexpr(reflects_base(mo)) {
        _add_base_class(
          chai, get_reflected_type(get_class(mo)), get_reflected_type(ms));
    } else {
        const std::string name{get_name(mo)};
        if constexpr(reflects_variable(mo)) {
            if constexpr(reflects_record_member(mo)) {
                if constexpr(is_public(mo)) {
                    chai.add(chaiscript::fun(get_pointer(mo)), name);
                }
            } else {
                chai.add(chaiscript::var(get_reference(mo)), name);
            }
        } else if constexpr(reflects_constructor(mo)) {
            if constexpr(is_public(mo)) {
                _add_constructor(
                  chai,
                  get_reflected_type(get_scope(mo)),
                  extract_types(transform(get_parameters(mo), get_type(_1))),
                  name);
            }
        } else if constexpr(reflects_function(mo)) {
            if constexpr(reflects_record_member(mo) && is_public(mo)) {
                if constexpr(reflects_conversion_operator(mo)) {
                    if constexpr(!is_deleted(mo)) {
                        _add_conversion(
                          chai,
                          get_reflected_type(get_scope(mo)),
                          get_reflected_type(get_type(mo)));
                    }
                } else {
                    if constexpr(!is_deleted(mo)) {
                        chai.add(chaiscript::fun(get_pointer(mo)), name);
                    }
                }
            } else {
                chai.add(chaiscript::fun(get_pointer(mo)), name);
            }
        } else if constexpr(reflects_record(mo)) {
            _add_type(chai, get_reflected_type(mo), name);
            _do_add_to(chai, get_base_classes(mo), mo);
            _do_add_to(chai, get_member_types(mo), mo);
            _do_add_to(chai, get_data_members(mo), mo);
            _do_add_to(chai, get_constructors(mo), mo);
            _do_add_to(chai, get_member_functions(mo), mo);
            _do_add_to(chai, get_operators(mo), mo);
        }
    }
}

static inline void add_to(chaiscript::ChaiScript& chai, metaobject auto mo) {
    _do_add_to(chai, mo, no_metaobject);
}

#if defined(MIRROR_DOXYGEN)
/// @brief Registers the entities reflected by metaobjects with a ChaiScript engine.
/// @ingroup utilities
void add_to(chaiscript::ChaiScript& chai, metaobject_sequence auto mos);
#else
template <__metaobject_id... M>
void add_to(
  chaiscript::ChaiScript& chai,
  unpacked_metaobject_sequence<M...> mos) {
    for_each(mos, [&](auto me) { _do_add_to(chai, me, no_metaobject); });
}
#endif

} // namespace mirror

#endif
