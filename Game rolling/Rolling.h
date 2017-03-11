// class parser
#ifndef ROLLING_H
#define ROLLING_H

#include <iostream>
#include <string>
#include "line.h"

using namespace std;


class Rolling {
public :
        Point p1, p2;
        Color c;
        int thick;
        
        Rolling(){}
        
        bool startGame(){
			return false;
		}
};
#endif
