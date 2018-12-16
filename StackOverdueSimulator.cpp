//
// Created by WilliamUSER on 12/8/2017.
//
#include <iomanip>
#include <fstream>
#include <iostream>

#include "Time.h"
#include "Administrator.h"

using namespace std; // make std members visible

// Initialize static member of class Time
unsigned int Time::uiTime = 1;

int main(int argc, char* argv[]) {
    string sBookFileName="";
    string sAccountFileName="";

    switch(argc) {
        case 1 :
            break;
        case 2 :
            sBookFileName = argv[1];
            break;
        case 3 :
            sBookFileName = argv[1];
            sAccountFileName = argv[2];
            break;
        default :
            sBookFileName = argv[1];
            sAccountFileName = argv[2];
            break;
    }

    Administrator admin(sBookFileName,sAccountFileName);
    admin.runCommands();

    return 0;
}