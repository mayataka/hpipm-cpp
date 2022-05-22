cmake_minimum_required(VERSION 3.1)
project(hpipm-cpp-examples CXX)

find_package(Eigen3 REQUIRED)
find_package(hpipm-cpp REQUIRED)

macro(add_example EXAMPLE)
  add_executable(
    ${EXAMPLE} 
    ${EXAMPLE}.cpp
  )
  target_include_directories(
    ${EXAMPLE} 
    PRIVATE
    ${EIGEN_INCLUDE_DIR}
    ${hpipm-cpp_INCLUDE_DIR}
  )
  target_link_libraries(
    ${EXAMPLE} 
    PRIVATE
    hpipm-cpp::hpipm-cpp
  )
endmacro()

add_example(example_ocp_qp)
add_example(example_mpc)
add_example(example_mpc_resize)