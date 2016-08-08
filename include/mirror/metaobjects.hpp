/**
 * @file mirror/metaobjects.hpp
 * @brief Metaobject type wrappers
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_METAOBJECTS_1105240825_HPP
#define MIRROR_METAOBJECTS_1105240825_HPP

#include <reflexpr>
#include "int_const.hpp"

namespace mirror {

template <typename MO>
struct meta_object
{
	static_assert(
		std::is_metaobject_v<MO>,
		"Template argument to `meta_object` must be a metaobject type!"
	);
};

namespace _aux {

template <typename X>
struct is_meta_object
 : false_
{ };

template <typename MO>
struct is_meta_object<meta_object<MO>>
 : true_
{ };

} // namespace _aux

} // namespace mirror

#endif //include guard

