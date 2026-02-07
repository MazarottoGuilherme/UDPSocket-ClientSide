cmake_minimum_required(VERSION 3.16)
project(UDPSocketClient C)

set(CMAKE_C_STANDARD 11)

find_package(PkgConfig REQUIRED)

pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
pkg_check_modules(CJSON REQUIRED libcjson)

add_executable(UDPSocketClient
        src/main.c
        src/net/net.c
        src/render/render.c
        src/input/input.c
        src/engine/engine.c
        src/engine/engine.h
        src/screens/screen.c
        src/screens/screen.h
        src/screens/login/login.c
        src/screens/login/login.h
        src/config/Config.h
        src/render/render_objects.c
        src/render/render_objects.h
        src/game/game_state.c
        src/game/game_state.h
        src/screens/game/game.c
        src/screens/game/game.h
        src/render/tilemap.c
        src/render/tilemap.h
        src/map/map.c
        src/map/map.h
        src/map/map_loader.c
        src/map/map_loader.h
)

target_include_directories(UDPSocketClient PRIVATE
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIRS}
        ${CJSON_INCLUDE_DIRS}
)

target_link_libraries(UDPSocketClient PRIVATE
        ${SDL2_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
        ${CJSON_LIBRARIES}
        m
)
add_compile_definitions(ASSETS_DIR="${CMAKE_SOURCE_DIR}/assets")

