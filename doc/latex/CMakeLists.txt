# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt
#
include(LaTeX.cmake)

add_custom_target(doc-latex)
add_dependencies(doc doc-latex)

mirror_add_latex_presentation(
	reflection_api
	FIGURES rpc_class rpc_sequence
)
add_dependencies(doc-latex doc-reflection_api-pdf)
