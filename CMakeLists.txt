cmake_minimum_required(VERSION 3.15)

project(snake VERSION 1.0
        DESCRIPTION "My snake game!"
        LANGUAGES CXX)

add_executable(snake.exe
                main.cpp
                )

find_package(raylib REQUIRED)

target_link_libraries(snake.exe PRIVATE raylib)

set_property(TARGET snake.exe 
        PROPERTY RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")