cmake_minimum_required(VERSION 3.30)

project(Raycing)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

foreach(package fmt raylib)
    find_package(${package} CONFIG REQUIRED)
endforeach()

add_executable(main main.cpp)

target_link_libraries(main PRIVATE fmt::fmt raylib)
