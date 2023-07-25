cmake_minimum_required(VERSION 3.22)

add_subdirectory(SDL)



include_directories(    
                        SDL/include
                        bgfx/include
                        bx/include
                        bimg/include
                        ${OpenCV_INCLUDE_DIRS}
                        ${OPENGL_INCLUDE_DIRS}
                        ${X11_INCLUDE_DIR}
                        )