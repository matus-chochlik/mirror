/**
 * .file lagoon/metaobject_traits.inl
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
#include <puddle/metaobject_ops.hpp>

namespace lagoon {

constexpr inline
metaobject_traits::
metaobject_traits(mirror::none)
noexcept
 : has_source_info{false}
 , reflects_specifier{false}
 , reflects_global_scope{false}
 , reflects_namespace{false}
 , reflects_type{false}
 , reflects_alias{false}
 , reflects_variable{false}
 , reflects_constant{false}
 , reflects_enum_member{false}
 , reflects_record_member{false}
 , reflects_inheritance{false}
 , is_anonymous{false}
 , is_class{false}
 , is_struct{false}
 , is_union{false}
 , is_enum{false}
 , is_scoped_enum{false}
 , is_static{false}
 , is_virtual{false}
{ }

template <typename MO>
constexpr inline
metaobject_traits::
metaobject_traits(MO mo)
noexcept
 : has_source_info{puddle::has_source_info(mo)}
 , reflects_specifier{puddle::reflects_specifier(mo)}
 , reflects_global_scope{puddle::reflects_global_scope(mo)}
 , reflects_namespace{puddle::reflects_namespace(mo)}
 , reflects_type{puddle::reflects_type(mo)}
 , reflects_alias{puddle::reflects_type(mo)}
 , reflects_variable{puddle::reflects_variable(mo)}
 , reflects_constant{puddle::reflects_constant(mo)}
 , reflects_enum_member{puddle::reflects_enum_member(mo)}
 , reflects_record_member{puddle::reflects_record_member(mo)}
 , reflects_inheritance{puddle::reflects_inheritance(mo)}
 , is_anonymous{puddle::is_anonymous(mo)}
 , is_class{puddle::is_class(mo)}
 , is_struct{puddle::is_struct(mo)}
 , is_union{puddle::is_union(mo)}
 , is_enum{puddle::is_enum(mo)}
 , is_scoped_enum{puddle::is_scoped_enum(mo)}
 , is_static{puddle::is_static(mo)}
 , is_virtual{puddle::is_virtual(mo)}
{ }

} // namespace lagoon
