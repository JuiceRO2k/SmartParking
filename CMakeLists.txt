cmake_minimum_required(VERSION 3.10)
# for MSVC: static link at C/C++ runtime
if (MSVC)
  # CMake ≥ 3.15
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
else()
  # for MinGW or other compilers, you can leave default or link static with -static
endif()
project(SmartParkingSystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB_RECURSE SOURCES
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

add_executable(SmartParking ${SOURCES})
