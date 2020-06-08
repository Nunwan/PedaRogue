cmake_minimum_required(VERSION 3.16)
project(PedaRogue)

get_filename_component(ROOT_DIR     ${CMAKE_CURRENT_LIST_FILE} PATH)
set(DOCS_DIR "${ROOT_DIR}/docs")

set(CMAKE_CXX_STANDARD 14)
include_directories(include/)
include_directories(src/win/include)

add_definitions(-Wl,-rpath -Wl,/usr/local/lib)
add_executable(PedaRogue src/main.cpp src/win/Window.cpp src/win/include/Window.hpp include/ECSTypes.hpp include/EntityManager.cpp include/EntityManager.hpp)
find_library(LIBTCOD NAMES libtcod.so PATHS /usr/local/lib)
target_link_libraries(PedaRogue ${LIBTCOD})

add_custom_target(doc doxygen ${DOCS_DIR}/Doxyfile WORKING_DIRECTORY ${ROOT_DIR})
