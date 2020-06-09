cmake_minimum_required(VERSION 3.5)

project(TEST_ENGINE LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(run.exe
    src/main.cpp
)

include_directories(headers)