cmake_minimum_required(VERSION 3.12)
project(tetris C)

set(CMAKE_C_STANDARD 11)

add_compile_options(-lm -fsanitize=address)
add_link_options(-lm -fsanitize=address)

set(SOURCES
    main.c 
    scenes/mainmenu/mainmenu.c
    utility/textrenderer/textrenderer.c
    utility/gamemanager/gamemanager.c
    interactions/events.c
    scenes/game/game.c
    scenes/game_over/game_over.c
    )

add_executable(Tetris ${SOURCES})

find_package(SDL2 REQUIRED)


target_include_directories(Tetris PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(Tetris SDL2 SDL2_image SDL2_ttf)