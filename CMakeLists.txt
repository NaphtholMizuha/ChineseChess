cmake_minimum_required(VERSION 3.19)
project(ChineseChess)

set(CMAKE_CXX_STANDARD 17)

add_executable(ChineseChess main.cpp Chessman.cpp Chessman.h Process.cpp graphic.h Game.cpp Game.h)