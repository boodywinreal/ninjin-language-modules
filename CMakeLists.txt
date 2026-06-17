# Main project data
cmake_minimum_required(VERSION 3.20)

project(carrot-ninjin-modules VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Project output directories
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/include)

# Math
add_library(nin-math SHARED src/math/math.cpp)

target_include_directories(nin-math PUBLIC head)
target_link_libraries(nin-math PRIVATE
  "-static-libgcc"
  "-static-libstdc++"
)
