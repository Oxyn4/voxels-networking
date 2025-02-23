
cmake_minimum_required(VERSION 3.10)

project(
        voxels-networking-documentation
        VERSION 0.1.0
        DESCRIPTION "Documentation for voxels networking"
        HOMEPAGE_URL "https://www.github.com/Oxyn4/voxels-networking"
)

find_package(Doxygen)

if (DOXYGEN_FOUND)
    message(STATUS "Found doxygen")
    add_custom_target(docs ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM
    )
else ()
    message(STATUS "Unable to find Doxygen")
endif ()