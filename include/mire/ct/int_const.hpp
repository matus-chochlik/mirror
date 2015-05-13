/**
 * @file mire/ct/int_const.hpp
 * @brief Integral constant types
 *
 *  Copyright 2008-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_INT_CONST_1105240825_HPP
#define MIRE_CT_INT_CONST_1105240825_HPP

#include <type_traits>

namespace mire {
namespace ct {

using ::std::integral_constant;
using ::std::true_type;
using ::std::false_type;
using ::std::is_same;

template <bool B>
using boolean_constant = integral_constant<bool, B>;

template <size_t S>
using size_constant = integral_constant<size_t, S>;

} // namespace ct
} // namespace mire

#endif //include guard

