//
// Created by NaphtholMizuha on 2021/5/19.
//

#include <fstream>
#include "Game.h"

Game::Game() {
    isFinished = false;
    canRedWithdraw = false;
    canBlueWithdraw = false;
    campToControl = RED;
}

void Game::toggleCamp() {
    campToControl = (campToControl == RED) ? BLUE : RED;
}

void Game::checkIsFinished() {
    for (int i = 0; i < AMOUNT_OF_WHOLE_CHESSMEN; i++) {
        Chessman* temp = chessboard(DEAD , i + 1);
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

string Game::getEndingInfo() const {
    return endingInfo;
}

void Game::playOneGame() {
    while (true) {
        //Welcome
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
    }




}

bool Game::transform(const string& input, int &x, int &y) const {
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

    while (true) {
        cout << ASK_FOR_COORDINATE;
        cin >> input;
        if (input == "S") {
            save();
            cout << "保存完毕，";
            continue;
        };
        if (input == "W") {
            withdraw();
            changeCanOneWithdraw(false);
            continue;
        };
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
                if (campToControl == RED) {
                    redHistoryChessboard = chessboard;
                }

                if (campToControl == BLUE) {
                    blueHistoryChessboard = chessboard;
                }

                if (dest->getCamp() != campToControl) {
                    dest->die(chessboard);
                }

                changeCanOneWithdraw(true);
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

void Game::save() const {
    ofstream outFile;
    outFile.open("ChineseChessSave.txt" , ios::trunc);
    for (int i = 1; i <= CHESSBOARD_LENGTH; i++) {
        for (int j = 1; j <= CHESSBOARD_WIDTH; j++) {
            Chessman* target = chessboard(i , j);
            if (target->getCamp() == RED) outFile << "R";
            else if (target->getCamp() == BLUE) outFile << "B";
            else outFile << "N";

            switch (target->getType()) {
                case SOLDIER:
                    outFile << "S";
                    break;
                case BOMBARD:
                    outFile << "B";
                    break;
                case HORSE:
                    outFile << "H";
                    break;
                case VEHICLE:
                    outFile << "V";
                    break;
                case ELEPHANT:
                    outFile << "E";
                    break;
                case GUARDER:
                    outFile << "U";
                    break;
                case GENERAL:
                    outFile << "G";
                    break;
                case VACCUM:
                    outFile << "N";
                    break;
            }

            outFile << endl;
        }
    }

    for (int i = 1; i <= AMOUNT_OF_WHOLE_CHESSMEN; i++) {
        Chessman* target = chessboard(DEAD , i);

        if (target->getCamp() == RED) outFile << "R";
        else if (target->getCamp() == BLUE) outFile << "B";
        else outFile << "N";

        switch (target->getType()) {
            case SOLDIER:
                outFile << "S";
                break;
            case BOMBARD:
                outFile << "B";
                break;
            case HORSE:
                outFile << "H";
                break;
            case VEHICLE:
                outFile << "V";
                break;
            case ELEPHANT:
                outFile << "E";
                break;
            case GUARDER:
                outFile << "U";
                break;
            case GENERAL:
                outFile << "G";
                break;
            case VACCUM:
                outFile << "N";
                break;
        }

        outFile << endl;
    }
    if (campToControl == RED) outFile << "Red";
    else outFile << "Blue";
}

void Game::load(ifstream& src) {
    chessboard.loadSave(src);
    string input;
    src >> input;
    if (input == "Red") campToControl = RED;
    else campToControl = BLUE;
}

void Game::withdraw() {
    if (canRedWithdraw && campToControl == RED) {
        chessboard = redHistoryChessboard;
        campToControl = RED;
        chessboard.print();
        cout << "撤回成功！";

    }
    else if (canBlueWithdraw && campToControl == BLUE) {
        campToControl = BLUE;
        chessboard = blueHistoryChessboard;

        campToControl = BLUE;
        chessboard.print();
        cout << "撤回成功！";
    }
    else {
        cout << "撤回失败！可能是刚开局或者撤回了太多次！" << endl;
    }
}

void Game::changeCanOneWithdraw(bool canWithdraw) {
    if (campToControl == RED) canRedWithdraw = canWithdraw;
    else canBlueWithdraw = canWithdraw;
}
