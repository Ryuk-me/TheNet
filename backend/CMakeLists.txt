
### Preamble ###
cmake_minimum_required(VERSION 3.14)
project(TheNet VERSION 1.0 LANGUAGES CXX)

# find_package(ZLIB)
##### Project wide setup ####
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread  -lsqlite3")

### Dependencies ###
add_subdirectory(dependencies)
include_directories(dependencies)

### Main Targets ###
add_subdirectory(src)

# target_link_libraries(TheNet LINK_PUBLIC sqlite3)