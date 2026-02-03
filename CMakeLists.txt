cmake_minimum_required(VERSION 3.16)
project(UDPSocketClient C)

set(CMAKE_C_STANDARD 11)

find_package(PkgConfig REQUIRED)
find_package(PostgreSQL REQUIRED)

pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)

add_executable(UDPSocketClient
    src/main.c
    src/login/login.c
    src/db/conexao/conexao.c
    src/db/login/loginUser.c
    src/net/net.c
    src/render/render.c
    src/input/input.c
    src/game/game.c
)

# adicione os includes aqui
target_include_directories(UDPSocketClient PRIVATE 
    ${SDL2_INCLUDE_DIRS} 
    ${SDL2_TTF_INCLUDE_DIRS} 
    ${PostgreSQL_INCLUDE_DIRS}
)

# adds os links
target_link_libraries(UDPSocketClient PRIVATE 
    ${SDL2_LIBRARIES} 
    ${SDL2_TTF_LIBRARIES} 
    ${PostgreSQL_LIBRARIES} 
    m
)