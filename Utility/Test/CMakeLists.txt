# Utility模块单元测试配置

find_package(GTest CONFIG REQUIRED)
include(GoogleTest)

file(GLOB_RECURSE UTILITY_TEST_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
)

add_executable(UtilityTests ${UTILITY_TEST_SOURCES})

target_compile_features(UtilityTests PRIVATE cxx_std_17)

target_include_directories(UtilityTests PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/.."
    "${CMAKE_CURRENT_SOURCE_DIR}/../Include"
)

target_link_libraries(UtilityTests PRIVATE
    Utility
    GTest::gtest
    GTest::gtest_main
    GTest::gmock
    GTest::gmock_main
)

# PRE_TEST：构建期发现时 exe 曾以 0xc0000135 启动失败（运行库 DLL 拷贝时序/PATH）；
# 推迟到 ctest 运行时发现（与 UI/PythonHost 一致）。
gtest_discover_tests(UtilityTests DISCOVERY_MODE PRE_TEST)

set_property(TARGET UtilityTests PROPERTY FOLDER "Tests")

if(MSVC)
    target_compile_options(UtilityTests PRIVATE /utf-8)
endif()