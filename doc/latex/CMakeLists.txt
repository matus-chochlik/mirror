# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt
#

find_program(PDFLATEX_COMMAND pdflatex)
find_program(PYTHON3_COMMAND python3)

add_custom_target(latex-doc)
add_dependencies(doc latex-doc)

file(GENERATE
    OUTPUT "beamercolorthememirror.sty"
    INPUT "beamercolorthememirror.sty.in"
)

file(GENERATE
    OUTPUT "beamer_mirror.tex"
    INPUT "beamer_mirror.tex.in"
)

macro(mirror_add_latex_presentation SRC_NAME)
    if(PDFLATEX_COMMAND)
        set(SRC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/${SRC_NAME}.tex")

        add_custom_command(
            OUTPUT "${SRC_NAME}.tex"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different "${SRC_PATH}" "./"
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
            DEPENDS ${SRC_PATH}
            COMMENT "Copying ${SRC_NAME} LaTeX source"
        )

        set(PRESENTATION_DEPENDS
            "${CMAKE_CURRENT_BINARY_DIR}/beamercolorthememirror.sty"
            "${CMAKE_CURRENT_BINARY_DIR}/beamer_mirror.tex"
            "${CMAKE_CURRENT_BINARY_DIR}/${SRC_NAME}.tex"
        )

        add_custom_target(
            ${SRC_NAME}-latex-sources
            DEPENDS ${PRESENTATION_DEPENDS}
        )

        foreach(DEPNAME ${ARGN})
            list(APPEND PRESENTATION_DEPENDS mirror-${DEPNAME}.pdf)
        endforeach()

        add_custom_command(
            OUTPUT mirror-${SRC_NAME}.toc
            COMMAND pdflatex
                "-shell-escape"
                "-interaction" "batchmode"
                "-halt-on-error"
                "-output-directory=${CMAKE_CURRENT_BINARY_DIR}"
                "-jobname" "mirror-${SRC_NAME}"
                "${SRC_NAME}.tex"
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
            DEPENDS
                ${PRESENTATION_DEPENDS}
                ${SRC_NAME}-latex-sources
            COMMENT "Preparing mirror-${SRC_NAME}.pdf"
        )

        add_custom_command(
            OUTPUT mirror-${SRC_NAME}.pdf
            COMMAND pdflatex
                "-shell-escape"
                "-interaction" "batchmode"
                "-output-directory=${CMAKE_CURRENT_BINARY_DIR}"
                "-jobname" "mirror-${SRC_NAME}"
                "${SRC_NAME}.tex"
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
            DEPENDS mirror-${SRC_NAME}.toc
            COMMENT "Generating mirror-${SRC_NAME}.pdf"
        )

        add_custom_target(
            mirror-${SRC_NAME}-pdf
            DEPENDS mirror-${SRC_NAME}.pdf
        )

        add_dependencies(latex-doc mirror-${SRC_NAME}-pdf)
    endif()
endmacro()

mirror_add_latex_presentation(
    factory_on_P2320
)
