cmake_minimum_required(VERSION 3.12)
project(CastleGame3D C)

set(CMAKE_C_STANDARD 11)

set(DEPENDENCIES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/)

if (${CMAKE_BUILD_TYPE} STREQUAL Release)
    add_definitions("-DRELEASE_BUILD")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mwindows -Wall -Wextra")
elseif (${CMAKE_BUILD_TYPE} STREQUAL Debug)
    add_definitions("-DDEBUG_BUILD")
endif ()

add_subdirectory(dependencies/TEngine)

set(SOURCE_FILES src/main.c src/settings.c src/settings.h src/player.c src/player.h src/defs.h src/game.c src/game.h src/world.c src/world.h src/engine.c src/engine.h src/defs.c src/iswitch.c src/iswitch.h src/physics.c src/physics.h src/platform.c src/platform.h src/jewel.c src/jewel.h)
add_executable(CastleGame3D ${SOURCE_FILES})

target_include_directories(CastleGame3D PUBLIC ${DEPENDENCIES_DIR}TEngine/src/)
target_link_libraries(CastleGame3D TEngine)
