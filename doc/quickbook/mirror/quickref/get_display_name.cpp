/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[mirror_op_get_display_name
template <__std_meta_Named N>
using get_display_name<__metaobject<N>> = __string<__unspecified /*<
The characters of the base name of the [^__std_meta_Named] metaobject
as returned by [^__std_meta_get_display_name].
>*/>;

template <__std_meta_Object O>
using get_display_name<__metaobject<O>> = __empty_string /*<
For non-named metaobjects an empty string is returned.
>*/;

using get_display_name<__none> = __empty_string;
//]

