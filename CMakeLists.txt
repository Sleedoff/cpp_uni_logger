cmake_minimum_required(VERSION 3.14)
project(cpp_uni_logger)

include_directories(${SOURCE_DIR}/Source
                    ${SOURCE_DIR}/Include
)       

set(INCLUDES_FILES 
    ${SOURCE_DIR}../Include/cpp_uni_logger.h
)

set(SOURCES_FILES
    ${SOURCE_DIR}../Source/cpp_uni_logger.cpp
)

add_executable(cpp_uni_logger ${SOURCES_FILES} ${INCLUDES_FILES})


