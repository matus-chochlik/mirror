/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_TRAITS_HPP
#define MIRROR_TRAITS_HPP

#include "primitives.hpp"

namespace mirror {

enum class metaobject_trait {
    is_object = 1,
    is_object_sequence,
    is_named,
    is_alias,
    is_typed,
    is_scope,
    is_scope_member,
    is_enumerator,
    is_record_member,
    is_base,
    is_namespace,
    is_global_scope,
    is_type,
    is_enum,
    is_record,
    is_class,
    is_lambda,
    is_constant,
    is_variable,
    is_lambda_capture,
    is_function_parameter,
    is_callable,
    is_function,
    is_member_function,
    is_special_member_function,
    is_constructor,
    is_destructor,
    is_operator,
    is_conversion_operator,
    is_expression,
    is_parenthesized_expression,
    is_function_call_expression,
    is_specifier
};

template <metaobject_trait>
struct map_trait;

#define MIRROR_IMPLEMENT_MAP_TRAIT(NAME)                  \
    template <>                                           \
    struct map_trait<metaobject_trait::is_##NAME> {       \
        static consteval auto apply(__metaobject_id mi) { \
            return __metaobject_is_meta_##NAME(mi);       \
        }                                                 \
    };

MIRROR_IMPLEMENT_MAP_TRAIT(object)
MIRROR_IMPLEMENT_MAP_TRAIT(object_sequence)
MIRROR_IMPLEMENT_MAP_TRAIT(named)
MIRROR_IMPLEMENT_MAP_TRAIT(alias)
MIRROR_IMPLEMENT_MAP_TRAIT(typed)
MIRROR_IMPLEMENT_MAP_TRAIT(scope)
MIRROR_IMPLEMENT_MAP_TRAIT(scope_member)
MIRROR_IMPLEMENT_MAP_TRAIT(enumerator)
MIRROR_IMPLEMENT_MAP_TRAIT(record_member)
MIRROR_IMPLEMENT_MAP_TRAIT(base)
MIRROR_IMPLEMENT_MAP_TRAIT(namespace)
MIRROR_IMPLEMENT_MAP_TRAIT(global_scope)
MIRROR_IMPLEMENT_MAP_TRAIT(type)
MIRROR_IMPLEMENT_MAP_TRAIT(enum)
MIRROR_IMPLEMENT_MAP_TRAIT(record)
MIRROR_IMPLEMENT_MAP_TRAIT(class)
MIRROR_IMPLEMENT_MAP_TRAIT(lambda)
MIRROR_IMPLEMENT_MAP_TRAIT(constant)
MIRROR_IMPLEMENT_MAP_TRAIT(variable)
MIRROR_IMPLEMENT_MAP_TRAIT(lambda_capture)
MIRROR_IMPLEMENT_MAP_TRAIT(function_parameter)
MIRROR_IMPLEMENT_MAP_TRAIT(callable)
MIRROR_IMPLEMENT_MAP_TRAIT(function)
MIRROR_IMPLEMENT_MAP_TRAIT(member_function)
MIRROR_IMPLEMENT_MAP_TRAIT(special_member_function)
MIRROR_IMPLEMENT_MAP_TRAIT(constructor)
MIRROR_IMPLEMENT_MAP_TRAIT(destructor)
MIRROR_IMPLEMENT_MAP_TRAIT(operator)
MIRROR_IMPLEMENT_MAP_TRAIT(conversion_operator)
MIRROR_IMPLEMENT_MAP_TRAIT(expression)
MIRROR_IMPLEMENT_MAP_TRAIT(parenthesized_expression)
MIRROR_IMPLEMENT_MAP_TRAIT(function_call_expression)
MIRROR_IMPLEMENT_MAP_TRAIT(specifier)

#undef MIRROR_IMPLEMENT_MAP_TRAIT

template <metaobject_trait T, __metaobject_id M>
constexpr auto has_trait(wrapped_metaobject<M>) noexcept -> bool {
    return map_trait<T>::apply(M);
}

} // namespace mirror

#endif
