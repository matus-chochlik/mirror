/**
 *  @file mire/ct/append.hpp
 *  @brief Meta-function returning a range having the passed item
 *  appended.
 *
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_APPEND_1011291729_HPP
#define MIRE_CT_APPEND_1011291729_HPP


#include <mire/ct/default.hpp>

namespace mire {
namespace ct {

#ifndef MIRROR_DOCUMENTATION_ONLY

template <typename ... P, typename ... T>
struct append<range<P...>, T...>
{
	typedef range<P..., T...> type;
};

template <char ... C, char ... T>
struct append_char<basic_string<char, C...>, T...>
{
	typedef basic_string<char, C..., T...> type;
};

#endif // !MIRROR_DOCUMENTATION_ONLY

} // namespace ct
} // namespace mire

#endif //include guard

