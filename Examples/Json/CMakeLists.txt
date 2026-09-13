cmake_minimum_required(VERSION 3.15)
project(MyProject)

# 1. Define your executable target
add_executable(example-1 
                ${CMAKE_CURRENT_SOURCE_DIR}/../../src/json/parser.cpp
                eg-01.cpp)

# 2. Add your include directories to that target
target_include_directories(example-1 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../include/)