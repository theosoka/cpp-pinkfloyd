#include <iostream>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <winuser.h>

#include "structs.h"

enum states { pause, stop, going };
states state = going;

int changeState(char c) {
    switch (c)
    {
        case VK_SPACE:
            state = pause;
            return 1;
        case 113:
            state = stop;
            return 1;
        default:
            return 0;
    }
}

// removes flickering
void clearScreen() {
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

int main() {
    buffer pf;
    char c;

    std::cout << "press any key to start the animation. \nduring the animation press space to pause and resume the animation\npress q to exit";
    _getch();
    while (true) {
        if (kbhit()) 
        {
            c = _getch();
            if (c == VK_SPACE) 
            {
                state = going;
            }
        }
        if (state == pause)
            continue;
        if (state == stop)
            break;
        for (int i = 0; i < 115; i += 3) {
            pf.result(i);
            if (kbhit()) {
                if (changeState(_getch()))
                    break;
            }
            pf.clear();
            clearScreen();
        }
    }
}
