cmake_minimum_required(VERSION 3.26)
project(pingPongICG)

set(CMAKE_CXX_STANDARD 23)

add_executable(pingPongICG main.cpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

target_link_libraries(pingPongICG OpenGL::GL GLUT::GLUT GLU)