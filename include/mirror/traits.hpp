/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_TRAITS_HPP
#define MIRROR_TRAITS_HPP

#include "preprocessor.hpp"
#include "primitives.hpp"

namespace mirror {

/// @brief Enumeration of metaobject trait operations.
/// @ingroup classification
/// @see has_trait
/// @see metaobject_unary_op
enum class metaobject_trait {
    /// @brief Indicates if the argument is a metaobject.
    /// @see reflects_object
    is_object = 1,
    /// @brief Indicates if the argument reflects a sequence of metaobjects.
    /// @see reflects_object_sequence
    is_object_sequence,
    /// @brief Indicates if a metaobject reflects a named base-level entity.
    /// @see reflects_named
    is_named,
    /// @brief Indicates if a metaobject reflects a base-level alias.
    /// @see reflects_alias
    is_alias,
    /// @brief Indicates if a metaobject reflects a base-level entity with a type.
    /// @see reflects_typed
    is_typed,
    /// @brief Indicates if a metaobject reflects a base-level scope.
    /// @see reflects_scope
    is_scope,
    /// @brief Indicates if a metaobject reflects a base-level scope member.
    /// @see reflects_scope_member
    is_scope_member,
    /// @brief Indicates if a metaobject reflects an enumerator.
    /// @see reflects_enumerator
    is_enumerator,
    /// @brief Indicates if a metaobject reflects a record member.
    /// @see reflects_record_member
    is_record_member,
    /// @brief Indicates if a metaobject reflects a base class specifier.
    /// @see reflects_base
    is_base,
    /// @brief Indicates if a metaobject reflects a namespace.
    /// @see reflects_namespace
    is_namespace,
    /// @brief Indicates if a metaobject reflects the global scope.
    /// @see reflects_global_scope
    is_global_scope,
    /// @brief Indicates if a metaobject reflects a type.
    /// @see reflects_type
    is_type,
    /// @brief Indicates if a metaobject reflects an enumeration type.
    /// @see reflects_enum
    is_enum,
    /// @brief Indicates if a metaobject reflects a record types (union or class).
    /// @see reflects_record
    is_record,
    /// @brief Indicates if a metaobject reflects a class.
    /// @see reflects_class
    is_class,
    /// @brief Indicates if a metaobject reflects a lambda closure type.
    /// @see reflects_lambda
    is_lambda,
    /// @brief Indicates if a metaobject reflects a constant.
    /// @see reflects_constant
    is_constant,
    /// @brief Indicates if a metaobject reflects a variable.
    /// @see reflects_variable
    is_variable,
    /// @brief Indicates if a metaobject reflects a lambda capture.
    /// @see reflects_lambda_capture
    is_lambda_capture,
    /// @brief Indicates if a metaobject reflects a function parameter.
    /// @see reflects_function_parameter
    is_function_parameter,
    /// @brief Indicates if a metaobject reflects a callable base-level entity.
    /// @see reflects_callable
    is_callable,
    /// @brief Indicates if a metaobject reflects a function.
    /// @see reflects_function
    is_function,
    /// @brief Indicates if a metaobject reflects a record member function.
    /// @see reflects_member_function
    is_member_function,
    /// @brief Indicates if a metaobject reflects a special member function.
    /// @see reflects_special_member_function
    is_special_member_function,
    /// @brief Indicates if a metaobject reflects a constructor.
    /// @see reflects_constructor
    is_constructor,
    /// @brief Indicates if a metaobject reflects a destructor.
    /// @see reflects_destructor
    is_destructor,
    /// @brief Indicates if a metaobject reflects an operator.
    /// @see reflects_operator
    is_operator,
    /// @brief Indicates if a metaobject reflects a conversion operator.
    /// @see reflects_conversion_operator
    is_conversion_operator,
    /// @brief Indicates if a metaobject reflects an expression.
    /// @see reflects_expression
    is_expression,
    /// @brief Indicates if a metaobject reflects a parenthesized expression.
    /// @see reflects_parenthesized_expression
    is_parenthesized_expression,
    /// @brief Indicates if a metaobject reflects a function call expression.
    /// @see reflects_function_call_expression
    is_function_call_expression,
    /// @brief Indicates if a metaobject reflects a specifier.
    /// @see reflects_specifier
    is_specifier
};

template <metaobject_trait>
struct map_trait;

#define MIRROR_IMPLEMENT_MAP_TRAIT(NAME)                         \
    template <>                                                  \
    struct map_trait<metaobject_trait::MIRROR_JOIN(is_, NAME)> { \
        static consteval auto apply(__metaobject_id mi) {        \
            return MIRROR_JOIN(__metaobject_is_meta_, NAME)(mi); \
        }                                                        \
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

/// @brief Indicates if a metaobject has the specified trait.
/// @ingroup classification
/// @see metaobject_trait
/// @see metaobject_unary_op
template <metaobject_trait T, __metaobject_id M>
constexpr auto has_trait(wrapped_metaobject<M>) noexcept -> bool {
    return map_trait<T>::apply(M);
}

} // namespace mirror

#endif
