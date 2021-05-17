cmake_minimum_required(VERSION 3.17)
project(clear-logic)

set(CMAKE_CXX_STANDARD 11)


add_library(dependency
        src/libs/arifm_mirea.h
        src/libs/arifm_mirea.cpp
        )


add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} dependency)
