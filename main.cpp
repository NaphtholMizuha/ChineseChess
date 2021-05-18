#include <iostream>
#include "font.h"
#include "mainPage.h"
#include <iostream>


int main() {
    bool isPlaying = false;

    std::string info = "请输入操作代号以进行操作:";
    while (!isPlaying) {
        clearScreen();
        showTitle(info);
        int input = getchar();
        if (input == '1') {
            isPlaying = true;
        } else if (input == '2') {

        } else if (input == '3') {
            break;
        } else {
            info = "无效指令！请重新输入:";
        }
        return 0;
    }
}