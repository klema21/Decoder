cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_COMPILER "clang++")

project(Decoder)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
find_package(ICU 4.4 COMPONENTS io i18n REQUIRED)

include_directories(${ICU_INCLUDE_DIRS})

add_executable(decoder src/decode.cpp)
target_link_libraries(decoder ${ICU_LIBRARIES})