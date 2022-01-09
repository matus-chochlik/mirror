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

template <typename T, typename... P>
void _add_constructor_to(
  chaiscript::ChaiScript& chai,
  std::type_identity<T>,
  type_list<P...>,
  const std::string& name) {
    chai.add(chaiscript::constructor<T(P...)>(), name);
}

template <__metaobject_id M>
void add_to(chaiscript::ChaiScript& chai, wrapped_metaobject<M> mo) {
    if constexpr(reflects_object_sequence(mo)) {
        add_to(chai, unpack(mo));
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
                _add_constructor_to(
                  chai,
                  get_reflected_type(get_scope(mo)),
                  extract_types(transform(get_parameters(mo), get_type(_1))),
                  name);
            }
        } else if constexpr(reflects_function(mo)) {
            if constexpr(reflects_record_member(mo) && is_public(mo)) {
                chai.add(chaiscript::fun(get_pointer(mo)), name);
            } else {
                chai.add(chaiscript::fun(get_pointer(mo)), name);
            }
        } else if constexpr(reflects_record(mo)) {
            chai.add(
              chaiscript::user_type<
                get_reflected_type_t<wrapped_metaobject<M>>>(),
              name);
            add_to(chai, get_member_types(mo));
            add_to(chai, get_data_members(mo));
            add_to(chai, get_constructors(mo));
            add_to(chai, get_member_functions(mo));
        }
    }
}

template <__metaobject_id... M>
void add_to(chaiscript::ChaiScript& chai, unpacked_metaobject_sequence<M...>) {
    (void)(..., add_to(chai, wrapped_metaobject<M>{}));
}

} // namespace mirror

#endif
