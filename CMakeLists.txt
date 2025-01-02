cmake_minimum_required(VERSION 3.12)
project(tetris C)

set(CMAKE_C_STANDARD 11)



set(SOURCES
    main.c 
    scenes/mainmenu/mainmenu.c
    utility/textrenderer/textrenderer.c
    utility/gamemanager/gamemanager.c
    interactions/events.c
    scenes/game/game.c
    scenes/game_over/game_over.c
    )

add_executable(sdlgame ${SOURCES})

find_package(SDL2 REQUIRED)


target_include_directories(sdlgame PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(sdlgame SDL2 SDL2_image SDL2_ttf)