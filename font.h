//
// Created by NaphtholMizuha on 2021/5/12.
//

#ifndef CHINESECHESS_FONT_H
#define CHINESECHESS_FONT_H
#include <string>
using std::string;

const string RED_WORD = "\033[1;31m";
const string BLUE_WORD = "\033[1;34m";
const string TWINKLE_WORD = "\033[5m";
const string DEFAULT_WORD = "\033[0m";

const string TEN_SPACES = "          ";
const string ELEVEN_SPACES = "           ";
const string SEPERATOR = "-------------------------------------------";
const string CHINESS_CHESS = "          \033[1;31m中     国     \033[1;34m象     棋\033[0m           ";

const string X_AXIOM = " 　  A 　 B 　 C 　 D 　 E 　 F 　 G 　 H 　 I";
const string VERTICAL_LINES = "    ｜   ｜   ｜   ｜   ｜   ｜   ｜   ｜   ｜";
const string VERTICAL_LINES_WITH_INWARD_SLASHES = "    ｜   ｜   ｜   ｜ \\ ｜ / ｜   ｜   ｜   ｜";
const string VERTICAL_LINES_WITH_OUTWARD_SLASHES = "    ｜   ｜   ｜   ｜ / ｜ \\ ｜   ｜   ｜   ｜";
const string CHU_HE_HAN_JIE = "    ｜        楚河             汉界        ｜";

const string SHAPE_OF_VACCUM = " ・ ";
const string SHAPE_OF_SOLDIER_RED = RED_WORD + "(兵)" + DEFAULT_WORD;
const string SHAPE_OF_SOLDIER_BLUE = BLUE_WORD + "(卒)" + DEFAULT_WORD;
const string SHAPE_OF_GENERAL_RED = RED_WORD +  "(帥)" + DEFAULT_WORD;
const string SHAPE_OF_GENERAL_BLUE = BLUE_WORD + "(將)" + DEFAULT_WORD;
const string SHAPE_OF_GUARDER_RED = RED_WORD +  "(仕)" + DEFAULT_WORD;
const string SHAPE_OF_GUARDER_BLUE = BLUE_WORD + "(士)" + DEFAULT_WORD;
const string SHAPE_OF_ELEPHANT_RED = RED_WORD + "(相)" + DEFAULT_WORD;
const string SHAPE_OF_ELEPHANT_BLUE = BLUE_WORD + "(象)" + DEFAULT_WORD;
const string SHAPE_OF_BOMBARD_RED = RED_WORD + "(炮)" + DEFAULT_WORD;
const string SHAPE_OF_BOMBARD_BLUE = BLUE_WORD + "(砲)" + DEFAULT_WORD;
const string SHAPE_OF_HORSE_RED = RED_WORD + "(馬)" + DEFAULT_WORD;
const string SHAPE_OF_HORSE_BLUE = BLUE_WORD + "(馬)" + DEFAULT_WORD;
const string SHAPE_OF_VEHICLE_RED = RED_WORD + "(車)" + DEFAULT_WORD;
const string SHAPE_OF_VEHICLE_BLUE = BLUE_WORD + "(車)" + DEFAULT_WORD;


#endif //CHINESECHESS_FONT_H
