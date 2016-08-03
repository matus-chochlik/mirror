/**
 * @file mire/ct/transform.hpp
 * @brief Implementation of the transform function
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_TRANSFORM_1105240825_HPP
#define MIRE_CT_TRANSFORM_1105240825_HPP

#include <mire/ct/default.hpp>
#include <mire/ct/lambda.hpp>

namespace mire {
namespace ct {

template <typename ... P, class UnaryMetaFnClass>
struct transform<range<P...>, UnaryMetaFnClass>
 : range<typename apply<UnaryMetaFnClass, P>::type ...>
{ };

template <typename Char, Char ... C, class UnaryMetaFnClass>
struct transform_c<basic_string<Char, C...>, UnaryMetaFnClass>
 : basic_string<Char, apply_c<UnaryMetaFnClass, Char, C>::value...>
{ };

} // namespace ct
} // namespace mire

#endif //include guard

