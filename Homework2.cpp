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
	int xGS = 10; //set x value for grid size
	int yGS = 10; //set y calue for grid size
	int Ax = rand() % xGS; //Randomly assign agent new grid location
	int Ay = rand() % yGS;
	int Gx = rand() % xGS; //Randomly assign goal new grid location
	int Gy = rand() % yGS;
	char action = 'a';
	char **fullgrid;

	void build_grid();
	void init();
	void print();
	void update_agent();
	void clear();



};

void grid::build_grid() {
	fullgrid = new char*[xGS]();
	for (int i = 0; i < xGS; i++) {
		fullgrid[i] = new char[yGS];
	}
}

void grid::init() {
	
}

void grid::print() {
	for (int i = 0; i < xGS; i++) {
		for (int j = 0; j < yGS; j++) {
			if (i == Ax && j == Ay) {
				fullgrid[i][j] = 'A';
			}
			else if (i == Gx && j == Gy) {
				fullgrid[i][j] = 'G';
			}
			else {
				fullgrid[i][j] = '-';
			}

		}
	}
	system("cls");
	for (int i = 0; i < xGS; i++) {
		for (int j = 0; j < yGS; j++) {
			cout << fullgrid[i][j] << "\t";
		}
		cout << endl;
	}
}

void grid::update_agent() {
	if (action == 'u') {
		if (Ax > xGS || Ax <= 0) {
			cout << "Invalid Move\n";
		}
		else {
			Ax -= 1;
		}
	}
	else if (action == 'd') {
		if (Ax > xGS || Ax <= 0) {
			cout << "Invalid Move\n";
		}
		else {
			Ax += 1;
		}
	}
	else if (action == 'r') {
		if (Ay > yGS || Ay <= 0) {
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


void grid::clear() {
	delete[] fullgrid;
}

int main() {
	grid G;
	G.build_grid(); //build grid array
	G.init(); //place A and G in random locations and fill grid array
	int gameplay = 0; //variable for selecting gameplay option
	cout << "Select a Gameplay Option:\n1.Human Controlled\n2.Autosolve" << endl;
	cin >> gameplay;
	if (gameplay == 1) {
		bool gamestatus = true; //variable for gameplay loop
		while (gamestatus == true) {
			G.print();
			if (G.Ax == G.Gx && G.Ay == G.Gy) {
				cout << "WINNER!!\n";
				gamestatus = false;
			}
			else {
				cout << "Choose a direction to move the agent.\nEnter U for up, D for down, R for Right, or L for left\n";
				cin >> G.action;
				G.update_agent();
			}
		}
	}
	else if (gameplay == 2) {

	}
		
	G.clear();
	return 0;
}