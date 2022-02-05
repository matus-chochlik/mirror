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

mirror_add_latex_presentation(
	meeting_cpp
	FIGURES rpc_class rpc_sequence
)
add_dependencies(doc-latex doc-meeting_cpp-pdf)

mirror_add_latex_presentation(
	use_cases
	FIGURES
		rpc_class rpc_sequence
		serialize_class deserialize_class
		cards_class
)
add_dependencies(doc-latex doc-use_cases-pdf)

mirror_add_latex_presentation(
	value_vs_type_based
)
add_dependencies(doc-latex doc-value_vs_type_based-pdf)

