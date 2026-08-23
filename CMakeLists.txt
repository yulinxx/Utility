cmake_minimum_required(VERSION 4.3)

include(../Config.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/../CMake/StandaloneInit.cmake)

project(SanYiCore
    VERSION 1.0.0
    DESCRIPTION "SanYi CAD Core Utility Library"
    LANGUAGES CXX
)

option(BUILD_UTILITY_TESTS "Build Utility unit tests" OFF)

add_subdirectory(Utility)

message(STATUS "[Standalone: ${PROJECT_NAME}]")
message(STATUS "  Version: ${PROJECT_VERSION}")
message(STATUS "  Tests: ${BUILD_UTILITY_TESTS}")
message(STATUS "----------------------------------------")
