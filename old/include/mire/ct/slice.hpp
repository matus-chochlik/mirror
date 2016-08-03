/**
 * @file mire/ct/slice.hpp
 * @brief Implementation of the slice meta-function
 *
 *  Copyright 2008-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_SLICE_1105240825_HPP
#define MIRE_CT_SLICE_1105240825_HPP

#include <mire/ct/default.hpp>
#include <mire/ct/head.hpp>
#include <mire/ct/tail.hpp>

namespace mire {
namespace ct {

#ifndef MIRROR_DOCUMENTATION_ONLY

template <typename Range, typename Start, typename Size>
struct slice
 : tail<
	head<
		Range,
		size_constant<Start::value + Size::value>
	>,
	Size
> { };

template <typename Range, size_t Start, size_t Size>
struct slice_c
 : slice<
	Range,
	size_constant<Start>,
	size_constant<Size>
> { };

#endif

} // namespace ct
} // namespace mire

#endif //include guard

