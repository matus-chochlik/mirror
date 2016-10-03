/**
 * @file mire/ct/iter_info.hpp
 * @brief Definition of the helper iteration_info structure.
 *
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_ITER_INFO_1011291729_HPP
#define MIRE_CT_ITER_INFO_1011291729_HPP

#include <mire/ct/stddef.hpp>

namespace mire {
namespace ct {
namespace aux {

template <
	typename T,
	typename IsFirst,
	typename IsLast,
	typename Position
>
struct iteration_info
{
	typedef T type;

	typedef IsFirst is_first;
	static constexpr bool first(void)
	{
		return is_first::value;
	}

	typedef IsLast is_last;
	static constexpr bool last(void)
	{
		return is_last::value;
	}

	typedef Position position;
	static constexpr size_t pos(void)
	{
		return position::value;
	}
};

} // namespace aux
} // namespace ct
} // namespace mire

#endif //include guard

