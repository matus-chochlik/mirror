/**
 * @file mire/ct/char_type.hpp
 * @brief Implementation of the char_type meta-function
 *
 *  Copyright 2008-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_CHAR_TYPE_1105240825_HPP
#define MIRE_CT_CHAR_TYPE_1105240825_HPP

#include <mire/ct/default.hpp>
#include <mire/ct/identity.hpp>

namespace mire {
namespace ct {

template <typename Char, Char ... C>
struct char_type<basic_string<Char, C...>>
 : identity<Char>
{ };

} // namespace ct
} // namespace mire

#endif //include guard

