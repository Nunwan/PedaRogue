project(Google_tests)
add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(../include ../src/win/include)

add_executable(Google_Tests_run Test.cpp Test_ComponentManager.cpp Test_ComponentManager.cpp Test_EntityManager.cpp Test_ComponentPool.cpp)
target_link_libraries(Google_Tests_run gtest gtest_main PedaRogueLib)
