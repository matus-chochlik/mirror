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

mirror_generate_figure(
    ct-per-1-i5-2400
    GENERATOR ct-per-1-mo
	LABEL reflection_kind
    BASELINE
        ct-baseline-sequence-500x1000-i5-2400@3.1GHz
    SOURCE_DATA
        ct-tbr-sequence-tmp-500x1000-i5-2400@3.1GHz
        ct-tbr-sequence-cmp-500x1000-i5-2400@3.1GHz
        ct-vbr-sequence-tmp-500x1000-i5-2400@3.1GHz
        ct-vbr-sequence-cmp-500x1000-i5-2400@3.1GHz
)

mirror_generate_figure(
    ct-per-n-i5-2400
    GENERATOR ct-per-n-mo
	LABEL reflection_kind
    BASELINE
        ct-baseline-sequence-500x1000-i5-2400@3.1GHz
    SOURCE_DATA
        ct-tbr-sequence-tmp-500x1000-i5-2400@3.1GHz
        ct-tbr-sequence-cmp-500x1000-i5-2400@3.1GHz
        ct-vbr-sequence-tmp-500x1000-i5-2400@3.1GHz
        ct-vbr-sequence-cmp-500x1000-i5-2400@3.1GHz
)

mirror_generate_figure(
    ct-per-1-i7-1185
    GENERATOR ct-per-1-mo
	LABEL reflection_kind
    BASELINE
        ct-baseline-sequence-1000x1000-i7-1185G7@3.0GHz
    SOURCE_DATA
        ct-tbr-sequence-tmp-1000x1000-i7-1185G7@3.0GHz
        ct-tbr-sequence-cmp-1000x1000-i7-1185G7@3.0GHz
        ct-vbr-sequence-tmp-1000x1000-i7-1185G7@3.0GHz
        ct-vbr-sequence-cmp-1000x1000-i7-1185G7@3.0GHz
)

mirror_generate_figure(
    ct-per-n-i7-1185
    GENERATOR ct-per-n-mo
	LABEL reflection_kind
    BASELINE
        ct-baseline-sequence-1000x1000-i7-1185G7@3.0GHz
    SOURCE_DATA
        ct-tbr-sequence-tmp-1000x1000-i7-1185G7@3.0GHz
        ct-tbr-sequence-cmp-1000x1000-i7-1185G7@3.0GHz
        ct-vbr-sequence-tmp-1000x1000-i7-1185G7@3.0GHz
        ct-vbr-sequence-cmp-1000x1000-i7-1185G7@3.0GHz
)

mirror_generate_figure(
    ct-per-1-R7-4800
    GENERATOR ct-per-1-mo
	LABEL reflection_kind
    BASELINE
        ct-baseline-sequence-500x1000-Ryzen7-4800HS
    SOURCE_DATA
        ct-tbr-sequence-tmp-400x1000-Ryzen7-4800HS
        ct-tbr-sequence-cmp-400x1000-Ryzen7-4800HS
        ct-vbr-sequence-tmp-500x1000-Ryzen7-4800HS
        ct-vbr-sequence-cmp-500x1000-Ryzen7-4800HS
)

mirror_generate_figure(
    ct-per-n-R7-4800
    GENERATOR ct-per-n-mo
	LABEL reflection_kind
    BASELINE
        ct-baseline-sequence-500x1000-Ryzen7-4800HS
    SOURCE_DATA
        ct-tbr-sequence-tmp-400x1000-Ryzen7-4800HS
        ct-tbr-sequence-cmp-400x1000-Ryzen7-4800HS
        ct-vbr-sequence-tmp-500x1000-Ryzen7-4800HS
        ct-vbr-sequence-cmp-500x1000-Ryzen7-4800HS
)

mirror_generate_figure(
	ct-per-1-ARMv7l
    GENERATOR ct-per-1-mo
	LABEL reflection_kind
    BASELINE
        ct-baseline-sequence-250x1000-ARMv7l
    SOURCE_DATA
        ct-tbr-sequence-tmp-150x1000-ARMv7l
        ct-tbr-sequence-cmp-150x1000-ARMv7l
        ct-vbr-sequence-tmp-250x1000-ARMv7l
        ct-vbr-sequence-cmp-250x1000-ARMv7l
)

mirror_generate_figure(
	ct-per-n-ARMv7l
    GENERATOR ct-per-n-mo
	LABEL reflection_kind
    BASELINE
        ct-baseline-sequence-250x1000-ARMv7l
    SOURCE_DATA
        ct-tbr-sequence-tmp-150x1000-ARMv7l
        ct-tbr-sequence-cmp-150x1000-ARMv7l
        ct-vbr-sequence-tmp-250x1000-ARMv7l
        ct-vbr-sequence-cmp-250x1000-ARMv7l
)

mirror_add_latex_presentation(
    value_vs_type_based
    FIGURES
        ct-per-1-i5-2400
        ct-per-n-i5-2400
        ct-per-1-i7-1185
        ct-per-n-i7-1185
        ct-per-1-R7-4800
        ct-per-n-R7-4800
		ct-per-1-ARMv7l
		ct-per-n-ARMv7l
)
add_dependencies(doc-latex doc-value_vs_type_based-pdf)

