cmake_minimum_required(VERSION 3.18)
project(cpp_uni_logger)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Specify header and source files
set(INCLUDES_FILES 
    ${SOURCE_DIR}/Include/cpp_uni_logger.h
)

set(SOURCES_FILES 
    ${SOURCE_DIR}/Source/cpp_uni_logger.cpp
)

add_library(cpp_uni_logger STATIC ${SOURCES_FILES})

target_include_directories(cpp_uni_logger PUBLIC
    ${SOURCE_DIR}/Include
)

target_include_directories(cpp_uni_logger PRIVATE
    ${SOURCE_DIR}/Source
)