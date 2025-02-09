cmake_minimum_required(VERSION 3.21.1)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebug$<$<CONFIG:Debug>:Debug>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")

add_subdirectory("thirdparty/glfw")
add_subdirectory("thirdparty/glad")

project(Interaction2D)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(Interaction2D "${MY_SOURCES}")


target_compile_definitions("${PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/") # This is for debug
#target_compile_definitions("${PROJECT_NAME}" PUBLIC RESOURCES_PATH="./resources/") # Uncomment this before shipping


target_include_directories(Interaction2D PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")
target_link_libraries(Interaction2D PRIVATE glfw glad)