cmake_minimum_required(VERSION 3.1)

project(vh-compress)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(vh-compress main.cpp)

add_subdirectory(src)
target_link_libraries(vh-compress Haffman)

install(
    TARGETS vh-compress
    RUNTIME DESTINATION bin
)
