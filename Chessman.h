#ifndef CHINESECHESS_CHESSMAN_H
#define CHINESECHESS_CHESSMAN_H
#include <iostream>
#include <string>
#include "graphic.h"
using namespace std;

const int AMOUNT_OF_WHOLE_CHESSMEN = 32;
const int CHESSBOARD_LENGTH = 9;
const int CHESSBOARD_WIDTH = 10;

const int RED_NINE_PALACE_TOP = 1;
const int NINE_PALACE_LEFT = 4;
const int NINE_PALACE_RIGHT = 6;
const int RED_NINE_PALACE_BOTTOM = 3;
const int BLUE_NINE_PALACE_TOP = 8;
const int BLUE_NINE_PALACE_BOTTOM = 10;

typedef string ErrorInfo;// to store why some control is invalid

class Chessboard;

enum Type {
    VACCUM , SOLDIER , VEHICLE , BOMBARD , ELEPHANT , HORSE , GUARDER , GENERAL
};

enum Camp {
    RED , BLUE , NEUTRAL
};

const int DEAD = -1;

class Chessman{
protected:
    const Type type_;// the type of chessman, like "Horse""Elephant"...
    int x_;//coordinates
    int y_;//coordinates
    const Camp camp_;// the camp of chessman, which in this game is "RED" or "BLUE"
public:
    static int deadAmount;// The total count of dead chessman

    Chessman(int x, int y, Camp camp , Type type = VACCUM);
    void swapPosition(int destX , int destY , Chessboard& chessboard) const;//swap 'this' chessman and destination chessman
    int getX() const;
    int getY() const;
    void set(int x , int y);
    Camp getCamp() const;
    Type getType() const;
    void die(Chessboard& chessboard) const; // when 'this' is eaten by enemy
    int chessmanAmountBetween(int destX , int destY , const Chessboard& chessboard) const;//count the number of chessmans which are between 'this' and destination
    virtual bool canMove (int destX, int destY, const Chessboard& chessboard , ErrorInfo& errorInfo);//judge whether 'this' chessman can be moved to destination
};

class Soldier : public Chessman {
private:
    bool isAdvanced;//note the statement whether this soldier has passed the river
    void levelUp();//to judge whether this soldier has passed the river , if yes , 'isAdvanced' would be toggled to true
public:
    Soldier(int x, int y, Camp camp);
    bool canMove (int destX, int destY, const Chessboard& chessboard, ErrorInfo& errorInfo) override;
};

class Vehicle : public Chessman{
public:
    Vehicle(int x , int y , Camp camp);
    bool canMove (int destX, int destY, const Chessboard& chessboard, ErrorInfo& errorInfo) override;
};

class Horse : public Chessman {
public:
    Horse(int x , int y , Camp camp);
    bool canMove (int destX, int destY, const Chessboard& chessboard, ErrorInfo& errorInfo) override;
};

class Elephant : public Chessman {
public:
    Elephant(int x , int y , Camp camp);
    bool canMove (int destX, int destY, const Chessboard& chessboard, ErrorInfo& errorInfo) override;
};

class Guarder : public Chessman {
public:
    Guarder(int x , int y , Camp camp);
    bool canMove (int destX, int destY, const Chessboard& chessboard, ErrorInfo& errorInfo) override;
};

class General : public Chessman {
public:
    General(int x , int y , Camp camp);
    bool canMove (int destX, int destY, const Chessboard& chessboard, ErrorInfo& errorInfo) override;
};

class Bombard : public Chessman {
public:
    Bombard(int x , int y , Camp camp);
    bool canMove (int destX, int destY, const Chessboard& chessboard, ErrorInfo& errorInfo) override;
};

class Chessboard {
public:
    Chessboard();
    ~Chessboard();

    void loadSave(ifstream& src);

    Chessman* at(int x , int y) const;//find the chess by coordinate
    Chessman* operator() (int x , int y) const;//the same as the function "at"

    void swap(int x1 , int y1 , int x2 , int y2);

    string shape(int x , int y) const;//spawn the appearance of a chessman
    void print() const;//print all the chessboard

    Chessboard& operator= (const Chessboard& src);

private:
    Chessman* battleField[CHESSBOARD_LENGTH][CHESSBOARD_WIDTH];//stores the chessmen which is still can be controlled
    Chessman* tomb[AMOUNT_OF_WHOLE_CHESSMEN];//stores the chessmen which have been eaten
};

#endif //CHINESECHESS_CHESSMAN_H
