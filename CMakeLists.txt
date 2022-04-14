cmake_minimum_required(VERSION 3.0.0)
project(shaderpp VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
add_executable(shaderpp main.cpp)

add_subdirectory(test)
add_subdirectory(core)

target_link_libraries(shaderpp 
    core
)

include(CTest)
add_test(test_shaderpp test/test_shaderpp)