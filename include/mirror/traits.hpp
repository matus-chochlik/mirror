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
/// @see meta_traits
/// @see has_trait
/// @see metaobject_unary_op
enum class meta_trait : std::uint64_t {
    /// @brief Indicates if the argument is a metaobject.
    /// @see mirror::reflects_object
    reflects_object = 1ULL << 0ULL,
    /// @brief Indicates if the argument reflects a sequence of metaobjects.
    /// @see mirror::reflects_object_sequence
    reflects_object_sequence = 1ULL << 1ULL,
    /// @brief Indicates if a metaobject reflects a named base-level entity.
    /// @see mirror::reflects_named
    reflects_named = 1ULL << 2ULL,
    /// @brief Indicates if a metaobject reflects a base-level alias.
    /// @see mirror::reflects_alias
    reflects_alias = 1ULL << 3ULL,
    /// @brief Indicates if a metaobject reflects a base-level entity with a type.
    /// @see mirror::reflects_typed
    reflects_typed = 1ULL << 4ULL,
    /// @brief Indicates if a metaobject reflects a base-level scope.
    /// @see mirror::reflects_scope
    reflects_scope = 1ULL << 5ULL,
    /// @brief Indicates if a metaobject reflects a base-level scope member.
    /// @see mirror::reflects_scope_member
    reflects_scope_member = 1ULL << 6ULL,
    /// @brief Indicates if a metaobject reflects an enumerator.
    /// @see mirror::reflects_enumerator
    reflects_enumerator = 1ULL << 7ULL,
    /// @brief Indicates if a metaobject reflects a record member.
    /// @see mirror::reflects_record_member
    reflects_record_member = 1ULL << 8ULL,
    /// @brief Indicates if a metaobject reflects a base class specifier.
    /// @see mirror::reflects_base
    reflects_base = 1ULL << 9ULL,
    /// @brief Indicates if a metaobject reflects a namespace.
    /// @see mirror::reflects_namespace
    reflects_namespace = 1ULL << 10ULL,
    /// @brief Indicates if a metaobject reflects the global scope.
    /// @see mirror::reflects_global_scope
    reflects_global_scope = 1ULL << 11ULL,
    /// @brief Indicates if a metaobject reflects a type.
    /// @see mirror::reflects_type
    reflects_type = 1ULL << 12ULL,
    /// @brief Indicates if a metaobject reflects an enumeration type.
    /// @see mirror::reflects_enum
    reflects_enum = 1ULL << 13ULL,
    /// @brief Indicates if a metaobject reflects a record types (union or class).
    /// @see mirror::reflects_record
    reflects_record = 1ULL << 14ULL,
    /// @brief Indicates if a metaobject reflects a class.
    /// @see mirror::reflects_class
    reflects_class = 1ULL << 15ULL,
    /// @brief Indicates if a metaobject reflects a lambda closure type.
    /// @see mirror::reflects_lambda
    reflects_lambda = 1ULL << 16ULL,
    /// @brief Indicates if a metaobject reflects a constant.
    /// @see mirror::reflects_constant
    reflects_constant = 1ULL << 17ULL,
    /// @brief Indicates if a metaobject reflects a variable.
    /// @see mirror::reflects_variable
    reflects_variable = 1ULL << 18ULL,
    /// @brief Indicates if a metaobject reflects a lambda capture.
    /// @see mirror::reflects_lambda_capture
    reflects_lambda_capture = 1ULL << 19ULL,
    /// @brief Indicates if a metaobject reflects a function parameter.
    /// @see mirror::reflects_function_parameter
    reflects_function_parameter = 1ULL << 20ULL,
    /// @brief Indicates if a metaobject reflects a callable base-level entity.
    /// @see mirror::reflects_callable
    reflects_callable = 1ULL << 21ULL,
    /// @brief Indicates if a metaobject reflects a function.
    /// @see mirror::reflects_function
    reflects_function = 1ULL << 22ULL,
    /// @brief Indicates if a metaobject reflects a record member function.
    /// @see mirror::reflects_member_function
    reflects_member_function = 1ULL << 23ULL,
    /// @brief Indicates if a metaobject reflects a special member function.
    /// @see mirror::reflects_special_member_function
    reflects_special_member_function = 1ULL << 24ULL,
    /// @brief Indicates if a metaobject reflects a constructor.
    /// @see mirror::reflects_constructor
    reflects_constructor = 1ULL << 25ULL,
    /// @brief Indicates if a metaobject reflects a destructor.
    /// @see mirror::reflects_destructor
    reflects_destructor = 1ULL << 26ULL,
    /// @brief Indicates if a metaobject reflects an operator.
    /// @see mirror::reflects_operator
    reflects_operator = 1ULL << 27ULL,
    /// @brief Indicates if a metaobject reflects a conversion operator.
    /// @see mirror::reflects_conversion_operator
    reflects_conversion_operator = 1ULL << 28ULL,
    /// @brief Indicates if a metaobject reflects an expression.
    /// @see mirror::reflects_expression
    reflects_expression = 1ULL << 29ULL,
    /// @brief Indicates if a metaobject reflects a parenthesized expression.
    /// @see mirror::reflects_parenthesized_expression
    reflects_parenthesized_expression = 1ULL << 30ULL,
    /// @brief Indicates if a metaobject reflects a function call expression.
    /// @see mirror::reflects_function_call_expression
    reflects_function_call_expression = 1ULL << 31ULL,
    /// @brief Indicates if a metaobject reflects a specifier.
    /// @see mirror::reflects_specifier
    reflects_specifier = 1ULL << 32ULL
};

/// @brief Metaobject trait bitfield.
/// @ingroup classification
/// @see meta_trait
/// @see get_traits
using meta_traits = bitfield<meta_trait>;

static constexpr auto operator|(meta_trait l, meta_trait r) noexcept
  -> meta_traits {
    return {l, r};
}

template <meta_trait>
struct map_trait;

#define MIRROR_IMPLEMENT_MAP_TRAIT(NAME)                         \
    template <>                                                  \
    struct map_trait<meta_trait::MIRROR_JOIN(reflects_, NAME)> { \
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
/// @see meta_trait
/// @see metaobject_unary_op
/// @see get_traits
template <meta_trait T, __metaobject_id M>
constexpr auto has_trait(wrapped_metaobject<M>) noexcept -> bool {
    return map_trait<T>::apply(M);
}

/// @brief Gets all metaobject traits.
/// @ingroup classification
/// @see meta_traits
/// @see metaobject_unary_op
/// @see has_trait
template <__metaobject_id M>
constexpr auto get_traits(wrapped_metaobject<M> mo) noexcept -> meta_traits {
    meta_traits result{};
    for_each(get_enumerators(mirror(meta_trait)), [&](auto me) {
        if(has_trait<get_constant(me)>(mo)) {
            result |= get_constant(me);
        }
    });
    return result;
}

} // namespace mirror

#endif
