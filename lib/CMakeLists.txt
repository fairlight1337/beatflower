cmake_minimum_required(VERSION 2.8.12)
project(BeatFlower)

set(${PROJECT_NAME}_VERSION_MAJOR_0)
set(${PROJECT_NAME}_VERSION_MINOR_1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

include_directories(
  ${PROJECT_SOURCE_DIR}/include/)

add_executable(${PROJECT_NAME}-demo
  src/demo.cpp)

file(GLOB_RECURSE LIB_SOURCE "src/beatflower/*.cpp")
add_library(${PROJECT_NAME}
  ${LIB_SOURCE})

target_link_libraries(${PROJECT_NAME}-demo
  ${PROJECT_NAME})
