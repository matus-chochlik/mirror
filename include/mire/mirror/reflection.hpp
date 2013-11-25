/**
 *  @file mire/mirror/reflection.hpp
 *  @brief Implementation of reflection templates and operators
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2006-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_MIRROR_REFLECTION_1310291537_HPP
#define MIRE_MIRROR_REFLECTION_1310291537_HPP

#include <mire/mirror/fwd.hpp>
#include <mire/mirror/stddef.hpp>
#include <mire/reg/global_scope.hpp>

namespace mire {
namespace mirror {

#define MIRRORED(NAME) mirror::meta<mire::reg::_##NAME::_, void>
#define MIRRORED_GLOBAL_SCOPE() mirror::meta<mire::reg::_, void>
// TODO: define only optionally
#define mirrored(NAME) MIRRORED(NAME)

/// Reflects the specified Type
/** Returns a Metaobject reflecting the specified type.
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
