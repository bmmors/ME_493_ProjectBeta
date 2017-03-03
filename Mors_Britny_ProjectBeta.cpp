//Britny Mors
//ME 493 - Autonomy
//Project Beta
//Worked with Scott Four

#include <iostream>
#include <assert.h>
#include <vector>
#include <random>
#include <time.h>
#include <stdio.h>
#include <cmath>
#include <time.h>

using namespace std;

#define LYRAND (double)rand()/RAND_MAX

class grid {
public:
	int xGS = 2; //set x value for grid size
	int yGS = 3; //set y calue for grid size
	int Gx = 0;//rand() % xGS;
	int Gy = 1;//rand() % yGS;

};

class agent {
public:
	int Ax_start = 1;
	int Ay_start = 2;
	int ax;
	int ay;
	int action;
	int state;

	vector< vector<double> > qtable;

	void init(int gridx, int gridy);
	int get_state(int gridx);
};

void agent::init(int gridx, int gridy) {
	for (int i = 0; i < (gridx*gridy); i++) {
		vector<double> row;
		for (int j = 0; j < 4; j++) {
			row.push_back(LYRAND);
		}
		qtable.push_back(row);
	}
	ax = Ax_start;
	ay = Ay_start;
	state = get_state(gridx);
	action = 5;
}

int agent::get_state(int gridx) {
	return ax + (ay*gridx);
}

/*
void grid::human_update_agent() {
	if (action == 'u') {
		if (Ax > xGS || Ax <= 0) {
			cout << ".";
		}
		else {
			Ax -= 1;
		}
	}
	else if (action == 'd') {
		if (Ax >= xGS - 1 || Ax < 0) {
			cout << "Invalid Move\n";
		}
		else {
			Ax += 1;
		}
	}
	else if (action == 'r') {
		if (Ay >= yGS - 1 || Ay < 0) {
			cout << "Invalid Move\n";
		}
		else {
			Ay += 1;
		}
	}
	else if (action == 'l') {
		if (Ay > yGS || Ay <= 0) {
			cout << "Invalid Move\n";
		}
		else {
			Ay -= 1;
		}
	}
}
*/

int main() {
	grid G;
	agent A;
	A.init(G.xGS, G.yGS);
	cout << "Grid	x:" << G.xGS << endl;
	cout << "Grid	y:" << G.yGS << endl;
	cout << "Agent	x:" << A.ax << endl;
	cout << "Agent	y:" << A.ay << endl;
	cout << "State	 :" << A.state << endl;
	cout << "Qtable" << endl;
	for (int i = 0; i < (G.xGS*G.yGS); i++) {
		for (int j = 0; j < 4; j++) {
			cout << A.qtable[i][j] << "\t" << endl;
		}
	}

	return 0;
}