# Utility模块单元测试配置

find_package(GTest REQUIRED)
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

gtest_discover_tests(UtilityTests)

set_property(TARGET UtilityTests PROPERTY FOLDER "Tests")

if(MSVC)
    target_compile_options(UtilityTests PRIVATE /utf-8)
endif()