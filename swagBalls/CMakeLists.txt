cmake_minimum_required(VERSION 3.26)
project(Game2)

set(CMAKE_CXX_STANDARD 17)

add_executable(Game2 main.cpp
        game.cpp
        game.h
        player.cpp
        player.h
        swagBall.cpp
        swagBall.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)


include_directories(c:/SFML/include)
target_link_libraries(Game2 sfml-system sfml-window sfml-graphics sfml-audio)