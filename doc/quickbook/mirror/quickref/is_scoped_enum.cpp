/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[mirror_op_is_scoped_enum
template <__std_meta_Enum E>
using is_scoped_enum<__metaobject<E>>
 = __bool_<__std_meta_is_scoped_enum_v<E>>;

template <__std_meta_Object O>
using is_scoped_enum<__metaobject<O>> = __false_ /*<
For metaobjects not conforming to the [^__std_meta_Enum] concept [^__false_]
is returned.
>*/;

using is_scoped_enum<__none> = __false_;
//]

