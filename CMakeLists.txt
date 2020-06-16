cmake_minimum_required(VERSION 3.16)
project(PedaRogue)

add_subdirectory(tests)

# PEDA ROGUE
get_filename_component(ROOT_DIR     ${CMAKE_CURRENT_LIST_FILE} PATH)
set(DOCS_DIR "${ROOT_DIR}/docs")

set(CMAKE_CXX_STANDARD 17)
include_directories(lib/BearLib/Include/C)
include_directories(include)
include_directories(src/win/include)

add_definitions(-Wl,-rpath -Wl,lib/BearLib/Linux64)
add_executable(PedaRogue src/main.cpp src/win/Window.cpp include/core/ECSManager.hpp src/Engine.cpp include/Engine.hpp src/Game.cpp include/Game.hpp src/systems/RenderSystem.cpp include/systems/RenderSystem.hpp include/Components.hpp src/InputHandler.cpp include/InputHandler.hpp src/systems/PlayerMovement.cpp include/systems/PlayerMovement.hpp include/Types.hpp)
add_library(PedaRogueLib src/win/Window.cpp src/Engine.cpp include/Engine.hpp src/Game.cpp include/Game.hpp src/systems/RenderSystem.cpp include/systems/RenderSystem.hpp include/Components.hpp src/InputHandler.cpp include/InputHandler.hpp src/systems/PlayerMovement.cpp include/systems/PlayerMovement.hpp include/Types.hpp)
find_library(BEARLIB NAMES libBearLibTerminal.so  PATHS lib/BearLib/Linux64)
target_link_libraries(PedaRogue ${BEARLIB})
target_link_libraries(PedaRogue gtest_main)

add_custom_target(doc doxygen ${DOCS_DIR}/Doxyfile WORKING_DIRECTORY ${ROOT_DIR})
