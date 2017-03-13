#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>

class Matrix 
{
public :
	Matrix(int x, int y) {
		xsize = x;
		ysize = y;
		M = (char **) malloc(ysize * sizeof(char *));
		for (int i = 0; i < ysize; i++) {
			M[i] = (char *) malloc(xsize * sizeof(char));
		}
	}

	~Matrix() {
		delete (M);
	}

	char ** getMatrix() {
		return M;
	}

	void fillMatrix(int x, int y, char value) {
		M[x][y] = value;
	}

	void resetMatrix() {
		M = (char **) malloc(ysize * sizeof(char *));
		for (int i = 0; i < ysize; i++) {
			M[i] = (char *) malloc(xsize * sizeof(int));
		}
	}

private :
	char **M;
	int xsize;
	int ysize;
};

#endif