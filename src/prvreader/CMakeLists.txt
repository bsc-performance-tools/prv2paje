cmake_minimum_required(VERSION 2.8)
find_package(Boost REQUIRED)

project(prvreader)

file(GLOB_RECURSE SRC_FILES ${CMAKE_HOME_DIRECTORY}/src/prvreader/*.cpp)
set(HEADER_DIR ${CMAKE_HOME_DIRECTORY}/src/prvreader/headers)
file(GLOB HEADER_FILES ${HEADER_DIR}/*.h)
include_directories(${HEADER_DIR} ${Boost_INCLUDE_DIRS})

if(STATIC_OPT)
  add_library(${PROJECT_NAME} STATIC ${SRC_FILES} ${HEADER_FILES})
else()
  add_library(${PROJECT_NAME} SHARED ${SRC_FILES} ${HEADER_FILES})
endif()
add_definitions(-D__BUILD_VERSION__="${PRVSUITE_VERSION}")

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PRVSUITE_VERSION} SOVERSION ${PRVSUITE_VERSION_MAJOR})
set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)

set(${PROJECT_NAME}_INCLUDE_DIRS ${HEADER_DIR} ${Boost_INCLUDE_DIRS} CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES ${HEADER_FILES} DESTINATION include)
