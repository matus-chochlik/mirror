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
 =  is_metaobject_v<T>;
//]

//[reflexpr_header_concepts_ObjectSequence
template <Object T> concept bool ObjectSequence
 =  __implementation_defined;
//]

//[reflexpr_header_concepts
template <Object T> concept bool Reversible
 =  __implementation_defined;

template <Object T> concept bool Named
 =  __implementation_defined;

template <Object T> concept bool Alias
 =  Named<T>
 && __implementation_defined;

template <Object T> concept bool Typed
 =  __implementation_defined;

template <Object T> concept bool Scope
 =  __implementation_defined;

template <Object T> concept bool Namespace
 =  Named<T>
 && Scoped<T>
 && ScopeMember<T>
 && __implementation_defined;

template <Object T> concept bool GlobalScope
 =  Namespace<T>
 && __implementation_defined;

template <Object T> concept bool Type
 =  Named<T>
 && Reversible<T>
 && __implementation_defined;

template <Object T> concept bool TagType
 =  Type<T>
 && Scope<T>
 && ScopeMember<T>
 && __implementation_defined;

template <Object T> concept bool Record
 =  TagType<T>
 && __implementation_defined;

template <Object T> concept bool Enum
 =  TagType<T>
 && __implementation_defined;

template <Object T> concept bool Class
 =  Record<T>
 && __implementation_defined;

template <Object T> concept bool ScopeMember
 =  __implementation_defined;

template <Object T> concept bool EnumMember
 =  ScopeMember<T>
 && __implementation_defined;

template <Object T> concept bool RecordMember
 =  ScopeMember<T>
 && __implementation_defined;

template <Object T> concept bool Variable
 =  Named<T>
 && Typed<T>
 && ScopeMember<T>
 && __implementation_defined;

template <Object T> concept bool Constant
 =  Typed<T>
 && __implementation_defined;

template <Object T> concept bool Specifier
 =  Named<T>
 && __implementation_defined;

template <Object T> concept bool Inheritance
 =  __implementation_defined;
//]

// TODO

//[reflexpr_header_close_meta
} // namespace meta
//]
//[reflexpr_header_close_std
} // namespace std
//]

