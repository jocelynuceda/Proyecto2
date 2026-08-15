cmake_minimum_required(VERSION 4.0)
project(Proyecto_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(Proyecto_2
        main.cpp
        Enemy.h Enemy.cpp
        Tower.h Tower.cpp
        Camera.h Camera.cpp
        Map.h Map.cpp
        Game.h Game.cpp
)
