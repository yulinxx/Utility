# Utility模块单元测试配置 —— 用 apr_add_test 封装

find_package(GTest CONFIG REQUIRED)
include(GoogleTest)

file(GLOB_RECURSE UTILITY_TEST_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
)

# 统一封装：GTest 注入、MSVC /OPT:NOREF、PRE_TEST 发现、FOLDER 全部自动处理
apr_add_test(NAME UtilityTests
    SOURCES ${UTILITY_TEST_SOURCES}
    LIBS Utility
    LABELS core utility
    MOCK
    WORKING_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

# 额外 include 路径（各模块自己的差异点，apr_add_test 不强求统一）
target_include_directories(UtilityTests PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/.."
    "${CMAKE_CURRENT_SOURCE_DIR}/../Include")