cmake_minimum_required(VERSION 3.16)

project(cyclic_queue LANGUAGES CXX)

# Set C++ standard to C++17 so that
# string_view can be used whenever possible
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(STATIC_ANALYSIS "Whether to automatically perform static analysis and code quality functions" ON)


enable_testing()
find_package(GTest REQUIRED)

# Tests for the CyclicQueue
set(CQTEST cyclic-queue-test)
add_executable( ${CQTEST} cyclic-queue-tests.cpp )
target_include_directories(${CQTEST} PUBLIC ${CMAKE_SOURCE_DIR}/src/common )
target_link_libraries(${CQTEST} GTest::gtest )

if( ${STATIC_ANALYSIS} )
    set( DEV_KIT_PATH ${CMAKE_CURRENT_LIST_DIR}/../../dev-kit )
    set(CLANG_STYLE_PATH ${DEV_KIT_PATH}/clang-format )
    include(${DEV_KIT_PATH}/cmake/code-quality.cmake)
    run_code_quality_analysis( ${CQTEST} ./ )
endif()


include(GoogleTest)
gtest_discover_tests(${CQTEST})
