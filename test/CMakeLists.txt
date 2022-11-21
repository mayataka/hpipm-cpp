# enable google test
include(gtest.cmake)

# macto for testing
macro(add_hpipm_test TESTNAME)
  add_executable(
    ${TESTNAME} 
    ${TESTNAME}.cpp
  )
  target_include_directories(
    ${TESTNAME} 
    PRIVATE
    ${GTEST_INCLUDE_PATH}
    ${GMOCK_INCLUDE_PATH}
    ${GTEST_LIBRARY_PATH}
    ${PROJECT_SOURCE_DIR}/include
    ${PINOCCHIO_INCLUDE_DIRS}
  )
  target_link_libraries(
    ${TESTNAME} 
    PRIVATE
    GTest::GTest
    GTest::GMock
    ${PROJECT_NAME}
  )
  add_dependencies(
    ${TESTNAME} 
    googletest
  )
  add_test(
    NAME ${TESTNAME} 
    COMMAND $<TARGET_FILE:${TESTNAME}>
  )
endmacro()

add_hpipm_test(d_ocp_qp_dim_wrapper)
add_hpipm_test(d_ocp_qp_sol_wrapper)
add_hpipm_test(d_ocp_qp_wrapper)
add_hpipm_test(d_ocp_qp_ipm_arg_wrapper)
add_hpipm_test(d_ocp_qp_ipm_ws_wrapper)