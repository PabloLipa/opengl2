cmake_minimum_required(VERSION 3.10)
project(progamOGL VERSION 3.3 LANGUAGES C CXX)
add_subdirectory(libs)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} glad glfw)