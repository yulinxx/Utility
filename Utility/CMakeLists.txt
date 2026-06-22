cmake_minimum_required(VERSION 3.20)

set(LIB_NAME "Utility")

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../../CMake/Utils.cmake")
    include("${CMAKE_CURRENT_SOURCE_DIR}/../../CMake/Utils.cmake")
endif()

# 版本号定义
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)
set(PROJECT_VERSION_MAJOR ${VERSION_MAJOR})
set(PROJECT_VERSION_MINOR ${VERSION_MINOR})
set(PROJECT_VERSION_PATCH ${VERSION_PATCH})
set(PROJECT_VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

# 收集所有源文件和头文件
file(GLOB_RECURSE UTILITY_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/Src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Src/*.cxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/Src/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/Src/*.c"
)

file(GLOB_RECURSE UTILITY_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/Include/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Include/*.hpp"
)

find_path(BSHOSHANY_THREAD_POOL_INCLUDE_DIRS "BS_thread_pool.hpp")

add_library(${LIB_NAME} SHARED
    ${UTILITY_SOURCES}
    ${UTILITY_HEADERS}
)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${UTILITY_SOURCES} ${UTILITY_HEADERS})

target_include_directories(${LIB_NAME}
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/Include"
        "${CMAKE_CURRENT_SOURCE_DIR}/Include/Ut"
        "${CMAKE_CURRENT_SOURCE_DIR}/Include/BBox"
        "${CMAKE_CURRENT_SOURCE_DIR}/Include/Color"
        "${CMAKE_CURRENT_SOURCE_DIR}/Include/Mat"
        "${CMAKE_CURRENT_SOURCE_DIR}/Include/Vec"
        "${CMAKE_SOURCE_DIR}/Log/Log/Include"
        ${BSHOSHANY_THREAD_POOL_INCLUDE_DIRS}
)

# C++ 标准
target_compile_features(${LIB_NAME} PUBLIC cxx_std_17)

target_link_libraries(${LIB_NAME}
    PUBLIC
        Log
)

# 导出宏定义
target_compile_definitions(${LIB_NAME} PRIVATE UTILITY_EXPORTS)
target_compile_definitions(${LIB_NAME} PUBLIC UTILITY_EXTERN_TEMPLATES)

# MSVC 编译选项
if(MSVC)
    target_compile_options(${LIB_NAME} PRIVATE /utf-8)
endif()

option(BUILD_UTILITY_TESTS "Build Utility unit tests" OFF)

if(BUILD_UTILITY_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)
    add_subdirectory(Test)
endif()

sanyi_add_version_info(${LIB_NAME} "${LIB_NAME}" "Core Utility Library")

message(STATUS "[${LIB_NAME}]")
message(STATUS "  Library: ${LIB_NAME}")
message(STATUS "  Version: ${PROJECT_VERSION}")
message(STATUS "  Platform: ${CMAKE_SYSTEM_NAME}(${CMAKE_SYSTEM_PROCESSOR})")
message(STATUS "  Build Type: ${CMAKE_BUILD_TYPE}")
if(BUILD_UTILITY_TESTS)
    message(STATUS "  Tests: ENABLED")
else()
    message(STATUS "  Tests: DISABLED")
endif()
message(STATUS "")
message(STATUS "----------------------------------------")