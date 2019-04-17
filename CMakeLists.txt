# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("pvi")

set (pvi_VERSION_MAJOR 1)
set (pvi_VERSION_MINOR 0)

set (SOURCE_DIR)

# Include sub-projects.
add_subdirectory ("src")
