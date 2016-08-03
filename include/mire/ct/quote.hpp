/**
 * @file mire/ct/quote.hpp
 * @brief Implementation of the quote meta-function
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_QUOTE_1105240825_HPP
#define MIRE_CT_QUOTE_1105240825_HPP

namespace mire {
namespace ct {

/// Converts a Metafunction into a MetafunctionClass
/**
 *  @ingroup ct_utils
 */
template <template <typename ...> class Metafunction>
struct quote
{
	/// The nested apply template
	template <typename ... P>
	struct apply
	 : Metafunction<P...>
	{ };
};

template <template <typename Char, Char...> class Metafunction>
struct quote_c
{
	template <typename Char, Char ... C>
	struct apply_c
	 : Metafunction<Char, C...>
	{ };
};

} // namespace ct
} // namespace mire

#endif //include guard

