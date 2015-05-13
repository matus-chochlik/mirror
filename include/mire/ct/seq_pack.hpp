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

namespace mire {
namespace ct {
namespace aux {

//  Helper which calls the apply meta-function and "returns" its type
/*  This template takes the pack of integral constant types with
 *  values forming a sequence 0, 1, 2, ..., N-1 and defines a do_apply
 *  template that takes a meta-function class.
 */
template <size_t N, class ... I>
struct seq_pack_applier
{
	template <class MetaFunctionClass>
	struct do_apply
	 : MetaFunctionClass::template apply<(N - I::value - 1)...>
	{ };
};

//  Forward declaration the seq_pack helper class
/*  This template class is used for expanding
 *  the parameter pack containing the sequence
 *  of integral constant types from 0 to the
 *  value specified as the first template parameter.
 *  When the parameter pack is fully expanded
 *  the seq_packr_applier template is used to instantiate
 *  the apply meta-function of the custom meta function
 *  class.
 */
template <class N, class ...I>
struct seq_pack_helper;

/*  Specialization of the seq_pack_helper for single
 *  element packs.
 */
template <>
struct seq_pack_helper<
	size_constant<1u>,
	size_constant<0u>
> : seq_pack_applier<1u, size_constant<0u>>
{ };

/*  Specialization of the seq_pack_helper with fully
 *  assembled integral constant type pack. This
 *  version derives from the seq_pack_applier providing
 *  the do_apply meta-function
 */
template <size_t N, class ...I>
struct seq_pack_helper<
	size_constant<N>,
	size_constant<N>,
	I...
> : seq_pack_applier<N, I...>
{ };

/*  This specialization of the seq_pack_helper which
 *  adds one item to the integral constant type pack
 *  which is not yet fully assembled.
 */
template <size_t N, size_t I_plus_1, class ... I>
struct seq_pack_helper<
	size_constant<N>,
	size_constant<I_plus_1>,
	I...
> : seq_pack_helper<
	size_constant<N>,
	size_constant<I_plus_1 + 1>,
	size_constant<I_plus_1>,
	I...
>
{ };

} // namespace aux

#ifndef MIRROR_DOCUMENTATION_ONLY
template <typename MetaFunctionClass, size_t Count>
struct apply_on_seq_pack_c
 : aux::seq_pack_helper<
	size_constant<Count>,
	size_constant<0u>
>::template do_apply<MetaFunctionClass>
{ };

template <typename MetaFunctionClass>
struct apply_on_seq_pack_c<MetaFunctionClass, 0>
 : MetaFunctionClass::template apply< >
{ };

template <typename MetaFunctionClass>
struct apply_on_seq_pack_c<MetaFunctionClass, 1>
 : MetaFunctionClass::template apply<0>
{ };

template <typename MetaFunctionClass>
struct apply_on_seq_pack_c<MetaFunctionClass, 2>
 : MetaFunctionClass::template apply<0,1>
{ };

template <typename MetaFunctionClass>
struct apply_on_seq_pack_c<MetaFunctionClass, 3>
 : MetaFunctionClass::template apply<0,1,2>
{ };

template <typename MetaFunctionClass>
struct apply_on_seq_pack_c<MetaFunctionClass, 4>
 : MetaFunctionClass::template apply<0,1,2,3>
{ };

template <typename MetaFunctionClass>
struct apply_on_seq_pack_c<MetaFunctionClass, 5>
 : MetaFunctionClass::template apply<0,1,2,3,4>
{ };

template <typename MetaFunctionClass>
struct apply_on_seq_pack_c<MetaFunctionClass, 6>
 : MetaFunctionClass::template apply<0,1,2,3,4,5>
{ };

template <typename MetaFunctionClass>
struct apply_on_seq_pack_c<MetaFunctionClass, 7>
 : MetaFunctionClass::template apply<0,1,2,3,4,5,6>
{ };

template <typename MetaFunctionClass>
struct apply_on_seq_pack_c<MetaFunctionClass, 8>
 : MetaFunctionClass::template apply<0,1,2,3,4,5,6,7>
{ };

template <typename MetaFunctionClass>
struct apply_on_seq_pack_c<MetaFunctionClass, 9>
 : MetaFunctionClass::template apply<0,1,2,3,4,5,6,7,8>
{ };

template <typename MetaFunctionClass>
struct apply_on_seq_pack_c<MetaFunctionClass, 10>
 : MetaFunctionClass::template apply<0,1,2,3,4,5,6,7,8,9>
{ };

template <typename MetaFunctionClass>
struct apply_on_seq_pack_c<MetaFunctionClass, 11>
 : MetaFunctionClass::template apply<0,1,2,3,4,5,6,7,8,9,10>
{ };

template <typename MetaFunctionClass>
struct apply_on_seq_pack_c<MetaFunctionClass, 12>
 : MetaFunctionClass::template apply<0,1,2,3,4,5,6,7,8,9,10,11>
{ };

template <typename MetaFunctionClass>
struct apply_on_seq_pack_c<MetaFunctionClass, 13>
 : MetaFunctionClass::template apply<0,1,2,3,4,5,6,7,8,9,10,11,12>
{ };

template <typename MetaFunctionClass>
struct apply_on_seq_pack_c<MetaFunctionClass, 14>
 : MetaFunctionClass::template apply<0,1,2,3,4,5,6,7,8,9,10,11,12,13>
{ };

#endif

} // namespace ct
} // namespace mire

#endif //include guard

