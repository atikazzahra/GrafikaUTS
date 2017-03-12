#include <iostream>
#include <fstream>
#include <sstream>
#include "Rolling.h"
#include "line.h"
using namespace std;
 
int main(int argc, char** argv) {
	Rolling R;
	Framebuffer fp;
	Line l(Point(300,300), Point(100,100));
	

	FramePanel panelBig(500, 500, 550, 0);
	panelBig.set(Color(0,255,0), 100, 100);
	panelBig.set(Color(0,255,0), 200, 100);
	
	l.draw(&panelBig);
	Circle Ball1(10, 200, 200, 1);
	Ball1.draw(&panelBig);
	panelBig.set(Color(0,255,0), 300, 400);
	fp.drawFrame(panelBig);
}

