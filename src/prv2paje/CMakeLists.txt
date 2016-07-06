cmake_minimum_required(VERSION 2.8)
find_package(PkgConfig REQUIRED)

project(prv2paje)

file(GLOB_RECURSE SRC_FILES ${CMAKE_HOME_DIRECTORY}/src/prv2paje/*.cpp)
set(HEADER_DIR ${CMAKE_HOME_DIRECTORY}/src/prv2paje/headers)
file(GLOB HEADER_FILES ${HEADER_DIR}/*.h)

include_directories(${HEADER_DIR} ${prvreader_INCLUDE_DIRS} "${CMAKE_BINARY_DIR}/include")

add_executable(${PROJECT_NAME} ${SRC_FILES} ${HEADER_FILES})

add_definitions(-D__BUILD_VERSION__="${PRVSUITE_VERSION}")

target_link_libraries(${PROJECT_NAME} "${CMAKE_BINARY_DIR}/lib/libpoti.so" prvreader)

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PRVSUITE_VERSION} SOVERSION ${PRVSUITE_VERSION_MAJOR})

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
