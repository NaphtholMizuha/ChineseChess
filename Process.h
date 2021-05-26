//
// Created by NaphtholMizuha on 2021/5/12.
//

#ifndef CHINESECHESS_PROCESS_H
#define CHINESECHESS_PROCESS_H
#include <iostream>
#include "graphic.h"
#include "Game.h"

using namespace std;

void showTitle(std::string = "请输入操作代号以进行操作:");
void clearScreen();
string space(int num);
void playGame(bool shouldLoad);

#endif //CHINESECHESS_GRAPHIC_H
