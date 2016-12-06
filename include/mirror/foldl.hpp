/**
 * @file mirror/foldl.hpp
 * @brief Implementation of the `foldl` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_FOLDL_1105240825_HPP
#define MIRROR_FOLDL_1105240825_HPP

#include "int_const.hpp"
#include "identity.hpp"
#include "string.hpp"
#include "range.hpp"
#include "none.hpp"

namespace mirror {
namespace _aux {

template <template <class, class> class Reduce, typename Rng, typename Init>
struct op_foldl;

template <template <class, class> class Reduce, typename Init>
struct op_foldl<Reduce, none, Init>
 : identity<Init>
{ };

template <template <class, class> class Reduce, typename Init>
struct op_foldl<Reduce, empty_range, Init>
 : identity<Init>
{ };

template <
	template <class, class> class Reduce,
	typename H,
	typename ... T,
	typename Init
> struct op_foldl<Reduce, range<H, T...>, Init>
 : op_foldl<Reduce, range<T...>, Reduce<Init, H>>
{ };

template <
	template <class, class> class Reduce,
	typename H1,
	typename H2,
	typename ... T
> struct op_foldl<Reduce, range<H1, H2, T...>, none>
 : op_foldl<Reduce, range<T...>, Reduce<H1, H2>>
{ };

template <template <class, class> class Reduce, typename Init>
struct op_foldl<Reduce, empty_string, Init>
 : identity<Init>
{ };

template <
	template <class, class> class Reduce,
	typename Char,
	Char H,
	Char ... T,
	typename Init
> struct op_foldl<Reduce, basic_string<Char, H, T...>, Init>
 : op_foldl<
	Reduce,
	basic_string<Char, T...>,
	Reduce<Init, int_const<Char, H>>
> { };

template <
	template <class, class> class Reduce,
	typename Char,
	Char H1,
	Char H2,
	Char ... T
> struct op_foldl<Reduce, basic_string<Char, H1, H2, T...>, none>
 : op_foldl<
	Reduce,
	basic_string<Char, T...>,
	Reduce<int_const<Char, H1>, int_const<Char, H2>>
> { };

} // namespace _aux

template <
	template <class, class> class Reduce,
	typename Range,
	typename Init = none
> using foldl = eval<_aux::op_foldl<Reduce, Range, Init>>;

} // namespace mirror

#endif //include guard

