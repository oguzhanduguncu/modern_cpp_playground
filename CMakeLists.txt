cmake_minimum_required(VERSION 3.20)

project(modern-cpp-playground
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_subdirectory(cpp20)
add_subdirectory(performance)
add_subdirectory(mini_projects)

# add_subdirectory(concurrency)
