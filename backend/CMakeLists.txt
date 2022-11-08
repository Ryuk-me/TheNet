
### Preamble ###
cmake_minimum_required(VERSION 3.14)
project(TheNet VERSION 1.0 LANGUAGES CXX)

# find_package(ZLIB)
##### Project wide setup ####
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

### Dependencies ###
add_subdirectory(dependencies)
include_directories(dependencies)

### Main Targets ###
add_subdirectory(src)