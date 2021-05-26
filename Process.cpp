//
// Created by NaphtholMizuha on 2021/5/12.
//

#include <fstream>
#include "Process.h"
#include "graphic.h"
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

string space(int num) {
    string result;
    for (int i = 0; i < num; ++i) {
        result += " ";
    }
    return result;
}

void playGame (bool shouldLoad) {
    Game game;

    if (shouldLoad) {
        ifstream src;
        src.open("ChineseChessSave.txt" , ios::in);
        game.load(src);
        src.close();
    }

    game.playOneGame();

    cout << endl << SEPERATOR << endl << game.getEndingInfo() << endl << SEPERATOR;

}



