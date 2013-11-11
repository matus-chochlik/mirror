/**
 * @file mire/ct/to_string.hpp
 * @brief Implementation of the to_string function
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_TO_STRING_1105240825_HPP
#define MIRE_CT_TO_STRING_1105240825_HPP

#include <mire/ct/string.hpp>
#include <mire/ct/default.hpp>
#include <mire/ct/seq_pack.hpp>

namespace mire {
namespace ct {
namespace aux {

template <typename Char, typename SLC>
struct to_basic_string_fn
{
	template <size_t ... I>
	struct apply
	 : basic_string<Char, SLC::c_str[I]...>
	{ };
};

} // namespace aux

template <typename Char, typename StringLiteralClass>
struct to_basic_string
 : apply_on_seq_pack_c<
	aux::to_basic_string_fn<Char, StringLiteralClass>,
	StringLiteralClass::size
>
{ };

template <typename StringLiteralClass>
struct to_string
 : to_basic_string<char, StringLiteralClass>
{ };

} // namespace ct
} // namespace mire

#endif //include guard

