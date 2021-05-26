//
// Created by NaphtholMizuha on 2021/5/19.
//

#ifndef CHINESECHESS_GAME_H
#define CHINESECHESS_GAME_H
#include "graphic.h"
#include "Chessman.h"
using std::cin;
using std::cout;
using std::string;
using std::endl;

class Game {
public:
    Game();
    void playOneGame();// process of many and many playOneGame
    void load(ifstream& src);// load a chessboard from a txt file
    string getEndingInfo() const;

private:
    Chessboard chessboard;// store the chess
    Chessboard redHistoryChessboard;
    Chessboard blueHistoryChessboard;

    bool isFinished;// store whether the game have finished

    Camp campToControl;// note what camp should play this round

    string info; // printed at the beginning of each round, to welcome the player
    string endingInfo;// store the string printed in the end of the game

    bool canRedWithdraw;//store whether the red camp can withdraw
    bool canBlueWithdraw;//store whether the blue camp can withdraw

    Chessman* chooseSrc();// choose and return a source chessman
    bool chooseDest(Chessman* src);// choose a destination chessman and move 'source chessman' to that place

    void toggleCamp(); //toggle the camp to control
    void checkIsFinished();// checks whether this game is finished. If yes, then spawns the ending information

    void withdraw();//process the operation of withdrawl of one round.
    void changeCanOneWithdraw(bool canWithdraw);// change the state of whether some camp can withdraw

    bool transform(const string& input , int& x , int& y) const;//turns coordinate like "A1" into two numbers : like(1 , 1)

    void save() const;//dump the chessboard into a txt file
};


#endif //CHINESECHESS_GAME_H
