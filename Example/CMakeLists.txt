add_executable(SyUtilityExample
    main.cpp
)

target_compile_features(SyUtilityExample PRIVATE cxx_std_17)

target_link_libraries(SyUtilityExample PRIVATE
    Utility
)

if(MSVC)
    target_compile_options(SyUtilityExample PRIVATE /utf-8)
endif()

set_target_properties(SyUtilityExample PROPERTIES FOLDER "Examples")

message(STATUS "  Example: SyUtilityExample")
