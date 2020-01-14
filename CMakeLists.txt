cmake_minimum_required(VERSION 3.7)
project(jnp1zad2)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_C_FLAGS_RELEASE)

set(SOURCE_FILES cdict cdictglobal dict.cc dict.h dictglobal.cc dictglobal.h)
add_executable(test2 non_existing_dicts.cc ${SOURCE_FILES})