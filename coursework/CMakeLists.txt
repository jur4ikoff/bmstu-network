cmake_minimum_required(VERSION 3.20)

project(WebServer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(webserver
    src/main.cpp
    src/webserver/tcp_listener.cpp
)

target_include_directories(webserver
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(webserver PRIVATE -Wall -Wextra -Wpedantic)
endif()
