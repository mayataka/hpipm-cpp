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
set(BLASFEO_INSTALL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/external/blasfeo-install)
set(HPIPM_INSTALL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/external/hpipm-install)

#####################
## Build hpipm-cpp ##
#####################
set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib)
# find Eigen
find_package(Eigen3 REQUIRED)

file(GLOB_RECURSE ${PROJECT_NAME}_SOURCES src/*.cpp)
file(GLOB_RECURSE ${PROJECT_NAME}_HEADERS include/${PROJECT_NAME}/*.h*)
add_library(
  ${PROJECT_NAME} 
  SHARED
  ${${PROJECT_NAME}_SOURCES} 
  ${${PROJECT_NAME}_HEADERS}
)
target_link_libraries(
  ${PROJECT_NAME} 
  PUBLIC
  $<BUILD_INTERFACE:${BLASFEO_INSTALL_PATH}/lib/libblasfeo.so>
  $<BUILD_INTERFACE:${HPIPM_INSTALL_PATH}/lib/libhpipm.so>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_RPATH}/hpipm-cpp/libblasfeo.so>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_RPATH}/hpipm-cpp/libhpipm.so>
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