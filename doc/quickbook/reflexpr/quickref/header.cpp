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
[^true] if [^T] is a __Metaobject [^false] otherwise.
>*/>
{ };
//]
//[reflexpr_header_open_meta
namespace meta {
//]

// TODO

//[reflexpr_header_close_meta
} // namespace meta
//]
//[reflexpr_header_close_std
} // namespace std
//]

