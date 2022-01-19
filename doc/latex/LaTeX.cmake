# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt
#

file(GENERATE
    OUTPUT "beamercolorthememirror.sty"
    INPUT "beamercolorthememirror.sty.in"
)

file(GENERATE
    OUTPUT "beamerouterthememirror.sty"
    INPUT "beamerouterthememirror.sty.in"
)

file(GENERATE
    OUTPUT "beamer_mirror.tex"
    INPUT "beamer_mirror.tex.in"
)

find_program(PYTHON3_COMMAND python3)

macro(mirror_generate_figure NAME)
    cmake_parse_arguments(
        MIRROR_FIGURE
        ""
        "GENERATOR"
        "SOURCE_DATA"
        ${ARGN}
    )
    if(PYTHON3_COMMAND)
        set(FIG_DEPS)
        set(GEN_ARGS)
        foreach(SRC_DATA ${MIRROR_FIGURE_SOURCE_NAME})
            list(APPEND GEN_ARGS "-i")
            list(APPEND GEN_ARGS "${CMAKE_CURRENT_SOURCE_DIR}/data/${SRC_DATA}.json")
            list(APPEND FIG_DEPS "${CMAKE_CURRENT_SOURCE_DIR}/data/${SRC_DATA}.json")
        endforeach()
        list(APPEND GEN_ARGS "-o")
        list(APPEND GEN_ARGS "${NAME}.pdf")
        list(APPEND FIG_DEPS "${CMAKE_CURRENT_SOURCE_DIR}/tools/${MIRROR_FIGURE_GENERATOR}.py")

        add_custom_command(
            OUTPUT ${NAME}.pdf
            COMMAND "${PYTHON3_COMMAND}" "-B"
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/${MIRROR_FIGURE_GENERATOR}.py"
            ${GEN_ARGS}
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
            DEPENDS ${FIG_DEPS}
            COMMENT "Rendering ${NAME}.pdf"
        )
    endif()
endmacro()

macro(mirror_add_latex_presentation NAME)
    cmake_parse_arguments(
        MIRROR_LATEX
        ""
        ""
        "FIGURES"
        ${ARGN}
    )
    set(SRC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/${NAME}.tex")

    add_custom_command(
        OUTPUT "${NAME}.tex"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${SRC_PATH}" "./"
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        DEPENDS ${SRC_PATH}
        COMMENT "Copying ${NAME} LaTeX source"
    )

    set(PRESENTATION_DEPENDS
        "${CMAKE_CURRENT_BINARY_DIR}/beamerouterthememirror.sty"
        "${CMAKE_CURRENT_BINARY_DIR}/beamercolorthememirror.sty"
        "${CMAKE_CURRENT_BINARY_DIR}/beamer_mirror.tex"
        "${CMAKE_CURRENT_BINARY_DIR}/${NAME}.tex"
    )

    add_custom_target(
        ${NAME}-latex-sources
        DEPENDS ${PRESENTATION_DEPENDS}
    )
    foreach(FIGURE ${MIRROR_LATEX_FIGURES})
        list(APPEND PRESENTATION_DEPENDS ${FIGURE}.pdf)
    endforeach()

    add_custom_command(
        OUTPUT ${NAME}.toc
        COMMAND pdflatex
            "-shell-escape"
            "-interaction" "batchmode"
            "-halt-on-error"
            "-output-directory=${CMAKE_CURRENT_BINARY_DIR}"
            "-jobname" "${NAME}"
            "${NAME}.tex"
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        DEPENDS
            ${PRESENTATION_DEPENDS}
            ${NAME}-latex-sources
        COMMENT "Preparing ${NAME}.pdf"
    )

    add_custom_command(
        OUTPUT ${NAME}.pdf
        COMMAND pdflatex
            "-shell-escape"
            "-interaction" "batchmode"
            "-output-directory=${CMAKE_CURRENT_BINARY_DIR}"
            "-jobname" "${NAME}"
            "${NAME}.tex"
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        DEPENDS ${NAME}.toc
        COMMENT "Generating ${NAME}.pdf"
    )

    add_custom_target(doc-${NAME}-pdf DEPENDS ${NAME}.pdf)
endmacro()