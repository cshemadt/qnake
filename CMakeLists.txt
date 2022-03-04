cmake_minimum_required(VERSION 3.0)
project(znake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++17 -Wall")
set(SOURCES textbox.cpp textbox.h world.h world.cpp main.cpp snake.h snake.cpp game.h game.cpp window.h window.cpp)
find_package(SFML 2.5.1 COMPONENTS graphics audio network REQUIRED)
include_directories(${SFML_INCLUDE_DIR})
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE sfml-audio  sfml-network sfml-graphics)
