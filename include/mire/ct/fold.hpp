/**
 * @file mire/ct/fold.hpp
 * @brief Definition of the fold template.
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_FOLD_1011291729_HPP
#define MIRE_CT_FOLD_1011291729_HPP

#include <mire/ct/default.hpp>
#include <mire/ct/lambda.hpp>

namespace mire {
namespace ct {

template <typename Status, class ForwardOp>
struct fold<range<>, Status, ForwardOp>
{
	typedef Status type;
};

template <
	typename T,
	typename Status,
	class ForwardOp
> struct fold<range<T>, Status, ForwardOp>
 : apply<ForwardOp, Status, T>
{ };

template <
	typename T,
	typename ... P,
	typename Status,
	class ForwardOp
> struct fold<range<T, P...>, Status, ForwardOp>
 : fold<
	range<P...>,
	typename apply<
		ForwardOp,
		Status,
		T
	>::type,
	ForwardOp
>
{ };

} // namespace ct
} // namespace mire

#endif //include guard

