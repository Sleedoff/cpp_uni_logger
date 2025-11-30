cmake_minimum_required(VERSION 3.14)
set (CMAKE_CXX_STANDARD 20)
project(cpp_uni_logger)

# Set the source and include directories
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${SOURCE_DIR}/Source
                    ${SOURCE_DIR}/../Source
                    ${SOURCE_DIR}/../Include
)

# Specify header and source files
set(INCLUDES_FILES 
    ${SOURCE_DIR}/../Include/cpp_uni_logger.h
)

set(SOURCES_FILES 
    ${SOURCE_DIR}/Source/main.cpp
    ${SOURCE_DIR}/../Source/cpp_uni_logger.cpp
)

# Create the executable
add_executable(cpp_uni_logger ${SOURCES_FILES} ${INCLUDES_FILES})


