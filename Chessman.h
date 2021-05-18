#ifndef CHINESECHESS_CHESSMAN_H
#define CHINESECHESS_CHESSMAN_H
#include <iostream>
#include <string>
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

typedef string ErrorInfo;

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
    static int deadAmount;// The total count of dead chessman
    const Camp camp_;// the camp of chessman, which in this game is "RED" or "BLUE"
public:
    Chessman(int x, int y, Camp camp , Type type = VACCUM);
    void swapPosition(int destX , int destY , Chessboard& chessboard) const;//swap 'this' chessman and destination chessman
    int getX() const;
    int getY() const;
    Camp getCamp() const;
    Type getType() const;
    void eat (Chessman& enemy , Chessboard& chessboard) const; // when eating enemy's chessman
    void die(Chessboard& chessboard) const; // when 'this' is eaten by enemy
    int chessmanAmountBetween(int destX , int destY , const Chessboard& chessboard) const;//count the number of chessmans which are between 'this' and destination
    virtual bool canMove (int destX, int destY, const Chessboard& chessboard , ErrorInfo& errorInfo);//judge whether 'this' chessman can be moved to destination
};

class Soldier : public Chessman {
private:
    bool isAdvanced;//note the statement whether this soldier has passed the river
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
private:
    Chessman* battleField[CHESSBOARD_LENGTH][CHESSBOARD_WIDTH];
    Chessman* tomb[AMOUNT_OF_WHOLE_CHESSMEN];//store the chessmans which have been eaten
public:
    Chessboard();
    ~Chessboard();
    Chessman* at(int x , int y) const;
    Chessman* operator() (int x , int y) const;
    void swap(int x1 , int y1 , int x2 , int y2);
    void print();
};

#endif //CHINESECHESS_CHESSMAN_H
