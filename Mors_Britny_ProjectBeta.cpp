//Britny Mors
//ME 493 - Autonomy
//Project Beta
//Worked with Scott Four & Bryant Clouse

#include <iostream>
#include <assert.h>
#include <vector>
#include <random>
#include <time.h>
#include <stdio.h>
#include <cmath>
#include <time.h>
#include <fstream>

using namespace std;

#define LYRAND (double)rand()/RAND_MAX

class grid {
public:
	int xGS = 5; //set x value for grid size
	int yGS = xGS; //set y value for grid size
	int Gx = xGS-2;//rand() % xGS;
	int Gy = yGS-2;//rand() % yGS;

};

class agent {
public:
	int Ax_start;
	int Ay_start;
	int ax;
	int ay;

	void init(int xGS, int yGS);
	void update(int move, int gridx, int gridy);
	void reset(int check);
};

class qlearner {
public:
	double Qval;
	double Qmax;
	int reward;
	double alpha = 0.1;
	double gamma = 0.9;
	double epsilon;
	int action;
	int state;
	int newstate;
	vector< vector<double> > qtable;
	vector< vector<int> > rtable;
	void init(int gridx, int gridy, int goalx, int goaly);
	void sense(int agentx, int agenty, int x_dim);
	void decide();
	int act();
	void react(int agentx, int agenty, int x_dim);
	int check();
	void testD();

};

void agent::reset(int check) {
	if (check == 0) {
		ax = Ax_start;
		ay = Ay_start;
	}
}

void agent::init(int xGS, int yGS) {
	Ax_start = 0;//rand() % xGS;
	Ay_start = 0;//rand() % yGS;
	ax = Ax_start;
	ay = Ay_start;
}

void agent::update(int move, int gridx, int gridy) {
	//cout << "Action:	" << move << endl;
	if (move == 0) { ay -= 1; }
	else if (move == 1) { ay += 1; }
	else if (move == 2) { ax += 1; }
	else if (move == 3) { ax -= 1; }
	//cout << "A:(" << ax << "," << ay << ")" << endl;
	while (ax < 0) { ax += 1; }
	while (ay < 0) { ay += 1; }
	while (ax >= gridx) { ax -= 1; }
	while (ay >= gridy) { ay -= 1; }
	//cout << "A:(" << ax << "," << ay << ")" << endl;
}

void qlearner::init(int gridx, int gridy, int goalx, int goaly) {
	//build reward table
	for (int i = 0; i < gridy; i++) {
		vector<int> rrow;
		for (int j = 0; j < gridx; j++) {
			if (i == goalx && j == goaly) {
				rrow.push_back(100);
			}
			else {
				rrow.push_back(-1);
			}
		}
		rtable.push_back(rrow);
	}
	/*
	cout << "Reward Table" << endl;
	for (int i = 0; i < gridy; i++) {
		for (int j = 0; j < gridx; j++) {
			cout << rtable[i][j] << "\t";
		}
		cout << endl;
	}
	*/
	
	//build qtable
	for (int i = 0; i < (gridx*gridy); i++) {
		vector<double> qrow;
		for (int j = 0; j < 4; j++) {
			qrow.push_back(LYRAND);
		}
		qtable.push_back(qrow);
	}/*
	cout << "Q Table BEFORE" << endl;
	for (int i = 0; i < gridx*gridy; i++) {
		for (int j = 0; j < 4; j++) {
			cout << qtable[i][j] << "	";
		}
		cout << endl;
	}
	*/
}

void qlearner::sense(int agentx, int agenty,int x_dim) {
	state = agentx + (agenty*x_dim);
	//cout << reward << endl;
}

void qlearner::decide() {
	epsilon = LYRAND;
	if (epsilon <= 0.1) {
		action = rand() % 4; //random option
		//cout << "Random action:	" << action << endl;
		//cout << "R: ";
	}
	else {
		//cout << "G: ";
		//int test = qtable[state][0]; //set test variable to the  first qvalue that corresponds with the agents current state
		//cout << "Qtable:	" << qtable[state][0] << endl;
		action = 0; //start the search at zero 
		for (int i = 1; i < 4; i++) {
			//cout << action << "..";
			if (qtable[state][action] < qtable[state][i]) {
				action = i; //if the next qvalue is greater set the action to that number
				//test = qtable[state][i]; //set the new test variable with the corresponding qvalue
			}
		}
		//cout << action << endl;
	}
}

int qlearner::act() {
	//action list:
	//0 = up
	//1 = down
	//2 = right
	//3 = left
	Qval = qtable[state][action];
	return action;
}

void qlearner::react(int agentx, int agenty, int x_dim) {
	reward = rtable[agenty][agentx];
	newstate = agentx + (agenty*x_dim);
	int w = qtable[newstate][0]; //save first int in vector
	//printf("%2d %2d %2d\n", state, action, newstate);
	for (int i = 1; i < 4; i++) {
		if (w < qtable[newstate][i]) {
			Qmax = qtable[newstate][i]; //save the new max value in qmax
			w = qtable[newstate][i]; //reset w with higest number
		}
	}
	//printf("\nValues: %f, %f, %d, %f, %f\n\n", Qval, alpha, reward, gamma, Qmax);
	qtable[state][action] = Qval + alpha*(reward + (gamma*Qmax) - Qval);
}

void qlearner::testD() {
	for (int i = 0; i < qtable.size(); i++) {
		for (int j = 0; j < 4; j++) {
			assert(qtable[i][j] != 100);
		}
	}
}

int main() {
	srand(time(NULL));
	grid G;
	agent A;
	qlearner Q;
	A.init(G.xGS,G.yGS);
	bool broke = false;
	int n = 1000;
	int run = 30;
	int time[1000];
	for (int i = 0; i < n; i++) {
		time[i] = 0;
	}
	for (int i = 0; i < run; i++){
		Q.testD();
		Q.qtable.clear();
		Q.init(G.xGS, G.yGS, G.Gx, G.Gy);
		for (int j = 0; j < n; j++) {
			while (!broke) {
				Q.sense(A.ax, A.ay, G.xGS);
				Q.decide();
				A.update(Q.act(), G.xGS, G.yGS);
				Q.react(A.ax, A.ay, G.xGS);
				if (A.ax == G.Gx && A.ay == G.Gy) {
					broke = true;
				}
				time[j]++;
			}
			A.reset(0);
			broke = false;
		}
	}
	
	ofstream myfile;
	myfile.open("learningcurve.csv");
	myfile.clear();
	for (int i = 0; i < n; i++) {
		myfile << time[i] << endl;
	}
	myfile.close();

	return 0;
}