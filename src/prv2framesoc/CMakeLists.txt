cmake_minimum_required(VERSION 2.8)
find_package(PkgConfig REQUIRED)

project(prv2framesoc CXX)

file(GLOB_RECURSE SRC_FILES ${CMAKE_HOME_DIRECTORY}/src/prv2framesoc/*.cpp)
set(HEADER_DIR ${CMAKE_HOME_DIRECTORY}/src/prv2framesoc/headers)
file(GLOB HEADER_FILES ${HEADER_DIR}/*.h)

include_directories(${HEADER_DIR} ${prvreader_INCLUDE_DIRS})

add_library(${PROJECT_NAME} STATIC ${SRC_FILES} ${HEADER_FILES})

add_definitions(-D__BUILD_VERSION__="${PRVSUITE_VERSION}")

target_link_libraries(${PROJECT_NAME} prvreader)

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PRVSUITE_VERSION} SOVERSION ${PRVSUITE_VERSION_MAJOR})

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
