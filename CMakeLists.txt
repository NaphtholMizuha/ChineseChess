cmake_minimum_required(VERSION 3.19)
project(ChineseChess)

set(CMAKE_CXX_STANDARD 17)

add_executable(ChineseChess main.cpp font.h mainPage.cpp mainPage.h Chessman.cpp Chessman.h graphic.cpp graphic.h)