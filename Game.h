//
// Created by NaphtholMizuha on 2021/5/19.
//

#ifndef CHINESECHESS_GAME_H
#define CHINESECHESS_GAME_H
#include "Chessman.h"
#include "graphic.h"
using std::cin;
using std::cout;
using std::string;
using std::endl;
class Game {
private:
    Chessboard chessboard;
    Chessboard lastSaved;
    bool isFinished;
    Camp campToControl;
    string info;
    string endingInfo;

    Chessman* chooseSrc();
    bool chooseDest(Chessman* src);
    void toggleCamp(); //toggle the camp to control
    void checkIsFinished();// checks whether this game is finished. If yes, then spawns the ending information

    bool transform(const string& input , int& x , int& y);// turns coordinate like "A1" into two numbers : like(1 , 1)
public:
    Game();
    void rounds();
    bool getIsFinished() const;
    string getEndingInfo() const;


};


#endif //CHINESECHESS_GAME_H
