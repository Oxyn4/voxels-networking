cmake_minimum_required(VERSION 3.10)

project(
        voxels-networking-documentation
        VERSION 0.1.0
        DESCRIPTION "Documentation for voxels networking"
        HOMEPAGE_URL "https://www.github.com/Oxyn4/voxels-networking"
)

message(STATUS "Compiling voxels-networking-documentation")

find_package(Doxygen)

find_program(SPHINX_BUILD_EXECUTABLE NAMES sphinx-build)

if (${SPHINX_BUILD_EXECUTABLE} STREQUAL "${SPHINX_BUILD_EXECUTABLE}-NOTFOUND")
    message(FATAL_ERROR "could not find sphinx-build executable via cmake find_package() !")
endif ()

if (DOXYGEN_FOUND)
    message(STATUS "Found doxygen")
    add_custom_target(docs ALL
            COMMAND
            mkdir -p ${CMAKE_CURRENT_SOURCE_DIR}/generated/
            COMMAND
            ${DOXYGEN_EXECUTABLE} Doxyfile
            COMMAND
            ${SPHINX_BUILD_EXECUTABLE}
            -M singlehtml
            .
            generated/
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
            COMMENT "Generating xml API documentation with Doxygen"
            VERBATIM
    )
else ()
    message(STATUS "Unable to find Doxygen")
endif ()