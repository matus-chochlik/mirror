/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[mirror_op_is_enum
template <__std_meta_TagType T>
using is_enum<__metaobject<T>>
 = __bool_<__std_meta_is_enum_v<T>>;

template <__std_meta_Object O>
using is_enum<__metaobject<O>> = __false_ /*<
For metaobjects not conforming to the [^__std_meta_TagType] concept [^__false_]
is returned.
>*/;

using is_enum<__none> = __false_;
//]

