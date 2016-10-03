/**
 * @file reflbase/reflfake.hpp
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef REFLBASE_REFLFAKE_1105240825_HPP
#define REFLBASE_REFLFAKE_1105240825_HPP

#ifndef REFLBASE_REFLBASE_1105240825_HPP
#error Do not include "reflbase/reflexpr.hpp" directly, include "reflbase.hpp"!
#endif

#include <type_traits>
#include "string.hpp"
#include "sequence.hpp"

namespace reflbase {

template <typename Reg, typename Typ = void>
struct metaobject;

template <typename X>
struct is_metaobject
 : std::false_type
{ };

// is_metaobject
template <typename Reg, typename Typ>
struct is_metaobject<metaobject<Reg, Typ>>
 : std::true_type
{ };

template <typename ... P>
struct is_metaobject<sequence<P...>>
 : std::true_type
{ };

// Object
template <typename X>
constexpr const bool Object = is_metaobject<X>::value;

namespace _aux {

template <typename X>
struct is_metaobject_sequence
 : std::false_type
{ };

template <typename ... P>
struct is_metaobject_sequence<sequence<P...>>
 : std::true_type
{ };

} // namespace _aux

// ObjectSequence
template <typename X>
constexpr const bool ObjectSequence = _aux::is_metaobject_sequence<X>::value;

namespace _aux {

enum metaobject_category : unsigned
{
    MOC_ObjectSequence  = (1 <<  0),
    MOC_Reversible      = (1 <<  1),
    MOC_Named           = (1 <<  2),
    MOC_Typed           = (1 <<  3),
    MOC_Scope           = (1 <<  4),
    MOC_ScopeMember     = (1 <<  5),
    MOC_Inheritance     = (1 <<  6),
    MOC_Template        = (1 <<  7),
    MOC_Parameter       = (1 <<  8),
    MOC_EnumMember      = (1 <<  9) | MOC_ScopeMember,
    MOC_RecordMember    = (1 << 10) | MOC_ScopeMember,
    MOC_Alias           = (1 << 11) | MOC_Named,
    MOC_Constant        = (1 << 12) | MOC_Typed,
    MOC_Variable        = (1 << 13) | MOC_Named | MOC_Typed | MOC_ScopeMember,
    MOC_Namespace       = (1 << 14) | MOC_Named | MOC_Scope | MOC_ScopeMember,
    MOC_GlobalScope     = (1 << 15) | MOC_Namespace,
    MOC_Type            = (1 << 16) | MOC_Named | MOC_Reversible,
    MOC_TagType         = (1 << 17) | MOC_Type | MOC_Scope | MOC_ScopeMember,
    MOC_Enum            = (1 << 18) | MOC_TagType,
    MOC_Record          = (1 << 19) | MOC_TagType,
    MOC_Class           = (1 << 20) | MOC_Record,
    MOC_Specifier       = (1 << 21) | MOC_Named,
    MOC_TplTypeParam    = MOC_Template | MOC_Type| MOC_Parameter | MOC_Alias,
    MOC_NamespaceAlias  = MOC_Namespace | MOC_Alias,
    MOC_TypeAlias       = MOC_Type | MOC_Alias | MOC_ScopeMember,
    MOC_EnumAlias       = MOC_Enum | MOC_Alias,
    MOC_ClassAlias      = MOC_Class | MOC_Alias,
    MOC_DataMember      = MOC_RecordMember | MOC_Variable,
    MOC_MemberType      = MOC_RecordMember | MOC_Type,
    MOC_MemberClass     = MOC_RecordMember | MOC_Class,
    MOC_MemberEnum      = MOC_RecordMember | MOC_Enum,
    MOC_Enumerator      = MOC_Constant | MOC_Named | MOC_EnumMember
};

template <typename X>
struct get_category;

template <typename X>
constexpr bool is_a(metaobject_category moc)
noexcept { return (get_category<X>::value & moc) == moc; }

} // namespace _aux

// Other categories
template <typename X>
constexpr const bool Reversible = _aux::is_a<X>(_aux::MOC_Reversible);

template <typename X>
constexpr const bool Named = _aux::is_a<X>(_aux::MOC_Named);

template <typename X>
constexpr const bool Alias = _aux::is_a<X>(_aux::MOC_Alias);

template <typename X>
constexpr const bool Typed = _aux::is_a<X>(_aux::MOC_Typed);

template <typename X>
constexpr const bool Scope = _aux::is_a<X>(_aux::MOC_Scope);

template <typename X>
constexpr const bool Namespace = _aux::is_a<X>(_aux::MOC_Namespace);

template <typename X>
constexpr const bool GlobalScope = _aux::is_a<X>(_aux::MOC_GlobalScope);

template <typename X>
constexpr const bool ScopeMember = _aux::is_a<X>(_aux::MOC_ScopeMember);

template <typename X>
constexpr const bool EnumMember = _aux::is_a<X>(_aux::MOC_EnumMember);

template <typename X>
constexpr const bool RecordMember = _aux::is_a<X>(_aux::MOC_RecordMember);

template <typename X>
constexpr const bool Type = _aux::is_a<X>(_aux::MOC_Type);

template <typename X>
constexpr const bool TagType = _aux::is_a<X>(_aux::MOC_TagType);

template <typename X>
constexpr const bool Enum = _aux::is_a<X>(_aux::MOC_Enum);

template <typename X>
constexpr const bool Record = _aux::is_a<X>(_aux::MOC_Record);

template <typename X>
constexpr const bool Class = _aux::is_a<X>(_aux::MOC_Class);

template <typename X>
constexpr const bool Variable = _aux::is_a<X>(_aux::MOC_Variable);

template <typename X>
constexpr const bool Constant = _aux::is_a<X>(_aux::MOC_Constant);

template <typename X>
constexpr const bool Inheritance = _aux::is_a<X>(_aux::MOC_Inheritance);

template <typename X>
constexpr const bool Specifier = _aux::is_a<X>(_aux::MOC_Specifier);

// get_size
template <typename X>
struct get_size;

template <typename ... P>
struct get_size<sequence<P...>>
 : std::integral_constant<unsigned, unsigned(sizeof...(P))>
{ };

// get_element
template <typename X, unsigned I>
struct get_element;

template <typename H, typename ... T>
struct get_element<sequence<H, T...>, 0u>
{
	using type = H;
};

template <typename H, typename ... T, unsigned I>
struct get_element<sequence<H, T...>, I>
 : get_element<sequence<T...>, I-1>
{ };

// unpack_sequence
template <typename X, template <class...> class Tpl>
struct unpack_sequence;

template <typename ... P, template <class...> class Tpl>
struct unpack_sequence<sequence<P...>, Tpl>
{
	using type = Tpl<P...>;
};

// get_source_file
template <typename X>
struct get_source_file
 : empty_string
{ };

// get_source_line
template <typename X>
struct get_source_line
 : std::integral_constant<unsigned, 0>
{ };

// get_source_column
template <typename X>
struct get_source_column
 : std::integral_constant<unsigned, 0>
{ };

// get_base_name
template <typename X>
struct get_base_name;

// get_display_name
template <typename X>
struct get_display_name
 : get_base_name<X> // TODO
{ };

// is_anonymous
template <typename X>
struct is_anonymous
 : std::integral_constant<bool, get_base_name<X>::size == 0>
{ };

// get_aliased
template <typename X>
struct get_aliased;

// get_scope
template <typename X>
struct get_scope;

// get_type
template <typename X>
struct get_type;

// get_elaborated_type_specifier
template <typename X>
struct get_elaborated_type_specifier;

// is_enum
template <typename X>
struct is_enum;

// is_scoped_enum
template <typename X>
struct is_scoped_enum;

// is_struct
template <typename X>
struct is_struct;

// is_class
template <typename X>
struct is_class;

// is_union
template <typename X>
struct is_union;

// get_enumerators
template <typename X>
struct get_enumerators;

// get_member_types
template <typename X>
struct get_member_types;

// get_public_member_types
template <typename X>
struct get_public_member_types;

// get_data_members
template <typename X>
struct get_data_members;

// get_public_data_members
template <typename X>
struct get_public_data_members;

// get_base_classes
template <typename X>
struct get_base_classes;

// get_public_base_classes
template <typename X>
struct get_public_base_classes;

// get_reflected_type
template <typename X>
struct get_reflected_type;

template <typename Reg, typename Typ>
struct get_reflected_type<metaobject<Reg, Typ>>
{
	using type = Typ;
};

// get_pointer
template <typename X>
struct get_pointer;

// get_constant
template <typename X>
struct get_constant;

// get_base_class
template <typename X>
struct get_base_class;

// get_access_specifier
template <typename X>
struct get_access_specifier;

// is_public
template <typename X>
struct is_public;

// is_protected
template <typename X>
struct is_protected;

// is_private
template <typename X>
struct is_private;

// is_static
template <typename X>
struct is_static;

// is_virtual
template <typename X>
struct is_virtual;

} // namespace reflbase

#endif //include guard

