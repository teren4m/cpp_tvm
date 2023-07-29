cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(cpp_tvm)

find_package(OpenCV REQUIRED)

add_subdirectory(3rdparty)


include_directories(    
                        ${CMAKE_CURRENT_LIST_DIR}/include
                        ${OpenCV_INCLUDE_DIRS}
                        ${CMAKE_CURRENT_LIST_DIR}/3rdparty/tvm/include
                        ${CMAKE_CURRENT_LIST_DIR}/3rdparty/tvm/3rdparty/dmlc-core/include
                        ${CMAKE_CURRENT_LIST_DIR}/3rdparty/tvm/3rdparty/dlpack/include
                        ${CMAKE_CURRENT_LIST_DIR}/3rdparty/tvm/3rdparty/cnpy/include
                        )

add_executable(
                cpp_tvm 
                src/main.cpp
                src/receipt_nn.cpp
                src/tvm_runner.cpp
                src/tvm_utils.cpp
                )

target_link_libraries(cpp_tvm 
                                ${OpenCV_LIBS} 
                                tvm
                                tvm_runtime
                                )
