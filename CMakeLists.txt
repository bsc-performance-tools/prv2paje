cmake_minimum_required(VERSION 2.8)
include( ExternalProject )

set(CMAKE_VERBOSE_MAKEFILE OFF)

OPTION(PRV2PAJE_OPT "Paraver to Pajé trace formats converter" ON)
OPTION(STATIC_OPT "Generate static libraries" OFF)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(PRVSUITE_VERSION_MAJOR "1")
set(PRVSUITE_VERSION_MINOR "0")
set(PRVSUITE_VERSION_PATCH "0")
set(PRVSUITE_VERSION "${PRVSUITE_VERSION_MAJOR}.${PRVSUITE_VERSION_MINOR}.${PRVSUITE_VERSION_PATCH}")

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
  message(ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

# use, i.e. don't skip the full RPATH for the build tree
SET(CMAKE_SKIP_BUILD_RPATH  FALSE)

# when building, don't use the install RPATH already
# (but later on when installing)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE) 

SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)


# the RPATH to be used when installing, but only if it's not a system directory
LIST(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/lib" isSystemDir)
IF("${isSystemDir}" STREQUAL "-1")
   SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
ENDIF("${isSystemDir}" STREQUAL "-1")

if(PRV2PAJE_OPT)
  ExternalProject_Add(poti
    DOWNLOAD_COMMAND ""
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}
    SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/poti"
  )
  file(GLOB POTI_HEADERS ${CMAKE_BINARY_DIR}/include/*.h)
  file(GLOB POTI_LIB ${CMAKE_BINARY_DIR}/lib/*.so*)
  install(FILES ${POTI_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
  install(FILES ${POTI_LIB} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
endif()

ADD_SUBDIRECTORY(src)

#export(PACKAGE ${PROJECT_NAME})
file(GLOB SCRIPTS ${CMAKE_SOURCE_DIR}/scripts/*)
install(PROGRAMS ${SCRIPTS} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/config DESTINATION ${CMAKE_INSTALL_PREFIX})
add_custom_target(uninstall "${CMAKE_COMMAND}" -P "${CMAKE_MODULE_PATH}/uninstall.cmake")
