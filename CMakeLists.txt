
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

add_library(voxels_networking INTERFACE)

target_include_directories(voxels_networking INTERFACE include/)

target_link_libraries(voxels_networking INTERFACE Boost::log Boost::asio)
target_link_libraries(voxels_networking INTERFACE msquic)
