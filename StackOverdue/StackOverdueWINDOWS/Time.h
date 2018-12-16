//
// Created by WilliamUSER on 12/9/2017.
//

#ifndef STACKOVERDUE_TIME_H
#define STACKOVERDUE_TIME_H

#include <iostream>
using namespace std;

class Time {
public:
    static unsigned int uiTime;
    static unsigned int getTime() {return uiTime;}
    static void timeTravel(unsigned int uiTravel) {uiTime += uiTravel;}
};


#endif //STACKOVERDUE_TIME_H
