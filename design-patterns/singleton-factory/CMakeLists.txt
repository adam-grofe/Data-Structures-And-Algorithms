cmake_minimum_required(VERSION 3.16)

project(singleton LANGUAGES CXX)

option(COMPILE_TESTS "Whether to compile the unit tests which can be run with CTest" ON)
option(STATIC_ANALYSIS "Whether to automatically perform static analysis and code quality functions" ON)

add_executable( singleton example.cpp)

if( ${STATIC_ANALYSIS} )
    set( DEV_KIT_PATH ${CMAKE_CURRENT_LIST_DIR}/../../dev-kit )
    set(CLANG_STYLE_PATH ${DEV_KIT_PATH}/clang-format )
    include(${DEV_KIT_PATH}/cmake/code-quality.cmake)
    run_code_quality_analysis( singleton ./ )
endif()

if( ${COMPILE_TESTS} )
    enable_testing()

    find_package(GTest REQUIRED)

    add_executable( singleton_test singleton_test.cpp )
    target_link_libraries(singleton_test GTest::gtest GTest::gtest_main)

    include(GoogleTest)
    gtest_discover_tests(singleton_test)
endif()
