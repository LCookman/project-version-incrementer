# CMakeList.txt : CMake project for pvi, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (pvi "main.cpp" "IProcessController.h"
"LinuxProcessController.cpp" "LinuxProcessController.h"
"WindowsProcessController.cpp" "WindowsProcessController.h"
"PviException.cpp" "PviException.h")

# TODO: Add tests and install targets if needed.
