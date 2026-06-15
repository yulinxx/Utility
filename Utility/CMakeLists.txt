cmake_minimum_required(VERSION 3.20)

set(LIB_NAME "Utility")

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

# 创建动态库
add_library(${LIB_NAME} SHARED
    ${UTILITY_SOURCES}
    ${UTILITY_HEADERS}
)

# 在 VS 项目中按头文件和源文件分类
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "Header Files" FILES ${UTILITY_HEADERS})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "Source Files" FILES ${UTILITY_SOURCES})

# 添加头文件目录
target_include_directories(${LIB_NAME}
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/Include"
        "${CMAKE_CURRENT_SOURCE_DIR}/Include/Ut"
        "${CMAKE_CURRENT_SOURCE_DIR}/Include/BBox"
        "${CMAKE_CURRENT_SOURCE_DIR}/Include/Color"
        "${CMAKE_CURRENT_SOURCE_DIR}/Include/Mat"
        "${CMAKE_CURRENT_SOURCE_DIR}/Include/Vec"
        "${CMAKE_SOURCE_DIR}/Log/Log/Include"
)

# C++ 标准
target_compile_features(${LIB_NAME} PUBLIC cxx_std_17)

# 链接 Log 库 —— 所有依赖 Utility 的模块自动继承
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

# 项目配置信息输出
message(STATUS "  [Core/Utility]")
message(STATUS "    Library: ${LIB_NAME}")
message(STATUS "    Version: 1.0.0")