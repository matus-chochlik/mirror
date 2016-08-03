/**
 * @file mire/ct/get.hpp
 * @brief Implementation of the get meta-function
 *
 *  Copyright 2008-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_GET_1105240825_HPP
#define MIRE_CT_GET_1105240825_HPP

#include <mire/ct/default.hpp>
#include <mire/ct/identity.hpp>

namespace mire {
namespace ct {

#ifndef MIRROR_DOCUMENTATION_ONLY

template <typename T>
struct get<optional<T>>
 : identity<T>
{ };

#endif

} // namespace ct
} // namespace mire

#endif //include guard

