cmake_minimum_required(VERSION 3.17)
project(GraphProject)

set(CMAKE_CXX_STANDARD 17)

add_library(graph_lib src/Graph.cpp)
target_include_directories(graph_lib PUBLIC include)

add_executable(main_app src/main.cpp)
target_link_libraries(main_app graph_lib)

add_subdirectory(googletest)

add_executable(test_app tests/test_graph.cpp)
target_link_libraries(test_app graph_lib gtest gtest_main)