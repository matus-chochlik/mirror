/**
 *  @file mire/mirror/source_file.hpp
 *  @brief Implementation of the source_file metafunction.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2008-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_MIRROR_SOURCE_FILE_1310291537_HPP
#define MIRE_MIRROR_SOURCE_FILE_1310291537_HPP

#include <mire/mirror/default.hpp>
#include <mire/ct/to_string.hpp>

namespace mire {
namespace mirror {

template <typename R, typename M>
struct source_file<meta<R, M>>
 : ct::to_string<typename R::source_file>
{ };

} // namespace mirror
} // namespace mire

#endif // include guard
