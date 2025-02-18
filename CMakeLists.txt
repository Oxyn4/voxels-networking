
cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
        voxels-networking
        VERSION 0.1.0
        DESCRIPTION "Various network protocol library implementations for a game called voxels"
        HOMEPAGE_URL "https://www.github.com/Oxyn4/voxels-networking"
)

# find boost dependencies
# allows us to use them in our project
find_package(Boost CONFIG REQUIRED COMPONENTS
        log # debugging and code observability
)

# compilation options used by our custom target
set(FLATBUFFERS_GAME_OUT ${CMAKE_CURRENT_BINARY_DIR}/schema/game/)
set(FLATBUFFERS_GAME_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/schema/game)

add_custom_target(flatbuffers_compilation_game
    COMMAND
        # create our directory for our compiled flatbuffers schema
        mkdir -p ${FLATBUFFERS_GAME_OUT}
    COMMAND
        # generate our compiled flatbuffers schema
        flatc
        # generate c++ bindings
        --cpp
        # creates a more flexible API that does not strictly adhere to the no copy nature of typical flatbuffers
        # Using this API is also more verbose making it clear when we stop getting so much performance benefits
        --gen-object-api
        # recursively build includes
        --gen-all
        # create a single output file
        --gen-onefile
        --filename-suffix _raw_types
        --filename-ext hpp
        # it will be outputted to our output directory
        -o ${FLATBUFFERS_GAME_OUT}
        # the root source file contains includes for other protocol buffer files
        ${FLATBUFFERS_GAME_SOURCE}/protocol.fbs
    RESULT_VARIABLE FLATBUFFERS_COMPILATION_GAME_RESULT
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

# create a header only library consisting of our flatbuffer generated header files
add_library(voxels_game_raw_types INTERFACE)
# Ensure that our custom compilation target is run before generating this library
add_dependencies(voxels_game_raw_types flatbuffers_compilation_game)
# Add these as includes for our main networking library
target_include_directories(voxels_game_raw_types INTERFACE ${FLATBUFFERS_GAME_OUT})

# create the main library
add_library(voxels_networking INTERFACE)

target_include_directories(voxels_networking INTERFACE include/)

target_link_libraries(voxels_networking INTERFACE Boost::log)
target_link_libraries(voxels_networking INTERFACE msquic)
target_link_libraries(voxels_networking INTERFACE voxels_game_raw_types)

add_dependencies(voxels_networking flatbuffers_compilation_game)

# build examples

add_executable(examples_server
    examples/server.cpp
)

target_link_libraries(examples_server voxels_networking)

add_executable(examples_client
    examples/client.cpp
)

target_link_libraries(examples_client voxels_networking)