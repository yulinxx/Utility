add_executable(AprUtilityExample
    main.cpp
)

target_compile_features(AprUtilityExample PRIVATE cxx_std_17)

target_link_libraries(AprUtilityExample PRIVATE
    Utility
)

if(MSVC)
    target_compile_options(AprUtilityExample PRIVATE /utf-8)
endif()

set_target_properties(AprUtilityExample PROPERTIES FOLDER "Examples")

message(STATUS "  Example: AprUtilityExample")
