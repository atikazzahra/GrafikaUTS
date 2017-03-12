// class parser
#ifndef ROLLING_H
#define ROLLING_H

#include <iostream>
#include <string>
#include "circle.h"
#include "line.h"

using namespace std;

class Rolling {
public :	
        Rolling(){}
        bool startGame(){
			FramePanel p(900, 500, 200, 80);
			Framebuffer fp;
			while(1) {
				Circle Ball1(20, 800, 970, 1);
				Ball1.draw(&p);
		   
				fp.drawFrame(p);
				fp.Draw();
				p.EmptyFrame();
			}
			return false;
		}
};
#endif
