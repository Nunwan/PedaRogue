cmake_minimum_required(VERSION 3.16)
project(PedaRogue)

set(CMAKE_CXX_STANDARD 14)
include_directories(include/)
include_directories(src/win/include)

add_definitions(-Wl,-rpath -Wl,/usr/local/lib)
add_executable(PedaRogue src/main.cpp src/win/Window.cpp src/win/include/Window.h)
find_library(LIBTCOD NAMES libtcod.so PATHS /usr/local/lib)
target_link_libraries(PedaRogue ${LIBTCOD})
