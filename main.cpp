#include <iostream>
#include "Process.h"

int main() {
    bool isPlaying = false;

    std::string info = "请输入操作代号以进行操作:";
    while (true) {
        clearScreen();
        showTitle(info);
        int input;
        cin >> input;
        if (input == 1) {
            playGame(false);
        } else if (input == 2) {
            cout << "此功能尚未开发" << endl;
            return 0;
        } else if (input == 3) {
            return 0;
        } else {
            info = "无效指令！请重新输入:";
        }
    }
}

