include_directories(${SHADERPP_INCLUDE_DIR})

add_executable(test_shaderpp test_shaderpp.cpp)
target_link_libraries(test_shaderpp shaderpp)

add_executable(test_phong test_phong.cpp)
target_link_libraries(test_phong shaderpp)

include(CTest)
add_test(test_shaderpp test_shaderpp)
add_test(test_phong test_phong)