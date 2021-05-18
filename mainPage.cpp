//
// Created by NaphtholMizuha on 2021/5/12.
//

#include "mainPage.h"
void showTitle(std::string info) {
    cout << SEPERATOR << endl<< space(10)
        << RED_WORD << " 中国" << BLUE_WORD << "象棋 " << DEFAULT_WORD
        << space(10) << endl << SEPERATOR << endl;
    cout << space(10) << "1.开始游戏" << space(10) << endl;
    cout << space(10) << "2.载入游戏" << space(10) << endl;
    cout << space(10) << "3.退出游戏" << space(10) << endl;
    cout << SEPERATOR << endl;
    cout << info;
}

void clearScreen() {
    cout << "\033[2J" << endl;
}

string space(int length) {
    std::string result;
    for (int i = 0; i < length; ++i) {
        result += " ";
    }
    return result;
}



