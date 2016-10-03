/**
 * @file reflbase/reflexpr.hpp
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef REFLBASE_REFLEXPR_1105240825_HPP
#define REFLBASE_REFLEXPR_1105240825_HPP

#ifndef REFLBASE_REFLBASE_1105240825_HPP
#error Do not include "reflbase/reflexpr.hpp" directly, include "reflbase.hpp"!
#endif

#include <reflexpr>

namespace reflbase {

using std::is_metaobject;

using std::meta::Object;
using std::meta::ObjectSequence;
using std::meta::Reversible;
using std::meta::Named;
using std::meta::Typed;
using std::meta::Scope;
using std::meta::Inheritance;
using std::meta::ScopeMember;
using std::meta::EnumMember;
using std::meta::RecordMember;
using std::meta::Alias;
using std::meta::Constant;
using std::meta::Variable;
using std::meta::Namespace;
using std::meta::GlobalScope;
using std::meta::Type;
using std::meta::TagType;
using std::meta::Enum;
using std::meta::Record;
using std::meta::Class;
using std::meta::Specifier;

using std::meta::get_source_file;
using std::meta::get_source_line;
using std::meta::get_source_column;

using std::meta::get_size;
using std::meta::get_element;
using std::meta::unpack_sequence;

using std::meta::is_anonymous;
using std::meta::get_base_name;
using std::meta::get_display_name;
using std::meta::get_aliased;

using std::meta::get_scope;
using std::meta::get_type;

using std::meta::get_elaborated_type_specifier;
using std::meta::is_enum;
using std::meta::is_scoped_enum;
using std::meta::is_struct;
using std::meta::is_class;
using std::meta::is_union;

using std::meta::get_enumerators;
using std::meta::get_member_types;
using std::meta::get_public_member_types;
using std::meta::get_data_members;
using std::meta::get_public_data_members;
using std::meta::get_base_classes;
using std::meta::get_public_base_classes;

using std::meta::get_reflected_type;
using std::meta::get_pointer;
using std::meta::get_constant;

using std::meta::get_base_class;

using std::meta::get_access_specifier;
using std::meta::is_public;
using std::meta::is_protected;
using std::meta::is_private;

using std::meta::is_static;
using std::meta::is_virtual;

} // namespace reflbase

#endif //include guard

