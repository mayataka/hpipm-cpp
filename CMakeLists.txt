cmake_minimum_required(VERSION 3.11)
project(hpipm-cpp CXX)
set(CMAKE_CXX_STANDARD 11)

#############
## Options ##
#############
option(OPTIMIZE_FOR_NATIVE "Enable -march=native" OFF)
option(BUILD_TESTS "Build unit tests" OFF)


#############################
## Build blasfeo and hpipm ##
#############################
add_subdirectory(external)
set(BLASFEO_INSTALL_PATH ${PROJECT_SOURCE_DIR}/external/blasfeo-install)
set(HPIPM_INSTALL_PATH ${PROJECT_SOURCE_DIR}/external/hpipm-install)

#####################
## Build hpipm-cpp ##
#####################
set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib)
# find Eigen
find_package(Eigen3 REQUIRED)

add_library(
  ${PROJECT_NAME} 
  SHARED
  src/d_ocp_qp_dim_wrapper.cpp
  src/d_ocp_qp_wrapper.cpp
  src/d_ocp_qp_sol_wrapper.cpp
  src/d_ocp_qp_ipm_arg_wrapper.cpp
  src/d_ocp_qp_ipm_ws_wrapper.cpp
  src/ocp_qp_dim.cpp
  src/ocp_qp_ipm_solver_settings.cpp
  src/ocp_qp_ipm_solver_statistics.cpp
  src/ocp_qp_ipm_solver.cpp
)
target_link_libraries(
  ${PROJECT_NAME} 
  PUBLIC
  ${BLASFEO_INSTALL_PATH}/lib/libblasfeo.so
  ${HPIPM_INSTALL_PATH}/lib/libhpipm.so
)
target_include_directories(
  ${PROJECT_NAME} 
  PUBLIC
  ${EIGEN3_INCLUDE_DIR}
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/hpipm-cpp/blasfeo>
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/hpipm-cpp/hpipm>
  $<INSTALL_INTERFACE:include>
  $<INSTALL_INTERFACE:include/hpipm-cpp/blasfeo>
  $<INSTALL_INTERFACE:include/hpipm-cpp/hpipm>
)
if (OPTIMIZE_FOR_NATIVE)
  target_compile_options(
    ${PROJECT_NAME} 
    PUBLIC
    -march=native
  )
endif()
add_dependencies(${PROJECT_NAME} external_hpipm external_blasfeo)

#############
## Testing ##
#############
# Add testing directory
if (BUILD_TESTS)
  enable_testing()
  # coverage options
  set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} --coverage")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
  add_library(coverage_config INTERFACE)
  if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(coverage_config INTERFACE
      -O0        
      -g         
      --coverage 
    )
    if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
      target_link_options(coverage_config INTERFACE --coverage)
    else()
      target_link_libraries(coverage_config INTERFACE --coverage)
    endif()
  endif()
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
endif() # end if (BUILD_TESTS)

#############
## Install ##
#############
include(GNUInstallDirs)
# Install lib files
install(
  FILES ${BLASFEO_INSTALL_PATH}/lib/libblasfeo.so ${HPIPM_INSTALL_PATH}/lib/libhpipm.so
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}
)
install(
  TARGETS ${PROJECT_NAME}  
  EXPORT ${PROJECT_NAME}-config
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}
)
# Install header files
install(
  DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
)
# Install config file 
set(CONFIG_PACKAGE_LOCATION "share/${PROJECT_NAME}/cmake")
install(
  EXPORT ${PROJECT_NAME}-config
  FILE ${PROJECT_NAME}-config.cmake
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION ${CONFIG_PACKAGE_LOCATION}
)
# Install alias
add_library(
  ${PROJECT_NAME}::${PROJECT_NAME} 
  ALIAS ${PROJECT_NAME}
)
