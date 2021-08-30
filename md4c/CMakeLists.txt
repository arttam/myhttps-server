# MD4C Library thaks to https://github.com/mity/md4c
project(md4c)

set (BUILD_SHARED_LIBS ON)

# Version number 
set(MD_VERSION_MAJOR 0)
set(MD_VERSION_MINOR 4)
set(MD_VERSION_RELEASE 8)
set(MD_VERSION "${MD_VERSION_MAJOR}.${MD_VERSION_MINOR}.${MD_VERSION_RELEASE}")

# Build rules for MD4C parser library
add_library(${PROJECT_NAME} md4c.c md4c.h)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set_target_properties(${PROJECT_NAME} PROPERTIES
   COMPILE_FLAGS " -DMD4C_USE_UTF8"
    VERSION ${MD_VERSION}
    SOVERSION ${MD_VERSION_MAJOR}
    PUBLIC_HEADER md4c.h
)

# Build rules for HTML renderer library
add_library(${PROJECT_NAME}-html md4c-html.c md4c-html.h entity.c entity.h)
set_target_properties(${PROJECT_NAME}-html PROPERTIES
    VERSION ${MD_VERSION}
    SOVERSION ${MD_VERSION_MAJOR}
    PUBLIC_HEADER md4c-html.h
)
target_link_libraries(${PROJECT_NAME}-html ${PROJECT_NAME})
set_target_properties(${PROJECT_NAME}-html PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${PROJECT_NAME}-html PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)



