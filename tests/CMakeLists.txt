cmake_minimum_required(VERSION 3.16)

find_package(Catch2 REQUIRED)
include(Catch)

add_executable(termcontrol-tests
        test_control_sequence.cpp
    test_concepts.cpp
    test_color.cpp
        test_parse.cpp
    main.cpp)


target_link_libraries(termcontrol-tests
        Catch2::Catch2
        termcontrol
)

catch_discover_tests(termcontrol-tests)