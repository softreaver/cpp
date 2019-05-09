#include <iostream>
#include "conio.h"

//Key mapping
const int ARROWKEYS = 224;
const int LEFT      = 75;
const int RIGHT     = 77;
const int UP        = 72;
const int DOWN      = 80;
const int ESC       = 27;
const int SPACE     = 32;

int main()
{
    int c(0);

    do
    {
        do
        {
        c = getch();

        if(c == ESC) return 0;

        }while(c != ARROWKEYS);

        c = getch();

        switch(c)
        {
        case LEFT:
            std::cout << "LEFT" << std::endl;
            break;

        case RIGHT:
            std::cout << "RIGHT" << std::endl;
            break;

        case UP:
            std::cout << "UP" << std::endl;
            break;

        case DOWN:
            std::cout << "DOWN" << std::endl;
            break;
        }
    }while(true);
}
