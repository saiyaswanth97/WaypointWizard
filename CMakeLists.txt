cmake_minimum_required(VERSION 3.29)
project(rrt_star)

set(CMAKE_CXX_STANDARD 17)

add_executable(rrt_star src/main.cpp
        include/primitives.h
        src/primitives.cpp
        include/smoother.h

)
add_executable(smoother_checker src/main_smoother.cpp
        include/smoother.h
        src/smoother.cpp
)

