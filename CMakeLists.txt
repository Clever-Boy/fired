cmake_minimum_required(VERSION 2.8)
project(fired)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
include_directories("include" "include/meta")
include_directories("include/meta")
include_directories("include/common")

file(GLOB SRC "src/*/*.cpp")
add_executable(fired ${SRC})

target_link_libraries(fired sfml-system)
target_link_libraries(fired sfml-window)
target_link_libraries(fired sfml-graphics)
target_link_libraries(fired sfml-audio)
target_link_libraries(fired m)
target_link_libraries(fired sqlite3)
target_link_libraries(fired stdc++)

