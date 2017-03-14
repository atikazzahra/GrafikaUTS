#ifndef OVERLAP_H
#define OVERLAP_H

#define COLOR_1 1
#define EMPTY 0

#include "framebuffer.h"
using namespace std;

class Overlap : public Framebuffer {
	private:
		Framebuffer fb;
		int m[600][600][3];
		int i, j;

	public:
		Overlap() {
			int k;
			for(i=0;i<600;i++) {
				for(j=0;j<600;j++) {
					for(k=0;k<=2;k++) {
						m[i][j][k] = 0;
					}
				}
			}
			for(i=0;i<600;i++) {
				for(j=0;j<600;j++) {
					//if (m[i][j][1] != 0)
						fb.putPixel(i,j,255,0,0); //sementara merah; nanti pake constant aja
				}
			}
		}

		void initMatrix() {
			//back layer
			//I
			for(i=174;i<=267;i++) {
				for(j=30;j<=386;j++) {
					m[i][j][0] = COLOR_1;
				}
			}

			//F
			for(j=30;j<=386;j++) {
				for(i=304;i<=397;i++) {
					m[i][j][0] = COLOR_1;
				}
			}
			for(i=397;i<=462;i++) {
				for(j=30;j<=100;j++) {
					m[i][j][0] = COLOR_1;
				}
			}
			for(i=397;i<=455;i++) {
				for(j=168;j<=236;j++) {
					m[i][j][0] = COLOR_1;
				}
			}
			
			//middle layer
			//Box
			for(i=0;i<=600;i++) {
				for(j=245;j<=351;j++) {
					m[i][j][1] = COLOR_1;
				}
			}
			
			//front layer
			//S
			
			//U
			for(j=261;j<=336;j++) {
				for(i=156;i<=165;i++) {
					m[i][j][2] = COLOR_1;
				}
				for(i=183;i<=192;i++) {
					m[i][j][2] = COLOR_1;
				}
			}
			
			//R
			
			//V1
			
			//I
			for(i=369;i<=378;i++) {
				for(j=261;j<=336;j++) {
					m[i][j][2] = COLOR_1;
				}
			}
			
			//V2
			
			//E
			for(j=261;j<=336;j++) {
				for(i=484;i<=494;i++) {
					m[i][j][2] = COLOR_1;
				}
			}
			for(i=494;i<=518;i++) {
				for(j=261;j<=276;j++) {
					m[i][j][2] = COLOR_1;
				}
				for(j=291;j<=306;j++) {
					m[i][j][2] = COLOR_1;
				}
				for(j=321;j<=336;j++) {
					m[i][j][2] = COLOR_1;
				}
			}
		}

		void printLogo() {
			//print front layer
			for(i=0;i<=600;i++) {
				for(j=0;j<=600;j++) {
					if (m[i][j][2] != 0) {
						if (m[i][j][2] == COLOR_1) {
							fb.putPixel(i,j,255,0,0); //sementara merah; nanti pake constant aja
						//add additional cases here
					}
				}
			}

			//print middle layer
			for(i=0;i<=600;i++) {
				for(j=0;j<=600;j++) {
					if (m[i][j][1] != 0 && m[i][j][2] == 0) {
						if (m[i][j][1] == COLOR_1) {
							fb.putPixel(i,j,255,0,0); //idem
						}
					}
				}
			}
			
			//print front layer
			for(i=0;i<=600;i++) {
				for(j=0;j<=600;j++) {
					if (m[i][j][0] != 0 && m[i][j][1] == 0) {
						if (m[i][j][0] == COLOR_1) {
							fb.putPixel(i,j,255,0,0); //idem
						}
					}
				}
			}
		}
};
#endif
