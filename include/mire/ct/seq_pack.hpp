/**
 * @file mire/ct/seq_pack.hpp
 * @brief Meta function calling the apply metafunction of a meta-function
 * class with a range of integer params of 0,1, ..., N-1.
 *
 *  Copyright 2008-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_SEQ_PACK_1011291729_HPP
#define MIRE_CT_SEQ_PACK_1011291729_HPP

#include <mire/ct/default.hpp>
#include <mire/ct/int_sequence.hpp>

namespace mire {
namespace ct {
namespace aux {

template <typename Sequence>
struct seq_pack_applier;

//  Helper which calls the apply meta-function and "returns" its type
/*  This template takes the pack of integral constant types with
 *  values forming a sequence 0, 1, 2, ..., N-1 and defines a do_apply
 *  template that takes a meta-function class.
 */
template <size_t ... I>
struct seq_pack_applier<index_sequence<I...>>
{
	template <class MetaFunctionClass>
	struct do_apply
	 : MetaFunctionClass::template apply<I...>
	{ };
};

} // namespace aux

#ifndef MIRROR_DOCUMENTATION_ONLY
template <typename MetaFunctionClass, size_t Count>
struct apply_on_seq_pack_c
 : aux::seq_pack_applier<
	typename make_index_sequence<Count>::type
>::template do_apply<MetaFunctionClass>
{ };

#endif

} // namespace ct
} // namespace mire

#endif //include guard

