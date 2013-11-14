/**
 * @file mire/ct/for_each.hpp
 * @brief Implementation of the for_each function.
 *
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_FOR_EACH_1011291729_HPP
#define MIRE_CT_FOR_EACH_1011291729_HPP

#include <mire/ct/evaluate.hpp>
#include <mire/ct/iter_info.hpp>
#include <mire/ct/int_const.hpp>
#include <mire/ct/stddef.hpp>

namespace mire {
namespace ct {
namespace aux {

template <
	typename Functor,
	typename IsFirst,
	typename IsLast,
	typename Position
>
void for_each(
	Functor& func,
	range<>,
	IsFirst,
	IsLast,
	Position
)
{ }

template <
	typename T,
	typename Functor,
	typename IsFirst,
	typename IsLast,
	typename Position
>
void for_each(
	Functor& func,
	range<T>,
	IsFirst,
	IsLast,
	Position
)
{
	func(iteration_info<
		T,
		IsFirst,
		true_type,
		Position
	>());
}

template <
	typename T1,
	typename T2,
	typename ... P,
	typename Functor,
	typename IsFirst,
	typename IsLast,
	size_t Position
>
void for_each(
	Functor& func,
	range<T1, T2, P...>,
	IsFirst,
	IsLast,
	integral_constant<size_t, Position>
)
{
	func(iteration_info<
		T1,
		IsFirst,
		IsLast,
		integral_constant<size_t, Position>
	>());
	for_each(
		func,
		range<T2, P...>(),
		false_type(),
		IsLast(),
		integral_constant<size_t, Position+1>()
	);
}

} // namespace aux

/// Calls the unary functor on all elements of the range with iteration info
/** This function calls the @a Functor passed as argument
 *  on instances of iteration_info (which provides additional
 *  information about the progress of the iteration)
 *  for every type in the @a Range.
 *
 *  The iteration_info type defines the following member typenames
 *  - type : a type from the @a Range
 *  - is_first : true_type or false_type indicating the first step of iteration
 *  - is_last : true_type or false_type indicating the last step of iteration
 *  - position : integral constant indication the position of the current element
 *
 *  @tparam Range the range to be traversed
 *  @tparam Functor the type of the functor to be called on each element
 *  @param func the functor to be called on each element
 *
 *  @see fold
 *
 *  @ingroup ct_utilities
 */
template <typename Range, typename Functor>
Functor for_each(Functor func)
{
	aux::for_each(
		func,
		typename evaluate<Range>::type(),
		true_type(),
		false_type(),
		integral_constant<size_t, 0>()
	);
	return func;
}

} // namespace ct
} // namespace mire

#endif //include guard

