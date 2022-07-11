cmake_minimum_required(VERSION 3.0.0)
project(shaderpp VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(SHADERPP_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

file(GLOB SOURCE_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/types/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cc"
)

add_library(shaderpp STATIC ${SOURCE_FILES})
target_include_directories(shaderpp
    PUBLIC ${SHADERPP_INCLUDE_DIR})

include(CTest)
add_subdirectory(test)
