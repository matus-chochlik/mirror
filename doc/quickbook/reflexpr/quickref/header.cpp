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
template <Object T> concept bool ObjectSequence
 =  __implementation_defined;
//]

//[reflexpr_header_concepts_Reversible
template <Object T> concept bool Reversible
 =  __implementation_defined;
//]

//[reflexpr_header_concepts_Named
template <Object T> concept bool Named
 =  __implementation_defined;
//]

//[reflexpr_header_concepts_Alias
template <Object T> concept bool Alias
 =  Named<T>
 && __implementation_defined;
//]

//[reflexpr_header_concepts_Typed
template <Object T> concept bool Typed
 =  __implementation_defined;
//]

//[reflexpr_header_concepts_Scope
template <Object T> concept bool Scope
 =  __implementation_defined;
//]

//[reflexpr_header_concepts_Namespace
template <Object T> concept bool Namespace
 =  __Named<T>
 && __Scope<T>
 && __ScopeMember<T>
 && __implementation_defined;
//]

//[reflexpr_header_concepts_GlobalScope
template <Object T> concept bool GlobalScope
 =  __Namespace<T>
 && __implementation_defined;
//]

//[reflexpr_header_concepts_Type
template <Object T> concept bool Type
 =  __Named<T>
 && __Reversible<T>
 && __implementation_defined;
//]

//[reflexpr_header_concepts_TagType
template <Object T> concept bool TagType
 =  __Type<T>
 && __Scope<T>
 && __ScopeMember<T>
 && __implementation_defined;
//]

//[reflexpr_header_concepts_Record
template <Object T> concept bool Record
 =  __TagType<T>
 && __implementation_defined;
//]

//[reflexpr_header_concepts_Enum
template <Object T> concept bool Enum
 =  __TagType<T>
 && __implementation_defined;
//]

//[reflexpr_header_concepts_Class
template <Object T> concept bool Class
 =  __Record<T>
 && __implementation_defined;
//]

//[reflexpr_header_concepts_ScopeMember
template <Object T> concept bool ScopeMember
 =  __implementation_defined;
//]

//[reflexpr_header_concepts_EnumMember
template <Object T> concept bool EnumMember
 =  __ScopeMember<T>
 && __implementation_defined;
//]

//[reflexpr_header_concepts_RecordMember
template <Object T> concept bool RecordMember
 =  __ScopeMember<T>
 && __implementation_defined;
//]

//[reflexpr_header_concepts_Variable
template <Object T> concept bool Variable
 =  __Named<T>
 && __Typed<T>
 && __ScopeMember<T>
 && __implementation_defined;
//]

//[reflexpr_header_concepts_Constant
template <Object T> concept bool Constant
 =  __Typed<T>
 && __implementation_defined;
//]

//[reflexpr_header_concepts_Specifier
template <Object T> concept bool Specifier
 =  __Named<T>
 && __implementation_defined;
//]

//[reflexpr_header_concepts_Inheritance
template <Object T> concept bool Inheritance
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

// TODO

//[reflexpr_header_close_meta
} // namespace meta
//]
//[reflexpr_header_close_std
} // namespace std
//]

