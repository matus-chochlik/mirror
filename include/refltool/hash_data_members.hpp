/**
 * @file refltool/hash_data_members.hpp
 * @brief Implementation of the hash_data_members operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef REFLTOOL_HASH_DATA_MEMBERS_1105240825_HPP
#define REFLTOOL_HASH_DATA_MEMBERS_1105240825_HPP

#include <puddle/reflection.hpp>
#include <puddle/sequence_ops.hpp>
#include <puddle/meta_variable_ops.hpp>
#include <puddle/meta_record_ops.hpp>
#include <reflbase/type_traits_fixes.hpp>
#include <functional>
#include <climits>

namespace refltool {

template <typename T>
static constexpr inline
auto hash_data_members(const T& v)
{
	using namespace puddle;

	std::size_t i = 0;

	auto do_hash = [&i](const auto& u)
	{
		using U = std::remove_const_t<
			std::remove_volatile_t<
				std::remove_reference_t<decltype(u)>
			>
		>;
		auto rot = [](const std::size_t n, const std::size_t c)
		{
			const std::size_t m = (CHAR_BIT*sizeof(n)-1);
			return (n << c) | (n >> (-c & m));
		};

		std::size_t hu = std::hash<U>()(u);
		i = rot(++i, hu&0xFF);
		return std::hash<std::size_t>()(hu+i);
	};

	return apply_on(
		get_data_members(PUDDLED(T)),
		[&v, &do_hash](auto ... mdm)
		{
			return (... ^ do_hash(dereference(mdm, v)));
		}
	);
}

} // namespace refltool

#endif //include guard

