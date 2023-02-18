cmake_minimum_required(VERSION 3.16)

project(linux_file_io LANGUAGES CXX)

option(STATIC_ANALYSIS "Whether to automatically perform static analysis and code quality functions" ON)

add_executable( main main.cpp)

if( ${STATIC_ANALYSIS} )
    set( DEV_KIT_PATH ${CMAKE_CURRENT_LIST_DIR}/../../../dev-kit )
    set(CLANG_STYLE_PATH ${DEV_KIT_PATH}/clang-format )
    include(${DEV_KIT_PATH}/cmake/code-quality.cmake)
    run_code_quality_analysis( main ./ )
endif()

add_executable( benchmark benchmark.cpp)

if( ${STATIC_ANALYSIS} )
    set( DEV_KIT_PATH ${CMAKE_CURRENT_LIST_DIR}/../../../dev-kit )
    set(CLANG_STYLE_PATH ${DEV_KIT_PATH}/clang-format )
    include(${DEV_KIT_PATH}/cmake/code-quality.cmake)
    run_code_quality_analysis( benchmark ./ )
endif()

find_package(benchmark REQUIRED)
message("Google Benchmark Target:")
include(CMakePrintHelpers)
cmake_print_properties(TARGETS benchmark::benchmark PROPERTIES LOCATION INTERFACE_INCLUDE_DIRECTORIES)
target_link_libraries(benchmark benchmark::benchmark)
target_include_directories(benchmark PUBLIC benchmark::benchmark)
