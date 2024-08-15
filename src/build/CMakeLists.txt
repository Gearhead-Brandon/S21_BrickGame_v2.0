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

# Create an executable target
add_executable(brick_game ${SOURCE_FILES})

# Add necessary libraries or dependencies
target_link_libraries(
    brick_game
    Qt6::Core 
    Qt6::Gui 
    Qt6::Widgets
    -lstdc++ 
    -lncursesw
)