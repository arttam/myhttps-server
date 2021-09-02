cmake_minimum_required(VERSION 3.16)
set (CMAKE_CXX_COMPILER /usr/bin/clang++)
set (CMAKE_C_COMPILER /usr/bin/clang)

project(mirri CXX)

set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# RPATH
set (CMAKE_SKIP_BUILD_RPATH  FALSE)
set (CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set (CMAKE_INSTALL_RPATH "$\{ORIGIN\}")

add_subdirectory(md4c)

include_directories("md4c")

file(GLOB SOURCES
    src/helpers.cpp
    src/server.cpp
    src/parser.cpp
    src/resource.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
#set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-Wl,-rpath,'$ORIGIN'")
target_link_libraries(${PROJECT_NAME} ssl crypto md4c-html)
