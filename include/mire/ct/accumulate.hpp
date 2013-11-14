/**
 * @file mire/ct/accumulate.hpp
 * @brief Implementation of the accumulate function.
 *
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_ACCUMULATE_1011291729_HPP
#define MIRE_CT_ACCUMULATE_1011291729_HPP

#include <mire/ct/evaluate.hpp>
#include <mire/ct/iter_info.hpp>
#include <mire/ct/int_const.hpp>
#include <mire/ct/stddef.hpp>

namespace mire {
namespace ct {
namespace aux {

template <
	typename StatusType,
	typename Functor,
	typename IsFirst,
	typename IsLast,
	typename Position
>
StatusType accumulate(
	StatusType status,
	Functor& func,
	range<>,
	IsFirst,
	IsLast,
	Position
)
{
	return status;
}

template <
	typename StatusType,
	typename T,
	typename Functor,
	typename IsFirst,
	typename IsLast,
	typename Position
>
StatusType accumulate(
	StatusType status,
	Functor& func,
	range<T>,
	IsFirst,
	IsLast,
	Position
)
{
	return func(
		status,
		iteration_info<
			T,
			IsFirst,
			true_type,
			Position
		>()
	);
}

template <
	typename StatusType,
	typename T1,
	typename T2,
	typename ... P,
	typename Functor,
	typename IsFirst,
	typename IsLast,
	size_t Position
>
StatusType accumulate(
	StatusType status,
	Functor& func,
	range<T1, T2, P...>,
	IsFirst,
	IsLast,
	integral_constant<size_t, Position>
)
{
	return accumulate(
		func(
			status,
			iteration_info<
				T1,
				IsFirst,
				IsLast,
				integral_constant<size_t, Position>
			>()
		),
		func,
		range<T2, P...>(),
		false_type(),
		IsLast(),
		integral_constant<size_t, Position+1>()
	);
}

} // namespace aux

/// Accumulates the results of a binary functor on all elements of a range
/** This function calls the binary @a Functor passed as argument
 *  on instances of iteration_info (which provides additional
 *  information about the progress of the iteration)
 *  for every type in the @a Range, together with the current accumulation status.
 *
 *  For example, having a binary functor defined as follows:
 *  @code
 *  struct functor
 *  {
 *    template <typename IterationInfo>
 *    size_t operator()(size_t status, IterationInfo) const
 *    {
 *      return status + sizeof(typename IterationInfo::type);
 *    }
 *  };
 *  @endcode
 *
 *  and a range of several types:
 *  @code
 *  typedef range<bool, int, double, char, float, unsigned> some_range;
 *  @endcode
 *
 *  calling:
 *  @code
 *  size_t x = accumulate<some_range>(functor, 0);
 *  @endcode
 *
 *  is equivalent to:
 *  @code
 *  size_t x = functor(
 *    functor(
 *      functor(
 *        functor(
 *          functor(
 *            functor(0, IterInfo_bool),
 *            IterInfo_int()
 *          ),
 *          IterInfo_double()
 *        ),
 *        IterInfo_char()
 *      ),
 *      IterInfo_float()
 *    ),
 *    IterInfo_unsigned()
 *  );
 *  @encode
 *
 *  Where the @c IterInfo_xyz types as models of the IterationInfo concept.
 *
 *  The IterationInfo type defines the following member typenames
 *  - type : a type from the @a Range
 *  - is_first : true_type or false_type indicating the first step of iteration
 *  - is_last : true_type or false_type indicating the last step of iteration
 *  - position : integral constant indication the position of the current element
 *
 *  @tparam Range the range to be traversed
 *  @tparam StatusType the type of the accumulation status variable
 *  @tparam Functor the type of the functor to be called on each element
 *  @param func the functor to be called on each element
 *  @param initial the initial value passed to the first invocation of func
 *
 *  @see fold
 *  @see for_each
 *
 *  @ingroup ct_utilities
 */
template <typename Range, typename Functor, typename StatusType>
StatusType accumulate(Functor func, StatusType initial)
{
	return aux::accumulate(
		initial,
		func,
		typename evaluate<Range>::type(),
		true_type(),
		false_type(),
		integral_constant<size_t, 0>()
	);
}

} // namespace ct
} // namespace mire

#endif //include guard

