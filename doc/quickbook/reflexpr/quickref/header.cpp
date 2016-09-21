/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[reflexpr_header_open_std
namespace std {
//]
//[reflexpr_header_is_metaobject
template <typename T>
struct is_metaobject
 : integral_constant<bool, __implementation_defined /*<
[^true] if [^T] is a [link reflexpr.intro.metaobjects Metaobject]
[^false] otherwise.
>*/>
{ };

template <typename T>
constexpr bool is_metaobject_v = is_metaobject<T>::value;
//]
//[reflexpr_header_open_meta
namespace meta {
//]
//[reflexpr_header_concepts_Object
template <typename T> concept bool Object
 =  __is_metaobject_v<T>;
//]

//[reflexpr_header_concepts_ObjectSequence
template <__Object T> concept bool ObjectSequence
 =  __implementation_defined;
//]

//[reflexpr_header_concepts_Reversible
template <__Object T> concept bool Reversible
 =  __implementation_defined;
//]

//[reflexpr_header_concepts_Named
template <__Object T> concept bool Named
 =  __implementation_defined;
//]

//[reflexpr_header_concepts_Alias
template <__Object T> concept bool Alias
 =  Named<T>
 && __implementation_defined;
//]

//[reflexpr_header_concepts_Typed
template <__Object T> concept bool Typed
 =  __implementation_defined;
//]

//[reflexpr_header_concepts_Scope
template <__Object T> concept bool Scope
 =  __implementation_defined;
//]

//[reflexpr_header_concepts_Namespace
template <__Object T> concept bool Namespace
 =  __Named<T>
 && __Scope<T>
 && __ScopeMember<T>
 && __implementation_defined;
//]

//[reflexpr_header_concepts_GlobalScope
template <__Object T> concept bool GlobalScope
 =  __Namespace<T>
 && __implementation_defined;
//]

//[reflexpr_header_concepts_Type
template <__Object T> concept bool Type
 =  __Named<T>
 && __Reversible<T>
 && __implementation_defined;
//]

//[reflexpr_header_concepts_TagType
template <__Object T> concept bool TagType
 =  __Type<T>
 && __Scope<T>
 && __ScopeMember<T>
 && __implementation_defined;
//]

//[reflexpr_header_concepts_Record
template <__Object T> concept bool Record
 =  __TagType<T>
 && __implementation_defined;
//]

//[reflexpr_header_concepts_Enum
template <__Object T> concept bool Enum
 =  __TagType<T>
 && __implementation_defined;
//]

//[reflexpr_header_concepts_Class
template <__Object T> concept bool Class
 =  __Record<T>
 && __implementation_defined;
//]

//[reflexpr_header_concepts_ScopeMember
template <__Object T> concept bool ScopeMember
 =  __implementation_defined;
//]

//[reflexpr_header_concepts_EnumMember
template <__Object T> concept bool EnumMember
 =  __ScopeMember<T>
 && __implementation_defined;
//]

//[reflexpr_header_concepts_RecordMember
template <__Object T> concept bool RecordMember
 =  __ScopeMember<T>
 && __implementation_defined;
//]

//[reflexpr_header_concepts_Variable
template <__Object T> concept bool Variable
 =  __Named<T>
 && __Typed<T>
 && __ScopeMember<T>
 && __implementation_defined;
//]

//[reflexpr_header_concepts_Constant
template <__Object T> concept bool Constant
 =  __Typed<T>
 && __implementation_defined;
//]

//[reflexpr_header_concepts_Specifier
template <__Object T> concept bool Specifier
 =  __Named<T>
 && __implementation_defined;
//]

//[reflexpr_header_concepts_Inheritance
template <__Object T> concept bool Inheritance
 =  __implementation_defined;
//]

//[reflexpr_header_operations_Object
// reflects_same
template <__Object T1, __Object T2>
struct reflects_same
 : integral_constant<bool, __implementation_defined /*<
[^true] if both [^T1] and [^T2] reflect the same base-level declaration,
[^false] otherwise.
>*/>
{ };

template <__Object T1, __Object T2>
constexpr bool reflects_same_v
 = reflects_same<T1, T2>::value;


// get_source_file
template <__Object T>
struct get_source_file {
	using value_type = const char [N+1];
	static constexpr value_type value = __implementation_defined; /*<
	Null-terminated constexpr [^char] array containing the path
	to the source file, where the base-level entity reflected by [^T]
	was declared. If [^T] does not have an in-source declaration
	(for example a built-in type), the value is an empty (null-terminated)
	string.
	>*/
};

template <__Object T>
constexpr auto get_source_file_v
 = get_source_file<T>::value;


// get_source_line
template <__Object T>
struct get_source_line
 : integral_constant<unsigned, __implementation_defined /*<
The source file line number, where the base-level entity reflected by [^T]
was declared. If [^T] does not have an in-source declaration
(for example a built-in type), then the value is zero. >*/>
{ };

template <__Object T>
constexpr auto get_source_line_v
 = get_source_line<T>::value;


// get_source_column
template <__Object T>
struct get_source_column
 : integral_constant<unsigned, __implementation_defined> /*<
The source file column number, where the base-level entity reflected by [^T]
was declared. If [^T] does not have an in-source declaration
(for example a built-in type), then the value is zero. >*/
{ };

template <__Object T>
constexpr auto get_source_column_v
 = get_source_column<T>::value;
//]

//[reflexpr_header_operations_ObjectSequence

// get_size
template <__ObjectSequence T>
struct get_size
 : integral_constant<unsigned, __implementation_defined /*<
The number of elements in the metaobject sequence [^T]. >*/>
{ };

template <__ObjectSequence T>
constexpr auto get_size_v
 = get_size<T>::value;


// get_element
template <__ObjectSequence T, unsigned I>
struct get_element {
	using type = __Object /*<
The [^I]-th metaobject in the metaobject sequence [^T]. >*/
};

template <__ObjectSequence T, unsigned I>
using get_element_m
 = typename get_element<T, I>::type;


// unpack_sequence
template <__ObjectSequence T, template <class ...> class Tpl>
struct unpack_sequence {
	using type = Tpl<__Object ... /*<
	A pack of all metaobjects in the metaobject sequence [^T].
	>*/>;
};

template <__ObjectSequence T, template <class ...> class Tpl>
using unpack_sequence_t
 = typename unpack_sequence<T, Tpl>::type;

//]
//[reflexpr_header_operations_Named

// is_anonymous
template <__Named T>
struct is_anonymous
 : integral_constant<bool, __implementation_defined /*<
[^true] if the base-level entity reflected by [^T] is anonymous
(like a anonymous namespace or class), [^false] otherwise. >*/>
{ };

template <__Named T>
constexpr auto is_anonymous_v
 = is_anonymous<T>::value;


// get_base_name
template <__Named T>
struct get_base_name {
	using value_type = const char [N+1];
	static constexpr value_type value = __implementation_defined; /*<
	Null-terminated constexpr [^char] array containing the base name
	of the base-level named declaration reflected by [^T].
	If the base-level declaration is anonymous then [^value] is an
	empty null-teminated [^char] array.
	The [^get_base_name] operation returns the type, namespace, etc. name
	without any qualifiers, asterisks, ampersands, angle or square brackets,
	etc.
	>*/
};

template <__Named T>
constexpr auto get_base_name_v 
 = get_base_name<T>::value;


// get_display_name
template <__Named T>
struct get_display_name {
	using value_type = const char [N+1];
	static constexpr value_type value = __implementation_defined; /*<
	Null-terminated constexpr [^char] array containing the display name
	of the base-level named declaration reflected by [^T].
	If the base-level declaration is anonymous then [^value] is an
	empty null-teminated [^char] array.
	The name returned by this operation is implementation-defined
	and it should be as close as possible to the declaration name as spelled
	in the source.
	>*/
};

template <__Named T>
constexpr auto get_display_name_v 
 = get_display_name<T>::value;
//]

//[reflexpr_header_operations_Alias

// get_aliased
template <__Alias T>
struct get_aliased {
	using type = __Named; /*<
	The reflection of the original, underlying named declaration aliased by
	the alias reflected by [^T].
	>*/
};

template <__Alias T>
using get_aliased_m
 = typename get_aliased<T>::type;
//]

//[reflexpr_header_operations_Typed

// get_type
template <__Typed T>
struct get_type {
	using type = __Type; /*<
	The reflection of the type of the typed declaration reflected by [^T].
	>*/
};

template <__Typed T>
using get_type_m
 = typename get_type<T>::type;
//]

//[reflexpr_header_operations_Type
// get_reflected_ type
template <__Type T>
struct get_reflected_type {
	using type = __implementation_defined; /*<
	The base-level type reflected by the [^meta::__Type] [^T].
	>*/
};


template <__Type T>
using get_reflected_type_t
 = typename get_reflected_type<T>::type;
//]

//[reflexpr_header_operations_TagType

// is_enum
template <__TagType T>
struct is_enum
 : integral_constant<bool, __implementation_defined /*<
[^true] if the [^meta::__TagType] [^T] reflects an enumeration type,
[^false] otherwise.
>*/
{ };

template <__TagType T>
constexpr bool is_enum_v<T> = is_enum<T>::value;


// is_union
template <__TagType T>
struct is_union
 : integral_constant<bool, __implementation_defined /*<
[^true] if the [^meta::__TagType] [^T] reflects a [^union], [^false] otherwise.
>*/
{ };

template <__TagType T>
constexpr bool is_union_v<T> = is_union<T>::value;

// is_struct
template <__TagType T>
struct is_struct
 : integral_constant<bool, __implementation_defined /*<
[^true] if the [^meta::__TagType] [^T] reflects a [^struct], [^false] otherwise.
>*/
{ };

template <__TagType T>
constexpr bool is_struct_v<T> = is_struct<T>::value;


// is_class
template <__TagType T>
struct is_class
 : integral_constant<bool, __implementation_defined /*<
[^true] if the [^meta::__TagType] [^T] reflects a [^class], [^false] otherwise.
>*/
{ };

template <__TagType T>
constexpr bool is_class_v<T> = is_class<T>::value;

// get_elaborated_type_specifier
template <__TagType T>
struct get_elaborated_type_specifier {
	using type = __Specifier; /*<
	A [^meta::__Specifier] reflecting the elaborated type specifier
	([^enum], [^union], [^struct] or [^class]) of the tag-type reflected
	by [^T].
	>*/
};

template <__TagType T>
using get_elaborated_type_specifier_m
 = typename get_elaborated_type_specifier<T>::type;
//]

//[reflexpr_header_operations_Enum

// is_scoped_enum
template <__Enum T>
struct is_scoped_enum
 : integral_constant<bool, __implementation_defined /*<
[^true] if the [^meta::__Enum] [^T] reflects a scoped (strongly-typed)
enumeration, [^false] otherwise.
>*/
{ };

template <__Enum T>
constexpr bool is_scoped_enum_v<T> = is_scoped_enum<T>::value;

// get_enumerators
template <__Enum T>
struct get_enumerators {
	using type = __ObjectSequence; /*<
	A [^meta::__ObjectSequence] containing [^meta::__EnumMember],
	[^meta::__Constant] metaobjects reflecting the individual enumerators
	of the enumeration reflected by [^T].
	>*/
};

template <__Enum T>
using get_enumerators_m
 = typename get_enumerators<T>::type;
//]

//[reflexpr_header_operations_Record

// get_member_types
template <__Record T>
struct get_member_types {
	using type = __ObjectSequence; /*<
	A [^meta::__ObjectSequence] containing [^meta::__RecordMember],
	[^meta::__Type] metaobjects reflecting the individual member types
	(all of them including the private and protected ones)
	of the [^class], [^struct] or [^union] reflected by [^T].
	>*/
};

template <__Record T>
using get_member_types_m
 = typename get_member_types<T>::type;

// get_public_member_types
template <__Record T>
struct get_public_member_types {
	using type = __ObjectSequence; /*<
	A [^meta::__ObjectSequence] containing [^meta::__RecordMember],
	[^meta::__Type] metaobjects reflecting only the public member types
	of the [^class], [^struct] or [^union] reflected by [^T].
	>*/
};

template <__Record T>
using get_public_member_types_m
 = typename get_public_member_types<T>::type;

// get_data_members
template <__Record T>
struct get_data_members {
	using type = __ObjectSequence; /*<
	A [^meta::__ObjectSequence] containing [^meta::__RecordMember],
	[^meta::__Variable] metaobjects reflecting the individual data
	members (all including the private and protected ones)
	of the [^class], [^struct] or [^union] reflected by [^T].
	>*/
};

template <__Record T>
using get_data_members_m
 = typename get_data_members<T>::type;

// get_public_data_members
template <__Record T>
struct get_public_data_members {
	using type = __ObjectSequence; /*<
	A [^meta::__ObjectSequence] containing [^meta::__RecordMember],
	[^meta::__Variable] metaobjects reflecting only the public data
	members of the [^class], [^struct] or [^union] reflected by [^T].
	>*/
};

template <__Record T>
using get_public_data_members_m
 = typename get_public_data_members<T>::type;
//]

//[reflexpr_header_operations_Class

// get_base_classes
template <__Class T>
struct get_base_classes {
	using type = __ObjectSequence; /*<
	A [^meta::__ObjectSequence] containing [^meta::__Inheritance]
	metaobjects reflecting the individual base class declarations
	of the [^class] or [^struct] reflected by [^T].
	>*/
};

template <__Class T>
using get_base_classes_m
 = typename get_base_classes<T>::type;
//]

//[reflexpr_header_operations_ScopeMember

// get_scope
template <__ScopeMember T>
struct get_scope {
	using type = __Scope; /*<
	A [^meta::__Scope] reflecting the scope of the base-level entity
	reflected by [^T].
	>*/
};

template <__ScopeMember T>
using get_scope_m
 = typename get_scope<T>::type;
//]

//[reflexpr_header_operations_Variable

// get_pointer
template <__Variable T>
struct get_pointer
 : integral_constant<__unspecified /*<
The type of the pointer to the variable reflected by [^T].
>*/, __implementation_defined /*<
If [^T] is also a [^__meta::__RecordMember] and [^__meta_is_static] returns
[^false], i.e. if [^T] is reflecting a non-static class data member, then
this is a class member pointer, otherwise it is a ["plain] pointer to
the reflected variable.
>*/>
{ };

template <__Variable T>
constexpr auto get_pointer_v<T> = get_pointer<T>::value;
//]

//[reflexpr_header_operations_Constant

// get_constant
template <__Constant T>
struct get_constant
 : integral_constant<__unspecified /*<
The type of the constant value reflected by [^T].
>*/, __implementation_defined /*<
The constant base-level value reflected by [^T].
>*/>
{ };

template <__Constant T>
constexpr auto get_constant_v<T> = get_constant<T>::value;
//]

//[reflexpr_header_operations_Inheritance

// get_base_class
template <__Inheritance T>
struct get_base_class {
	using type = __Record; /*<
	A [^meta::__Record] reflecting the base-class in the inheritance
	reflected by [^T].
	>*/
};

template <__Inheritance T>
using get_base_class_m
 = typename get_base_class<T>::type;
//]

//[reflexpr_header_operations_access
// is_private
template <__Object T>
struct is_private;

template <__RecordMember T>
struct is_private<T>
 : integral_constant<bool, __implementation_defined /*<
[^true] if the record member reflected by [^T] has private access,
[^false] otherwise.
>*/
{ };

template <__Inheritance T>
struct is_private<T>
 : integral_constant<bool, __implementation_defined /*<
[^true] if the class inheritance reflected by [^T] is private,
[^false] otherwise.
>*/
{ };

template <__Object T>
constexpr bool is_private_v<T> = is_private<T>::value;


// is_protected
template <__Object T>
struct is_protected;

template <__RecordMember T>
struct is_protected<T>
 : integral_constant<bool, __implementation_defined /*<
[^true] if the record member reflected by [^T] has private access,
[^false] otherwise.
>*/
{ };

template <__Inheritance T>
struct is_protected<T>
 : integral_constant<bool, __implementation_defined /*<
[^true] if the class inheritance reflected by [^T] is protected,
[^false] otherwise.
>*/
{ };

template <__Object T>
constexpr bool is_protected_v<T> = is_protected<T>::value;


// is_public
template <__Object T>
struct is_public;

template <__RecordMember T>
struct is_public<T>
 : integral_constant<bool, __implementation_defined /*<
[^true] if the record member reflected by [^T] has public access,
[^false] otherwise.
>*/
{ };

template <__Inheritance T>
struct is_public<T>
 : integral_constant<bool, __implementation_defined /*<
[^true] if the class inheritance reflected by [^T] is public,
[^false] otherwise.
>*/
{ };

template <__Object T>
constexpr bool is_public_v<T> = is_public<T>::value;

// get_access_specifier
template <__Object T>
struct get_access_specifier;

template <__RecordMember T>
struct get_access_specifier<T> {
	using type = __Specifier; /*<
	A [^meta::__Specifier] reflecting the access specifier of the
	record member reflected by [^T].
	>*/
};

template <__Inheritance T>
struct get_access_specifier<T> {
	using type = __Specifier; /*<
	A [^meta::__Specifier] reflecting the access specifier of the
	class inheritance reflected by [^T].
	>*/
};

template <__Object T>
using get_access_specifier_m
 = typename get_access_specifier<T>::type;
//]


//[reflexpr_header_operations_virtual
// is_virtual
template <__Object T>
struct is_virtual;

template <__Inheritance T>
struct is_virtual<T>
 : integral_constant<bool, __implementation_defined /*<
[^true] if the class inheritance reflected by [^T] is virtual,
[^false] otherwise.
>*/
{ };

template <__Object T>
constexpr bool is_virtual_v<T> = is_virtual<T>::value;
//]


//[reflexpr_header_operations_static
// is_static
template <__Object T>
struct is_static;

template <__Variable T>
struct is_static<T>
 : integral_constant<bool, __implementation_defined /*<
[^true] if the (possibly class member) variable reflected by [^T] is static,
[^false] otherwise.
>*/
{ };

template <__Object T>
constexpr bool is_static_v<T> = is_static<T>::value;
//]

// TODO

//[reflexpr_header_close_meta
} // namespace meta
//]
//[reflexpr_header_close_std
} // namespace std
//]

