/**
 * @file mire/ct/arg.hpp
 * @brief Definition of the arg template.
 *
 *  Copyright 2008-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_ARG_1011291729_HPP
#define MIRE_CT_ARG_1011291729_HPP

#include <mire/ct/range.hpp>
#include <mire/ct/string.hpp>
#include <mire/ct/at.hpp>

namespace mire {
namespace ct {

/// Meta-function class returning the @a Number -th of its arguments
/** This template is used in two different ways. First it wraps a meta-function
 *  returning the N-th of its arguments. Second it is used as a placeholder
 *  for the N-th argument in placeholder lambda expressions.
 *
 *  @ingroup ct_utils
 */
template <size_t Number>
struct arg
{
	typedef arg type;

	template <typename ... Params>
	struct apply
	 : at_c<range<Params...>, Number>
	{ };
};

template <size_t Number>
struct arg_c
{
	typedef arg_c type;

	template <typename Char, Char ... Params>
	struct apply_c
	 : at_c<basic_string<Char, Params...>, Number>
	{ };
};

} // namespace ct
} // namespace mire

#endif //include guard

