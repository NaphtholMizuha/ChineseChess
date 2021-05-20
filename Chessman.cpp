//
// Created by NaphtholMizuha on 2021/5/12.
//

#include "Chessman.h"

Chessman::Chessman(int x, int y, Camp camp , Type type):x_(x) , y_(y) , camp_(camp) , type_(type){}

int Chessman::getX() const {
    return x_;
}

int Chessman::getY() const {
    return y_;
}

void Chessman::swapPosition(int destX, int destY, Chessboard& chessboard) const {
    chessboard.swap(x_ , y_ , destX , destY);
}

Camp Chessman::getCamp() const {
    return camp_;
}

void Chessman::die(Chessboard& chessboard) const {
    swapPosition(DEAD , deadAmount + 1 , chessboard);
    deadAmount++;
}

int Chessman::deadAmount = 0;

bool Chessman::canMove(int destX, int destY , const Chessboard& chessboard , ErrorInfo& errorInfo) {
    bool flag = true;

    // to check whether the destination is took up by any ally
    if (chessboard(destX , destY)->getCamp() == this->camp_) {
        errorInfo = "别打了是友军，请再次确认！";
        flag = false;
    }

    return flag;
}

Type Chessman::getType() const {
    return type_;
}

int Chessman::chessmanAmountBetween(int destX, int destY , const Chessboard& chessboard) const {
    int amount = 0;
    if (destX == x_) {
        for (int i = min(y_ , destY) + 1; i < max(y_ , destY); i++) {
            if (chessboard(x_ , i)->getType() != VACCUM) amount++;
        }
    }

    if (destY == y_) {
        for (int i = min(x_ , destX) + 1; i < max(x_ , destX); i++) {
            if (chessboard(i , destY)->getType() != VACCUM) amount++;
        }
    }
    return amount;
}

void Chessman::set(int x, int y) {
    x_ = x;
    y_ = y;
}

bool Soldier::canMove(int destX, int destY , const Chessboard& chessboard, ErrorInfo& errorInfo) {
    levelUp();
    cout << isAdvanced << endl;

    // to check whether this soldier would move only one step forward
    if (Chessman::canMove(destX , destY , chessboard , errorInfo)) {
        if (!isAdvanced) {
            if (camp_ == RED) {
                if (destX == x_ && destY - y_ == 1) return true;
                else {
                    errorInfo = "兵过河前只能前进一格";
                    return false;
                }
            }
            else {
                if (destX == x_ && destY - y_ == -1) return true;
                else {
                    errorInfo = "卒过河前只能前进一格";
                    return false;
                }
            }
        }
        else {// to check whether this soldier would move only one step forward , leftward or rightward
            if (camp_ == RED) {
                if ((abs(destX - x_) == 1  && destY == y_) || (destX == x_ && destY - y_ == 1)) return true;
                else {
                    errorInfo = "兵过河后只能想前、中、左走一格";
                    return false;
                }
            }
            else {
                if ((abs(destX - x_) == 1  && destY == y_) || (destX == x_ && destY - y_ == -1)) return true;
                else {
                    errorInfo = "兵过河后只能想前、中、左走一格";
                    return false;
                }
            }
        }
    }
    else return false;
}

Soldier::Soldier(int x, int y , Camp camp) : Chessman(x , y , camp , SOLDIER){
    isAdvanced = false;
}

void Soldier::levelUp() {
    // to check if the soldier has passed the river
    if ((camp_ == RED && y_ > 5) || (camp_ == BLUE && y_ <= 5)) isAdvanced = true;
}

Vehicle::Vehicle(int x, int y , Camp camp) : Chessman(x , y , camp , VEHICLE){}

bool Vehicle::canMove(int destX, int destY, const Chessboard &chessboard , ErrorInfo& errorInfo) {

    if (!Chessman::canMove(destX, destY, chessboard , errorInfo)) {
        return false;
    }

    // to check if the vehicle would move in vertical of horizontal line
    if (destX != x_ && destY != y_) {
        errorInfo = "车只能走直线";
        return false;
    }


    // to check if the vehicle is blocked by some enemy
    if (chessmanAmountBetween(destX , destY , chessboard) != 0) {
        errorInfo = "此车被其他棋子阻挡";
        return false;
    }

    return true;
}


Horse::Horse(int x, int y, Camp camp) : Chessman(x, y, camp , HORSE) {}

bool Horse::canMove(int destX, int destY, const Chessboard &chessboard , ErrorInfo& errorInfo) {
    if (!Chessman::canMove(destX, destY, chessboard , errorInfo)) {
        return false;
    }

    // to check if the horse move in the shape of 日
    if (!(abs(destX - x_) == 1 && abs(destY - y_) == 2) && !(abs(destX - x_) == 2 && abs(destY - y_) == 1)) {
        errorInfo = "马只能走\"日\"字，请再次确认！";
        return false;
    }

    if ((destX - x_ == 2 && chessboard(x_ + 1 , y_)->getType() != VACCUM) ||
        (destY - y_ == 2 && chessboard(x_ , y_ + 1)->getType() != VACCUM) ||
        (x_ - destX == 2 && chessboard(x_ - 1 , y_)->getType() != VACCUM) ||
        (y_ - destY == 2 && chessboard(x_ , y_ - 1)->getType() != VACCUM)) {
        errorInfo = "此马被\"拐马脚\"";
        return false;
    }
    return true;
}

Elephant::Elephant(int x, int y, Camp camp): Chessman(x , y , camp , ELEPHANT) {}

bool Elephant::canMove(int destX, int destY, const Chessboard &chessboard, ErrorInfo &errorInfo) {
    if (!Chessman::canMove(destX, destY, chessboard , errorInfo)) {
        return false;
    }

    if ((camp_ == RED && destY > 5) || (camp_ == BLUE && destY <= 5)) {
        errorInfo = "相/象不能过河";
        return false;
    }

    if (!(abs(destX - x_) == 2 && abs(destY - y_) == 2)) {
        errorInfo = "象只能走田字";
        return false;
    }

    if ((destX - x_ == 2 && destY - y_ == 2 && chessboard(x_ + 1 , y_ + 1)->getType() != VACCUM) ||
        (destX - x_ == 2 && y_ - destY == 2 && chessboard(x_ + 1 , y_ - 1)->getType() != VACCUM) ||
        (x_ - destX == 2 && destY - y_ == 2 && chessboard(x_ - 1 , y_ + 1)->getType() != VACCUM) ||
        (x_ - destX == 2 && y_ - destY == 2 && chessboard(x_ - 1 , y_ - 1)->getType() != VACCUM)){
        errorInfo = "此象被\"憋象脚\"";
        return false;
    }

    return true;
}

Guarder::Guarder(int x , int y , Camp camp) : Chessman(x , y , camp , GUARDER){}

bool Guarder::canMove(int destX, int destY, const Chessboard &chessboard, ErrorInfo &errorInfo) {
    if (!Chessman::canMove(destX, destY, chessboard , errorInfo)) {
        return false;
    }

    if (destX < NINE_PALACE_LEFT || destX > NINE_PALACE_RIGHT ||
        (camp_ == BLUE && (destY > BLUE_NINE_PALACE_BOTTOM || destY < BLUE_NINE_PALACE_TOP)) ||
        (camp_ == RED && (destY > RED_NINE_PALACE_BOTTOM || destY < RED_NINE_PALACE_TOP))){
        errorInfo = "士/仕不能离开九宫";
        return false;
    }

    if (!(abs(destX - x_) == 1 && abs(destY - y_) == 1)) {
        errorInfo = "士/仕只能在斜线走一步";
        return false;
    }

    return true;
}

General::General(int x, int y, Camp camp) : Chessman(x , y , camp , GENERAL){}

bool General::canMove(int destX, int destY, const Chessboard &chessboard, ErrorInfo &errorInfo) {
    if (!Chessman::canMove(destX, destY, chessboard , errorInfo)) {
        return false;
    }

    if (chessboard(destX , destY)->getType() == GENERAL &&
        chessboard(destX , destY)->getCamp() != this->camp_ &&
            chessmanAmountBetween(destX , destY , chessboard) == 0) {
        return true;
    }

    if (destX < NINE_PALACE_LEFT || destX > NINE_PALACE_RIGHT ||
        (camp_ == BLUE && (destY > BLUE_NINE_PALACE_BOTTOM || destY < BLUE_NINE_PALACE_TOP)) ||
        (camp_ == RED && (destY > RED_NINE_PALACE_BOTTOM || destY < RED_NINE_PALACE_TOP))){
        errorInfo = "除\"飞将\"外，将/帅不能离开九宫";
        return false;
    }

    if (!((x_ == destX && abs(y_ - destY) == 1) || (y_ == destY && abs(x_ - destX) == 1))) {
        errorInfo = "除\"飞将\"外，将/帅只能在横竖方向走一格";
        return false;
    }

    return true;
}

Bombard::Bombard(int x, int y, Camp camp) : Chessman(x , y , camp , BOMBARD) {}

bool Bombard::canMove(int destX, int destY, const Chessboard &chessboard, ErrorInfo &errorInfo) {
    if (!Chessman::canMove(destX, destY, chessboard , errorInfo)) {
        return false;
    }

    if (destX != x_ && destY != y_) {
        errorInfo = "炮/砲只能走直线";
        return false;
    }

    if (chessmanAmountBetween(destX , destY , chessboard) == 0 && chessboard(destX , destY)->getType() != VACCUM) {
        errorInfo = "炮/砲不能直接吃子";
        return false;
    }

    if (chessmanAmountBetween(destX , destY , chessboard) == 1 && chessboard(destX , destY)->getType() == VACCUM) {
        errorInfo = "炮/砲只有在吃子的时候才能越过棋子";
        return false;
    }

    if (chessmanAmountBetween(destX , destY , chessboard) > 1) {
        errorInfo = "炮/砲不能越过这么多棋子";
        return false;
    }

    return true;
}

Chessboard::Chessboard() {
    for (int i = 0; i < CHESSBOARD_LENGTH; i++) {
        for (int j = 0; j < CHESSBOARD_WIDTH; j++) {
            battleField[i][j] = nullptr;
        }
    }

    for (int i = 0; i < AMOUNT_OF_WHOLE_CHESSMEN; ++i) {
        tomb[i] = new Chessman(DEAD , i , NEUTRAL , VACCUM);
    }

    for (int i = 0; i < 5; i++) {//Create Soldiers
        battleField[2 * i][3] = new Soldier(2 * i + 1 , 4 , RED);
        battleField[2 * i][6] = new Soldier(2 * i + 1 , 7 , BLUE);
    }
    //Create Bombards
    battleField[1][2] = new Bombard(2 , 3 , RED);
    battleField[7][2] = new Bombard(8 , 3 , RED);
    battleField[1][7] = new Bombard(2 , 8 , BLUE);
    battleField[7][7] = new Bombard(8 , 8 , BLUE);
    //Create Vehicles
    battleField[0][0] = new Vehicle(1 , 1 , RED);
    battleField[8][0] = new Vehicle(9 , 1 , RED);
    battleField[0][9] = new Vehicle(1 , 10 , BLUE);
    battleField[8][9] = new Vehicle(9 , 10 , BLUE);
    //Create Horses
    battleField[1][0] = new Horse(2 , 1 , RED);
    battleField[7][0] = new Horse(8 , 1 , RED);
    battleField[1][9] = new Horse(2 , 10 , BLUE);
    battleField[7][9] = new Horse(8 , 10 , BLUE);
    //Create Elephants
    battleField[2][0] = new Elephant(3 , 1 , RED);
    battleField[6][0] = new Elephant(7 , 1 , RED);
    battleField[2][9] = new Elephant(3 , 10 , BLUE);
    battleField[6][9] = new Elephant(7 , 10 , BLUE);
    //Create Guarders
    battleField[3][0] = new Guarder(4 , 1 , RED);
    battleField[5][0] = new Guarder(6 , 1 , RED);
    battleField[3][9] = new Guarder(4 , 10 , BLUE);
    battleField[5][9] = new Guarder(6 , 10 , BLUE);
    //Create Generals
    battleField[4][0] = new General(5 , 1 , RED);
    battleField[4][9] = new General(5 , 10 , BLUE);
    //Create Vaccums
    for (int i = 0; i < CHESSBOARD_LENGTH; i++) {
        for (int j = 0; j < CHESSBOARD_WIDTH; j++) {
            if (battleField[i][j] == nullptr) {
                battleField[i][j] = new Chessman(i + 1 , j + 1 , NEUTRAL , VACCUM);
            }
        }
    }

}

Chessman* Chessboard::operator()(int x, int y) const {
    return at(x , y);
}

void Chessboard::swap(int x1, int y1, int x2, int y2) {
    Chessman* temp;
    if (x1 != DEAD && x2 != DEAD) {
        temp = battleField[x1 - 1][y1 - 1];
        battleField[x1 - 1][y1 - 1] = battleField[x2 - 1][y2 - 1];
        battleField[x2 - 1][y2 - 1] = temp;
        battleField[x1 - 1][y1 - 1]->set(x1 , y1);
        battleField[x2 - 1][y2 - 1]->set(x2 , y2);
    }
    else {
        temp = battleField[x1 - 1][y1 - 1];
        battleField[x1 - 1][y1 - 1] = tomb[y2 - 1];
        tomb[y2 - 1] = temp;
        battleField[x1 - 1][y1 - 1]->set(x1 , y1);
        tomb[y2 - 1]->set(x2 , y2);
    }
}

Chessman *Chessboard::at(int x, int y) const{
    if (x != DEAD) {
        return battleField[x - 1][y - 1];
    }
    else return tomb[y - 1];
}

Chessboard::~Chessboard() {
    for (int i = 0; i < CHESSBOARD_LENGTH; i++) {
        for (int j = 0; j < CHESSBOARD_WIDTH; j++) {
            delete battleField[i][j];
        }
    }

    for (int i = 0; i < AMOUNT_OF_WHOLE_CHESSMEN; ++i) {
        delete tomb[i];
    }
}

void Chessboard::print() {
    cout << X_AXIOM << endl << endl;
    for (int i = 1; i <= CHESSBOARD_WIDTH; i++) {
        if (i != 10) cout << i << "  ";
        else cout << i << " ";

        for (int j = 1; j <= CHESSBOARD_LENGTH; j++) {
            cout << shape(j , i);
            if (j != CHESSBOARD_LENGTH) cout << "-";
        }
        cout << endl;

        if (i == 1 || i == 8) cout << VERTICAL_LINES_WITH_INWARD_SLASHES;
        if (i == 2 || i == 9) cout << VERTICAL_LINES_WITH_OUTWARD_SLASHES;
        if (i == 5) cout << CHU_HE_HAN_JIE;
        if (i == 3 || i == 4 || i == 6 || i == 7) cout << VERTICAL_LINES;

        cout << endl;

    }

    cout << SEPERATOR << endl;
    cout << "墓地：" << endl;

    int deadAmount = 0;
    for (int i = 1; i < AMOUNT_OF_WHOLE_CHESSMEN; i++) {
        if (at(DEAD , i)->getType() != VACCUM) {
            cout << shape(DEAD , i) << " ";
            deadAmount++;
        }

        if (deadAmount == 9) {
            cout << endl;
            deadAmount = 0;
        }
    }
    cout << endl << SEPERATOR << endl;
}

string Chessboard::shape(int x, int y) const {
    Chessman* target = at(x , y);
    if (target->getType() == VACCUM) return SHAPE_OF_VACCUM;

    if (target->getCamp() == RED){
        if (target->getType() == GENERAL) return SHAPE_OF_GENERAL_RED;
        if (target->getType() == GUARDER) return SHAPE_OF_GUARDER_RED;
        if (target->getType() == ELEPHANT) return SHAPE_OF_ELEPHANT_RED;
        if (target->getType() == HORSE) return SHAPE_OF_HORSE_RED;
        if (target->getType() == VEHICLE) return SHAPE_OF_VEHICLE_RED;
        if (target->getType() == BOMBARD) return SHAPE_OF_BOMBARD_RED;
        if (target->getType() == SOLDIER) return SHAPE_OF_SOLDIER_RED;
    }
    else {
        if (target->getType() == GENERAL) return SHAPE_OF_GENERAL_BLUE;
        if (target->getType() == GUARDER) return SHAPE_OF_GUARDER_BLUE;
        if (target->getType() == ELEPHANT) return SHAPE_OF_ELEPHANT_BLUE;
        if (target->getType() == HORSE) return SHAPE_OF_HORSE_BLUE;
        if (target->getType() == VEHICLE) return SHAPE_OF_VEHICLE_BLUE;
        if (target->getType() == BOMBARD) return SHAPE_OF_BOMBARD_BLUE;
        if (target->getType() == SOLDIER) return SHAPE_OF_SOLDIER_BLUE;
    }
}

bool Chessboard::isFinished() const {
    for (int i = 1; i < AMOUNT_OF_WHOLE_CHESSMEN; i++) {
        if (at(DEAD , i)->getType() == GENERAL) return true;
    }

    return false;
}

