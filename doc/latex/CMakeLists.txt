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
        time-baseline-sequence-500x1000-i5-2400
    SOURCE_DATA
        time-tbr-sequence-tmp-500x1000-i5-2400
        time-tbr-sequence-cmp-500x1000-i5-2400
        time-vbr-sequence-tmp-500x1000-i5-2400
        time-vbr-sequence-cmp-500x1000-i5-2400
)

mirror_generate_figure(
    ct-per-n-i5-2400
    GENERATOR ct-per-n-mo
	LABEL reflection_kind
    BASELINE
        time-baseline-sequence-500x1000-i5-2400
    SOURCE_DATA
        time-tbr-sequence-tmp-500x1000-i5-2400
        time-tbr-sequence-cmp-500x1000-i5-2400
        time-vbr-sequence-tmp-500x1000-i5-2400
        time-vbr-sequence-cmp-500x1000-i5-2400
)

mirror_generate_figure(
    ct-per-1-i7-1185
    GENERATOR ct-per-1-mo
	LABEL reflection_kind
    BASELINE
        time-baseline-sequence-1000x1000-i7-1185G7
    SOURCE_DATA
        time-tbr-sequence-tmp-1000x1000-i7-1185G7
        time-tbr-sequence-cmp-1000x1000-i7-1185G7
        time-vbr-sequence-tmp-1000x1000-i7-1185G7
        time-vbr-sequence-cmp-1000x1000-i7-1185G7
)

mirror_generate_figure(
    ct-per-n-i7-1185
    GENERATOR ct-per-n-mo
	LABEL reflection_kind
    BASELINE
        time-baseline-sequence-1000x1000-i7-1185G7
    SOURCE_DATA
        time-tbr-sequence-tmp-1000x1000-i7-1185G7
        time-tbr-sequence-cmp-1000x1000-i7-1185G7
        time-vbr-sequence-tmp-1000x1000-i7-1185G7
        time-vbr-sequence-cmp-1000x1000-i7-1185G7
)

mirror_generate_figure(
    ct-per-1-R7-4800
    GENERATOR ct-per-1-mo
	LABEL reflection_kind
    BASELINE
        time-baseline-sequence-500x1000-Ryzen7-4800HS
    SOURCE_DATA
        time-tbr-sequence-tmp-400x1000-Ryzen7-4800HS
        time-tbr-sequence-cmp-400x1000-Ryzen7-4800HS
        time-vbr-sequence-tmp-500x1000-Ryzen7-4800HS
        time-vbr-sequence-cmp-500x1000-Ryzen7-4800HS
)

mirror_generate_figure(
    ct-per-n-R7-4800
    GENERATOR ct-per-n-mo
	LABEL reflection_kind
    BASELINE
        time-baseline-sequence-500x1000-Ryzen7-4800HS
    SOURCE_DATA
        time-tbr-sequence-tmp-400x1000-Ryzen7-4800HS
        time-tbr-sequence-cmp-400x1000-Ryzen7-4800HS
        time-vbr-sequence-tmp-500x1000-Ryzen7-4800HS
        time-vbr-sequence-cmp-500x1000-Ryzen7-4800HS
)

mirror_generate_figure(
	ct-per-1-ARMv7l
    GENERATOR ct-per-1-mo
	LABEL reflection_kind
    BASELINE
        time-baseline-sequence-250x1000-ARMv7l
    SOURCE_DATA
        time-tbr-sequence-tmp-150x1000-ARMv7l
        time-tbr-sequence-cmp-150x1000-ARMv7l
        time-vbr-sequence-tmp-250x1000-ARMv7l
        time-vbr-sequence-cmp-250x1000-ARMv7l
)

mirror_generate_figure(
	ct-per-n-ARMv7l
    GENERATOR ct-per-n-mo
	LABEL reflection_kind
    BASELINE
        time-baseline-sequence-250x1000-ARMv7l
    SOURCE_DATA
        time-tbr-sequence-tmp-150x1000-ARMv7l
        time-tbr-sequence-cmp-150x1000-ARMv7l
        time-vbr-sequence-tmp-250x1000-ARMv7l
        time-vbr-sequence-cmp-250x1000-ARMv7l
)

mirror_generate_figure(
    ct-ratios-i5-2400
    GENERATOR ct-ratios
	LABEL reflection_kind
    BASELINE
        time-baseline-sequence-1000x1000-i7-1185G7
    SOURCE_DATA
        time-tbr-sequence-tmp-1000x1000-i7-1185G7
        time-vbr-sequence-tmp-1000x1000-i7-1185G7
        time-tbr-sequence-cmp-1000x1000-i7-1185G7
        time-vbr-sequence-cmp-1000x1000-i7-1185G7
)

mirror_generate_figure(
    ct-ratios-i7-1185
    GENERATOR ct-ratios
	LABEL reflection_kind
    BASELINE
        time-baseline-sequence-1000x1000-i7-1185G7
    SOURCE_DATA
        time-tbr-sequence-tmp-1000x1000-i7-1185G7
        time-vbr-sequence-tmp-1000x1000-i7-1185G7
        time-tbr-sequence-cmp-1000x1000-i7-1185G7
        time-vbr-sequence-cmp-1000x1000-i7-1185G7
)

mirror_generate_figure(
    ct-ratios-R7-4800
    GENERATOR ct-ratios
	LABEL reflection_kind
    BASELINE
        time-baseline-sequence-500x1000-Ryzen7-4800HS
    SOURCE_DATA
        time-tbr-sequence-tmp-400x1000-Ryzen7-4800HS
        time-vbr-sequence-tmp-500x1000-Ryzen7-4800HS
        time-tbr-sequence-cmp-400x1000-Ryzen7-4800HS
        time-vbr-sequence-cmp-500x1000-Ryzen7-4800HS
)

mirror_generate_figure(
	ct-ratios-ARMv7l
    GENERATOR ct-ratios
	LABEL reflection_kind
    BASELINE
        time-baseline-sequence-250x1000-ARMv7l
    SOURCE_DATA
        time-tbr-sequence-tmp-150x1000-ARMv7l
        time-vbr-sequence-tmp-250x1000-ARMv7l
        time-tbr-sequence-cmp-150x1000-ARMv7l
        time-vbr-sequence-cmp-250x1000-ARMv7l
)

mirror_generate_figure(
    ct-per-1-i5-2400-cp
    GENERATOR ct-per-1-mo
	LABEL reflection_kind
    SOURCE_DATA
        time-tbr-copypaste-tmp-125x100-i5-2400
        time-tbr-copypaste-cmp-125x100-i5-2400
        time-vbr-copypaste-tmp-125x100-i5-2400
        time-vbr-copypaste-cmp-125x100-i5-2400
)

mirror_generate_figure(
    ct-per-n-i5-2400-cp
    GENERATOR ct-per-n-mo
	LABEL reflection_kind
    SOURCE_DATA
        time-tbr-copypaste-tmp-125x100-i5-2400
        time-tbr-copypaste-cmp-125x100-i5-2400
        time-vbr-copypaste-tmp-125x100-i5-2400
        time-vbr-copypaste-cmp-125x100-i5-2400
)

mirror_generate_figure(
    ct-ratios-i5-2400-cp
    GENERATOR ct-ratios
	LABEL reflection_kind
    SOURCE_DATA
        time-tbr-copypaste-tmp-125x100-i5-2400
        time-vbr-copypaste-tmp-125x100-i5-2400
        time-tbr-copypaste-cmp-125x100-i5-2400
        time-vbr-copypaste-cmp-125x100-i5-2400
)

mirror_generate_figure(
    ct-per-1-R7-4800-cp
    GENERATOR ct-per-1-mo
	LABEL reflection_kind
    SOURCE_DATA
        time-tbr-copypaste-tmp-100x100-Ryzen7-4800HS
        time-tbr-copypaste-cmp-100x100-Ryzen7-4800HS
        time-vbr-copypaste-tmp-100x100-Ryzen7-4800HS
        time-vbr-copypaste-cmp-100x100-Ryzen7-4800HS
)

mirror_generate_figure(
    ct-per-n-R7-4800-cp
    GENERATOR ct-per-n-mo
	LABEL reflection_kind
    SOURCE_DATA
        time-tbr-copypaste-tmp-100x100-Ryzen7-4800HS
        time-tbr-copypaste-cmp-100x100-Ryzen7-4800HS
        time-vbr-copypaste-tmp-100x100-Ryzen7-4800HS
        time-vbr-copypaste-cmp-100x100-Ryzen7-4800HS
)

mirror_generate_figure(
    ct-ratios-R7-4800-cp
    GENERATOR ct-ratios
	LABEL reflection_kind
    SOURCE_DATA
        time-tbr-copypaste-tmp-100x100-Ryzen7-4800HS
        time-vbr-copypaste-tmp-100x100-Ryzen7-4800HS
        time-tbr-copypaste-cmp-100x100-Ryzen7-4800HS
        time-vbr-copypaste-cmp-100x100-Ryzen7-4800HS
)

mirror_generate_figure(
    ct-per-1-ARMv7l-cp
    GENERATOR ct-per-1-mo
	LABEL reflection_kind
    SOURCE_DATA
        time-tbr-copypaste-tmp-80x100-ARMv7l
        time-tbr-copypaste-cmp-80x100-ARMv7l
        time-vbr-copypaste-tmp-80x100-ARMv7l
        time-vbr-copypaste-cmp-80x100-ARMv7l
)

mirror_generate_figure(
    ct-per-n-ARMv7l-cp
    GENERATOR ct-per-n-mo
	LABEL reflection_kind
    SOURCE_DATA
        time-tbr-copypaste-tmp-80x100-ARMv7l
        time-tbr-copypaste-cmp-80x100-ARMv7l
        time-vbr-copypaste-tmp-80x100-ARMv7l
        time-vbr-copypaste-cmp-80x100-ARMv7l
)

mirror_generate_figure(
    ct-ratios-ARMv7l-cp
    GENERATOR ct-ratios
	LABEL reflection_kind
    SOURCE_DATA
        time-tbr-copypaste-tmp-80x100-ARMv7l
        time-vbr-copypaste-tmp-80x100-ARMv7l
        time-tbr-copypaste-cmp-80x100-ARMv7l
        time-vbr-copypaste-cmp-80x100-ARMv7l
)

mirror_generate_figure(
    ct-per-1-R7-4800-cp-op
    GENERATOR ct-per-1-mo
	LABEL reflection_kind
    SOURCE_DATA
        time-tbr-copypaste-op-tmp-100x100-Ryzen7-4800HS
        time-tbr-copypaste-op-cmp-100x100-Ryzen7-4800HS
        time-vbr-copypaste-op-tmp-100x100-Ryzen7-4800HS
        time-vbr-copypaste-op-cmp-100x100-Ryzen7-4800HS
)

mirror_generate_figure(
    ct-per-n-R7-4800-cp-op
    GENERATOR ct-per-n-mo
	LABEL reflection_kind
    SOURCE_DATA
        time-tbr-copypaste-op-tmp-100x100-Ryzen7-4800HS
        time-tbr-copypaste-op-cmp-100x100-Ryzen7-4800HS
        time-vbr-copypaste-op-tmp-100x100-Ryzen7-4800HS
        time-vbr-copypaste-op-cmp-100x100-Ryzen7-4800HS
)

mirror_generate_figure(
    ct-ratios-R7-4800-cp-op
    GENERATOR ct-ratios
	LABEL reflection_kind
    SOURCE_DATA
        time-tbr-copypaste-op-tmp-100x100-Ryzen7-4800HS
        time-vbr-copypaste-op-tmp-100x100-Ryzen7-4800HS
        time-tbr-copypaste-op-cmp-100x100-Ryzen7-4800HS
        time-vbr-copypaste-op-cmp-100x100-Ryzen7-4800HS
)

mirror_add_latex_presentation(
    value_vs_type_based
    FIGURES
        ct-per-1-i5-2400
        ct-per-n-i5-2400
        ct-ratios-i5-2400
        ct-per-1-i7-1185
        ct-per-n-i7-1185
        ct-ratios-i7-1185
        ct-per-1-R7-4800
        ct-per-n-R7-4800
        ct-ratios-R7-4800
		ct-per-1-ARMv7l
		ct-per-n-ARMv7l
		ct-ratios-ARMv7l
        ct-per-1-i5-2400-cp
        ct-per-n-i5-2400-cp
        ct-ratios-i5-2400-cp
        ct-per-1-R7-4800-cp
        ct-per-n-R7-4800-cp
        ct-ratios-R7-4800-cp
		ct-per-1-ARMv7l-cp
		ct-per-n-ARMv7l-cp
		ct-ratios-ARMv7l-cp
        ct-per-1-R7-4800-cp-op
        ct-per-n-R7-4800-cp-op
        ct-ratios-R7-4800-cp-op
)
add_dependencies(doc-latex doc-value_vs_type_based-pdf)

mirror_add_latex_presentation(
	P2560Rx
    FIGURES
        ct-per-1-i5-2400
        ct-per-n-i5-2400
        ct-ratios-i5-2400
        ct-per-1-i7-1185
        ct-per-n-i7-1185
        ct-ratios-i7-1185
        ct-per-1-R7-4800
        ct-per-n-R7-4800
        ct-ratios-R7-4800
		ct-per-1-ARMv7l
		ct-per-n-ARMv7l
		ct-ratios-ARMv7l
        ct-per-1-i5-2400-cp
        ct-per-n-i5-2400-cp
        ct-ratios-i5-2400-cp
        ct-per-1-R7-4800-cp
        ct-per-n-R7-4800-cp
        ct-ratios-R7-4800-cp
		ct-per-1-ARMv7l-cp
		ct-per-n-ARMv7l-cp
		ct-ratios-ARMv7l-cp
        ct-per-1-R7-4800-cp-op
        ct-per-n-R7-4800-cp-op
        ct-ratios-R7-4800-cp-op
)
add_dependencies(doc-latex doc-P2560Rx-pdf)

