cmake_minimum_required(VERSION 3.16)
set (CMAKE_CXX_COMPILER /usr/bin/clang++)

project(my_https_server CXX)

set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories("maddy")

file(GLOB SOURCES
    src/helpers.cpp
    src/server.cpp
    src/parser.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
target_link_libraries(${PROJECT_NAME} ssl crypto)
