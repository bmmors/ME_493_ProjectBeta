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
#include <fstream>

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
	int ax=0;
	int ay=0;
	int action;
	int state;

	void update(int move, int gridx, int gridy);
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

};

void agent::update(int move, int gridx, int gridy) {
	if (move == 0) {
		if (ax > gridx || ax <= 0) {
			ax = ax;
		}
		else {
			ax -= 1;
		}
	}
	else if (move == 1) {
		if (ax >= gridx-1 || ax < 0) {
			ax = ax;
		}
		else {
			ax += 1;
		}

	}
	else if (move == 2) {
		if (ay > gridx || ax <= 0) {
			ay = ay;
		}
		else {
			ay -= 1;
		}
	}
	else if (move == 3) {
		if (ay >= gridx - 1 || ay < 0) {
			ay = ay;
		}
		else {
			ay += 1;
		}
	}
}

void qlearner::init(int gridx, int gridy, int goalx, int goaly) {
	//build reward table
	for (int i = 0; i < gridx; i++) {
		vector<int> rrow;
		for (int j = 0; j < gridy; j++) {
			if (i == goalx && j == goaly) {
				rrow.push_back(100);
			}
			else {
				rrow.push_back(-1);
			}
		}
		rtable.push_back(rrow);
	}
	/*for (int i = 0; i < gridx; i++) {
		for (int j = 0; j < gridy; j++) {
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
	}
	for (int i = 0; i < gridx*gridy; i++) {
		for (int j = 0; j < 4; j++) {
			cout << qtable[i][j] << "\t";
		}
		cout << endl;
	}
	
}

void qlearner::sense(int agentx, int agenty,int x_dim) {
	state = agentx + (agenty*x_dim);
	reward = rtable[agentx][agenty];
}
void qlearner::decide() {
	epsilon = LYRAND;
	if (epsilon <= 0.1) {
		action = rand() % 4; //random option
		cout << "Random action:	" << action << endl;
	}
	else {
		int test = qtable[state][0]; //set test variable to the  first qvalue that corresponds with the agents current state
		cout << "Qtable:	" << qtable[state][0] << endl;
		action = 0; //start the search at zero 
		for (int i = 0; i < 4; i++) {
			if (test < qtable[state][i]) {
				action = i; //if the next qvalue is greater set the action to that number
				test = qtable[state][i]; //set the new test variable with the corresponding qvalue
			}
		}
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
	newstate = agentx + (agenty*x_dim);
	int w = qtable[newstate][0]; //save first int in vector
	for (int i = 0; i < 4; i++) {
		if (w < qtable[newstate][i]) {
			Qmax = qtable[newstate][i]; //save the new max value in qmax
			w = qtable[newstate][i]; //reset w with higest number
		}
		qtable[newstate][action] = Qval + alpha*(reward + (gamma*Qmax) - Qval);
	}
}

int main() {
	srand(time(NULL));
	grid G;
	agent A;
	qlearner Q;
	Q.init(G.xGS, G.yGS, G.Gx, G.Gy);
	//for (int i = 0; i < 30; i++){
		//for (int j = 0; j < 1000; j++) {
			Q.sense(A.ax, A.ay, G.xGS);
			Q.decide();
			//A.update(Q.act(), G.xGS, G.yGS);
			//Q.react(A.ax, A.ay, G.xGS);
		//}
	//}	
	
	/*ofstream myfile;
	myfile.open("Qtable.csv");
	myfile.clear();
	for (int i = 0; i < G.xGS*G.yGS; i++) {
		for (int j = 0; j < 4; j++) {
			//myfile << Q.qtable[i][j] << ',';
		}
		//myfile << endl;
	}
	myfile.close();
	*/
	return 0;
}