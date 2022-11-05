cmake_minimum_required(VERSION 3.16)

project(singleton LANGUAGES CXX)

option(COMPILE_TESTS "Whether to compile the unit tests which can be run with CTest" ON)

add_executable( singleton example.cpp)

if( ${COMPILE_TESTS} )
    enable_testing()

    find_package(GTest REQUIRED)

    add_executable( singleton_test singleton_test.cpp )
    target_link_libraries(singleton_test GTest::gtest)

    include(GoogleTest)
    gtest_discover_tests(singleton_test)
endif()
