/**
 * @file mirror/dereference.hpp
 * @brief Implementation of the `dereference` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_DEREFERENCE_1105240825_HPP
#define MIRROR_DEREFERENCE_1105240825_HPP

#include "metaobject.hpp"
#include "get_pointer.hpp"
#include "is_static.hpp"
#include "traits.hpp"
#include "value.hpp"
#include "and.hpp"

namespace mirror {
namespace _aux {

template <typename MO, typename IsRecMem, typename IsStatic>
struct op_deref;

template <typename MO>
struct op_deref<MO, true_, false_>
{
	template <typename T>
	static auto& apply(T& parent)
	{ return parent.*value<get_pointer<MO>>; }
};

template <typename MO>
struct op_deref<MO, true_, true_>
{
	static auto& apply(void)
	{ return *value<get_pointer<MO>>; }

	template <typename T>
	static auto& apply(T&)
	{ return *value<get_pointer<MO>>; }
};

template <typename MO, typename Unused>
struct op_deref<MO, false_, Unused>
{
	static auto& apply(void)
	{ return *value<get_pointer<MO>>; }
};

} // namespace _aux

template <typename X>
struct dereference;

template <typename MO>
struct dereference<metaobject<MO>>
 : _aux::op_deref<
 	metaobject<MO>, 
	reflects_record_member<metaobject<MO>>,
	and_<reflects_record_member<metaobject<MO>>, is_static<metaobject<MO>>>
> { };

} // namespace mirror

#endif //include guard

