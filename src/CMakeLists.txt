cmake_minimum_required(VERSION 3.10)
project(Review_Project)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
file(CREATE_LINK
    "${PROJECT_BINARY_DIR}/compile_commands.json"
    "${PROJECT_SOURCE_DIR}/compile_commands.json"
    SYMBOLIC
)

add_executable(Main main.cpp)
add_library(Ball ball.cpp)

target_include_directories(Main PRIVATE "${PROJECT_BINARY_DIR}/../include")
target_include_directories(Ball PRIVATE "${PROJECT_BINARY_DIR}/../include")
target_link_libraries(Main PUBLIC
    sfml-graphics
    sfml-window
    sfml-system
    Ball
)
