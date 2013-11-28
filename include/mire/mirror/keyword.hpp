/**
 *  @file mire/mirror/keyword.hpp
 *  @brief Implementation of the keyword metafunction.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2006-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_MIRROR_KEYWORD_1310291537_HPP
#define MIRE_MIRROR_KEYWORD_1310291537_HPP

#include <mire/mirror/default.hpp>
#include <mire/ct/to_string.hpp>

namespace mire {
namespace mirror {

template <typename T>
struct keyword<spec<T>>
 : ct::to_string<typename T::_kw>
{ };

} // namespace mirror
} // namespace mire

#endif // include guard
