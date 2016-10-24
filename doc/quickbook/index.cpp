/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[index_configure_basic
__prompt__ cd /path/to/mirror/source
__prompt__ export CXX=/path/to/modified/clang++
__prompt__ ./configure.py --reflexpr-include-dir /path/to/reflexpr/include/ --build-dir _build
__prompt__ cd _build
__prompt__ make
//]
//[index_configure_build
__prompt__ cd /path/to/mirror/source
__prompt__ export CXX=/path/to/modified/clang++
__prompt__ ./configure.py --reflexpr-include-dir /path/to/reflexpr/include/ --build
//]
//[index_configure_bash_complete
__prompt__ cd /path/to/mirror/source
__prompt__ source config/bash-complete
__prompt__ ./mirror-config /*< Pressing the ['TAB] key here activates
the command-line option completion >*/
//]
