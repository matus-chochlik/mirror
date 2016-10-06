/**
 * @file refltool/tie_data_members.hpp
 * @brief Implementation of the tie_data_members operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef REFLTOOL_TIE_DATA_MEMBERS_1105240825_HPP
#define REFLTOOL_TIE_DATA_MEMBERS_1105240825_HPP

#include <puddle/reflection.hpp>
#include <puddle/sequence_ops.hpp>
#include <puddle/meta_variable_ops.hpp>
#include <puddle/meta_record_ops.hpp>
#include <tuple>

namespace refltool {

template <typename T>
static constexpr inline
auto tie_data_members(T& v)
{
	using namespace puddle;

	return apply_on(
		get_data_members(PUDDLED(T)),
		[&v](auto ... mdm)
		{
			return std::tie(dereference(mdm, v)...);
		}
	);
}

template <typename T>
static constexpr inline
auto tie_public_data_members(T& v)
{
	using namespace puddle;

	return apply_on(
		get_public_data_members(PUDDLED(T)),
		[&v](auto ... mdm)
		{
			return std::tie(dereference(mdm, v)...);
		}
	);
}

} // namespace refltool

#endif //include guard

