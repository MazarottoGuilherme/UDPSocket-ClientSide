cmake_minimum_required(VERSION 3.16)
project(UDPSocketClient C)

set(CMAKE_C_STANDARD 11)

find_package(PkgConfig REQUIRED)

pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)

add_executable(UDPSocketClient
    src/main.c
    src/login/login.c
    src/net/net.c
    src/render/render.c
    src/input/input.c
    src/game/game.c
)

target_include_directories(UDPSocketClient PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

target_link_libraries(UDPSocketClient PRIVATE ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES} m)