#ifndef CIRCLE_H
#define CIRCLE_H

#include <iostream>
#include <math.h>
#include "framebuffer.h"

using namespace std;

class Circle
{
    public:
		int r, xc, yc, full;
		Circle(int a, int b, int c, int d){
			r = a;
			xc = b;
			yc = c;
			full = d;
		}
		
		int rotate_pointx(int cx, int cy, int angle, int x, int y){
		float val = PI / 180;
		float s = sin(angle*val);
		float c = cos(angle*val);
		x -= cx;
		y -= cy;
		return (x * c - y * s) + cx;
		}

		int rotate_pointy(int cx, int cy, int angle, int x, int y){
		float val = PI / 180;
		float s = sin(angle*val);
		float c = cos(angle*val);
		x -= cx;
		y -= cy;
		return (x * s + y * c) + cy;
		}
		
		void draw(FramePanel* a){
		/* r = jari-jari; xc = koordinar X pusat lingkaran;
		 * yc= koordinat Y pusat lingkaran;
		 * full = 1: lingkaran penuh, 0: setengah lingkaran bgn atas;
		 * color= warna garis lingkaran
		 * Prosedur untuk ngegambar lingkaran Bresenham*/
			int xn=0, yn=r;
			int p = 3-2*r; 

			while (xn<yn){
				xn++;
				if (p>=0){
					yn--;
					p+=4*(xn-yn)+10;
				}else{
					p+=4*(xn)+6;
				}
				int x3=xn;
				int y3=yn*(-1)+0.5*r;
				//Sisi kanan atas
				printf("coba ah %d", (*a).getXSize());
				(*a).set(Color(255, 255, 255), x3+xc, y3+yc);
				printf(" coba lagi %d, %d = %d %d %d\n", x3+xc, y3+yc, (int)((*a).get(x3+xc, y3+yc)).getB(),(int)((*a).get(x3+xc, y3+yc)).getG(),(int)((*a).get(x3+xc, y3+yc)).getR());
				(*a).set((Color::GREEN), -1*y3+xc+0.5*r,-1*x3+yc+0.5*r);
				
				//Sisi kiri atas
				(*a).set((Color::GREEN), x3*(-1)+xc,y3+yc);
				(*a).set((Color::GREEN), y3+xc-0.5*r,-1*x3+yc+0.5*r);
				
				if (full==1){
					//sisi kanan bawah
					(*a).set((Color::GREEN), xn+xc,yn+yc+0.5*r);
					(*a).set((Color::GREEN), yn+xc,xn+yc+0.5*r);
				
					//sisi kiri bawah
					(*a).set((Color::GREEN),-1*x3+xc,-1*y3+yc+r);
					(*a).set((Color::GREEN), y3+xc-0.5*r,x3+yc+0.5*r);
				}
			}
		}
		
		void Bounce(Point start, Point fin){
			
		}
    
};

#endif
