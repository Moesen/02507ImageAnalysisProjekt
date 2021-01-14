cmake_minimum_required(VERSION 3.3)

project(CmakeTest VERSION 1.0
                  DESCRIPTION "Getting pointing to"
                  LANGUAGES CXX)

set(HEADERS
    ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/include/print.h)

add_executable(Main ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp ${HEADERS})