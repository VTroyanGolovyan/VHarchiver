cmake_minimum_required(VERSION 3.1)

project(Archiver)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(Archiver main.cpp)

add_subdirectory(src)
target_link_libraries(Archiver Haffman)

install(
    TARGETS Archiver
    RUNTIME DESTINATION bin
)
