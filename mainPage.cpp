//
// Created by NaphtholMizuha on 2021/5/12.
//

#include "mainPage.h"
void showTitle(std::string info) {
    cout << SEPERATOR << endl<< CHINESS_CHESS << endl << SEPERATOR << endl;
    cout << space(16) << "1.开始游戏" << space(16) << endl;
    cout << space(16) << "2.载入游戏" << space(16) << endl;
    cout << space(16) << "3.退出游戏" << space(16) << endl;
    cout << SEPERATOR << endl;
    cout << info;
}

void clearScreen() {
    cout << "\033[2J" << endl;
}





