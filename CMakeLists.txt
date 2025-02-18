
cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
        voxels-networking
        VERSION 0.1.0
        DESCRIPTION "Various network protocol library implementations for a game called voxels"
        HOMEPAGE_URL "https://www.github.com/Oxyn4/voxels-networking"
)

find_package(Boost CONFIG REQUIRED COMPONENTS
        log # debugging and code observability
)

set(FLATBUFFERS_GAME_OUT ${CMAKE_CURRENT_BINARY_DIR}/schema/game/)
set(FLATBUFFERS_GAME_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/schema/game)

add_custom_target(flatbuffers_compilation_game
    COMMAND
        mkdir -p ${FLATBUFFERS_GAME_OUT}
    COMMAND
        flatc
        --cpp
        --gen-object-api
        --gen-all
        --gen-onefile
        --filename-suffix _raw_types
        --filename-ext hpp
        -o ${FLATBUFFERS_GAME_OUT}
        ${FLATBUFFERS_GAME_SOURCE}/protocol.fbs
    RESULT_VARIABLE FLATBUFFERS_COMPILATION_GAME_RESULT
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)


add_library(voxels_networking INTERFACE)

target_include_directories(voxels_networking INTERFACE include/)
target_include_directories(voxels_networking INTERFACE ${FLATBUFFERS_GAME_OUT})

target_link_libraries(voxels_networking INTERFACE Boost::log)
target_link_libraries(voxels_networking INTERFACE msquic)

add_dependencies(voxels_networking flatbuffers_compilation_game)

add_executable(examples_server
    examples/server.cpp
)

target_link_libraries(examples_server voxels_networking)

add_executable(examples_client
    examples/client.cpp
)

target_link_libraries(examples_client voxels_networking)