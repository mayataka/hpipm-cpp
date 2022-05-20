cmake_minimum_required(VERSION 3.11)
project(hpipm-cpp CXX)

set(CMAKE_CXX_STANDARD 17)

#############
## Options ##
#############
option(OPTIMIZE_FOR_NATIVE "Enable -march=native" OFF)
option(BUILD_TESTS "Build unit tests" OFF)

#############################
## Build blasfeo and hpipm ##
#############################
# add_subdirectory(external)
include(FetchContent)
include(ExternalProject)

# build blasfeo
set(BLASFEO_SRC_DIR ${PROJECT_SOURCE_DIR}/external/blasfeo)
# set(BLASFEO_DEST_DIR ${CMAKE_INSTALL_PREFIX})
set(BLASFEO_DEST_DIR ${PROJECT_SOURCE_DIR}/external/blasfeo_install)
set(BLASFEO_HEADERS_INSTALLATION_DIRECTORY ${PROJECT_SOURCE_DIR}/include/hpipm-cpp/blasfeo/include)

FetchContent_GetProperties(blasfeo)
if(NOT inekf_POPULATED)
  FetchContent_Populate(
    blasfeo
    GIT_REPOSITORY https://github.com/giaf/blasfeo.git 
    GIT_TAG        master
    GIT_SHALLOW    TRUE
    SOURCE_DIR ${BLASFEO_SRC_DIR})
endif()
ExternalProject_Add(
  blasfeo
  SOURCE_DIR ${BLASFEO_SRC_DIR}
  BUILD_IN_SOURCE TRUE
  INSTALL_DIR ${BLASFEO_DEST_DIR}
  CONFIGURE_COMMAND ${CMAKE_COMMAND} -DCMAKE_INSTALL_PREFIX=${BLASFEO_DEST_DIR} -DBLASFEO_HEADERS_INSTALLATION_DIRECTORY=${BLASFEO_HEADERS_INSTALLATION_DIRECTORY} -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DBUILD_SHARED_LIBS=ON -DBLASFEO_EXAMPLES=OFF -DCMAKE_POSITION_INDEPENDENT_CODE=ON -DLA=HIGH_PERFORMANCE 
)
add_library(hpipm-cpp-blasfeo SHARED IMPORTED)
set_target_properties(
  hpipm-cpp-blasfeo PROPERTIES 
  IMPORTED_LOCATION ${BLASFEO_DEST_DIR}/lib/libblasfeo.so
)

# build hpipm
set(HPIPM_SRC_DIR ${PROJECT_SOURCE_DIR}/external/hpipm)
# set(HPIPM_DEST_DIR ${CMAKE_INSTALL_PREFIX})
set(HPIPM_DEST_DIR ${PROJECT_SOURCE_DIR}/external/hpipm_install)
set(HPIPM_HEADERS_INSTALLATION_DIRECTORY ${PROJECT_SOURCE_DIR}/include/hpipm-cpp/hpipm/include)

FetchContent_GetProperties(hpipm)
if(NOT inekf_POPULATED)
  FetchContent_Populate(
    hpipm
    GIT_REPOSITORY https://github.com/giaf/hpipm.git 
    GIT_TAG        master
    GIT_SHALLOW    TRUE
    SOURCE_DIR ${HPIPM_SRC_DIR})
endif()
ExternalProject_Add(
  hpipm
  SOURCE_DIR ${HPIPM_SRC_DIR}
  BUILD_IN_SOURCE TRUE
  INSTALL_DIR ${HPIPM_DEST_DIR}
  CONFIGURE_COMMAND ${CMAKE_COMMAND} -DCMAKE_INSTALL_PREFIX=${HPIPM_DEST_DIR} -DHPIPM_HEADERS_INSTALLATION_DIRECTORY=${HPIPM_HEADERS_INSTALLATION_DIRECTORY} -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DBUILD_SHARED_LIBS=ON -DHPIPM_TESTING=OFF -DCMAKE_POSITION_INDEPENDENT_CODE=ON -DBLASFEO_PATH=${BLASFEO_DEST_DIR} -DBLASFEO_INCLUDE_DIR=${BLASFEO_HEADERS_INSTALLATION_DIRECTORY} 
)
add_dependencies(hpipm blasfeo)
add_library(hpipm-cpp-hpipm SHARED IMPORTED)
set_target_properties(
  hpipm-cpp-hpipm PROPERTIES 
  IMPORTED_LOCATION ${HPIPM_DEST_DIR}/lib/libhpipm.so
)

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
  hpipm-cpp-blasfeo
  hpipm-cpp-hpipm 
)
link_directories(
  ${BLASFEO_DEST_DIR}/lib
  ${HPIPM_DEST_DIR}/lib
)
target_include_directories(
  ${PROJECT_NAME} 
  PUBLIC
  ${EIGEN3_INCLUDE_DIR}
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/hpipm-cpp/blasfeo/include>
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/hpipm-cpp/hpipm/include>
  $<INSTALL_INTERFACE:include>
  $<INSTALL_INTERFACE:include/hpipm-cpp/blasfeo/include>
  $<INSTALL_INTERFACE:include/hpipm-cpp/hpipm/include>
)
if (OPTIMIZE_FOR_NATIVE)
  target_compile_options(
    ${PROJECT_NAME} 
    PUBLIC
    -march=native
  )
endif()
add_dependencies(
  ${PROJECT_NAME} 
  blasfeo 
  hpipm
)

#############
## Install ##
#############
include(GNUInstallDirs)
# Install lib files
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