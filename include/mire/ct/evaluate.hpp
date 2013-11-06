/**
 * @file mire/ct/evaluate.hpp
 * @brief Implementation of the evaluate meta-function
 *
 *  Copyright 2008-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_EVALUATE_1105240825_HPP
#define MIRE_CT_EVALUATE_1105240825_HPP

#include <mire/ct/range.hpp>
#include <mire/ct/string.hpp>
#include <mire/ct/nil_type.hpp>
#include <mire/ct/int_const.hpp>

namespace mire {
namespace ct {

/// Meta-function evaluates a compile-time string expression
/**
 *  @see basic_string
 *  @see range
 *
 *  @ingroup ct_utils
 */
template <typename X>
struct evaluate
#ifndef MIRROR_DOCUMENTATION_ONLY
 : evaluate<typename X::type>
#endif
{ };

template <typename Char, Char ... C>
struct evaluate<basic_string<Char, C...>>
{
	typedef basic_string<Char, C...> type;
};

template <typename ... P>
struct evaluate<range<P...>>
{
	typedef range<P...> type;
};

template <bool B>
struct evaluate<integral_constant<bool, B>>
 : integral_constant<bool, B>
{ };

template <>
struct evaluate<nil_t>
{
	typedef empty_range type;
};

} // namespace ct
} // namespace mire

#endif //include guard

