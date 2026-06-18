# -Main project-
cmake_minimum_required(VERSION 3.20)

project(carrot-ninjin-modules VERSION 1.5 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Shared libraries destination
set(NIN_DESTINATION "$ENV{HOME}/.config/lib/carrot/CAPI")

# Project output directories
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# -Modules-
# Math
add_library(nin-math SHARED src/math/main.cpp)

target_include_directories(nin-math PUBLIC head)
target_link_libraries(nin-math PRIVATE
  "-static-libgcc"
  "-static-libstdc++"
)

# IO
add_library(nin-io SHARED src/io/main.cpp)

target_include_directories(nin-io PUBLIC head)
target_link_libraries(nin-io PRIVATE
  "-static-libgcc"
  "-static-libstdc++"
)

# -Installation-
# Math
add_custom_command(
  TARGET nin-math
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory "${NIN_DESTINATION}"
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:nin-math> "${NIN_DESTINATION}"
)

# IO
add_custom_command(
  TARGET nin-io
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory "${NIN_DESTINATION}"
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:nin-io> "${NIN_DESTINATION}"
)