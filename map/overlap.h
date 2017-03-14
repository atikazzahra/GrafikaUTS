#ifndef OVERLAP_H
#define OVERLAP_H

#define COLOR_1 1
#define EMPTY 0

#include "framebuffer.h"
using namespace std;

class Overlap : public Framebuffer {
	private:
		Framebuffer fb;
		int m[][][];
		int i, j;

	public:
		Overlap() {
			m = int[600][600][2];
			for(i=0;i<=600;i++) {
				for(j=0;j<=600;j++) {
					m[i][j][0] = 0;
					m[i][j][1] = 0;
				}
			}
		}

		initMatrix() {
			//I
			for(i=174;i<=267;i++) {
				for(j=30;j<=386;j++) {
					m[i][j][0] = COLOR_1;
				}
			}

			//lanjutin dari punya aan...
			//send help plz
		}

		printLogo() {
			int valx, valy;
			//print upper layer
			for(i=0;i<=600;i++) {
				for(j=0;j<=600;j++) {
					if (m[i][j][1] != 0)
						putPixel(i,j,255,0,0); //sementara merah; nanti pake constant aja
				}
			}

			//print lower layer
			for(i=0;i<=600;i++) {
				for(j=0;j<=600;j++) {
					if (m[i][j][0] != 0 && m[i][j][1] == 0)
						putPixel(i,j,255,0,0); //idem
				}
			}
		}
};
#endif
