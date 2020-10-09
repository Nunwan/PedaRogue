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
include_directories(tools/include)

set(SOURCES_FILES   src/CommandProcessor.cpp src/Engine.cpp src/FOVTools.cpp src/Game.cpp src/InputHandler.cpp src/Inventory.cpp
                    src/Level.cpp src/LevelGeneration.cpp src/main.cpp src/ProcessEvents.cpp src/UI.cpp src/UI_List.cpp
                    src/win/Window.cpp src/systems/AttackSystem.cpp src/systems/BackSystem.cpp src/systems/CollisionSystem.cpp
                    src/systems/FoVCompute.cpp src/systems/LightSystem.cpp src/systems/PickSystem.cpp src/systems/PlayerMovement.cpp
                    src/systems/RenderSystem.cpp tools/MonsterParse.cpp tools/ObjectParse.cpp src/ItemCommands.cpp src/systems/DropSystem.cpp include/systems/DropSystem.hpp)


add_definitions(-Wl,-rpath -Wl,lib/BearLib/Linux64)
add_executable(PedaRogue ${SOURCES_FILES} )
add_executable(Json tests/json_test.cpp )
add_library(PedaRogueLib ${SOURCES_FILES})
find_library(BEARLIB NAMES libBearLibTerminal.so  PATHS lib/BearLib/Linux64)
target_link_libraries(PedaRogue ${BEARLIB})
target_link_libraries(PedaRogue gtest_main)

add_custom_target(doc doxygen ${DOCS_DIR}/Doxyfile WORKING_DIRECTORY ${ROOT_DIR})
