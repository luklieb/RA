# How to use CMake on Linux with GNU Makefile backend:
#   - Use a separate build folder for intermediate files
#       mkdir build && cd build
#       cmake ..
#       make
#   - you can configure the project for Debug or Release mode by running a cmake GUI in the build folder:
#       cd build
#     then either
#       ccmake . 
#     or 
#       cmake-gui .
#
# There are more generators available, for example for Eclipse, Visual Studio, Ninja, ....
# You can list all available generators with "cmake -G"
#

# add this line to prevent CMake warning: it specifies the minimum cmake version which is required 
# to build this project
cmake_minimum_required(VERSION 3.0.2)  

# enable c++11 support
#set (CMAKE_CXX_STANDARD 11)

#set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -DLIKWID_PERFMON")
set(CMAKE_CXX_FLAGS "-Wall -std=c++11")
set(CMAKE_EXE_LINKER_FLAGS "-llikwid -pthread")
include_directories(/apps/likwid/system/include/)
link_directories(/apps/likwid/system/lib/)

# add a single executable


add_executable(cacheSim main.cpp sum.cpp cacheLine.cpp)

