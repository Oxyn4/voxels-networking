cmake_minimum_required(VERSION 3.10)

project(
        voxels-networking-documentation
        VERSION 0.1.0
        DESCRIPTION "Documentation for voxels networking"
        HOMEPAGE_URL "https://www.github.com/Oxyn4/voxels-networking"
)

message(STATUS "Compiling voxels-networking-documentation")

find_package(Doxygen)

if (DOXYGEN_FOUND)
    message(STATUS "Found doxygen")
    add_custom_target(docs ALL
            COMMAND
            mkdir -p ${CMAKE_CURRENT_SOURCE_DIR}/generated/
            COMMAND
            python3 -m venv .venv
            COMMAND
            source ./.venv/bin/activate
            COMMAND
            #install our dependencies
            pip3 install sphinx breathe
            COMMAND
            ${DOXYGEN_EXECUTABLE} Doxyfile
            COMMAND
            sphinx-build
            -M singlehtml
            .
            generated/
            COMMAND
            deactivate
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
            COMMENT "Generating xml API documentation with Doxygen"
            VERBATIM
    )
else ()
    message(STATUS "Unable to find Doxygen")
endif ()