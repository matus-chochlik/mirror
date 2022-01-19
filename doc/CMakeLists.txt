# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt
#
add_custom_target(doc)
add_custom_target(install-doc)

add_subdirectory(logo)

find_package(Doxygen)
if(Doxygen_FOUND)
	add_subdirectory(doxygen)
endif()

find_program(PDFLATEX_COMMAND pdflatex)
if(PDFLATEX_COMMAND)
	add_subdirectory(latex)
endif()

