cmake_minimum_required(VERSION 3.22)

configure_file(${CMAKE_CURRENT_LIST_DIR}/config.cmake ${CMAKE_BINARY_DIR}/config.cmake COPYONLY)

add_subdirectory(tvm)