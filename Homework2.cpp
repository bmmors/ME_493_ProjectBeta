//Britny Mors
//ME 493 - Autonomy
//Homework 2 - Grid World Domain
//Worked with Sierra Gonzales & Bryant Clouse

#include <iostream>
#include <assert.h>
#include <vector>
#include <random>
#include <time.h>
#include <stdio.h>

using namespace std;

class grid {
public:
	int xGS = 0; //set x value for grid size
	int yGS = 0; //set y calue for grid size
	int Ax = 0;
	int Ay = 0;
	int Gx = 0;
	int Gy = 0;

	char **fullgrid;

	grid(const int x, const int y);
	void init();
	void print();
	void update_agent();
	void clear();



};

grid::grid(int x,int y) {
	xGS = x; yGS = y;
	fullgrid = new char*[xGS]();
	for (int i = 0; i < xGS; i++) {
		fullgrid[i] = new char[yGS];
	}
}

void grid::init() {
	Ax = rand() % xGS;
	Ay = rand() % yGS;
	Gx = rand() % xGS;
	Gy = rand() % yGS;

	for (int i = 0; i < xGS; i++) {
		for (int j = 0; j < yGS; j++) {
			if (i == Ax && j == Ay) {
				fullgrid[i][j] = "A";
			}
			else if (i == Gx && j == Gy) {
				fullgrid[i][j] = "G";
			}
			else {
				fullgrid[i][j] = "-";
			}
			
		}
	}
}

void grid::print() {
	for (int i = 0; i < xGS; i++) {
		for (int j = 0; j < yGS; j++) {
			cout << fullgrid[i][j];
		}
	}

}
void grid::clear() {
	delete[] fullgrid;
}

int main() {
	int Ax = 0; //initialize agent location at (0,0)
	int Ay = 0;
	int Gx = 0; //initialize goal location at (0,0)
	int Gy = 0;

	return 0;
}