#include <iostream>
#include "Process.h"

int main() {
    std::string info = "请输入操作代号以进行操作:";
    while (true) {
        clearScreen();
        showTitle(info);
        int input;
        cin >> input;
        switch (input) {
            case 1:
                playGame(false);
                break;
            case 2:
                playGame(true);
                break;
            case 3:
                return 0;
            default:
                info = "无效指令，请再次输入";
                break;
        }
    }
}

