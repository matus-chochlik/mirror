#  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cmake_minimum_required(VERSION 2.8)

include(./mire_doc.cmake)

mire_doxy_doc_common(mire)

add_subdirectory(ct)
add_subdirectory(mirror)

add_custom_target(
	doc DEPENDS
		doc-mire
		doc-mire-ct
		doc-mire-mirror
)

