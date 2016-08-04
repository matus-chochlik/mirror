/**
 * @file mirror/metaobject.hpp
 * @brief Metaobject type wrapper
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_METAOBJECT_1105240825_HPP
#define MIRROR_METAOBJECT_1105240825_HPP

#include <reflexpr>

namespace mirror {

template <typename MO>
struct metaobject
{
	static_assert(
		std::is_metaobject_v<MO>,
		"Template argument to `metaobject` must be a metaobject type"
	);
};

} // namespace mirror

#endif //include guard

