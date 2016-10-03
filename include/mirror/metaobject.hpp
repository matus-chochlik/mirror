/**
 * @file mirror/metaobject.hpp
 * @brief Metaobject type wrappers
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_METAOBJECTS_1105240825_HPP
#define MIRROR_METAOBJECTS_1105240825_HPP

#include <reflbase/reflbase.hpp>

namespace mirror {

template <typename MO>
struct metaobject
{
	static_assert(
		reflbase::is_metaobject_v<MO>,
		"Template argument must be a meta-object type!"
	);
	using type = metaobject;
};

template <typename MOS>
struct metaobject_sequence
{
	static_assert(
		reflbase::is_metaobject_v<MOS> &&
		reflbase::ObjectSequence<MOS>,
		"Template argument must be a meta-object-sequence type!"
	);
	using type = metaobject_sequence;
};

} // namespace mirror

#endif //include guard

