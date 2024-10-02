cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_COMPILER "clang++")
set(Required_Icu_Version 63)

project(Decoder VERSION 1.0)

# include(FindICU)
# find_package(ICU ${Required_Icu_Version} OPTIONAL_COMPONENTS uc i18n)

#set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
#find_package(ICU 4.4 COMPONENTS io i18n REQUIRED)

#include_directories(${ICU_INCLUDE_DIRS})

add_subdirectory(external/icu-cmake)

add_executable(decoder src/decode.cpp)

#target_link_libraries(decoder external/icu-cmake)
target_link_libraries(decoder icu)