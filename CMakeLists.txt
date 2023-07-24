cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(cpp_tvm)

add_subdirectory(SDL)

find_package(OpenCV REQUIRED )
include_directories(
                        ${OpenCV_INCLUDE_DIRS}
                        SDL/include
                        )

add_executable(cpp_tvm main.cpp)

target_link_libraries(cpp_tvm 
                                ${OpenCV_LIBS} 
                                SDL3::SDL3
                                )


