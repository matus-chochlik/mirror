/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[lagoon_fingerprint_1
using fingerprint = __unspecified;

fingerprint get_fingerprint(__mirror_none);

template <__std_meta_Object MO>
fingerprint get_fingerprint(__mirror_metaobject<MO>);
//]

