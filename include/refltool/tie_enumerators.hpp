/**
 * @file refltool/tie_enumerators.hpp
 * @brief Implementation of the tie_enumerators operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef REFLTOOL_TIE_ENUMERATORS_1105240825_HPP
#define REFLTOOL_TIE_ENUMERATORS_1105240825_HPP

#include <puddle/reflection.hpp>
#include <puddle/sequence_ops.hpp>
#include <puddle/meta_constant_ops.hpp>
#include <puddle/meta_enum_ops.hpp>
#include <array>

namespace refltool {

template <typename T>
static constexpr inline
auto tie_enumerators(void)
{
	using namespace puddle;

	return apply_on(
		get_enumerators(PUDDLED(T)),
		[](auto ... mev)
		{
			return std::array<T, sizeof...(mev)>{{
				get_constant(mev)...
			}};
		}
	);
}

} // namespace refltool

#endif //include guard

