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


file(
        GLOB_RECURSE

        source_files

        src/*
        src/win/*
        src/systems/*
        tools/*
)
add_definitions(-Wl,-rpath -Wl,lib/BearLib/Linux64)
add_executable(PedaRogue ${source_files})
add_executable(Json tests/json_test.cpp)
add_library(PedaRogueLib ${source_files})
find_library(BEARLIB NAMES libBearLibTerminal.so  PATHS lib/BearLib/Linux64)
target_link_libraries(PedaRogue ${BEARLIB})
target_link_libraries(PedaRogue gtest_main)

add_custom_target(doc doxygen ${DOCS_DIR}/Doxyfile WORKING_DIRECTORY ${ROOT_DIR})
