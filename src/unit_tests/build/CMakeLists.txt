cmake_minimum_required(VERSION 3.0)

project(unit_tests LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_COMPILER "/usr/bin/gcc")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -fprofile-arcs -ftest-coverage") 

file(GLOB_RECURSE SNAKE_MODEL
    "../../brick_game/snake/source/snakeModel.cpp"
)

file(GLOB_RECURSE SOURCE_FILES
    "../tests_entry.cpp"
    "../tests_snakeModel.cpp"
)

add_library(snakeModel STATIC ${SNAKE_MODEL})

# Create an executable target
add_executable(snake_test ${SOURCE_FILES})

# Add necessary libraries or dependencies
target_link_libraries(
    snake_test
    snakeModel
    -lstdc++ 
    -Wall 
    -Werror
    -Wextra
    -lgtest
    -lm
)

set_target_properties(
    snake_test
    PROPERTIES
    COMPILE_FLAGS "-fprofile-arcs -ftest-coverage"
    LINK_FLAGS "--coverage"
    ENABLE_TESTING TRUE
)