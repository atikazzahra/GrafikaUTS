#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "framebuffer.h"
#include "line.h"
#include "circle.h"

using namespace std;

class Player
{
	public :
		std::vector<Line> arr_Line;
        int thickness;
        Color floodfill;
        Color LineColor;
		
		void drawTree(Point p) {
            Line a,b,c,d,e;

            a = Line(p, Point(p.getX(),p.getY()-5));
            b = Line(Point(p.getX()-4,p.getY()-5),Point(p.getX()+4,p.getY()-5));
            c = Line(Point(p.getX()-4,p.getY()-5),Point(p.getX()-4,p.getY()-9));
            d = Line(Point(p.getX()-4,p.getY()-9),Point(p.getX()+4,p.getY()-9));
            e = Line(Point(p.getX()+4,p.getY()-5),Point(p.getX()+4,p.getY()-9));
            arr_Line.push_back(a);
            arr_Line.push_back(b);
            arr_Line.push_back(c);
            arr_Line.push_back(d);
            arr_Line.push_back(e);
            (*this).setLineColor(Color::GREEN);
            (*this).setThickness(1);
            
            setAllLineColor();
        }
};

#endif
