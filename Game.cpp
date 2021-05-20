//
// Created by NaphtholMizuha on 2021/5/19.
//

#include "Game.h"

Game::Game() {
    campToControl = RED;
    isFinished = false;
}

void Game::toggleCamp() {
    campToControl = (campToControl == RED) ? BLUE : RED;
}

void Game::checkIsFinished() {
    for (int i = 1; i < AMOUNT_OF_WHOLE_CHESSMEN; i++) {
        Chessman* temp = chessboard(DEAD , i);
        if (temp->getType() == GENERAL) {
            if (temp->getCamp() == BLUE) {
                endingInfo = "恭喜" + RED_WORD + "红方" + DEFAULT_WORD + "获胜！";
            }
            if (temp->getCamp() == RED) {
                endingInfo = "恭喜" + BLUE_WORD + "蓝方" + DEFAULT_WORD + "获胜！";
            }

            isFinished = true;
        }
    }
}

bool Game::getIsFinished() const {
    return isFinished;
}

string Game::getEndingInfo() const {
    return endingInfo;
}

void Game::rounds() {
    while (true) {
        info = (campToControl == RED) ? WELCOME_RED : WELCOME_BLUE;
        cout << CLEAR_SCREEN;
        cout << SEPERATOR << endl << info << endl << SEPERATOR << endl;
        chessboard.print();


        while (true) {
            Chessman* src = chooseSrc();
            bool flag = chooseDest(src);
            if (flag) break;
        }
        checkIsFinished();
        toggleCamp();

        if (isFinished) {
            break;
        }
        else {
            continue;
        }
    }




}

bool Game::transform(const string& input, int &x, int &y) {
    if (input[0] >= 'A' && input[0] <= 'I') {
        x = input[0] - 'A' + 1;
    }
    else {
        return false;
    }

    if (input.length() == 2 && input[1] >= '1' && input[1] <= '9') {
        y = input[1] - '0';
    }
    else if (input.length() == 3 && input[1] == '1' && input[2] == '0') {
        y = 10;
    }
    else {
        return false;
    }

    return true;
}

Chessman *Game::chooseSrc() {
    string input;
    int srcX = 0 , srcY = 0;
    cout << ASK_FOR_COORDINATE;

    while (true) {
        cin >> input;
        if (transform(input , srcX , srcY)) {
            if (chessboard(srcX , srcY)->getCamp() == campToControl) {
                break;
            }
            else {
                cout << CAMP_WRONG;
                continue;
            }
        }
        else {
            cout << FORM_WRONG;
            continue;
        }
    }

    return chessboard(srcX , srcY);
}

bool Game::chooseDest(Chessman *src) {
    ErrorInfo errorInfo;
    string input;
    int destX = 0 , destY = 0;

    cout << "已选择 " << chessboard.shape(src->getX() , src->getY()) << " " << CHOOSE_DEST;
    while (true) {
        cin >> input;
        if (input == "Q") return false;
        if (transform(input , destX , destY)) {
            Chessman* dest = chessboard(destX , destY);
            if (src->canMove(destX , destY , chessboard , errorInfo)) {
                if (dest->getCamp() != campToControl) {
                    dest->die(chessboard);
                }
                chessboard.swap(src->getX() , src->getY() , destX , destY);
                break;
            }
            else {
                cout << errorInfo + "，请重新输入目标坐标：";
                continue;
            }
        }
        else {
            cout << FORM_WRONG;
            continue;
        }
    }
    return true;
}
