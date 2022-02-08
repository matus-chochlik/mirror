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
    BASELINE
        ct-baseline-sequence-500x1000-i5-2400@3.1GHz
    SOURCE_DATA
        ct-tbr-sequence-tmp-500x1000-i5-2400@3.1GHz        
        ct-tbr-sequence-cmp-500x1000-i5-2400@3.1GHz        
        ct-vbr-sequence-tmp-500x1000-i5-2400@3.1GHz        
        ct-vbr-sequence-cmp-500x1000-i5-2400@3.1GHz        
)

mirror_add_latex_presentation(
    value_vs_type_based
    FIGURES
        ct-per-1-i5-2400
        ct-per-n-i5-2400
)
add_dependencies(doc-latex doc-value_vs_type_based-pdf)

