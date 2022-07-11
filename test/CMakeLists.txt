include_directories(${SHADERPP_INCLUDE_DIR})

add_executable(main main.cc)
target_link_libraries(main shaderpp)

include(CTest)
add_test(main main)