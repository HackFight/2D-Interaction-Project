cmake_minimum_required(VERSION 3.21.1)
project(glad)


add_library(glad)
target_include_directories(glad PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")
target_sources(glad PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c")