cmake_minimum_required(VERSION 3.31)
project(atomic)

set(CMAKE_CXX_STANDARD 20)


add_executable(atomic main.cpp
        ../../val_categories/perfect_forwarding/main.cpp)