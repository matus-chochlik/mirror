/**
 *  @file mire/mirror/reflection.hpp
 *  @brief Implementation of reflection templates and operators
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2006-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_MIRROR_REFLECTION_1310291537_HPP
#define MIRE_MIRROR_REFLECTION_1310291537_HPP

#include <mire/mirror/fwd.hpp>
#include <mire/mirror/stddef.hpp>
#include <mire/mirror/traits.hpp>
#include <mire/reg/global_scope.hpp>

namespace mire {
namespace mirror {
namespace _aux {

template <typename Reg, typename IsSpecifier>
struct pick_refl;

template <typename Reg>
struct pick_refl<Reg, ct::false_type>
 : meta<Reg, void>
{ };

template <typename Reg>
struct pick_refl<Reg, ct::true_type>
 : spec<typename Reg::spec_tag>
{ };

} // namespace _aux

template <typename Reg>
struct pick_refl
 : _aux::pick_refl<Reg, typename Reg::is_specifier>
{ };

/** @defgroup mirror_reflection_expr Mirror's reflection expressions
 *
 *  In this group there are defined preprocessor macros and templates
 *  that can be used to reflect base-level constructs i.e. to obtain
 *  Metaobject providing meta-data about the reflected construct.
 */

/// This macro can be used to reflect non-type language constructs
/**
 *  @ingroup mirror_reflection_expr
 */
#define MIRRORED(NAME) \
	mire::mirror::pick_refl<mire::reg::_##NAME::_>

/// This macro can be used to reflect the global scope namespace
/**
 *  @ingroup mirror_reflection_expr
 */
#define MIRRORED_GLOBAL_SCOPE() \
	mire::mirror::meta<mire::reg::_, void>

/// This macro can be used to reflect a specifier
/**
 *  @ingroup mirror_reflection_expr
 */
#define MIRRORED_SPECIFIER(NAME) \
	mire::mirror::spec<mire::mirror::spec_##NAME##_tag>

// TODO: define only optionally
#define mirrored(NAME) MIRRORED(NAME)

/// Reflects the specified Type
/** Returns a Metaobject reflecting the specified type.
 *
 *  @ingroup mirror_reflection_expr
 */
template <typename Type>
struct mirrored_t
#ifndef MIRROR_DOCUMENTATION_ONLY
 : meta<typename reg::_type_reg<Type>::type, Type>
#else
 : MetaType
#endif
{ };

} // namespace mirror
} // namespace mire

#endif // include guard
