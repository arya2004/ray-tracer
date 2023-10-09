#include <iostream>
#include "CApp.h"
int main(int argc, char* argv[]) {
    CApp appie;
    return appie.OnExecute();
}

//g++ main.cpp CApp.cpp -lSDL2 -std=c++17