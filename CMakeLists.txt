cmake_minimum_required(VERSION 3.16.9)
project(gosdk VERSION 0.1.0)

file(GLOB_RECURSE SRC
        "${PROJECT_SOURCE_DIR}/gosdk/*.cpp"
        "${PROJECT_SOURCE_DIR}/gosdk/*.hpp"
        )

add_library(gosdk SHARED ${SRC})

set_property(TARGET gosdk PROPERTY CXX_STANDARD 17)
set_property(TARGET gosdk PROPERTY CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-DNOMINMAX")