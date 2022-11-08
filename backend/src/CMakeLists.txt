find_package(Boost 1.64.0 COMPONENTS system thread REQUIRED)

add_executable(TheNet main.cpp)

add_subdirectory(routes)
add_subdirectory(models)
# add_subdirectory(utilities)

# list(APPEND REQUIRED_LIBRARIES 
#   ${Boost_LIBRARIES}
#   ${CMAKE_THREAD_LIBS_INIT}
#   ZLIB::ZLIB
#   sqlpp11::sqlpp11
#   sqlpp11-connector-sqlite3
#   cryptopp-shared
# )

# target_compile_options(Forest PRIVATE "${compiler_options}")
# target_link_libraries(Forest PUBLIC ${REQUIRED_LIBRARIES})
target_link_libraries(TheNet PUBLIC sqlite3)
