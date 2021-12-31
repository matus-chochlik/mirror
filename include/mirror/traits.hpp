/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_TRAITS_HPP
#define MIRROR_TRAITS_HPP

#include "bitfield.hpp"
#include "preprocessor.hpp"
#include "sequence.hpp"
#include <cstdint>

namespace mirror {

/// @brief Enumeration of metaobject trait operations.
/// @ingroup classification
/// @see metaobject_traits
/// @see has_trait
/// @see metaobject_unary_op
enum class metaobject_trait : std::uint64_t {
    /// @brief Indicates if the argument is a metaobject.
    /// @see reflects_object
    is_object = 1ULL << 0ULL,
    /// @brief Indicates if the argument reflects a sequence of metaobjects.
    /// @see reflects_object_sequence
    is_object_sequence = 1ULL << 1ULL,
    /// @brief Indicates if a metaobject reflects a named base-level entity.
    /// @see reflects_named
    is_named = 1ULL << 2ULL,
    /// @brief Indicates if a metaobject reflects a base-level alias.
    /// @see reflects_alias
    is_alias = 1ULL << 3ULL,
    /// @brief Indicates if a metaobject reflects a base-level entity with a type.
    /// @see reflects_typed
    is_typed = 1ULL << 4ULL,
    /// @brief Indicates if a metaobject reflects a base-level scope.
    /// @see reflects_scope
    is_scope = 1ULL << 5ULL,
    /// @brief Indicates if a metaobject reflects a base-level scope member.
    /// @see reflects_scope_member
    is_scope_member = 1ULL << 6ULL,
    /// @brief Indicates if a metaobject reflects an enumerator.
    /// @see reflects_enumerator
    is_enumerator = 1ULL << 7ULL,
    /// @brief Indicates if a metaobject reflects a record member.
    /// @see reflects_record_member
    is_record_member = 1ULL << 8ULL,
    /// @brief Indicates if a metaobject reflects a base class specifier.
    /// @see reflects_base
    is_base = 1ULL << 9ULL,
    /// @brief Indicates if a metaobject reflects a namespace.
    /// @see reflects_namespace
    is_namespace = 1ULL << 10ULL,
    /// @brief Indicates if a metaobject reflects the global scope.
    /// @see reflects_global_scope
    is_global_scope = 1ULL << 11ULL,
    /// @brief Indicates if a metaobject reflects a type.
    /// @see reflects_type
    is_type = 1ULL << 12ULL,
    /// @brief Indicates if a metaobject reflects an enumeration type.
    /// @see reflects_enum
    is_enum = 1ULL << 13ULL,
    /// @brief Indicates if a metaobject reflects a record types (union or class).
    /// @see reflects_record
    is_record = 1ULL << 14ULL,
    /// @brief Indicates if a metaobject reflects a class.
    /// @see reflects_class
    is_class = 1ULL << 15ULL,
    /// @brief Indicates if a metaobject reflects a lambda closure type.
    /// @see reflects_lambda
    is_lambda = 1ULL << 16ULL,
    /// @brief Indicates if a metaobject reflects a constant.
    /// @see reflects_constant
    is_constant = 1ULL << 17ULL,
    /// @brief Indicates if a metaobject reflects a variable.
    /// @see reflects_variable
    is_variable = 1ULL << 18ULL,
    /// @brief Indicates if a metaobject reflects a lambda capture.
    /// @see reflects_lambda_capture
    is_lambda_capture = 1ULL << 19ULL,
    /// @brief Indicates if a metaobject reflects a function parameter.
    /// @see reflects_function_parameter
    is_function_parameter = 1ULL << 20ULL,
    /// @brief Indicates if a metaobject reflects a callable base-level entity.
    /// @see reflects_callable
    is_callable = 1ULL << 21ULL,
    /// @brief Indicates if a metaobject reflects a function.
    /// @see reflects_function
    is_function = 1ULL << 22ULL,
    /// @brief Indicates if a metaobject reflects a record member function.
    /// @see reflects_member_function
    is_member_function = 1ULL << 23ULL,
    /// @brief Indicates if a metaobject reflects a special member function.
    /// @see reflects_special_member_function
    is_special_member_function = 1ULL << 24ULL,
    /// @brief Indicates if a metaobject reflects a constructor.
    /// @see reflects_constructor
    is_constructor = 1ULL << 25ULL,
    /// @brief Indicates if a metaobject reflects a destructor.
    /// @see reflects_destructor
    is_destructor = 1ULL << 26ULL,
    /// @brief Indicates if a metaobject reflects an operator.
    /// @see reflects_operator
    is_operator = 1ULL << 27ULL,
    /// @brief Indicates if a metaobject reflects a conversion operator.
    /// @see reflects_conversion_operator
    is_conversion_operator = 1ULL << 28ULL,
    /// @brief Indicates if a metaobject reflects an expression.
    /// @see reflects_expression
    is_expression = 1ULL << 29ULL,
    /// @brief Indicates if a metaobject reflects a parenthesized expression.
    /// @see reflects_parenthesized_expression
    is_parenthesized_expression = 1ULL << 30ULL,
    /// @brief Indicates if a metaobject reflects a function call expression.
    /// @see reflects_function_call_expression
    is_function_call_expression = 1ULL << 31ULL,
    /// @brief Indicates if a metaobject reflects a specifier.
    /// @see reflects_specifier
    is_specifier = 1ULL << 32ULL
};

/// @brief Metaobject trait bitfield.
/// @ingroup classification
/// @see metaobject_trait
/// @see get_traits
using metaobject_traits = bitfield<metaobject_trait>;

static constexpr auto operator|(metaobject_trait l, metaobject_trait r) noexcept
  -> metaobject_traits {
    return {l, r};
}

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
/// @see get_traits
template <metaobject_trait T, __metaobject_id M>
constexpr auto has_trait(wrapped_metaobject<M>) noexcept -> bool {
    return map_trait<T>::apply(M);
}

/// @brief Gets all metaobject traits.
/// @ingroup classification
/// @see metaobject_traits
/// @see metaobject_unary_op
/// @see has_trait
template <__metaobject_id M>
constexpr auto get_traits(wrapped_metaobject<M> mo) noexcept
  -> metaobject_traits {
    metaobject_traits result{};
    for_each(get_enumerators(mirror(metaobject_trait)), [&](auto me) {
        if(has_trait<get_constant(me)>(mo)) {
            result |= get_constant(me);
        }
    });
    return result;
}

} // namespace mirror

#endif
