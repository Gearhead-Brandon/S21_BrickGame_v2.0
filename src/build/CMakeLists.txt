cmake_minimum_required(VERSION 3.0)

project(BrickGame LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_COMPILER "/usr/bin/gcc")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++ -Wall -Werror -Wextra -lncursesw") 

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# file(GLOB_RECURSE LIB_TETRIS
#     "../brick_game/tetris/source/*.c"
#     "../brick_game/tetris/source/**/*.c"

#     "../components/Wrappers/Tetris/TetrisModel.cpp"
# )

# file(GLOB_RECURSE LIB_SNAKE
#     "../brick_game/snake/source/*.cpp"
# )

# file(GLOB_RECURSE LIB_MATRIX
#     "../components/matrix/*.c"
# )

# file(GLOB_RECURSE LIB_CLI
#     "../gui/cli/*.c"
#     "../components/Wrappers/Cli/*.cpp"
# )

# file(GLOB_RECURSE LIB_DESKTOP
#     "../gui/desktop/*.cpp"
#     "../components/Wrappers/Desktop/*.cpp"
# )

# file(GLOB_RECURSE LIB_INPUT
#     "../components/Input/*.cpp"
# )

file(GLOB_RECURSE SOURCE_FILES
    "../main.cpp"
    "../brick_game/**/**/*.c"
    "../brick_game/**/**/*.cpp"
    "../gui/**/*.c"
    "../gui/**/*.cpp"
    "../components/**/*.c"
    "../components/**/*.cpp"
    "../components/**/**/*.cpp"
)

#Create a library target
# add_library(tetris STATIC ${LIB_TETRIS})
# add_library(snake STATIC ${LIB_SNAKE})

# add_library(cli_ui STATIC ${LIB_CLI})

# add_library(desktop_ui STATIC ${LIB_DESKTOP})
# target_link_libraries(desktop_ui Qt6::Core Qt6::Gui Qt6::Widgets)

# add_library(matrix STATIC ${LIB_MATRIX})

# add_library(input STATIC ${LIB_INPUT})
# target_link_libraries(input Qt6::Widgets)

# Create an executable target
add_executable(brick_game ${SOURCE_FILES})

# Add necessary libraries or dependencies
target_link_libraries(
    brick_game
    Qt6::Core 
    Qt6::Gui 
    Qt6::Widgets
    # tetris 
    # snake
    # cli_ui
    # desktop_ui
    # input
    # matrix
    -lstdc++ 
    -lncursesw
)

# Install the executable
#install(TARGETS brick_game RUNTIME DESTINATION ./out/)