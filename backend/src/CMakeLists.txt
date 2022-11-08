find_package(Boost 1.64.0 COMPONENTS system thread REQUIRED)

add_executable(TheNet main.cpp)

add_subdirectory(routes)
add_subdirectory(models)
add_subdirectory(utilities)

target_link_libraries(TheNet PUBLIC sqlite3)
