cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(cpp_tvm)

find_package(OpenCV REQUIRED)
find_package(OpenGL REQUIRED)
find_package(X11 REQUIRED)
find_package(Threads REQUIRED)

add_subdirectory(3rdparty)


include_directories(    
                        3rdparty/SDL/include
                        3rdparty/bgfx/include
                        3rdparty/bx/include
                        3rdparty/bimg/include
                        ${OpenCV_INCLUDE_DIRS}
                        ${OPENGL_INCLUDE_DIRS}
                        ${X11_INCLUDE_DIR}
                        )

add_executable(
                cpp_tvm 
                src/main.cpp
                )

target_link_libraries(cpp_tvm 
                                ${OPENGL_LIBRARIES}
                                ${X11_LIBRARIES}
                                ${OpenCV_LIBS} 
                                SDL3::SDL3
                                pthread
                                rt
                                dl
                                ${CMAKE_SOURCE_DIR}/3rdparty/bgfx/.build/linux64_gcc/bin/libbgfxRelease.a
                                )


