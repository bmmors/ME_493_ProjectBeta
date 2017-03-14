//Britny Mors
//ME 493 - Autonomy
//Homework 3 - Part 1

#include <iostream>
#include <assert.h>
#include <vector>
#include <random>
#include <time.h>
#include <stdio.h>
#include <cmath>
#include <time.h>

using namespace std;

class grid {
public:
	int xGS = 5; //set x value for grid size
	int yGS = 5; //set y calue for grid size
	int Ax = 0;//rand() % xGS; //Randomly assign agent new grid location
	int Ay = 0; //rand() % yGS;
	int Gx = xGS - 2;// rand() % xGS; //Randomly assign goal new grid location
	int Gy = yGS - 2;// rand() % yGS;
	char action = 'a';
	char **fullgrid;

	void build_grid();
	void print();
	void human_update_agent();
	void autosolve_update_agent();
	void TestA();
	void TestB();
	void TestC();
	void clear();



};

void grid::build_grid() {
	fullgrid = new char*[xGS]();
	for (int i = 0; i < xGS; i++) {
		fullgrid[i] = new char[yGS];
	}
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

void grid::autosolve_update_agent() {
	if (Ax < Gx) {
		Ax += 1;
	}
	else if (Ax > Gx) {
		Ax -= 1;
	}
	else if (Ay < Gy) {
		Ay += 1;
	}
	else if (Ay > Gy) {
		Ay -= 1;
	}
	while (Ax == 2 && Ay == 0) { Ax -= 1; }
	while (Ax == 2 && Ay == 1) { Ax -= 1; }
	while (Ax == 2 && Ay == 2) { Ax -= 1; }
}

void grid::TestA() {
	for (int i = 0; i < xGS + 1; i++) {
		action = 'u';
		human_update_agent();
	}
	assert(Ax == 0);
	cout << "Test A Passed" << endl;
}

void grid::TestB() {
	assert(Ax == Gx);
	assert(Ay == Gy);
	cout << "Test B Passed" << endl;
}

void grid::TestC() {
	assert(Ax == Gx);
	assert(Ay == Gy);
	cout << "Test C Passed" << endl;
}

void grid::clear() {
	delete[] fullgrid;
}

void TestAA(int goalx, int goaly, int agentx, int agenty) {
	assert(goalx != agentx);
	assert(goaly != agenty);
}

int main() {
	srand(time(NULL));
	grid G;
	G.build_grid(); //build grid array
	int gameplay = 0; //variable for selecting gameplay option
	cout << "Select a Gameplay Option:\n1.Human Controlled\n2.Autosolve" << endl;
	cin >> gameplay;
	int counter = 0;
	if (gameplay == 1) {
		bool gamestatus = true; //variable for gameplay loop
		while (gamestatus == true) {
			G.print();
			if (G.Ax == G.Gx && G.Ay == G.Gy) {
				cout << "WINNER!!\n"; //if the agent and the goal are in the same location the user has won
				gamestatus = false; //exit loop
			}
			else {
				cout << "Choose a direction to move the agent.\nEnter U for up, D for down, R for Right, or L for left\n";
				cin >> G.action; //take user input for action
				G.human_update_agent(); //move agent according to user input
			}
		}
		G.TestB();
	}
	else if (gameplay == 2) {
		bool status2 = true; //while loop condition
		while (status2 == true) {
			if (G.Ax == G.Gx && G.Ay == G.Gy) {
				cout << "PUZZLE SOLVED\n"; // if the agent and the goal are in the same location the puzzle is solved
				status2 = false; //loop exit
			}
			else {
				G.autosolve_update_agent(); //move agent logically towards goal
				G.print();
			}
			counter++;
			if (counter == 1000) { status2 = false; }
		}
		TestAA(G.Gx,G.Gy,G.Ax,G.Ay);
		//G.TestC();
	}
	G.TestA();
	G.clear(); //help clear up memory
	return 0;
}