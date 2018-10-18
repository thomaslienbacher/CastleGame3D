cmake_minimum_required(VERSION 3.12)
project(CastleGame3D C)

set(CMAKE_C_STANDARD 11)

set(DEPENDENCIES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/)

include_directories(${DEPENDENCIES_DIR}TEngine/src/)
include_directories(${DEPENDENCIES_DIR}TEngine/dependencies/sdl2/include/)
include_directories(${DEPENDENCIES_DIR}TEngine/dependencies/glew/include/)

#define RELEASE_BUILD   //release build
#define DEBUG_BUILD     //debug build

if(${CMAKE_BUILD_TYPE} STREQUAL Release)
    add_definitions("-DRELEASE_BUILD")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mwindows -Wall -Wextra -pedantic")
elseif(${CMAKE_BUILD_TYPE} STREQUAL Debug)
    add_definitions("-DDEBUG_BUILD")
endif()

set(TENGINE_BUILD_USAGE Library)
add_subdirectory(dependencies/TEngine)

set(SOURCE_FILES src/main.c src/settings.c src/settings.h src/player.c src/player.h src/defs.h src/game.c src/game.h src/world.c src/world.h src/engine.c src/engine.h src/defs.c src/switch.c src/switch.h src/physics.c src/physics.h)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} TEngine)