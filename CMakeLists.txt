cmake_minimum_required(VERSION 3.16)
project(PedaRogue)

add_subdirectory(tests)

# PEDA ROGUE
get_filename_component(ROOT_DIR     ${CMAKE_CURRENT_LIST_FILE} PATH)
set(DOCS_DIR "${ROOT_DIR}/docs")

set(CMAKE_CXX_STANDARD 17)
include_directories(include/)
include_directories(src/win/include)

add_definitions(-Wl,-rpath -Wl,/usr/local/lib)
add_executable(PedaRogue src/main.cpp src/win/Window.cpp include/core/ComponentManager.hpp include/core/SystemManager.hpp)
add_library(PedaRogueLib src/win/Window.cpp)
find_library(LIBTCOD NAMES libtcod.so PATHS /usr/local/lib)
target_link_libraries(PedaRogue ${LIBTCOD})
target_link_libraries(PedaRogue gtest_main)

add_custom_target(doc doxygen ${DOCS_DIR}/Doxyfile WORKING_DIRECTORY ${ROOT_DIR})
