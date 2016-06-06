cmake_minimum_required(VERSION 2.8)
find_package(PkgConfig)
find_package(Boost REQUIRED)

PKG_CHECK_MODULES(POTI REQUIRED poti>=4)



file(GLOB_RECURSE SRC_FILES ${CMAKE_HOME_DIRECTORY}/src/prv2paje/*.cpp)
set(HEADER_DIR ${CMAKE_HOME_DIRECTORY}/src/prv2paje/headers)
file(GLOB HEADER_FILES ${HEADER_DIR}/*.h)
include_directories(${HEADER_DIR} ${POTI_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})

link_directories(${POTI_LIBRARY_DIRS})

add_executable(${PROJECT_NAME} ${SRC_FILES} ${HEADER_FILES})

add_definitions(-D__BUILD_VERSION__="${PRV2PAJE_VERSION}")

target_link_libraries(${PROJECT_NAME} ${POTI_LIBRARIES} ${Boost_LIBRARIES})

target_compile_options(${PROJECT_NAME} PUBLIC ${POTI_CFLAGS_OTHER})

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PRV2PAJE_VERSION} SOVERSION ${PRV2PAJE_VERSION_MAJOR})

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
